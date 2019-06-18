/**
sumlist(Ns, Sum) :- sumlist(Ns, 0, Sum).

sumlist([], Sum, Sum).
sumlist([N|Ns], Acc, Sum) :-
    Acc0 is N + Acc,
sumlist(Ns, Acc0, Sum).
*/

sumlist( Ns, Sum) :-
    sumlist(Ns, 0, Sum).

sumlist([], Sum, Sum).
sumlist( [N| Ns], Acc, Sum):-
    Acc0 is N + Acc,
    sumlist(Ns, Acc0, Sum).

tree(empty).
tree(node(Left, _ Right)) :-
    tree(Left),
    tree(Right).

tree_list(Tree, List) :-
