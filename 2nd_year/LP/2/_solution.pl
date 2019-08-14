%     Щербаков А.А., номер по списку 22

%   Вариант 22:
% В одной школе уроки по биологии, географии, английскому языку, французскому языку, истории и математике 
% вели три учителя Морозов, Васильев и Токарев. Каждый из них преподавал два предмета. Учитель географии и 
% учитель французского языка соседи по дому. Морозов самый младший из троих. Все трое Токарев, учитель 
% биологии и учитель французского языка ездят из школы вместе. Учитель биологии старше учителя математики. 
% В свободное время, если им удастся найти четвертого партнера, учитель английского языка, учитель математики 
% и Морозов играют в домино. Кто какие предметы преподает?

solve(List) :-
    List = [ ['Morozov', M_subj, M_age], ['Vasiliev', V_subj, V_age], ['Tokarev', T_subj, T_age ] ],
    M_subj = [M1,M2], V_subj = [V1,V2], T_subj = [T1,T2],
    permutation(['BIO','GEO','FR', 'ENG', 'MATH', 'HIST'], [M1,M2,V1,V2,T1,T2]),
    
    % Морозов самый младший
    M_age = 1,
    (V_age = 2, T_age=3; V_age=3, T_age=2),
    
    %Биолог старше математика
    search('BIO', List, Age1), search('MATH', List, Age2), Age1 > Age2,   
    
    % географ и француз - соседи
    (
    ( member('GEO', M_subj), \+(member('FR', M_subj)) );
    ( member('GEO', V_subj), \+(member('FR', V_subj)) );
    ( member('GEO', T_subj), \+(member('FR', T_subj)) )
    ),
    
    % Токарев, биолог и географ ездят вместе
    \+(member('BIO', T_subj)), 
    \+(member('GEO', T_subj)),
    (
    ( member('GEO', M_subj), \+(member('BIO', M_subj)) );
    ( member('GEO', V_subj), \+(member('BIO', V_subj)) )
    ),

    % Англичанин, математик, Морозов играют в домино
    \+(member('ENG', M_subj)), 
    \+(member('MATH', M_subj)),
    (
    ( member('ENG', T_subj), \+(member('MATH', T_subj)) );
    ( member('ENG', V_subj), \+(member('MATH', V_subj)) )
    ), !.
 
search(_, []).
search(Subj, [ [_,X, Age] | T ], Res) :- member(Subj, X), Res = Age;
                                         search(Subj, T, Res).
