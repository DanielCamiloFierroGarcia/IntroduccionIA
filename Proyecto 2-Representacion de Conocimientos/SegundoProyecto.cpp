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
    list<premisa> premisas;
};
void imprimir_base(list<clausula> base);
void llenar_base(list<clausula> base);
void inferencia_x_resolucion(list<clausula> base, premisa p_negada);
list<clausula> Base_de_conocimiento;
int main()
{
    llenar_base(Base_de_conocimiento);

    return 0;
}
void inferencia_x_resolucion(list<clausula> base, premisa p_negada){
    list<clausula> copia;
    for(clausula c: base){
        copia.push_back(c);
    }
}
void imprimir_base(list<clausula> base){
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
void llenar_base(list<clausula> base)
{
    premisa Paux;
    clausula Caux;
    int num = 0, num2 = 0;
    char cad[50];
    char op;
    cout << "Numero de reglas a ingresar: ";
    cin >> num;
    cin.ignore();
    for (int i = 0; i < num; i++)
    {
        cout << "Nombre de la regla: " << endl;
        cin.getline(Paux.nombre, 50);
        cout << "Incluir negacion en la regla?(s/n)" << endl;
        cin >> op;
        cin.ignore();
        if (op == 's' || op == 'S')
        {
            Paux.negado = true;
        }
        else
        {
            Paux.negado = false;
        }
        cout << "Numero de parametros: " << endl;
        cin >> num2;
        cin.ignore();
        for (int j = 0; j < num2; j++)
        {
            cout << "Ingrese parametro:" << endl;
            cin.getline(cad, 50);
            Paux.parametros.push_back(cad);
        }
        Caux.premisas.push_back(Paux);
        base.push_back(Caux);
        strcpy(Paux.nombre, "");
        Paux.parametros.clear();
        Caux.premisas.clear();
    }

    imprimir_base(base);
}
