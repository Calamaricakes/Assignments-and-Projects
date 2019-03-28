
list_of( _ , []).
list_of( X, [X | XS] ) :- list_of( X, XS).

all_same( [] ).
all_same( [_X] ).
all_same( [X | XS] ) :- list_of(X, XS).
