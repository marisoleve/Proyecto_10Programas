#ifndef _LISTAINVERSA_H_
#define _LISTAINVERSA_H_
#include "iostream"
#include "stdlib.h"

using namespace std;

struct NodoLI {
	int info;
	NodoLI *sig;
	NodoLI *ant;
};

NodoLI *c = NULL;
NodoLI *ultimo = NULL;

void agregar(NodoLI *&, NodoLI *&, int);
void mostrar(NodoLI *cab);
void muestra1(NodoLI *cab);
void muestraInverso(NodoLI *);
void menuLI();

int mainLInv()
{
	system("color 1F");
	menuLI();
	system("color 9F");
	return 0;
}

void menuLI() {
	int opcion, dato;

	do {
		system("cls");
		gotoxy(10, 2); cout << "----------------------------------------------------------";
		gotoxy(10, 3); cout << "|                      LISTA INVERZA	                   |";
		gotoxy(10, 4); cout << "|--------------------------------------------------------|";
		gotoxy(10, 5); cout << "|           1) Ingrese un dato (numero entero)           |";
		gotoxy(10, 6); cout << "|           2) Mostrar los datos ingresados              |";
		gotoxy(10, 7); cout << "|           3) Mostrar con direccion                     |";
		gotoxy(10, 8); cout << "|           4) Mostrar inverso                           |";
		gotoxy(10, 9); cout << "|           5) Regresar                                  |";
		gotoxy(10, 10); cout << "----------------------------------------------------------";
		gotoxy(10, 12); cout << "Ingrese opcion: "; cin >> opcion;
		cout << endl;

		switch (opcion) {
		case 1:
			cout << "Ingrese informacion: " << endl;
			cin >> dato;
			agregar(c, ultimo, dato); break;
		case 2: mostrar(c); break;
		case 3: muestra1(c); break;
		case 4: muestraInverso(ultimo); break;
		}

	} while (opcion != 5);
}

void agregar(NodoLI *&c, NodoLI *&ultimo, int dato) {
	NodoLI *nuevoNodo = new NodoLI();
	nuevoNodo->info = dato;


	if (c == NULL) {
		c = new NodoLI();
		c->info = dato;
		c->sig = NULL;
		c->ant = NULL;
		ultimo = c;
	}
	else {
		ultimo->sig = nuevoNodo;
		nuevoNodo->sig = NULL;
		nuevoNodo->ant = ultimo;
		ultimo = nuevoNodo;
	}
}

void mostrar(NodoLI *cab) {
	cout << "Elementos en la lista:" << endl;
	NodoLI *temp;
	temp = cab;

	while (temp != NULL) {
		cout << temp->info << " ";
		temp = temp->sig;
	}

	system("pause");
}

void muestra1(NodoLI *cab) {
	cout << "Elementos en la lista: " << endl;
	NodoLI *temp;
	temp = cab;

	while (temp != NULL) {
		cout << temp->info << " " << temp->sig << endl;
		temp = temp->sig;
	}
	system("pause");
}

void muestraInverso(NodoLI *ult) {
	cout << "Elementos en la lista:" << endl;

	NodoLI *temp;
	temp = ult;

	if (c != NULL)
	{
		while (temp != NULL)
		{
			cout << temp->info << " ";
			temp = temp->ant;
		}
	}
	else
	{
		cout << "La lista se encuentra vacia\n";
	}
	system("pause");

}


#endif 


