#pragma once
#ifndef _PILASCOLAS_H_
#define _PILASCOLAS_H_

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <time.h>
#include <cstdlib>
#include "Diseño.h"

using namespace std;

//Funciones utilizadas
int aleatorio();
void generarVector();
void mostrarVector();
void Pop();
void Desencolar();

//Declaracion de valores 
char LetraAl[20];
int  Inicio, Final;
int	 NumLetras; // Variable auxiliar para llevar un control del numero de letras que estan en el vector
int  opcion = 0;


void generarVector() {
	int aux = 0;
	int arregloN[20];

	Final = 0;
	Inicio = 0;

	srand(time(NULL)); // se utiliza para que al momento que se corra el programa aparezcan letras diferentes

	for (int i = 0; i < 20; i++) {
		aux = aleatorio();
		int aux2 = 0;

		while (aux2 < i) {

			if (aux != arregloN[aux2])
				aux2++;
			else {
				aux = aleatorio();
				aux2 = 0;
			}
		}

		arregloN[i] = aux;
		LetraAl[i] = char(arregloN[i]); //Convierte el numero a letra y lo almacena en el vector LetraAl

		Final++;
		cout << "\t  |" << LetraAl[i] << "|" << " Posicion:" << Final << endl;
		cout << "\t  ---" << endl;
	}
}

int aleatorio() {
	// rand syntax: <int> = (<numeromenor> + rand() % ( <numeromayor> - <numeromenor> ) )
	int aux = (97 + rand() % (122 - 97)); // genera numeros del 97 al 122 (codigos de letras de tabla ascii)
	return aux;
}

//--------------------------------------------------- PILA ---------------------------------------------------------
void Pop() {
	if (NumLetras == 0) {
		gotoxy(10, 15); cout << "PILA VACIA!" << endl << endl;
	}

	else {
		gotoxy(28, 15); cout << "ELIMINANDO: ";
		gotoxy(32, 16); cout << "---";
		gotoxy(32, 17); cout << "|" << LetraAl[Final - 1] << "|";
		gotoxy(32, 18); cout << "---";
		gotoxy(19, 19); cout << "Con la posicion en la pila: " << Final << endl << endl;
		LetraAl[Final - 1] = 0;
		Final--;

		NumLetras--;

		mostrarVector();
	}
}

//--------------------------------------------------- COLA ---------------------------------------------------------
void Desencolar() {

	if (NumLetras == 0) {
		gotoxy(10, 15); cout << "COLA VACIA!" << endl << endl;
	}
	else {
		gotoxy(28, 15); cout << "ELIMINANDO: ";
		gotoxy(32, 16); cout << "---";
		gotoxy(32, 17); cout << "|" << LetraAl[Inicio] << "|";
		gotoxy(32, 18); cout << "---";
		gotoxy(19, 19); cout << "Con la posicion en la cola: " << Inicio + 1 << endl << endl;
		LetraAl[Inicio] = 0;
		Inicio++;

		NumLetras--;

		mostrarVector();
	}
}

void mostrarVector() {
	for (int r = Inicio; r < Final; r++) {
		cout << "\t  |" << LetraAl[r] << "|" << " Posicion:" << r + 1 << endl;
		cout << "\t  ---" << endl;
	}
}

//------------------------------------------------------ MAIN -------------------------------------------------------

void menuP() {
	Inicio = 0, Final = 0;

	do {
		system("cls");
		gotoxy(10, 2); cout << "----------------------------------------------------------";
		gotoxy(10, 3); cout << "|    CONTROL DE ABECEDARIO ALEATORIO POR PILA Y COLA	   |";
		gotoxy(10, 4); cout << "|--------------------------------------------------------|";
		gotoxy(10, 5); cout << "|            -> 1. Generar Vector Aleatorio              |";
		gotoxy(10, 6); cout << "|            -> 2. Mostrar Vector                        |";
		gotoxy(10, 7); cout << "|            -> 3. Eliminar/Mostrar (PILA)               |";
		gotoxy(10, 8); cout << "|            -> 4. Eliminar/Mostrar (COLA)               |";
		gotoxy(10, 9); cout << "|            -> 5. Vaciar Vector                         |";
		gotoxy(10, 10); cout << "|            -> 6. Regresar                              |";
		gotoxy(10, 11); cout << "----------------------------------------------------------";
		gotoxy(10, 13); cout << "Ingresar Opcion: ";  cin >> opcion;
		cout << endl;

		switch (opcion) {
		case 1:gotoxy(25, 15); cout << "NUEVO ARREGLO ALEATORIO" << endl << endl;
			generarVector();
			NumLetras = 20;
			break;

		case 2:
			if (NumLetras == 0) {
				gotoxy(10, 15); cout << "VECTOR VACIO.\n\n";
			}
			else {
				mostrarVector();
			}
			break;

		case 3: Pop();
			break;

		case 4: Desencolar();
			break;

		case 5:
			if (NumLetras == 0) {
				gotoxy(10, 15); cout << "ERROR! El vector se encuentra vacio.\n\n";
			}
			else {
				for (int i = 0; i < 20; i++) {
					LetraAl[i] = 0;
				}
				NumLetras = 0;
				gotoxy(10, 15); cout << "VECTOR COMPLETO ELIMINADO!\n\n";
			}
			break;

		case 6:
			gotoxy(10, 15); cout << "PROGRAMA FINALIZADO" << endl << endl;
			EXIT_SUCCESS;
			break;
		}
		_getch();
	} while (opcion != 6);
}

int mainPilasColas() {
	system("color 1F");
	menuP();
	system("color 9F");
	return 0;
}
#endif