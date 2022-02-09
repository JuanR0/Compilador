#include <cstdlib>
#include <iostream>
#include <string>

#include "lexico.h"
#include "pila.h"

using namespace std;

int main(int argc, char* argv[]) {

    int tablaLR[3][3] = {
        2, 0, 1,
        0, -1, 0,
        0, -2, 0
    };

    Pila pila;
    int fila, columna, accion;
    bool aceptacion = false;
    Lexico lexico("a");

    pila.push(TipoSimbolo::PESOS);
    pila.push(0);
    lexico.sigSimbolo();

    fila = pila.top();
    columna = lexico.tipo;
    accion = tablaLR[fila][columna];

    pila.muestra();
    cout << "entrada: " << lexico.simbolo << endl;
    cout << "accion: " << accion << endl;

    pila.push(lexico.tipo);
    pila.push(accion);
    lexico.sigSimbolo();

    fila = pila.top();
    columna = lexico.tipo;
    accion = tablaLR[fila][columna];

    pila.muestra();
    cout << "entrada: " << lexico.simbolo << endl;
    cout << "accion: " << accion << endl;

    return 0;
}