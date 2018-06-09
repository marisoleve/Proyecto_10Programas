#include "ABB.h"
#include "AVL.h"
#include "Floyd.h"
#include "PilasColas.h"
#include "ColaImpresion.h"


int menuPrincipal(const char *titulo, const char *opciones[], int n) {
	int OpSelect = 1; //Se posiciona en la primera opcion
	int tecla;
	bool repite = true;

	do {
		system("cls");

		for (int i = 1; i <= 51; i++) {
			gotoxy(57 + i, 10); cout << "*";
			gotoxy(57 + i, 5); cout << "*";
		}
		for (int i = 1; i <= 5; i++) {
			gotoxy(108, 5 + i); cout << "*";
			gotoxy(58, 5 + i); cout << "*";
		}

		gotoxy(60, 6); cout << "UNIVERSIDAD MARIANO GALVEZ DE GUATEMALA";
		gotoxy(60, 7); cout << "PROGRAMACION III - PROYECTO 10 PROGRAMAS";
		gotoxy(60, 8); cout << "Evelyn Marisol Oliva Veliz 0901-16-293";
		gotoxy(60, 9); cout << "Ninibeth Madiam Alvarez Marroquin 0901-16-9585";

		for (int i = 1; i <= 55; i++) {
			gotoxy(55 + i, 34); cout << "=";
			gotoxy(55 + i, 15); cout << "=";
			gotoxy(55 + i, 19); cout << "_";
		}
		for (int i = 1; i <= 18; i++) {
			gotoxy(111, 15 + i); cout << "|";
			gotoxy(55, 15 + i); cout << "|";
		}

		gotoxy(60, 20 + OpSelect); SetColor(10); cout << "==>"; SetColor(15);
		gotoxy(77, 17); cout << titulo;

		for (int i = 0; i < n; i++) {//Muestra las opciones ingresadas en el array opciones[] 
			gotoxy(65, 21 + i); cout << i + 1 << ". " << opciones[i];
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

int main() {
	int dato, opcion, contador = 0;
	bool repite = true;

	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE); //Maximiza la pantalla
	system("color 9F");
	ocultarcursor();

	const char *titulo = "MENU PRINCIPAL";
	const char *opciones[] = { "Arbol Binario de Busqueda", "Arbol Balanceado",
		"Algoritmo de Floyd - Warshall", "Abecedario Aleatorio (Pilas y Colas)",
		"Control de Impresion", " ", " ", " ", " ", " ", "Salir" };
	int n = 11; //Numero de opciones 

	do {
		opcion = menuPrincipal(titulo, opciones, n);
		cout << "\n\n\n\n";

		switch (opcion) {
		case 1:
			mainABB();
			break;

		case 2:
			mainAVL();
			break;
		case 3:
			mainFloyd();
			break;
		case 4:
			mainPilasColas();
			break;
		case 5:
			mainCola();
			break;
		case 6:
			break;
		case 7:
			break;
		case 8:
			break;
		case 9:
			break;
		case 10:
			break;
		case 11:
			exit(0);
			break;
		}
	} while (repite);

	return 0;
}