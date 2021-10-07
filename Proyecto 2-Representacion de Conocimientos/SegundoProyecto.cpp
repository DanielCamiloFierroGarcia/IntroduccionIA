#include <iostream>
#include <list>
#include <string.h>
#include <fstream>
using namespace std;


/*PROYECTO 2: INFERENCIA POR RESOLUCION


*Juan Esteban Rincon Bautista 
*Daniel Camilo Fierro Garcia
*Marco Antonio Valencia Dueñas 

Ejemplo de prueba 

Hombre(Marco)
Pompeyano(Marco)
-Pompeyano(x3) Romano(x3)
Gobernante(Cesar)
-Romano(x5) Leal(x5,Cesar) Odia(x5,Cesar)
-Hombre(x6,) -Gobernante(y6) -IntentaAsesinar(x6,y6) -Leal(x6,y6)
IntentaAsesinar(Marco,Cesar)

HIPOTESIS:Odia(Marco,Cesar)


*/
/*Estructura que representa una premisa se compone de un
estado de negación que indica si la premisa esta negada o no, un nombre 
que contiene el nombre de la premisa y una lista de parámetros sobre los
cuales recae la premisa*/
struct premisa
{
    bool negado;
    char nombre[50];
    list<char *> parametros;
};
/*Estructura que representa una cláusula definida como un conjunto de premisas, adicionalmente
contiene un estado de descartado que posteriormente se usa en el motor asobre las premisas que se deben
eliminar en el proceso de inferencia*/
struct clausula
{
    bool descartado = false;
    list<premisa> premisas;
};
//definición de funciones
void imprimir_base(list<clausula> base);//función que imprime la base de conocimiento
void llenar_base(list<clausula> &base);//función que llena la base de conocimiento desde un archivo en el disco
bool comparar_parametros(list<char *> p1, list<char *> p2);//función que compara los parámetros de las premisas
bool Unificar(list<clausula> base, premisa p_negada);//función que unifica los parámetros de la hipótesis con los de las premisas de la base de conocimiento
bool inferencia_x_resolucion(list<clausula> base);//función que recibe la base de conocimiento normalizada y unificada y posteriormente hace el proceso de inferencia por resolución
bool comparar_clausula(clausula c1, clausula c2, clausula &final);//función que compara las premisas de dos clausulas y elimina si puede hacerlo 
bool identicos(clausula c1, clausula c2);//función que determina si dos clausulas son exactamente iguales

