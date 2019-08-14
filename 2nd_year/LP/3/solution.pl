%reverse([X],[X]).
%reverse([H|T],R):- reverse(T,X),append(X,[H],R).
%writeln(X):- write(X),nl.

remove(X,[X|T],T).
remove(X,[Y|T],[Y|R]):- remove(X,T,R).

/*поиск в глубину*/
dsearch([X|T],X,[X|T]).
dsearch(P,Y,L):- prolong(P,P1),dsearch(P1,Y,L).
dpath(X,Y,P):- dsearch([X],Y,L),reverse(L,P).

/*поиск в ширину*/
bsearch([[X|T]|_],X,[X|T]).
bsearch([Z|T],X,L):- findall(P1,prolong(Z,P1),A),
    append(T,A,B),!,bsearch(B,X,L).
bsearch([_|T],Y,L):- bsearch(T,Y,L).
bpath(X,Y,P):- bsearch([[X]],Y,L),reverse(L,P).

/*поиск с итерационным загрублением*/
search_id(S,F,P,L):- depth_id([S],F,P,L).
search_id(S,F,P,L):- L1 is L+1, search_id(S,F,P,L1).
depth_id([F|T],F,[F|T],0).
depth_id(P,F,R,N):- N>0,prolong(P,NP),N1 is N-1, depth_id(NP,F,R,N1).
spath(S,F,P):- search_id(S,F,K,0),reverse(K,P).

/* prolong */
prolong([X|T],[Y,X|T]):- move(X,Y), \+(member(Y,[X|T])).
%--------------------------------------------

first([H|T], T, H).

last([X], [], X).
last(L, Y, T):- reverse(L,[T|H]), reverse(H,Y).

append1(List1,List2,First,Last,Result):- 
    append(List1,[First],X1), 
    X2=[Last|List2], 
    append(X1,X2,Result).

move(X,Y):-
    append(K,M,X),
    last(K,List1,Last),
    first(M,List2,First),   
    append1(List1,List2,First,Last,Y).
