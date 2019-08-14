% Щербаков Антон Александрович, номер по списку: 22.
% Представление 3, Вариант 2.

:- include('three').

% ----------------- 1)  Средний бал для каждого предмета

% Поиск оценки за предмет в списке из grade:   mark( список grade, предмет, оценка ).
mark( [], _, 0).
mark( [grade(Subj, M) | _], Subj, Mark) :- Mark is M.
mark( [ _ | T], Subj, Mark) :- mark( T, Subj, Mark ).

% Сумма баллов по предмету из списка списков grade : sum_mark(предмет, список списков, результат суммы).
sum_mark( _, [], 0).
sum_mark( Subj, [H|T], Sum ) :- 
    mark( H, Subj, Mark ),
    sum_mark( Subj, T, Sum1),
    Sum is Sum1 + Mark.
    
% Средний бал для каждого предмета (полное название предмета, ответ)
avg_for_subj(S, Res) :- 
    subject(Subj, S),     % из полного названия редмета получаем сокращенное
    findall(X, student(_,_, X), List),
    sum_mark( Subj, List, Sum),
    length( List, Num),
    Res is Sum/Num, !.
    


% ---------------- 2) Количество не сдавших для каждой группы (номер группы, кол-во не сдавших в этой группе).

% Проверка, есть ли в списке неуд: И - если все сдано, Л - если есть неуд.
did_pass([]).
did_pass([grade(_, Mark) | T ] ) :- Mark > 2, did_pass(T).

% Количество не сдавших в списке списков из оценок (список списков, количество не сдавших).
num_of_failed_stud([], 0).
num_of_failed_stud([H|T], Num) :- 
    did_pass(H), num_of_failed_stud(T, Num);
    num_of_failed_stud(T, Num1), Num is Num1+1.    

% Количество не сдавших для каждой группы (номер группы, кол-во не сдавших).
num_of_failed_for_group(Gr, Res) :- 
    findall(X, student(Gr, _, X), List), %список списков всех оценок в группе
    num_of_failed_stud(List, Res), !.
    


% -------------- 3) Найти количество не сдавших студентов для каждого из предметов

% количество не сдавших указанный предмет в списке списков
num_of_failed(_, [], 0).
num_of_failed(Subj, [H|T], Res) :- 
    mark(H, Subj, Mark),  Mark > 2,
    num_of_failed(Subj, T, Res);
    
    num_of_failed(Subj, T, Res1), Res is Res1+1.

% Кол-во не сдавших студентов для предмета (полное название предмета, результат)
num_of_failed_for_subj(S, Res) :-
    subject(Subj, S),
    findall(X, student(_,_,X), List),
    num_of_failed(Subj, List, Res), !.

