#pragma once
#ifndef _HASH_H_
#define _HASH_H_

#include <conio.h>
#include <stdio.h>
#include <iostream>

using namespace std;

struct nodoHash {
	int x;
	nodoHash *sig;
};

nodoHash *listas[14], *aux;

void insertarHash(int clave, int valor) {

	if (listas[clave] == NULL) {
		listas[clave] = new (struct nodoHash);
		listas[clave]->x = valor;
		listas[clave]->sig = NULL;
		cout << "Guardado correctamente con la clave: " << clave << endl;
		_getch();
	}
	else {
		aux = new (struct nodoHash);
		aux->x = valor;
		aux->sig = listas[clave];
		listas[clave] = aux;
		cout << "Guardado correctamente con la clave: " << clave << endl;
		_getch();
	}
}

bool buscar(int clave, int valor) {
	bool search = false;
	nodoHash *aux = listas[clave];
	while (aux != NULL) {
		if (aux->x == valor) {
			cout << "El valor " << valor << " se encontro en el indice: " << clave << endl;
			search = true;
		}
		aux = aux->sig;
	}
	_getch();
	return search;
}

bool eliminar(int clave, int valor) {
	bool search = false;
	nodoHash *aux = listas[clave];
	if (listas[clave] != NULL) {
		if (aux->x == valor) {
			listas[clave] = listas[clave]->sig;
			cout << "Se elimino el valor: " << aux->x << endl;
			search = true;
			free(aux);
		}
		else {
			while (aux != NULL) {
				if ((aux->sig)->x == valor) {
					nodoHash *aux2 = aux->sig;
					aux->sig = (aux->sig)->sig;
					cout << "Se elimino el valor: " << aux2->x << endl;
					search = true;
					free(aux2);
					break;
				}
				aux = aux->sig;
			}
		}
	}
	_getch();
	return search;
}

void imprimir(int clave) {
	nodoHash *aux = listas[clave];
	while (aux != NULL) {
		cout << aux->x << endl;
		aux = aux->sig;
	}
	_getch();
}

void Hash(int valor) {
	int clave = 0;
	clave = valor % 13;
	insertarHash(clave, valor);
}

void menuH() {

	int op = 0, valor = 0;

	do {
		system("cls");
		cout << "\n\n";
		cout << "\t         MENU HASH      \n";
		cout << "\t 1. Ingresar nuevo valor\n";
		cout << "\t 2. Imprimir una lista\n";
		cout << "\t 3. Buscar\n";
		cout << "\t 4. Eliminar\n";
		cout << "\t 5. Regresar\n\n";
		cout << " Ingrese opcion: ";
		cin >> op;
		switch (op) {
		case 1: cout << " Ingrese numero: ";
			cin >> valor;
			Hash(valor);
			break;
		case 2: cout << " Ingrese la Lista que desee imprimir: ";
			cin >> valor;
			imprimir(valor);
			break;
		case 3: cout << " Ingrese valor a buscar: ";
			cin >> valor;
			for (int i = 0; i < 14; i++) {
				if (buscar(i, valor) == true) {
					break;
				}
			}
			break;
		case 4: cout << " Ingrese el valor a eliminar: ";
			cin >> valor;
			for (int i = 0; i < 14; i++) {
				if (eliminar(i, valor) == true) {
					break;
				}
			}
			break;
		}
	} while (op != 5);
	_getch();
}
int mainHash() {
	system("color 1F");
	menuH();
	system("color 9F");
	return 0;
}

#endif // _HASH_H_
