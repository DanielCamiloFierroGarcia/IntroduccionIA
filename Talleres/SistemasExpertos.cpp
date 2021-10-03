#include <iostream>
#include <list>
#include <string.h>

using namespace std;
//se crean dos estructuras para las reglas y los hechos
//las reglas tienen dos listas la primera es la condicion de la premisa y la segunda es la conclucion de la misma
struct regla{
   list<char> condicion;
   list<char> conclucion;
};
struct hecho{
    list<char> componente;
};

hecho inferencia_adelante(list<regla> reglas,list<hecho> hechos,hecho inicial);
int main()
{
    list<regla> reglas;
    list<hecho> hechos;


    struct regla r1,r2;
    struct hecho h1;

    h1.componente.push_back('A');
    h1.componente.push_back('L');
    hechos.push_back(h1);


    r1.condicion.push_back('A');
    r1.condicion.push_back('&');
    r1.condicion.push_back('N');
    r1.conclucion.push_back('E');

    r2.condicion.push_back('A');
    r2.conclucion.push_back('M');

    //se llenan las listas con las reglas y hechos
    //en este caso se tiene los hechos conocidos (A,L)
    //se tiene una regla que es (A&N=>E) y otra (A=>M)

    reglas.push_back(r1);
    reglas.push_back(r2);

    //se recorre la lista de solucion para imprimir los hechos finales
    hecho solucion = inferencia_adelante(reglas,hechos,h1);
    for(char c: solucion.componente){
        cout<<c<<",";
    }

    return 0;
}
hecho inferencia_adelante(list<regla> reglas,list<hecho> hechos,hecho inicial){
        list<char> premisas;
        bool y = false, o = false;
        int cont =0;
        //Se empieza recorriendo la lista de reglas para comprobar las premmisas que existan y si no es un operador, se guarda en una lista temporal
        for(regla r: reglas){
            for(char cond: r.condicion){
                if(cond != '&' && cond != 'O'){
                    premisas.push_back(cond);
                }else if(cond == '&'){
                    y = true;
                }else if(cond == 'O'){
                    o = true;
                }
            }
            //se pasa a recorrer la lista de hechos, aqui para saber los hechos conocidos, e ir juntando con los hechos que se juantaran despues de la validacionn
            for(hecho h: hechos){
            //ahora se recorre la lista de premisas
                for(char pre: premisas){
                    for(char com: h.componente ){
                        //mientras se recorre las premisas y los componentes se verifica si son iguales para de esa manera aumentar un contador auxiliar en 1
                        if(pre == com){
                            cont++;
                        }
                    }

                }
                //yacon los recorridos hechos se pasa a las verificaciones finales
                //si se encontro el operador & y el contador es igual al tam de las premisas, la conclucion de la premisa se le hace push al final de la lista 'inicial'
                if(y == true && cont == premisas.size()){
                    for(char pre: r.conclucion){
                        inicial.componente.push_back(pre);
                    }
                //si el operador encontrado es O y se encontro una de las dos premisas, entonces la conclusion se le hace push a  la lista 'inicial'
                }else if(o == true && cont != premisas.size() && cont != 0){
                    for(char pre: r.conclucion){
                        inicial.componente.push_back(pre);
                    }
                //por ultimo si no se encontro ningun operador significa que solo existe una condicion en el hecho por lo que en caso que el cont no sea 0, la conclusion se le hace push a  la lista 'inicial'
                }else if(y == false && o ==false && cont != 0){
                    for(char pre: r.conclucion){
                        inicial.componente.push_back(pre);
                    }

                }
            }
            //por ultimo se 'reinician' las variables de los operadores, el contador y se limpian las premisas, para que no interfiera con las siguientes iteraciones
            y=false;
            o=false;
            cont = 0;
            premisas.clear();
        }
        //se retorna la lista de hechos 'inicial' que es la que se iba llenando con las ultimas verificaciones
        return inicial;

}
