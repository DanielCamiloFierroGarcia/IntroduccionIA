#include <iostream>
#include <list>
#include <string.h>
#include <fstream>
using namespace std;

struct premisa
{
    bool negado;
    char nombre[50];
    list<char *> parametros;
};
struct clausula
{
    bool descartado = false;
    list<premisa> premisas;
};
void imprimir_base(list<clausula> base);
void llenar_base(list<clausula> &base);
bool comparar_parametros(list<char *> p1, list<char *> p2);
bool inferencia_x_resolucion(list<clausula> base, premisa p_negada);
bool comparar_clausula(clausula c1, clausula c2, clausula &final);

list<clausula> Base_de_conocimiento;
int main()
{
    //llenar_base(Base_de_conocimiento);

    //imprimir_base(Base_de_conocimiento);
    clausula c1, c2, c3;
    premisa p1, p2, p3;
    p1.negado = false;
    strcpy(p1.nombre, "Hombre");
    char *parametro1 = new char(25);
    strcpy(parametro1, "marco");
    p1.parametros.push_back(parametro1);
    c1.premisas.push_back(p1);

    p3.negado = false;
    strcpy(p3.nombre, "Pompeyano");
    char *parametro3 = new char(25);
    strcpy(parametro3, "X1");
    p3.parametros.push_back(parametro3);
    c2.premisas.push_back(p3);

    /*p2.negado = false;
    strcpy(p2.nombre,"Odia");
    char * parametro4 = new char(25);
    strcpy(parametro4,"X1");
    p2.parametros.push_back(parametro4);
    char * parametro5 = new char(25);
    strcpy(parametro5,"Y1");
    p2.parametros.push_back(parametro5);
    c3.premisas.push_back(p2);
    
    Base_de_conocimiento.push_back(c3);
    Base_de_conocimiento.push_back(c1);
    Base_de_conocimiento.push_back(c2);
    //llenar_base(Base_de_conocimiento);
    imprimir_base(Base_de_conocimiento);
    p1.negado = false;
    premisa negada;
    negada.negado= true;
    strcpy(negada.nombre,"Odia");
    char * parametro6 = new char(25);
    strcpy(parametro6,"Marco");
    negada.parametros.push_back(parametro6);
    char * parametro7 = new char(25);
    strcpy(parametro7,"Cesar");
    negada.parametros.push_back(parametro7);
   bool funciono = inferencia_x_resolucion(Base_de_conocimiento,negada);
    cout<<"Estado de comprobacion de la premisa: "<<funciono;*/
    /*clausula final;
    bool cnf = comparar_clausula(c1,c2,final);
    cout<<cnf<<endl;
    for(premisa p:final.premisas ){
        cout<<p.nombre<<"(";
        for(char* para: p.parametros){
            cout<<para<<" ";
        }
        cout<<")";
    }
    cout<<endl;*/
    llenar_base(Base_de_conocimiento);
    imprimir_base(Base_de_conocimiento);
    return 0;
}
bool comparar_clausula(clausula c1, clausula c2, clausula &final)
{
    list<char *>::iterator itp1;
    list<char *>::iterator itp2;
    bool confirm = true, encontro = false;

    char nombre[25];
    // clausula final;
    for (premisa p1 : c1.premisas)
    {
        for (premisa p2 : c2.premisas)
        {
            if (strcmp(p1.nombre, p2.nombre) == 0 && p1.negado != p2.negado && p1.parametros.size() == p2.parametros.size())
            {
                encontro = true;
                strcpy(nombre, p1.nombre);
                for (itp1 = p1.parametros.begin(), itp2 = p2.parametros.begin(); itp1 != p1.parametros.end(), itp2 != p2.parametros.end(); itp1++, itp2++)
                {
                    char p[25];
                    char p2[25];
                    strcpy(p, *itp1);
                    strcpy(p2, *itp2);
                    if (p[0] == 'X' || p[0] == 'Y' && p2[0] != 'X' && p2[0] != 'Y')
                    {
                        strcpy(*itp1, *itp2);
                    }
                    else if (p2[0] == 'X' || p2[0] == 'Y' && p[0] != 'X' && p[0] != 'Y')
                    {
                        strcpy(*itp2, *itp1);
                    }

                    if (strcmp(*itp1, *itp2) != 0)
                    {
                        confirm = false;
                        strcpy(nombre, "");
                    }
                }
            }
        }
    }

    if (confirm && encontro)
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
    else
    {
        return false;
    }
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
bool inferencia_x_resolucion(list<clausula> base, premisa p_negada)
{

    list<clausula> copia;
    list<clausula> copia2;
    list<clausula> Nbase;
    clausula caux;
    int nid = 0;
    bool usar;
    caux.premisas.push_back(p_negada);
    for (clausula c : base)
    {
        copia.push_back(c);
        copia2.push_back(c);
    }
    copia.push_back(caux);
    copia2.push_back(caux);

    list<clausula>::iterator itc1;
    list<clausula>::iterator itc2;

    imprimir_base(Nbase);
    for (itc1 = copia.begin(); itc1 != copia.end(); itc1++)
    {
        for (itc2 = copia.begin(); itc2 != copia.end(); itc2++)
        {
            if (itc1 != itc2 && itc1->descartado == false && itc2->descartado == false)
            {
                clausula final;
                bool usar = comparar_clausula(*itc1, *itc2, final);
                if (usar == true && final.premisas.size() != 0)
                {
                    itc1->descartado = true;
                    itc1->descartado = true;
                    copia.push_back(final);
                }
                else if (usar == true && final.premisas.size() == 0)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

void imprimir_base(list<clausula> base)
{
    for (clausula c : base)
    {
        for (premisa p : c.premisas)
        {
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
                if(paux.parametros.size()!=0 && pos != 0){
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
                if(paux.parametros.size()!=0 && pos != 0){
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
