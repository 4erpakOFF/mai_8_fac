% Щербаков Антон Александрович, номер по списку: 22.
% -------------------------------------------------- 

% Длина
length_my([], 0).
length_my([_|Y], N) :- length_my(Y, N1), N is N1 + 1, !.

% Принадлежность
member_my(X,[X|_]).
member_my(X,[_|Y]) :- member_my(X,Y).    

% Конкатенация
append_my(X, [], X).
append_my([], X, X).
append_my([A|X], Y, [A|Z]) :- append_my(X, Y, Z).

% Удаление (элемент, список, результат).
remove_my(X, [X|T], T).
remove_my(X, [Y|T], [Y|T1]) :- remove_my(X, T, T1).

% Перестановки
permute_my([],[]).
permute_my( L, [X|R]) :- remove_my(X, L, T), permute_my(T, R). 

% Подсписок
sublist_my(S, L) :- append_my(_, Y, L), append_my(S, _, Y), !.


% Вариант 4: Удаление 3 первых эл-тов без ст предикатов
rem_first_3([_,_,_ | T], T).

% Вариант 4: Удаление 3 первых элементов
rem_first_3_2(List, Res) :- length(Head, 3), append(Head, Res, List).


%------ Числовые списки

% Вариант 8: Вычисление среднего арифметического элементов без ст предикатов (список, ответ).
sum_all([], 0, 0).           % Сумма эл-тов списка (список, сумма, количество элементов).          
sum_all( [Head | Tail], Sum, N) :- 
    sum_all(Tail, Sum1, N1), 
    Sum is Sum1+Head, 
    N is N1+1.

average([], _) :- !, fail.
average( List, Res ) :- sum_all(List, Sum, N), Res is Sum/N.

% Вариант8 : Вычисление среднего арифметического элементов (список, ответ).
sum_all_2([], 0).  % (список, сумма).
sum_all_2( [Head | Tail], Sum) :- 
    sum_all_2(Tail, Sum1), 
    Sum is Sum1+Head.

average_2([],_) :- !, fail.
average_2( List, Res ) :- 
    sum_all_2(List, Sum), 
    length_my(List, N), 
    Res is Sum/N.

















