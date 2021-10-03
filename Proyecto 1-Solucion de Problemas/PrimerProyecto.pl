%PROYECTO 1

%Juan Esteban Rincon Bautista 
%Daniel Camilo Fierro Garcia
%Marco Antonio Valencia Dueñas 

%REPRESENTACION DEL PROBLEMA
%   E  = [A,B,C,D]
%   E  =  [robot, caja amarilla, caja verde, caja roja]
% la posicion se representa con las letras i(izquierda), d(derecha), v(caja en la pinza del robot) 
% los estados inicial y final de la situacion en la que se desea pasar las cajas de izquierda a derecha se pueden representar de la siguiente forma:
% Ei = [i,i,i,i] , Ef = [d,d,d,d]

%Accion pasar
pasar([A,B,C,D],Actual):-(A==i), Actual = [d,B,C,D].
pasar([A,B,C,D],Actual):-(A==d), Actual = [i,B,C,D].
%se valida la posicion actual del robot y se pasa al lado contrario

%Accion cojer 
cojerCAmarilla([A,B,C,D],Actual):-(A==B),(C\==v),(D\==v), Actual = [A,v,C,D].
cojerCVerde([A,B,C,D],Actual):-(A==C),(B\==v),(D\==v), Actual = [A,B,v,D].
cojerCRoja([A,B,C,D],Actual):-(A==D),(B\==v),(C\==v), Actual = [A,B,C,v].
%se valida si el robot esta en la misma habitacion de la caja correspondiente y de ser asi se cambia su estado

%Accion soltar 
soltarCAmarilla([A,B,C,D],Actual):-(B==v), Actual = [A,A,C,D].
soltarCVerde([A,B,C,D],Actual):-(C==v), Actual = [A,B,A,D].
soltarCRoja([A,B,C,D],Actual):-(D==v), Actual = [A,B,C,A].
%se valida que la caja este en la pinza del robot si es asi se pone la caja en la misma posicion en la que esta el robot

%HEURISTICA


costoRobot([X,_,_,_],[Y,_,_,_], Score):-(X\==Y) , Score is 1.
costoRobot([X,_,_,_],[Y,_,_,_], Score):-(X==Y) , Score is 0.

costoCAmarilla([_,X,_,_],[_,Y,_,_], Score):-(X\==Y) , Score is 1.
costoCAmarilla([_,X,_,_],[_,Y,_,_], Score):-(X==Y) , Score is 0.

costoCVerde([_,_,X,_],[_,_,Y,_], Score):-(X\==Y) , Score is 1.
costoCVerde([_,_,X,_],[_,_,Y,_], Score):-(X==Y) , Score is 0.

costoCRoja([_,_,_,X],[_,_,_,Y], Score):-(X\==Y) , Score is  1.
costoCRoja([_,_,_,X],[_,_,_,Y], Score):-(X==Y) , Score is  0.




heuristica(Actual, Goal, Costo, A,B,C,D):-
    costoRobot(Actual,Goal, A),
    costoCAmarilla(Actual,Goal, B),
    costoCVerde(Actual,Goal, C),
    costoCRoja(Actual,Goal, D),
    Costo is A+B+C+D.


precedes([,,,,F1], [,,,,F2]) :- F1 =<F2.


%Metodos de manejo de set y cola ordenada 
empty_set([]). 
empty_sort_queue([]). 
insert_sort_queue(State, [], [State]).
insert_sort_queue(State, [H | T], [State, H | T]) :-
    precedes(State, H).
insert_sort_queue(State, [H|T], [H | T_new]) :-
    insert_sort_queue(State, T, T_new).
remove_sort_queue(First, [First|Rest], Rest).
add_to_set(X, S, [X|S]).
add_to_set(X, S, S) :- member(X, S), !. 
member_sort_queue(E, S) :- member(E, S).
member_set(E, S) :- member(E, S). 

%Guardar informacion del estado
state_record(State, Parent, G, H, F, [State, Parent, G, H, F]).



bestfirst(Start,Goal):-
empty_set(Closed),%set vacio
empty_sort_queue(Empty_open),%cola vacia
heuristica(Start,Goal,H,_,_,_,_),%calcula heuristica del primer nodo
state_record(Start, nil, 0, H, H, EI_record),%guarda la informacion del estado inicial
insert_sort_queue(EI_record, Empty_open, Open),%Inserta el estado inicial en open
path(Open,Closed, Goal).

%cola vacia por tanto no se encontro solucion
path(Open,_,_) :- 
    empty_sort_queue(Open),
    write("Solucion no encontrada").

%El siguiente estado es solucion por tanto se imprime el camino
path(Open, Closed, Goal) :- 
    remove_sort_queue(First_record, Open, _),
    state_record(State, _, _, _, _, First_record),
    State = Goal,
    write('El camino solucion es: '), nl,
    printsolution(First_record, Closed).
