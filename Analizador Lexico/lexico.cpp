#include "lexico.h"

Lexico::Lexico(string fuente) {
    ind = 0;
    this->fuente = fuente;
}

Lexico::Lexico() {
    ind = 0;
}

string Lexico::tipoAcad(int tipo) {
    string cad = "";

    switch (tipo) {
    case TipoSimbolo::IDENTIFICADOR:
        cad = "Identificador";
        break;
    case TipoSimbolo::ENTERO:
        cad = "Entero";
        break;
    case TipoSimbolo::REAL:
        cad = "Real";
        break;
    case TipoSimbolo::CADENA:
        cad = "Cadena";
        break;
    case TipoSimbolo::TIPO_DATO:
        cad = "Tipo dato";
        break;
    case TipoSimbolo::OPADIC:
        cad = "Op. Adicion";
        break;

    case TipoSimbolo::OPMULT:
        cad = "Op. Multiplicacion";
        break;
    case TipoSimbolo::OPRELAC:
        cad = "Op. Relacion";
        break;
    case TipoSimbolo::OPOR:
        cad = "Op. Disyuncion";
        break;
    case TipoSimbolo::OPAND:
        cad = "Op. Conjuncion";
        break;
    case TipoSimbolo::OPNOT:
        cad = "Op. Negacion";
        break;
    case TipoSimbolo::OPIGU:
        cad = "Op. Igualdad";
        break;
    case TipoSimbolo::PUNTO_Y_COMA:
        cad = "Punto y coma";
        break;
    case TipoSimbolo::COMA:
        cad = "Coma";
        break;
    case TipoSimbolo::PARENTESIS_IZQ:
        cad = "Parentesis izquierdo";
        break;
    case TipoSimbolo::PARENTESIS_DER:
        cad = "Parentesis derecho";
        break;
    case TipoSimbolo::LLAVE_DER:
        cad = "Llave derecha";
        break;
    case TipoSimbolo::LLAVE_IZQ:
        cad = "Llave izquierda";
        break;
    case TipoSimbolo::IGUAL:
        cad = "Igual";
        break;
    case TipoSimbolo::IF:
        cad = "If";
        break;
    case TipoSimbolo::WHILE:
        cad = "While";
        break;
    case TipoSimbolo::RETURN:
        cad = "Return";
        break;
    case TipoSimbolo::ELSE:
        cad = "Else";
        break;
    case TipoSimbolo::PESOS:
        cad = "Fin de la Entrada";
        break;

    }

    return cad;
}

void Lexico::entrada(string fuente) {
    ind = 0;
    this->fuente = fuente;
}

