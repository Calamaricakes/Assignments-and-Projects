
:-ensure_loaded(borders).
:-ensure_loaded(cities).
:-ensure_loaded(countries).
:-ensure_loaded(rivers).

country(C) :-
    country(C,_,_,_,_,_,_,_).

larger(C1, C2) :-
    country(C1, _, _, _, A, _, _, _),
    country(C2, _, _, _, B, _, _, _),
    A > B.

river_country(River, Country) :-
    river(River, C),
    member(Country, C),
    country(C).

country_region(Country, Region):-
    country(Country, Region, _, _, _, _, _, _).

river_country(River, Country1) :-
    river_country(River, Country2),
    country_region(Country1, Region1),
    country_region(Country2, Region2),
    Region1 \= Region2.
