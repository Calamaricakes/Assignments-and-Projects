
:- ensure_loaded(library(clpfd)).
:- set_prolog_flag(double_quotes, chars).


%FIX
compareMatches( Row, Column, Words ) :-
    % find words that match their respective rows
    matchingWords( Row, Words, MatchRow ),
    matchingWords( Column, Words, MatchColumn ).
    %matchRowColumn( Row, Column, MatchRow, MatchColumn, Matches ).


    % assign a matching word in the row, then find a compliment in the column


%matchRowColumn( Row, Column, RowWords, ColumnWords, SRow, SColumn ) :-



buildSubstring( Row, Substrings ) :-
    split_string( Row, "#", "#", Substrings ).

%use include to find all matching letters
matchingWords( Row, Words, Matches ) :-
    include( matchingLetters(Row), Words, Matches ).


matchingLetters( [], [] ).
matchingLetters( [Var | Vars], [Char | Chars] ) :-
    %if the variable is assigned and matches the current Char
    ( Var == Char ->
      true
    ; var(Var) ->
      true
    ),
    matchingLetters(Vars, Chars).

findAllMatching( [], _, []).
findAllMatching( [VarString | VarStrings], Words, Matches ) :-
    matchingWords( VarString, Words, Match ),
    append( Match, Rest, Matches ),
    findAllMatching( VarStrings, Words, Rest ).


matchingWords( Row, [Word | Words] ) :-
    assignWordToRow( Row, Word );
    matchingWords( Row, Words ).

assignWordToRow( [], [] ).
assignWordToRow( [Var | Vars], [Letter | Letters] ) :-
    Var = Letter,
    assignWordToRow(Vars, Letters).

%assignWordToRow( [], [], []).
%assignWordToRow( [Var | Vars], [Letter | Letters], AssignedRow ) :-
%    Var = Letter,
%    AssignedRow = [Var | Rest],
%    assignWordToRow(Vars, Letters, Rest).


uniqueLists( List1, List2 ) :-
    length( List1, Len1),
    length( List2, Len2),
    (Len1 #> Len2 ->
    noElementsInList( List1, List2)
    ;
    noElementsInList( List2, List1)
    ).

noElementsInList( [], _).
noElementsInList( [Head | Tail ], List) :-
    not( member( Head, List) ),
    noElementsInList( Tail, List ).

map(_F, [], []).
map(F, A0.As0, A.As) :-
    call(F, A0, A),
    map(F, As0, As).

filter(_,[],[]).
filter(P, [Head | Tail], As) :-
    (
        call(P, Head) -> As = [Head | Rest]
    ;
        As = Rest
    )
    , filter(P, Tail, Rest).
