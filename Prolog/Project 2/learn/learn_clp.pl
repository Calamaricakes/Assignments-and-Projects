
:- use_module(library(clpfd)).

flirt_constraint(Suzy, Nathan, John, FlirtPeriods) :-
        length(Suzy, 6),
        length(Nathan, 6),
        length(John, 6),
        Suzy ins 1..6,
        Nathan ins 1..6,
        John ins 1..6,
        all_different(Suzy),
        all_different(Nathan),
        all_different(John),
        FlirtPeriods = [A,B,C],
        FlirtPeriods ins 1..6,
        A #< B,    % remove unwanted symmetry
        B #< C,
        flirty_period(A, Suzy, Nathan, John),
        flirty_period(B, Suzy, Nathan, John),
        flirty_period(C, Suzy, Nathan, John),
        label(Suzy),
        label(FlirtPeriods).

flirty_period(Period, Suzy, Nathan, John) :-
        Class in 1..6,
        DiffClass #\= Class,
        element(Period, Suzy, Class),
        element(Period, Nathan, Class),
        element(Period, John, DiffClass).






















recommendEmployee( Es ) :-
    Es = [ [_Num, Rev, Saf, Time, Grade] ],
    Rev #>= 80,
    Saf #=< 1,
    Tm = [ [Grade, TimeNeeded] ],
    time_in_grade(Tg),
    tuples_in( Tm, Tg ),
    Time #>= TimeNeeded,
    employees(Em),
    tuples_in( Es, Em ).

employees([
   [1, 75, 0, 30, 1],
   [2, 83, 0, 45, 1],
   [3, 90, 1, 45, 2],
   [4, 45, 3, 75, 1],
   [5, 89, 0, 52, 2]
   ]).

time( Grade, TimeNeeded ):-
    Tm = [ [Grade, TimeNeeded] ],
    time_in_grade(Tg),
    tuples_in( Tm, Tg ).


time_in_grade([[1,25], [2,50]]).



%puzzle( [F, O, R, T, Y] + [T, E, N] + [T, E, N] = [S, I, X, T, Y] ) :-
%        Vars = [F, O, R, T, Y, E, N, S, I, X],
%        Vars ins 0..9,
%        all_different(Vars),
%                  F*10000 + O*1000 + R*100 + T*10 + Y + 2*(T*100 + E*10 + N*1) #=
%                  S*10000 + I*1000 + X*100 + T*10 + Y,
%        F #\= 0, S #\= 0,
%        label(Vars).