int Lexico::sigSimbolo() {

    estado = 0;
    continua = true;
    simbolo = "";
    c = sigCaracter();
    //Inicio del Automata
    while (continua) {
        

        switch (estado) {
        case 0:
            //if (esLetra(c)) aceptacion(0);
            if (esDigito(c)) sigEstado(2);
            else if (esLetra(c)) sigEstado(4);
            else if (c == '+' || c == '-') aceptacion(5);
            else if (c == '*' || c == '/') aceptacion(6);
            else if (c == '<' || c == '>') sigEstado(5);
            else if (c == '|') sigEstado(6);
            else if (c == '&') sigEstado(7);
            else if (c == '!') sigEstado(8);
            else if (c == '=') sigEstado(9);
            /*else
                if (c == '$') aceptacion(3);*/

            break;
        case 1:
            c = sigCaracter();
            if (esDigito(c)||esLetra(c)) sigEstado(1);
            else  if (c == '$') aceptacion(--estado);
            break;
        case 2:
            c = sigCaracter();
            if (esDigito(c)) sigEstado(2);
            else if (c == '.') sigEstado(3);
            else if (esLetra(c)) sigEstado(1);
            else  if (c == '$') aceptacion(--estado);
            break;
        case 3:
            c = sigCaracter();
            if (esDigito(c)) sigEstado(3);
            else  if (c == '$') aceptacion(--estado);
            break; 
        case 4:
            c = sigCaracter();
            if (esTipoDato(simbolo))aceptacion(4);
            else if (esLetra(c)) sigEstado(4);
            else if (esDigito(c)) sigEstado(1);
            else if (c == '$') aceptacion(--estado);
            break;
        case 5:
            c = sigCaracter();
            if (c == '=') aceptacion(7);
            else
                
                retroceso();
                aceptacion(7);
            break;
        case 6:
            c = sigCaracter();
            if (c == '|') aceptacion(8);
            break;
        case 7:
            c = sigCaracter();
            if (c == '&') aceptacion(9);
            break;
        case 8:
            c = sigCaracter();
            if (c == '=') aceptacion(11);
            else
                aceptacion(10);
            break;
        case 9:
            c = sigCaracter();
            if (c == '=') aceptacion(11);
            
            break;
        }
    }
    //Fin del Automata

    switch (estado) {
    case 0:
        tipo = TipoSimbolo::IDENTIFICADOR;
        break;
    case 1:
        tipo = TipoSimbolo::ENTERO;
        break;
    case 2:
        tipo = TipoSimbolo::REAL;
        break;
    case 3:
        tipo = TipoSimbolo::CADENA;
        break;
    case 4:
        tipo = TipoSimbolo::TIPO_DATO;
        break;
    case 5:
        tipo = TipoSimbolo::OPADIC;
        break;
    case 6:
        tipo = TipoSimbolo::OPMULT;
        break;
    case 7:
        tipo = TipoSimbolo::OPRELAC;
        break;
    case 8:
        tipo = TipoSimbolo::OPOR;
        break;
    case 9:
        tipo = TipoSimbolo::OPAND;
        break;
    case 10:
        tipo = TipoSimbolo::OPNOT;
        break;
    case 11:
        tipo = TipoSimbolo::OPIGU;
        break;
    case 12:
        tipo = TipoSimbolo::PUNTO_Y_COMA;
        break;
    case 13:
        tipo = TipoSimbolo::COMA;
        break;
    case 14:
        tipo = TipoSimbolo::PARENTESIS_IZQ;
        break;
    case 15:
        tipo = TipoSimbolo::PARENTESIS_DER;
        break;
    case 16:
        tipo = TipoSimbolo::LLAVE_IZQ;
        break;
    case 17:
        tipo = TipoSimbolo::LLAVE_DER;
        break;
    case 18:
        tipo = TipoSimbolo::IGUAL;
        break;
    case 19:
        tipo = TipoSimbolo::IF;
        break;
    case 20:
        tipo = TipoSimbolo::WHILE;
        break;
    case 21:
        tipo = TipoSimbolo::RETURN;
        break;
    case 22:
        tipo = TipoSimbolo::ELSE;
        break;
    case 23:
        tipo = TipoSimbolo::PESOS;
        break;
    dafault:
        tipo = TipoSimbolo::ERROR;
    }

    return tipo;
}

char Lexico::sigCaracter() {
    if (terminado()) return '$';

    return fuente[ind++];
}

void Lexico::sigEstado(int estado) {
    this->estado = estado;
    simbolo += c;
}

void Lexico::aceptacion(int estado) {
    sigEstado(estado);
    continua = false;
}

bool Lexico::terminado() {//fin de cadena
    return ind >= fuente.length();
}

bool Lexico::esLetra(char c) {
    return isalpha(c) || c == '_';
}


bool Lexico::esDigito(char c) {
    return isdigit(c);
}

bool Lexico::esEspacio(char c) {
    return c == ' ' || c == '\t';
}

bool Lexico::esTipoDato(string s) {
    
    return (simbolo == "int"|| simbolo == "float" || simbolo == "void");
}

void Lexico::retroceso() {
    if (c != '$') ind--;
    continua = false;
}