% Name: Lai Nge Nern
% Student Number: 639702

:- ensure_loaded(library(clpfd)).
:- set_prolog_flag(double_quotes, chars).

main(PuzzleFile, WordlistFile, SolutionFile) :-
	read_file(PuzzleFile, Puzzle),
	read_file(WordlistFile, Wordlist),
	valid_puzzle(Puzzle),
	solve_puzzle(Puzzle, Wordlist, Solved),
	print_puzzle(SolutionFile, Solved).

read_file(Filename, Content) :-
	open(Filename, read, Stream),
	read_lines(Stream, Content),
	close(Stream).

read_lines(Stream, Content) :-
	read_line(Stream, Line, Last),
	(   Last = true
	->  (   Line = []
	    ->  Content = []
	    ;   Content = [Line]
	    )
	;  Content = [Line|Content1],
	    read_lines(Stream, Content1)
	).

read_line(Stream, Line, Last) :-
	get_char(Stream, Char),
	(   Char = end_of_file
	->  Line = [],
	    Last = true
	; Char = '\n'
	->  Line = [],
	    Last = false
	;   Line = [Char|Line1],
	    read_line(Stream, Line1, Last)
	).

print_puzzle(SolutionFile, Puzzle) :-
	open(SolutionFile, write, Stream),
	maplist(print_row(Stream), Puzzle),
	close(Stream).

print_row(Stream, Row) :-
	maplist(put_puzzle_char(Stream), Row),
	nl(Stream).

put_puzzle_char(Stream, Char) :-
	(   var(Char)
	->  put_char(Stream, '_')
	;   put_char(Stream, Char)
	).

valid_puzzle([]).
valid_puzzle([Row|Rows]) :-
	maplist(same_length(Row), Rows).


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Start Solution

solve_puzzle( CharPuzzle, WordList, HorizontalPuzzle ) :-
	% create a variable representation of the puzzle along with the '#' symbols
	create_var_puzzle( CharPuzzle, HorizontalPuzzle ),

	% transform from horizontal to vertical
	transpose( HorizontalPuzzle, VerticalPuzzle ),

	% append the two puzzles together to obtain all the rows of the puzzles
	% this is to enable the ease of which we fetch all the variable strings.
	append( HorizontalPuzzle, VerticalPuzzle, FusedPuzzle ),

	% fetch the strings of variables from the concatenated puzzle
	get_all_varstrings( FusedPuzzle, Boxes ),

	% filter only the boxes that can be filled by a word
	find_valid_rows( Boxes, WordList, ValidBoxes ),

	% sort the ValidBoxes and WordList in descending order, to improve efficiency
	sort( 0, @>=, ValidBoxes, SortedBoxes ),
	sort( 0, @>=, WordList, SortedWordList ),

	% explained below
	find_matches_for_all_rows( SortedBoxes, SortedWordList ).


% takes the character representation of the string and converts it into a
% a list of variables and characters to represent the board.
create_var_puzzle( [], [] ).
create_var_puzzle( [ Row | Rows ], Puzzle ) :-
	Puzzle = [ VarRow | VarRows ],
	create_var_row( Row, VarRow ),
	create_var_puzzle( Rows, VarRows ).

% takes the the character row representing a row of the puzzle and converts it
% to its logical representation.
create_var_row( [], []).
create_var_row( Row, SetRow ) :-
	% stupid string stuff
	tokenize_atom( Row, TokenRow ),

    % creates a list of variables the same size as Row
    length(TokenRow, Len),
    length(VarRow, Len),

    % assigns the variables to the letters in the row, if possible
    assign_var( VarRow, TokenRow, SetRow ).

% assigns the variable to a particular type depending on the character,
% then returns the completed row
assign_var( [], [], [] ).
assign_var( [Var | Vars], [Char | Chars], SetRow ) :-
    ( Char == '_' ->
      Var = _NewVar
    ; Char == '#' ->
      Var = Char
    ; Var = Char
    ),
    SetRow = [ Var | Rest ],
    assign_var( Vars, Chars, Rest ).

% splits the row of 'boxes' that are separated by '#', into a list of list of logical variables
get_all_varstrings( [], [] ).
get_all_varstrings( [ Row | Rows ], Substrings ):-
	split(Row, '#', Substring),
	append( Substring, Rest, Substrings ),
	get_all_varstrings( Rows, Rest ).

% Predicate was found at
% https://stackoverflow.com/questions/26538695/how-to-split-a-list-filled-with-logic-variables-in-prolog
% that enabled the possibility of splitting the logical variables separated by
% '#' character, tried to do a custom implementation, but failed. (collectVarstrings)

split(L, P, R) :-
 	split(L, P, [], R).
split([], _P, [], []) :- !.
split([], _P, Acc, [Acc]).
split([X|Xs], P, Acc, Result) :-
    X \== P, !,
    append(Acc, [X], NewAcc),
    split(Xs, P, NewAcc, Result).
split([_X|Xs], P, [], Result) :- !, split(Xs, P, [], Result).
split([_X|Xs], P, Acc, [Acc|Result]) :- split(Xs, P, [], Result).

% failed custom implementation of split
collect_varstrings( [ Var | Vars ], Partial, Varstrings ) :-
	( var( Var ) ->
		( nextto( Var, A, [ Var | Vars ] ), var(A) ->
			Partial = [ Var ],
			collect_varstrings( Vars, Partial, Varstrings )

		;
		not( nextto( Var, _, [ Var | Vars ] ) ) ->
			append( Partial, [ Var ], Built ),
			Varstrings = [Built]
		;
		append(Partial, [ Var ], Built),
		Varstrings = [Built | Rest],
		collect_varstrings( Vars, Partial, Rest )
		)
	; Var == '#' ->
		( not( nextto( Var, _, [ Var | Vars ] ) ) ->
			Varstrings = [Partial]
		)
	).


% find the rows that can be filled by a word
find_valid_rows( Rows, Words, ValidRows ):-
    include( valid_row( Words ), Rows, ValidRows).

% a row is valid only if there is a matching word that can fit it.
valid_row( [ Word | Words], Row ):-
    ( length(Row, N), length(Word, N) ->
        true
    );
    valid_row( Words, Row ).

% this is a conjunction of all the matches for all the rows
% For example, C1 = (ListA = [A, B] can be filled with words "AT" OR "BE")
% 			   C2 = (ListB = [B, C] can be fill with words "TE" OR "ME")
% The conjunction of C1/\C2 would yield ListA = ['A', 'T'], ListB = ['T', 'E'] as solutions.

find_matches_for_all_rows( [], _).
find_matches_for_all_rows( [Row | Rows], Words) :-
	possible_match_for_row( Row, Words ),
	find_matches_for_all_rows( Rows, Words ).

% find all the possible words that can fill the list of logical variables
possible_match_for_row( Row, [ Word | Words ] ):-
    check_match( Row, Word )
    ; possible_match_for_row( Row, Words ).

% check if the list of logical variables can be unified with the words, also works with variables that is already
% assigned or was an atom to begin with
check_match( [], [] ).
check_match( [ Var | Vars ], [ Char | Chars ]) :-
    Var = Char,
    check_match( Vars, Chars ).