%El siguiente estado no es solucion
%genera los hijos los añade a open y continua 
path(Open, Closed, Goal) :- 
    remove_sort_queue(First_record, Open, Rest_of_open),
    (bagof(Child, moves(First_record, Open, Closed, Child, Goal), Children);Children = []),
    insert_list(Children, Rest_of_open, New_open),
    add_to_set(First_record, Closed, New_closed),
    path(New_open, New_closed, Goal),!.

%moves genera los hijos y calcula su heuristica
moves(State_record, Open, Closed,Child, Goal) :-
    state_record(State,_,G,_,_,State_record),
    pasar(State, Next),
    % not(unsafe(Next)),
    state_record(Next, _, _, _, _, Test),
    not(member_sort_queue(Test, Open)),
    not(member_set(Test, Closed)),
    G_new is G + 1,
    heuristica(Next, Goal, H,_,_,_,_),
    F is G_new + H,
    state_record(Next, State, G_new, H, F, Child).

moves(State_record, Open, Closed,Child, Goal) :-
    state_record(State,_,G,_,_,State_record),
    cojerCAmarilla(State, Next),
    % not(unsafe(Next)),
    state_record(Next, _, _, _, _, Test),
    not(member_sort_queue(Test, Open)),
    not(member_set(Test, Closed)),
    G_new is G + 1,
    heuristica(Next, Goal, H,_,_,_,_),
    F is G_new + H,
    state_record(Next, State, G_new, H, F, Child).

moves(State_record, Open, Closed,Child, Goal) :-
    state_record(State,_,G,_,_,State_record),
    cojerCVerde(State, Next),
    % not(unsafe(Next)),
    state_record(Next, _, _, _, _, Test),
    not(member_sort_queue(Test, Open)),
    not(member_set(Test, Closed)),
    G_new is G + 1,
    heuristica(Next, Goal, H,_,_,_,_),
    F is G_new + H,
    state_record(Next, State, G_new, H, F, Child).


moves(State_record, Open, Closed,Child, Goal) :-
    state_record(State,_,G,_,_,State_record),
    cojerCRoja(State, Next),
    % not(unsafe(Next)),
    state_record(Next, _, _, _, _, Test),
    not(member_sort_queue(Test, Open)),
    not(member_set(Test, Closed)),
    G_new is G + 1,
    heuristica(Next, Goal, H,_,_,_,_),
    F is G_new + H,
    state_record(Next, State, G_new, H, F, Child).


moves(State_record, Open, Closed,Child, Goal) :-
    state_record(State,_,G,_,_,State_record),
    soltarCVerde(State, Next),
    % not(unsafe(Next)),
    state_record(Next, _, _, _, _, Test),
    not(member_sort_queue(Test, Open)),
    not(member_set(Test, Closed)),
    G_new is G + 1,
    heuristica(Next, Goal, H,_,_,_,_),
    F is G_new + H,
    state_record(Next, State, G_new, H, F, Child).

moves(State_record, Open, Closed,Child, Goal) :-
    state_record(State,_,G,_,_,State_record),
    soltarCAmarilla(State, Next),
    % not(unsafe(Next)),
    state_record(Next, _, _, _, _, Test),
    not(member_sort_queue(Test, Open)),
    not(member_set(Test, Closed)),
    G_new is G + 1,
    heuristica(Next, Goal, H,_,_,_,_),
    F is G_new + H,
    state_record(Next, State, G_new, H, F, Child).


moves(State_record, Open, Closed,Child, Goal) :-
    state_record(State,_, G,_,_,State_record),
    soltarCRoja(State, Next),
    % not(unsafe(Next)),
    state_record(Next, _, _, _, _, Test),
    not(member_sort_queue(Test, Open)),
    not(member_set(Test, Closed)),
    G_new is G + 1,
    heuristica(Next, Goal, H,_,_,_,_),
    F is G_new + H,
    state_record(Next, State, G_new, H, F, Child).

%inserta en la lista los estados generados y despues en la cola uno por uno
insert_list([], L, L).
insert_list([State | Tail], L, New_L) :-
    insert_sort_queue(State, L, L2),
    insert_list(Tail, L2, New_L).

%imprime la ruta solucion 
printsolution(Next_record, _):-  
    state_record(State, nil, _, H,_, Next_record),
    write(State+H), nl.
printsolution(Next_record, Closed) :-
    state_record(State, Parent, _, H,_, Next_record),
    state_record(Parent, _, _, _, _, Parent_record),
    member_set(Parent_record, Closed),
    printsolution(Parent_record, Closed),
    write(State+H), nl.
