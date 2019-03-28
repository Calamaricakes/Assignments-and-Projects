
:- ensure_loaded(library(clpfd)).
:- set_prolog_flag(double_quotes, chars).



isA( [] ).
isA( Char ):-
    Char == 'a'.

fillableRows( Words, AllRows, FillableRows ):-
    include( possibleMatchForWord(Words), [AllRows], FillableRows ).

possibleMatchForWord( Words, [ Row | Rows ] ):-
    possibleMatchForRow( Row, Words );
    possibleMatchForWord( Words, Rows ).



findValidRows( Rows, Words, ValidRows ):-
    include( validRow( Words ), Rows, ValidRows).

validRow( [ Word | Words], Row ):-
    ( length(Row, N), length(Word, N) ->
        true
    );
    validRow( Words, Row ).


% implied restriction
findMatch( [], _).
findMatch( [Row | Rows], Words) :-
	possibleMatchForRow( Row, Words ),
	findMatch( Rows, Words ).

possibleMatchForRow( Row, [ Word | Words ] ):-
    checkMatch( Row, Word )
    ; possibleMatchForRow( Row, Words ).

checkMatch( [], [] ).
checkMatch( [ Var | Vars ], [ Char | Chars ]) :-
    Var = Char,
    checkMatch( Vars, Chars ).
