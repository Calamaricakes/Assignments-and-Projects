
list_of(_, []).
list_of(Elt, [Elt | List]) :-
    list_of(Elt, List).


all_same(List) :-
    list_of(_, List).

adjacent(E1, E2, List) :-
    append(_, [E1, E2| _], List).


adjacent1(E1, E2, [E1, E2| _]).
adjacent1(E1, E2, [ _ | [E1, E2| _] ]).
adjacent1(E1, E2, [ _ | [E1, E2] ] ).

adjacent2(E1, E2, [E1, E2| _]).
adjacent2(E1, E2, [ _ | Tail]) :-
    adjacent2(E1, E2, Tail).

intset_member(N, tree(_, N, _)).

intset_member(N, tree(Left, N0, _)) :-
    N < N0,
    intset_member(N, Left).

intset_member(N, tree(_, N0, Right)) :-
    N > N0,
    intset_member(N, Right).

intset_insert(N, )
