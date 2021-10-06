#include <iostream>
#include <list>
#include <string.h>
using namespace std;

struct premisa
{
    bool negado;
    char nombre[50];
    list<char *> parametros;
};
struct clausula
{
    int id;
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
    clausula c1,c2;
    premisa p1,p2,p3;
    p1.negado=false;
    c1.id =1;
    c2.id =2;
    strcpy(p1.nombre,"Hombre");
    char * parametro1 = new char(25);
    strcpy(parametro1,"marco");
    p1.parametros.push_back(parametro1);
    c1.premisas.push_back(p1);

    p2.negado=true;
    strcpy(p2.nombre,"Hombre");
    char * parametro2 = new char(25);
    strcpy(parametro2,"marco");
    p2.parametros.push_back(parametro2);
    c2.premisas.push_back(p2);

    p3.negado=false;
    strcpy(p3.nombre,"Pompeyano");
    char * parametro3 = new char(25);
    strcpy(parametro3,"cesar");
    p3.parametros.push_back(parametro3);
    c2.premisas.push_back(p3);

    Base_de_conocimiento.push_back(c1);
    Base_de_conocimiento.push_back(c2);
    premisa negada;
    negada.negado= true;
    strcpy(negada.nombre,"Pompeyano");
    char * parametro4 = new char(25);
    strcpy(parametro4,"cesar");
    negada.parametros.push_back(parametro4);

    bool funciono = inferencia_x_resolucion(Base_de_conocimiento,negada);
    cout<<funciono;
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
    return 0;
}
bool comparar_clausula(clausula c1, clausula c2, clausula &final){
    list<char*>::iterator itp1;
    list<char*>::iterator itp2;
    bool confirm = true,encontro =false;

    char nombre[25];
   // clausula final;
    for(premisa p1: c1.premisas){
        for(premisa p2: c2.premisas){
            if(strcmp(p1.nombre,p2.nombre) == 0 && p1.negado != p2.negado && p1.parametros.size() == p2.parametros.size()){
                encontro =true;
                strcpy(nombre,p1.nombre);
                for(itp1 = p1.parametros.begin(), itp2 = p2.parametros.begin(); itp1 != p1.parametros.end(),itp2 != p2.parametros.end();itp1++,itp2++){
                    if(strcmp(*itp1,*itp2) != 0){
                        confirm = false;
                        strcpy(nombre,"");
                    }
                }
            }
        }
    }

    if(confirm && encontro){
        for(premisa p1: c1.premisas){
            if(strcmp(p1.nombre,nombre) != 0){
                final.premisas.push_back(p1);
            }
        }
        for(premisa p2: c2.premisas){
            if(strcmp(p2.nombre,nombre) != 0){
                final.premisas.push_back(p2);
            }
        }
        return true;
    }else{
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
    clausula caux;
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
    //imprimir_base(copia);
    for(itc1=copia.begin(); itc1 != copia.end(); itc1++){
        
        for(itc2=copia.begin(); itc2 != copia.end(); itc2++){
            cout<<copia.size()<<" ";
            if(itc1->id != itc2->id){
                
                clausula nueva;
                usar = comparar_clausula(*itc1,*itc2,nueva);
               // cout<<nueva.premisas.size()<<endl;
                if(usar && nueva.premisas.empty()){
                    return true;
                    //cout<<"hola"<<endl;

                }else if(usar && !nueva.premisas.empty()){
                    copia.erase(itc1);
                    copia.erase(itc2);
                    copia.push_back(nueva);
                    //cout<<"hola"<<endl;
                }

            }
            //imprimir_base(copia);
            cout<<endl;
        }
        
        cout<<endl;
    }
    // cout<<"hola"<<endl;
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
    premisa Paux;
    clausula Caux;
    int cc, cp, parametros,cons = 0;
    char s;
    char nombre[50];
    cout << "Cantidad de clausulas" << endl;
    cin >> cc;
    cin.ignore();
    for (int i = 0; i < cc; i++)
    {
        cout << "ingrese la cantidad de premisas de la clausula " << i << " " << endl;
        cin >> cp;
        cin.ignore();
        for (int i = 0; i < cp; i++)
        {
            cout << "Incluir negacion (s/n):" << endl;
            cin >> s;
            cin.ignore();
            if (s == 's' || s == 'S')
            {
                Paux.negado = true;
            }
            else
            {
                Paux.negado = false;
            }
            cout << "Nombre de la premisa:" << endl;
            cin.getline(Paux.nombre, 50);
            cout << "Ingrese cantidad de parametros: " << endl;
            cin >> parametros;
            cin.ignore();
            for (int i = 0; i < parametros; i++)
            {
                
                cout << "Nombre del parametro:" << endl;
                cin.getline(nombre, 50);
                char* nombrep = new char(50);
                strcpy(nombrep,nombre);
                Paux.parametros.push_back(nombrep);
            }
            Caux.premisas.push_back(Paux);
             Paux.parametros.clear();
        }
        Caux.id =cons;
        base.push_back(Caux);
        Caux.premisas.clear();

        cons++;
    }
    //imprimir_base(base);

}//ya la primera
