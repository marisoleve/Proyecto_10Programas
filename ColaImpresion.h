#pragma once
#ifndef _COLAIMPRESION_H_
#define _COLAIMPRESION_H_

//COLA MEMORIA DINAMICA

#include <iostream>
#include <string>

using namespace std;

//Estructura de los nodos de la cola
struct nodo {
	string archivo;
	int hojas;
	string usuario;
	struct nodo *sgte;
};

//Estructura de la cola
struct cola {
	nodo *delante;
	nodo *atras;
};

void encolar(struct cola &q, string arc, int hja, string usr) {

	struct nodo *aux = new(struct nodo);

	aux->archivo = arc;
	aux->hojas = hja;
	aux->usuario = usr;
	aux->sgte = NULL;

	if (q.delante == NULL)
		q.delante = aux; //encola el primer elemento 
	else
		(q.atras)->sgte = aux;

	q.atras = aux; //puntero que siempre apunta al ultimo elemento
}

void desencolar(struct cola &q) {
	int h;
	string a, u;
	struct nodo *aux;

	aux = q.delante; //aux apunta al inicio de la cola
	a = aux->archivo;
	h = aux->hojas;
	u = aux->usuario;

	q.delante = (q.delante)->sgte;
	delete(aux); //libera memoria a donde apunta aux
}

void muestraCola(struct cola q) {
	struct nodo *aux;

	aux = q.delante;

	while (aux != NULL) {
		cout << "  " << &aux->archivo << " - " << "NOMBRE ARCHIVO: " << aux->archivo << endl;
		cout << "  " << &aux->hojas << " - " << "NO. HOJAS: " << aux->hojas << endl;
		cout << "  " << &aux->usuario << " - " << "USUARIO: " << aux->usuario << endl << endl;
		aux = aux->sgte;
	}
}

void vaciaCola(struct cola &q) {
	struct nodo *aux;

	while (q.delante == NULL) {
		aux = q.delante;
		q.delante = aux->sgte;
		delete(aux);
	}

	q.delante = NULL;
	q.atras = NULL;
}

void menu() {
	gotoxy(10, 2); cout << "----------------------------------------------------------";
	gotoxy(10, 3); cout << "|              CONTROL DE IMPRESION (COLAS)	           |";
	gotoxy(10, 4); cout << "|--------------------------------------------------------|";
	gotoxy(10, 5); cout << "|            -> 1. ENCOLAR                               |";
	gotoxy(10, 6); cout << "|            -> 2. DESENCOLAR                            |";
	gotoxy(10, 7); cout << "|            -> 3. MOSTRAR COLA                          |";
	gotoxy(10, 8); cout << "|            -> 4. VACIAR COLA                           |";
	gotoxy(10, 9); cout << "|            -> 5. REGRESAR                              |";
	gotoxy(10, 10); cout << "----------------------------------------------------------";
	
	cout <<  endl;

	cout << "\n INGRESE OPCION:  ";
}

int mainCola() {
	struct cola q;

	q.delante = NULL;
	q.atras = NULL;

	int hojas;
	string archivo, usuario;
	int op; //opcion del menu

	system("color 1F");

	do {
		system("cls");
		menu(); cin >> op;

		switch (op) {
		case 1:
			cout << "\n NOMBRE DEL ARCHIVO: "; cin >> archivo;
			cout << " NO. HOJAS: "; cin >> hojas;
			cout << " USUARIO: "; cin >> usuario;
			encolar(q, archivo, hojas, usuario);
			cout << "\n\n\tARCHIVO  " << archivo << " encolado..\n\n";
			break;

		case 2:
			if (q.delante != NULL && q.atras != NULL) {
				desencolar(q);
				cout << "\n\n\t\tArchivo desencolado..\n\n";
			}
			else
				cout << "\n\n\tERROR! No hay datos en cola.";
			break;

		case 3:
			cout << "\n\n MOSTRANDO COLA\n\n";
			if (q.delante != NULL) muestraCola(q);
			else cout << "\n\n\tCola vacia...! " << endl;
			break;

		case 4:
			if (q.delante != NULL && q.atras != NULL) {
				vaciaCola(q);
				cout << "\n\n\t\tHecho..\n\n";
			}else
				cout << "\n\n\tLa cola ya se encuentra vacia..";
			break;
		case 5:
			gotoxy(10, 15); cout << "PROGRAMA FINALIZADO" << endl << endl;
			EXIT_SUCCESS;
			break;
		}
		_getch();
	} while (op != 5);

	system("color 9F");
	return 0;
}

#endif