list<clausula> Base_de_conocimiento;
int main()
{
    premisa negada;
    negada.negado = true;
    strcpy(negada.nombre, "Odia");
    char *parametro6 = new char(25);
    strcpy(parametro6, "Marco");
    negada.parametros.push_back(parametro6);
    char *parametro7 = new char(25);
    strcpy(parametro7, "Cesar");
    negada.parametros.push_back(parametro7);

    llenar_base(Base_de_conocimiento);
    imprimir_base(Base_de_conocimiento);
    cout << endl;
    Unificar(Base_de_conocimiento, negada);

    return 0;
}
bool identicos(clausula c1, clausula c2)
{
    list<premisa>::iterator it;
    list<premisa>::iterator it2;
    list<char *>::iterator para;
    list<char *>::iterator para1;
    bool iguales = true;

    if (c1.premisas.size() == c2.premisas.size())
    {
        //cout<<"holi"<<endl;
        for (it = c1.premisas.begin(), it2 = c2.premisas.begin(); it != c1.premisas.end(), it2 != c2.premisas.end(); it++, it2++)
        {
            //cout<<it<<endl;
            cout<<it->nombre<<" "<<it2->nombre<<" "<<it->negado<<" "<<it2->negado<<endl;
            if (strcmp(it->nombre, it2->nombre) == 0 && it->negado == it2->negado && it->parametros.size() == it2->parametros.size())
            {
                cout<<"holi"<<endl;
                for(para = it->parametros.begin(), para1 = it2->parametros.begin(); para != it->parametros.end(),para1 != it2->parametros.end();para++,para1++){
                    if(strcmp(*para,*para1) != 0){
                        iguales = false;
                    }
                }
            }else{
                iguales =false;
            }
        }
    }else{
        iguales =false;
    }
    return iguales;
}
bool comparar_clausula(clausula c1, clausula c2, clausula &final)
{
    list<char *>::iterator para1;
    list<char *>::iterator para2;
    char nombre[50];
    bool comparables = true, encontro = false;
    for (premisa p1 : c1.premisas)
    {
        for (premisa p2 : c2.premisas)
        {
            if (strcmp(p1.nombre, p2.nombre) == 0 && p1.negado != p2.negado)
            {
                //cout<<"holi"<<endl;
                encontro = true;
                strcpy(nombre, p1.nombre);
                for (para1 = p1.parametros.begin(), para2 = p2.parametros.begin(); para1 != p1.parametros.end(), para2 != p2.parametros.end(); para1++, para2++)
                {
                    //cout<<*para1<<" "<<*para2<<endl;
                    if (strcmp(*para1, *para2) != 0)
                    {
                        comparables = false;
                    }
                }
            }
        }
    }
    if (comparables == true && encontro == true)
    {
        for (premisa p1 : c1.premisas)
        {
            if (strcmp(p1.nombre, nombre) != 0)
            {
                final.premisas.push_back(p1);
            }
        }
        for (premisa p2 : c2.premisas)
        {
            if (strcmp(p2.nombre, nombre) != 0)
            {
                final.premisas.push_back(p2);
            }
        }
        return true;
    }
    return false;
}
bool comparar_parametros(list<char *> p1, list<char *> p2)
{
    list<char *>::iterator it1;
    list<char *>::iterator it2;

    for (it1 = p1.begin(), it2 = p2.begin(); it1 != p1.end(), it2 != p2.end(); it1++, it2++)
    {
        if (strcmp(*it1, *it2) == 0 || strcmp(*it1, "x") == 0 || strcmp(*it2, "x") == 0)
        {
        }
    }
}
bool Unificar(list<clausula> base, premisa p_negada)
{
    list<char *> val_variables;
    for (char *var : p_negada.parametros)
    {
        val_variables.push_back(var);
    }
    clausula negada;
    negada.premisas.push_back(p_negada);
    base.push_back(negada);

    list<clausula>::iterator itclausula;
    list<premisa>::iterator itpremisa;
    list<char *>::iterator it1;
    list<char *>::iterator it2;

    for (itclausula = base.begin(); itclausula != base.end(); itclausula++)
    {
        for (itpremisa = itclausula->premisas.begin(); itpremisa != itclausula->premisas.end(); itpremisa++)
        {
            for (it1 = itpremisa->parametros.begin(), it2 = val_variables.begin(); it1 != itpremisa->parametros.end() && it2 != val_variables.end(); it1++, it2++)
            {
                if (strchr(*it1, 'x') != NULL || strchr(*it1, 'y') != NULL && itpremisa->parametros.size() > 1)
                {
                    strcpy(*it1, *it2);
                }
                else if (strchr(*it1, 'y') != NULL && itpremisa->parametros.size() == 1)
                {
                    it2++;
                    strcpy(*it1, *it2);
                }
            }
        }
    }
    imprimir_base(base);
    cout << endl;
    bool resul = inferencia_x_resolucion(base);
    cout << "resultado de la inferencia: " << resul << endl;
}
bool inferencia_x_resolucion(list<clausula> base)
{
    list<clausula> copia;
    imprimir_base(base);
    cout << endl;
    list<clausula> copia2;
    for (clausula c : base)
    {
        copia.push_back(c);
    }

    list<clausula>::iterator it1;
    list<clausula>::iterator it2;
    for (it1 = copia.begin(); it1 != copia.end(); it1++)
    {
        for (it2 = copia.begin(); it2 != copia.end(); it2++)
        {
            if (distance(it1, it2) != 0 && it2->descartado == false && it1->descartado == false)
            {
                clausula recipiente;
                bool usar = comparar_clausula(*it1, *it2, recipiente);
                if (usar == true && recipiente.premisas.size() != 0)
                {
                    it1->descartado = true;
                    it2->descartado = true;
                    copia2.push_back(recipiente);
                }
                else if (usar == true && recipiente.premisas.size() == 0)
                {
                    return true;
                }
            }
        }
    }
    int contd = 0;
    for (clausula c1 : copia)
    {
        if (c1.descartado != true)
        {
            contd++;
            copia2.push_back(c1);
        }
    }
    /*if(copia2.size()==2){
        clausula cc = copia2.front();
        clausula cc1 = copia2.back();
        bool iguales = identicos(cc,cc1);
        if(identicos){
            return false;
        }
    }*/
    if (contd > 0)
    {
        return inferencia_x_resolucion(copia2);
    }
    return false;
}
void imprimir_base(list<clausula> base)
{
    for (clausula c : base)
    {
        for (premisa p : c.premisas)
        {
            if (p.negado == true)
            {
                cout << "-";
            }
            cout << p.nombre << "(";
            for (char *pr : p.parametros)
            {
                cout << pr << ",";
            }
            cout << ")"
                 << " ";
        }
        cout << endl;
    }
}
void llenar_base(list<clausula> &base)
{
    clausula aux;
    premisa paux;
    int pos = 0;

    char linea[100];
    ifstream ar("base_de_conocimiento.txt");

    while (!ar.eof())
    {
        ar >> linea;
        char *ptr = strtok(linea, ";,");
        int pos = 0;
        while (ptr != NULL)
        {
            char cad[100];
            //cout<<ptr<<endl;
            strcpy(cad, ptr);
            if (strchr(cad, '-') != NULL)
            {
                if (paux.parametros.size() != 0 && pos != 0)
                {
                    aux.premisas.push_back(paux);
                    //strcpy(paux.nombre, "");
                }
                paux.parametros.clear();
                for (int i = 0; i < strlen(cad); i++)
                {
                    cad[i] = cad[i + 1];
                }
                //cout<<"negado:"<<cad<<endl;
                paux.negado = true;
                strcpy(paux.nombre, cad);
            }
            else if (strchr(cad, '+') != NULL)
            {
                if (paux.parametros.size() != 0 && pos != 0)
                {
                    aux.premisas.push_back(paux);
                    //strcpy(paux.nombre, "");
                }
                paux.parametros.clear();
                for (int i = 0; i < strlen(cad); i++)
                {
                    cad[i] = cad[i + 1];
                }
                //cout<<"no negado:"<<cad<<endl;
                paux.negado = false;
                strcpy(paux.nombre, cad);
            }
            else if (strchr(cad, '-') == NULL && strchr(cad, '+') == NULL)
            {
                char *parametro = new char(strlen(cad));
                strcpy(parametro, cad);
                paux.parametros.push_back(parametro);
            }
            ptr = strtok(NULL, ";,");
            pos++;
        }
        ptr = NULL;
        aux.premisas.push_back(paux);
        Base_de_conocimiento.push_back(aux);
        pos = 0;
        //strcpy(cad,"");
        aux.premisas.clear();
    }
    //Base_de_conocimiento.push_back(aux);
    // cout << linea << endl;

    ar.close();
}

