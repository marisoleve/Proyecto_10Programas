#ifndef _LISTADOBLEMENTE_H_
#define _LISTADOBLEMENTE_H_

#include <iostream>
#include "Diseño.h"
#include <string>
#include <conio.h>

using namespace std;

struct personasD {
	string nombre;
	int edad;
} personaD;

struct nodoD {
	personasD p;
	nodoD *siguiente;
	nodoD *anterior;
};

void agregarH(nodoD *head) {
	cout << "Ingresar nombre: ";
	cin >> personaD.nombre; cout << endl;
	cout << "Ingrear edad: ";
	cin >> personaD.edad; cout << endl;

	head->p = personaD;
	head->siguiente = NULL;
	head->anterior = NULL;
}

void agregarSiguiente(nodoD *head) {
	cout << "Ingresar nombre: ";
	cin >> personaD.nombre; cout << endl;
	cout << "Ingresar edad: ";
	cin >> personaD.edad; cout << endl;

	nodoD *lista = head;
	nodoD *nuevo = new nodoD();

	nuevo->p = personaD;
	nuevo->siguiente = NULL;
	while (lista)
	{
		if (lista->siguiente == NULL) {
			lista->siguiente = nuevo;
			break;
		}
		lista = lista->siguiente;
	}
}

nodoD *agregarAnterior(nodoD *head) {
	cout << "Ingrese nombre: ";
	cin >> personaD.nombre; cout << endl;
	cout << "Ingrese edad: ";
	cin >> personaD.edad; cout << endl;

	nodoD *nuevo = new nodoD();

	nuevo->p = personaD;
	nuevo->anterior = NULL;
	nuevo->siguiente = head;
	head->anterior = nuevo;
	head = nuevo;
	return head;
}

void agregarPosicion(nodoD *head, int tamañoLista) {
	int posicion, i = 1;
	cout << "Agregar posicion donde desea insertar la persona: ";
	cin >> posicion;
	if (posicion == 1) {
		system("cls");
		agregarH(head);
	}
	if (posicion == tamañoLista) {
		system("cls");
		agregarSiguiente(head);
	}
	else {
		if ((posicion > 1) && (posicion < tamañoLista)) {
			cout << "Ingrese nombre: ";
			cin >> personaD.nombre; cout << endl;
			cout << "Ingrese edad: ";
			cin >> personaD.edad; cout << endl;
			nodoD *lista = head;
			nodoD *nuevo = new nodoD;
			nuevo->p = personaD;
			while (posicion != i) {
				lista = lista->siguiente;
				i++;
			}
			lista->anterior->siguiente = nuevo;
			nuevo->siguiente = lista;
			nuevo->anterior = lista->anterior;
			lista->anterior = nuevo;
		}
		else {
			cout << "posicion invalida!!";
			_getch();
		}
	}
}

void mostrar(nodoD *head) {
	nodoD *lista = head;
	while (lista) {
		cout << "Nombre: " << lista->p.nombre << endl;
		cout << "Edad: " << lista->p.edad << endl;
		cout << endl << endl;
		lista = lista->siguiente;
	}
}



int mainLDoble() {
	int opc = 0, cont = 0, aceptar = 1;
	nodoD *head = new nodoD();
	system("color 1F");

	while (aceptar == 1) {
		system("cls");
		gotoxy(10, 2); cout << "----------------------------------------------------------";
		gotoxy(10, 3); cout << "|                LISTA DOBLEMENTE ENLAZADA	           |";
		gotoxy(10, 4); cout << "|--------------------------------------------------------|";
		gotoxy(10, 5); cout << "|            -> 1. Agregar atras                         |";
		gotoxy(10, 6); cout << "|            -> 2. Agregar adelante                      |";
		gotoxy(10, 7); cout << "|            -> 3. Agregar en una posicion               |";
		gotoxy(10, 8); cout << "|            -> 4. Mostrat lista                         |";
		gotoxy(10, 9); cout << "|            -> 5. Eliminar Dato                         |";
		gotoxy(10, 10); cout << "----------------------------------------------------------";
		gotoxy(10, 12); cout << "Ingresar Opcion: ";  cin >> opc;
		cout << endl;

		switch (opc) {
		case 1:
			if (cont == 0) {
				agregarH(head);
				cont++;
			}
			else {
				agregarSiguiente(head);
				cont++;
			}
			break;
		case 2:
			if (cont == 0) {
				agregarH(head);
				cont++;
			}
			else {
				head = agregarAnterior(head);
				cont++;
			}
			break;
		case 3:
			agregarPosicion(head, cont);
			cont++;
			break;
		case 4:
			mostrar(head);
			break;

		}
		cout << "Desea mostrar el menu de nuevo (1. Si,  2. No )\n";
		cin >> aceptar;
	}

	system("color 9F");
	return 0;
}

#endif
