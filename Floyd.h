#pragma once
#ifndef _FLOYD_H_
#define _FLOYD_H_
 
#include <iostream>
#include <conio.h>
#include "Diseño.h"

using namespace std;

int n;
int D[20][20], S[20][20];
int vect1[20], vect2[20];

int auxX1, auxY1, auxX2, auxY2;
int contD, contS;
int  x = 0;

//Prototipos
void ingresar();
void matrizS();
void floid();
void mostrarD();
void mostrarS();
void caminoMin();


void ingresar() {
	int i, j;
	SetColor(0); cout << "\n\tIngresar Orden de la Matriz Cuadrada: "; cin >> n; SetColor(1);
	gotoxy(56, 12); SetColor(3); cout << "IMPORTANTE: Ingresar valor infinito como -1"; SetColor(1);
	cout << endl;
	for (i = 1; i <= n; i++)
		for (j = 1; j <= n; j++) {
			cout << "\tIngresar Valor D0[" << i << "][" << j << "] =  ";
			cin >> D[i][j];
			if (D[i][j] == -1) {
				D[i][j] = 9999;
			}
		}
}

void matrizS() {
	int i, j;
	for (i = 1; i <= n; i++)
		for (j = 1; j <= n; j++)
		{
			if (i == j)
				S[i][j] = 0;
			else S[i][j] = j;
		}
}

void floid()
{
	int bucle, i, j, suma;
	for (bucle = 1; bucle <= n; bucle++) {
		for (i = 1; i <= n; i++) {
			vect1[i] = D[bucle][i];
			vect2[i] = D[i][bucle];
		}

		for (i = 1; i <= n; i++)
			for (j = 1; j <= n; j++) {
				if (vect2[i] == 9999 || vect1[j] == 9999) suma = 9999;
				else suma = vect2[i] + vect1[j];
				if (suma<D[i][j]) {
					D[i][j] = suma;
					S[i][j] = bucle;
				}
			}
		mostrarD();
		mostrarS();
	}

}

void mostrarD() {
	gotoxy(auxX1, auxY1); cout << "D" << contD << ":";

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++)
		{
			if (j == n) {
				x = auxX1 + j * 5;
			}

			if (D[i][j] == 9999) {
				gotoxy(auxX1 + j * 5, auxY1 + i);  cout << "INF" << " ";
			}
			else {
				gotoxy(auxX1 + j * 5, auxY1 + i);  cout << D[i][j] << " ";
			}
		}
		cout << endl;
	}
	contD++;
	auxY1 = auxY1 + n + 2;

}

void mostrarS() {
	gotoxy(auxX2, auxY2);  cout << "S" << contS << ":";
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++)
		{
			gotoxy(auxX2 + j * 4, auxY2 + i); cout << S[i][j];
		}
		cout << endl;
	}
	contS++;
	auxY2 = auxY2 + n + 2;
}

void caminoMin()
{
	int i, j;
	gotoxy(16, auxY1 + 2); SetColor(3); cout << "Camino Minimo Entre dos Vertices: "; SetColor(1);
	cout << "\n\t\tVertice1 = "; cin >> i;
	cout << "\t\tVertice2 = "; cin >> j;

	if (i > n || j > n || i>n && j>n) {
		SetColor(4); cout << "\n\t\tERROR! Vertice Invalido..."; SetColor(1);
	}
	else if (i == 0 || j == 0 || i == j)
		cout << "\n\t\tDistancia minima es 0";
	else {
		cout << "\n\t\tDistancia minima ";
		cout << D[i][j];
	}
}

int menuFloyd(const char *titulo, const char *opciones[], int n) {
	int OpSelect = 1; //Se posiciona en la primera opcion
	int tecla;
	bool repite = true;

	do {
		system("cls");

		for (int i = 1; i <= 55; i++) {
			gotoxy(20 + i, 10); cout << "=";
			gotoxy(20 + i, 1); cout << "=";
		}
		for (int i = 1; i <= 8; i++) {
			gotoxy(76, 1 + i); cout << "|";
			gotoxy(20, 1 + i); cout << "|";
		}

		gotoxy(26, 4 + OpSelect); SetColor(0); cout << "==>"; SetColor(1);
		gotoxy(33, 3); SetColor(0); cout << titulo; SetColor(1);

		for (int i = 0; i < n; i++) {//Muestra las opciones ingresadas en el array opciones[] 
			gotoxy(33, 5 + i); cout << i + 1 << ". " << opciones[i];
		}

		do {
			tecla = _getch();
		} while (tecla != TECLA_ARRIBA && tecla != TECLA_ABAJO && tecla != ENTER);

		switch (tecla) {
		case TECLA_ARRIBA:
			OpSelect--;

			if (OpSelect < 1) {
				OpSelect = n;
			}
			break;

		case TECLA_ABAJO:
			OpSelect++;
			if (OpSelect > n) {
				OpSelect = 1;
			}

			break;

		case ENTER:
			repite = false;
			break;
		}

	} while (repite);

	return OpSelect;
}

int mainFloyd() {
	int dato, opcion, contador = 0;
	bool repite = true;
	int val = 0;

	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE); //Maximiza la pantalla
	system("color 71");
	ocultarcursor();

	const char *titulo = "MENU ALGORITMO DE FLOYD-WARSHAL";
	const char *opciones[] = { "Ingresar Nueva Matriz D0", "Mostrar Matrices Dn y Sn","Regresar" };
	int n = 3; //Numero de opciones 

	do {
		opcion = menuFloyd(titulo, opciones, n);
		cout << "\n\n\n\n";

		switch (opcion) {
		case 1:
			ingresar();
			matrizS();
			auxX1 = 56, auxY1 = 16;
			gotoxy(56, 14); SetColor(3); cout << "MATRIZ D0 INGRESADA:"; SetColor(1);
			mostrarD();
			val = 1;
			break;
		case 2:
			if (val == 1) {
				system("cls");
				auxX1 = 16, auxY1 = 8, auxX2 = 16, auxY2 = 8;
				contD = 0, contS = 0;

				for (int i = 1; i <= 55; i++) {
					gotoxy(16 + i, 5); cout << "=";
					gotoxy(16 + i, 1); cout << "=";
				}
				for (int i = 1; i <= 3; i++) {
					gotoxy(72, 1 + i); cout << "|";
					gotoxy(16, 1 + i); cout << "|";
				}

				gotoxy(30, 3); SetColor(0); cout << "MOSTRANDO MATRICES DN Y SN..."; SetColor(1);

				mostrarD();
				auxX2 = x + 5;
				mostrarS();
				floid();

				caminoMin();
			}
			else {
				SetColor(4); cout << "\n\tERROR! Debe Ingresar la Matriz D0"; SetColor(1);
			}
			break;
		case 3:
			system("color 9F");
			return 0;
			break;
		}
		_getch();
	} while (repite);
}


#endif // !_FLOYD_H
