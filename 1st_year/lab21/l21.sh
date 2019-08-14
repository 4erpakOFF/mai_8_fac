#!/bin/bash

if [ "$CUR" = "" ]; then
    current=$( pwd )
    export current
fi
# ---------------------
if [ -n "$1" ]; then         # Обрабатываем ключи
    case "$1" in
	-h) echo "Использование:
может быть когда-нибудь здесь появится объяснение"
	    exit 0 ;;
	-f) if [[ "$2" == "" ]]; then
		echo "Не указан файл для считывания"
	    else
		for((i=1; i <= $(cat "$2" | wc -l); i++ )); do
		    new_line=$(sed -n "$i"p "$2")
		    bash "$(readlink -f $0)" $(readlink -f $new_line)
		done
	    fi
	    exit 0;;
	*) ;;
    esac
fi

#-------------------------------------------------------
if [[ "$1" == "" ]]; then
    echo "Отсутствуют параметры"
    exit 0
fi
                                      # Проверок много
if [[ "$2" == "" ]]; then                #       не бывает
    DIR="./"
else
    DIR="$2"
fi
if [ ! -d "$DIR"  ]; then
    echo "Директории $DIR не существует"
    exit 0
fi
if [ ! -f "$1" ]; then
    echo "Файла $1 не существует"
    exit 0
fi
#-----------------------------------------------------

SUFFIX="${1:(-1)}"
is_delete=1

for file in "$DIR"*; do
    if [ ! -f "$file" ]; then
	continue
    fi
    new_SUF="${file:(-1)}"
    if [[ "$SUFFIX" == "$new_SUF" ]]; then
	tmp=$(mktemp)
	diff "$1" "$file" 1> "$tmp"
	full=$(readlink -f "$1")
	full_=$(readlink -f "$file")
	if [[ "$full" != "$full_" ]] && [[ $(cat "$tmp") == ""  ]] ; then
	    #rm -f "$full_"
	    echo "Удален файл $full_"
	    is_delete=0
	fi
	unset tmp
    fi
done
if (( is_delete == 1 )); then
    echo "Не найден дубликат файла '$1' в директории '$DIR'"
fi



	
		
    

