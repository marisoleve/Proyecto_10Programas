#pragma once
#ifndef _LISTASIMPLE_H_
#define _LISTASIMPLE_H_

#include <conio.h>
#include <string>
#include <iostream>
#include "Diseño.h"

using namespace std;

struct personas {
	string nombre;
	int edad;
} persona;

struct nodoL{
	personas p;
	nodoL *siguiente;
};

void agregarH(nodoL *head) {
	cout << "Ingrese nombre: \n";
	cin >> persona.nombre;
	cout << "Ingrese edad: \n";
	cin >> persona.edad;

	head->p = persona;
	head->siguiente = NULL;
}

void agregar(nodoL *head)
{
	cout << "Ingrese nombre: ";
	cin >> persona.nombre; cout << endl;
	cout << "Ingrese edad: ";
	cin >> persona.edad; cout << endl;

	nodoL *lista = head;
	nodoL *nuevo = new nodoL();
	nuevo->p = persona;
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
void mostrar(nodoL *head)
{
	nodoL *lista = head;
	while (lista)
	{
		cout << " Nombre: " << lista->p.nombre << endl;
		cout << " Edad: " << lista->p.edad << endl;
		lista = lista->siguiente;
	}

}

void eliminar(nodoL *head) {
	string name;
	nodoL *h = head;
	nodoL *lista = head;
	cout << "Ingrese nombre a eliminar: ";
	cin >> name;

	if (lista->p.nombre == name) {
		h = h->siguiente;
		free(lista);
	}
	else {
		while ((lista->siguiente)->p.nombre != name) {
			lista = lista->siguiente;
		}
		nodoL *aux = lista->siguiente;
		lista->siguiente = (lista->siguiente)->siguiente;
		free(aux);
	}
	_getch();
}

int mainLSimple()
{
	int cont = 0, opc = 0, a = 1;
	nodoL *head = new nodoL();
	system("color 1F");

	while (a != 2) {
		system("cls");
		gotoxy(10, 2); cout << "----------------------------------------------------------";
		gotoxy(10, 3); cout << "|                LISTA SIMPLEMENTE ENLAZADA	            |";
		gotoxy(10, 4); cout << "|--------------------------------------------------------|";
		gotoxy(10, 5); cout << "|            -> 1. Ingresar Datos                        |";
		gotoxy(10, 6); cout << "|            -> 2. Mostrar Lista                         |";
		gotoxy(10, 7); cout << "|            -> 3. Eliminar Dato                         |";
		gotoxy(10, 8); cout << "----------------------------------------------------------";
		gotoxy(10, 10); cout << "Ingresar Opcion: ";  cin >> opc;
		cout << endl;
		
		switch (opc)
		{
		case 1:
			if (cont == 0) {
				agregarH(head);
				cont++;
			}
			else {
				agregar(head);
			}
			break;
		case 2: 
			mostrar(head);
			break;
		case 3: 
			eliminar(head);
			break;
		}
		cout << "Desea mostrar el menu de nuevo? 1.Si 2.No\n";
		cin >> a;
	}
	system("color 9F");
	return 0;
}

#endif