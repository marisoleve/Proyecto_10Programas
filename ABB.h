#pragma once

#ifndef _ABB_H_
#define _ABB_H_

#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<iostream>
#include<conio.h>
#include "Diseño.h"
#include <math.h>
#include <stdlib.h>                     
#include <ctype.h>                      
#include <fstream>
#include <string>

using namespace std;

/*ESTRUCTURA ARBOL BINARIO DE BUSQUEDA*/
struct Nodo {
	int dato;
	Nodo *derecho;
	Nodo *izquierdo;
	Nodo *padre;
};


//Prototipos ABB
Nodo *crearNodo(int, Nodo *);
void insertarNodo(Nodo *&, int, Nodo*);
void mostrarArbol(Nodo *, int);
bool busqueda(Nodo *, int);
int contarNodos(Nodo *);
int contarhojas(Nodo *);
int sumaNodos(Nodo *);
void eliminar(Nodo *, int);
void eliminarNodo(Nodo *);
Nodo *minimo(Nodo *); Nodo *maximo(Nodo *);
void reemplazar(Nodo *, Nodo *);
void destruirNodo(Nodo *);
void preOrden(Nodo *);
void inOrden(Nodo *);
void postOrden(Nodo *);
void abrirtxt(); void elimtxt();
void mostrarRecorridos1();

//Prototipos de Diseño
int menuABB(const char *, const char *[], int);
void letrasABB();


Nodo *arbol = NULL; //ABB
int X = 0; 
string nomba, abrir;


/*-------------------------------------- ARBOL BINARIO DE BUSQUEDA --------------------------------------*/

//Funcion para crear un nuevo nodo
Nodo *crearNodo(int n, Nodo *padre) {
	Nodo *nuevo_nodo = new Nodo(); //cracion de la nueva estructura

	nuevo_nodo->dato = n;
	//El valor del primer dato apunta a NULL tanto a izquierda como a derecha
	nuevo_nodo->derecho = NULL;
	nuevo_nodo->izquierdo = NULL;
	nuevo_nodo->padre = padre;

	return nuevo_nodo;
}

//Funcion para insertar elementos en el arbol
void insertarNodo(Nodo *&arbol, int n, Nodo *padre) {
	if (arbol == NULL) { //si el arbol esta vacio
		arbol = crearNodo(n, padre);
	}
	else { //si el arbol tiene un nodo o mas
		int valorRaiz = arbol->dato; //Obtenemos el valor de la raiz
		if (n < valorRaiz) { //Si el elemento es menor a la raiz, insertamos en izq
			insertarNodo(arbol->izquierdo, n, arbol);
		} // Si el elemento es mayor a la raiz, insertamos en der
		else if (n > valorRaiz) {
			insertarNodo(arbol->derecho, n, arbol);
		}
	}
}

//funcion para abrir un txt
void abrirtxt() {
	string arch, extension, x;
	ifstream archivo; //poder abrir un fichero para leerlo
	char cadena[100];
	int dato; //guarda la conversion de la variable token a tipo entero
	int contador = 0;
	int max = 0; //primera linea del archivo
	string linea;
	//cadena de caracteres que no van a ingresarse al arbol (caracteres indeseados)
	char no[60] = { 'A', 'B', 'C','D','E','F','G','H','I','J','K','L','M','N','Ñ','O','P','Q','R','S','T','U','V','W','X','Y','Z',
		'a','b','c','d','e','f','g','h','i','j','k','l','m','n','ñ','o','p','q','r','s','t','u','v','w','x','y','z',',',' ','.',';' };
	char* tok = (char*)malloc(sizeof(char));
	char* token = (char*)malloc(sizeof(char));
	char num[10] = { '1', '2', '3', '4', '5', '6', '7', '8', '9', '0' };
	arch = "C:/Users/Evelyn/Desktop/"; //Dirección de donde se buscara el archivo
	extension = ".txt";//Extensión que abrir el archivo
	cout << "\t Archivo de donde desea extraer el arbol: ";
	cin >> nomba;
	abrir = arch + nomba + extension;
	archivo.open(abrir.c_str());

	if (archivo.is_open()) { //Si el archivo se encuentra abierto
		while (!archivo.eof()) {
			while (getline(archivo, linea)) { //lectura de linea
				if (max == contador) {// max= numero de linea del archivo, contador= variable auxiliar para posicionarse e ingresar al condicional
					strcpy(cadena, linea.c_str()); //conversion de dato, haciendo que la cadena sea tipo string para ingresar lo que hay en la variable linea
					token = strtok(cadena, no); //Divide la cadena del archivo por los carecteres indeseados y los que se utilizaran y los ingresa a la variable token
					cout << "\t Los numeros a ingresar al arbol sin caracteres indeseados son: ";
					while (token != NULL) {//se crea un ciclo que mientras token no este vacio se realizara el proceso
						cout << token << " ";
						if (token != NULL) {
							dato = atoi(token);//conversion de la variable token que es char a tipo entero

						}
						insertarNodo(arbol, dato, NULL);
						token = strtok(NULL, no); //al momento que los parametros esten vacios, guarda la utlima cadena y palabra y lo devuelve y continua con la siguiente
					}
					strcpy(cadena, linea.c_str());
					tok = strtok(cadena, num);
					SetColor(12);
					cout << "\n\t Los caracteres indeseados encontrados son: ";
					if (tok == NULL)
					{
						cout << "\n\t No se encontraron caracteres indeseados!!";
					}
					else {
						while (tok != NULL) {
							cout << tok << " ";
							tok = strtok(NULL, num);
						}
					}SetColor(15);
				}
				contador++; //incrementa el contador en caso se quisisera leer otra linea
			}
		}
		SetColor(10); cout << "\n\t Cadena de numeros cargada al arbol con exito!\n"; SetColor(15);
		archivo.close(); //cierra el archivo
	}
	else {
		SetColor(12); cout << "\n\t Error no se pudo abrir el archivo!\n"; SetColor(15);
	}
}

void mostrarArbol(Nodo *arbol, int Y) {
	if (arbol == NULL) {
		return;
	}

	X += 5;//variable que permite posicionarse en el eje X
	mostrarArbol(arbol->izquierdo, Y + 2);//Se para hasta el nodo mas a la izquierda del árbol construye primero el subarbol izq porque sus valores en X son menores
	gotoxy(10 + X - Y, 18 + Y);//posiciona el nodo segun sus variables en X y en Y
	cout << "[" << arbol->dato << "]" << endl;//Muestra el dato del nodoAVL respectivo
	mostrarArbol(arbol->derecho, Y + 2);//Se para hasta el nodo mas a la derecho del árbol
}

//Funcion para buscar un elemento en el arbol 
bool busqueda(Nodo *arbol, int n) {
	if (arbol == NULL) { //si el arbol esta vacio
		return false;
	}
	else if (arbol->dato == n) {//si el nodo es igual al elemento
		return true;
	}
	else if (n<arbol->dato) {// si el nodo es menor al elemento busca por la izquierda
		return busqueda(arbol->izquierdo, n);
	}
	else if (n>arbol->dato) { // si el nodo es mayor al elemento busca por la derecha
		return busqueda(arbol->derecho, n);
	}
}

//ELIMINACION
//Muesta el arbol actualizado al eliminar nodo por nodo
void mostrarActualizado(Nodo *arbol, int dato) {
	for (int i = 1; i <= 50; i++) {
		gotoxy(58 + i, 1); cout << "=";
		gotoxy(58 + i, 3); cout << "=";
	}
	gotoxy(58, 2); cout << "|";
	gotoxy(109, 2); cout << "|";
	gotoxy(75, 2); cout << "ELIMINANDO NODOS...";

	gotoxy(7, 6); cout << "MOSTRANDO ABB ANTERIOR:";
	X = 10; mostrarArbol(arbol, -10);

	//Se busca el nodo previo a su eliminacion para verificar si este existe en el arbol
	if (busqueda(arbol, dato) == true) {
		cuadro();
		gotoxy(7, 27);
		eliminar(arbol, dato); //procede a eliminar el nodo
		gotoxy(7, 26); cout << "MOSTRANDO ABB ACTUALIZADO AL ELIMINAR: " << dato;
		X = 30; mostrarArbol(arbol, 10);
	}
	else
	{ //Si la salida de la funcion busqueda es false significa que el nodo no se encuetra en el arbol
		cuadro2();
		gotoxy(7, 7); SetColor(12); cout << "*El nodo " << dato << " no se encuentra en el arbol"; SetColor(15);
	}

	_getch();
}

void elimtxt() {
	string local, ext, arb;
	ifstream arch; //poder abrir un fichero para leerlo
	int cont = 0; //variable auxiliar para posicionarse en la linea a leer
	int max = 1; //segunda linea del archivo
	int dato;
	int i = 0, j = 0;
	char cadena[100];
	string linea;
	//cadena de caracteres que no van a ingresarse al arbol (caracteres indeseados)
	char no[60] = { 'A', 'B', 'C','D','E','F','G','H','I','J','K','L','M','N','Ñ','O','P','Q','R','S','T','U','V','W','X','Y','Z',
		'a','b','c','d','e','f','g','h','i','j','k','l','m','n','ñ','o','p','q','r','s','t','u','v','w','x','y','z',',',' ','.',';' };

	char* token = (char*)malloc(sizeof(char));

	local = "C:/Users/Evelyn/Desktop/";//Dirección de donde se buscara el archivo
	ext = ".txt"; //Extension del archivo
	gotoxy(5, 6); cout << "Archivo donde desea eliminar nodos: ";
	cin >> arb;
	abrir = local + arb + ext;
	arch.open(abrir.c_str());

	if (arch.is_open()) { //si el archivo se encuentra abierto

		while (!arch.eof()) {
			while (getline(arch, linea)) { //lectura de linea
				if (max == cont) {
					//conversion de dato, haciendo que la cadena sea tipo string para ingresar lo que hay en la variable linea
					strcpy(cadena, linea.c_str());
					//Divide la cadena del archivo por los carecteres indeseados y los que se utilizaran y los ingresa a la variable token
					token = strtok(cadena, no);
					while (token != NULL) { //se crea un ciclo que mientras token no este vacio se realizara el proceso
						if (token != NULL) {
							dato = atoi(token);//conversion de la variable token que es char a tipo entero
						}
						system("cls");
						mostrarActualizado(arbol, dato);
						token = strtok(NULL, no);
					}
				}
				cont++;
			}
		}
		arch.close(); //Cierra el archivo
	}
	else {
		gotoxy(5, 7); SetColor(12); cout << "Error no se pudo abrir el archivo!"; SetColor(15);
	}
}

//Eliminar un nodo del arbol
void eliminar(Nodo *arbol, int n) {
	if (arbol == NULL) {
		return;
	}
	else if (n < arbol->dato) { //si el valor es menor
		eliminar(arbol->izquierdo, n); //busca por la izquierda
	}
	else if (n > arbol->dato) { //si el valor es mayor
		eliminar(arbol->derecho, n); //busca por la derecha
	}
	else { //si se encuentra el valor 
		eliminarNodo(arbol);
	}
}

//Funcion para determinar el nodo mas izquierdo posible
Nodo *minimo(Nodo *arbol) {
	if (arbol == NULL) {
		return NULL;
	}

	if (arbol->izquierdo) { //si tiene hijo izquierdo
		return minimo(arbol->izquierdo); //buscamos la parte mas izq posible 
	}
	else { //si no tiene hijo izq
		return arbol; //retornamos al mismo nodo
	}
}

//Funcion para determinar el nodo mas derecho posible
Nodo *maximo(Nodo *arbol) {
	if (arbol == NULL) {
		return NULL;
	}

	if (arbol->derecho) { //si tiene hijo derecho
		return maximo(arbol->derecho); //buscamos la parte mas derecha posible 
	}
	else { //si no tiene hijo derecho
		return arbol; //retornamos al mismo nodo
	}
}

//Funcion para reemplazar dos nodos
void reemplazar(Nodo *arbol, Nodo *nuevoNodo) {
	if (arbol->padre) {
		//arbol->padre hay que asignarle su nuevo hijo
		if (arbol->padre->izquierdo == arbol) {
			arbol->padre->izquierdo = nuevoNodo;
		}
		else if (arbol->padre->derecho == arbol) {
			arbol->padre->derecho = nuevoNodo;
		}
	}
	if (nuevoNodo) {
		//Procedemos a asignarle su nuevo padre
		nuevoNodo->padre = arbol->padre;
	}
}

//Funcion para destruir un nodo
void destruirNodo(Nodo *nodo) {
	nodo->izquierdo = NULL;
	nodo->derecho = NULL;

	delete nodo; //Borra el nodo
}

//Funcion para eliminar el nodo encontrado
void eliminarNodo(Nodo *nodoEliminar) {
	int opcion;

	if (nodoEliminar->izquierdo && nodoEliminar->derecho) { //si el nodo tiene hijo izq y der

		gotoxy(110, 26); cout << "Eliminar " << nodoEliminar->dato << " por Derecha(1) / Izquierda(2): ";
		cin >> opcion;

		switch (opcion) {
		case 1://El nodo a eliminar se sustiuye por el nodo que se encuentra más a la izq del subarbol der
			Nodo * menor;
			menor = minimo(nodoEliminar->derecho);
			nodoEliminar->dato = menor->dato;
			eliminarNodo(menor);
			break;
		case 2: //El nodo a eliminar se sustiuye por el nodo que se encuentra más a la der del subarbol izq
			Nodo * mayor;
			mayor = maximo(nodoEliminar->izquierdo);
			nodoEliminar->dato = mayor->dato;
			eliminarNodo(mayor);
			break;
		default:
			gotoxy(110, 27);
			SetColor(12); cout << "Opcion no valida! Error al Eliminar el nodo " << nodoEliminar->dato << endl;
			SetColor(15);
			break;
		}
	}

	else if (nodoEliminar->izquierdo) {//si solo tiene hijo izquierdo
		reemplazar(nodoEliminar, nodoEliminar->izquierdo);
		destruirNodo(nodoEliminar);
	}
	else if (nodoEliminar->derecho) {//si solo tiene hijo derecho
		reemplazar(nodoEliminar, nodoEliminar->derecho);
		destruirNodo(nodoEliminar);
	}

	else { //no tiene hijos (nodo hoja)
		reemplazar(nodoEliminar, NULL);
		destruirNodo(nodoEliminar);
	}
}

//Funcion que cuenta  los nodos que hay en el arbol
int contarNodos(Nodo *arbol) {
	if (arbol == NULL) {
		return 0;
	}
	else {
		return 1 + contarNodos(arbol->izquierdo) + contarNodos(arbol->derecho);
	}
}

//Funcion que cuenta los nodos los cuales sus hijos izq y der apuntan a null (nodos terminales)
int contarHojas(Nodo *arbol) {
	if (arbol == NULL)
		return 0;

	if (arbol->izquierdo == NULL && arbol->derecho == NULL) {
		return 1;
	}
	else {
		return contarHojas(arbol->izquierdo) + contarHojas(arbol->derecho);
	}
}

//Funcion que muestra los nodos terminales
void mostrarHojas(Nodo *arbol) {
	if (arbol == NULL)
		return;
	//Si el dato no tiene hijo izq ni derecho entonces es un nodo hoja
	if (arbol->izquierdo == NULL && arbol->derecho == NULL)
		cout << arbol->dato << " ";

	mostrarHojas(arbol->derecho);
	mostrarHojas(arbol->izquierdo);
}

//Suma el valor del dato que se encuentra almacenado en cada nodo
int sumaNodos(Nodo *arbol) {
	if (arbol == NULL)
		return 0;
	else {
		return arbol->dato + sumaNodos(arbol->derecho) + sumaNodos(arbol->izquierdo);
	}
}

//RECORRIDOS
void preOrden(Nodo *arbol) {
	if (arbol == NULL) {
		return;
	}
	else {
		/*Visita la raiz
		Recorre el subarbol izquierdo
		Recorre el subarbol derecho*/
		cout << arbol->dato << "  ";
		preOrden(arbol->izquierdo);
		preOrden(arbol->derecho);
	}
}
void inOrden(Nodo *arbol) {
	if (arbol == NULL) {
		return;
	}
	else {
		/*Recorre el subarbol izquierdo
		Visita la raiz
		Recorre el subarbol derecho*/
		inOrden(arbol->izquierdo);
		cout << arbol->dato << "  ";
		inOrden(arbol->derecho);
	}
}
void postOrden(Nodo *arbol) {
	if (arbol == NULL) {
		return;
	}
	else {
		/*Recorre el subarbol izquierdo
		Recorre el subarbol derecho
		Visita la raiz*/
		postOrden(arbol->izquierdo);
		postOrden(arbol->derecho);
		cout << arbol->dato << "  ";
	}
}

void mostrarRecorridos1() {
	//Diseño
	for (int i = 1; i <= 30; i++) {
		gotoxy(9 + i, 3); cout << "*";
		gotoxy(9 + i, 5); cout << "*";
	}

	gotoxy(9, 4); cout << "|";
	gotoxy(40, 4); cout << "|";
	gotoxy(14, 4); cout << "MOSTRANDO RECORRIDOS..";

	for (int i = 1; i <= 140; i++) {
		gotoxy(9 + i, 7); cout << "-";
		gotoxy(9 + i, 9); cout << "-";
		gotoxy(9 + i, 11); cout << "-";
		gotoxy(9 + i, 13); cout << "-";
	}

	for (int i = 1; i <= 5; i++) {
		gotoxy(9, 7 + i); cout << "|";
		gotoxy(150, 7 + i); cout << "|";
	}

	//Muestra los recorridos del arbol
	gotoxy(10, 8); SetColor(10); cout << "Pre-Orden: "; SetColor(15); preOrden(arbol);
	gotoxy(10, 10); SetColor(10); cout << "In-Orden: "; SetColor(15); inOrden(arbol);
	gotoxy(10, 12); SetColor(10); cout << "Post-Orden: "; SetColor(15); postOrden(arbol);

}

void letrasABB() {
	//Letra A
	for (int i = 1; i <= 7; i++) {
		gotoxy(90, i + 5); SetColor(0); cout << "*"; SetColor(15);
		gotoxy(91, i + 5); SetColor(0); cout << "*"; SetColor(15);
		gotoxy(92, i + 5); SetColor(0); cout << "*"; SetColor(15);
		gotoxy(93, i + 5); SetColor(0); cout << "*"; SetColor(15);
		gotoxy(102, i + 5); SetColor(0); cout << "*"; SetColor(15);
		gotoxy(103, i + 5); SetColor(0); cout << "*"; SetColor(15);
		gotoxy(104, i + 5); SetColor(0); cout << "*"; SetColor(15);
		gotoxy(105, i + 5); SetColor(0); cout << "*"; SetColor(15);
	}
	for (int i = 1; i <= 12; i++) {
		gotoxy(91 + i, 4); SetColor(0); cout << "*"; SetColor(15);
		gotoxy(91 + i, 5); SetColor(0); cout << "*"; SetColor(15);
		gotoxy(91 + i, 8); SetColor(0); cout << "*"; SetColor(15);
		gotoxy(91 + i, 9); SetColor(0); cout << "*"; SetColor(15);
	}

	//Letra B
	for (int i = 1; i <= 9; i++) {
		gotoxy(109, i + 3); SetColor(0); cout << "*"; SetColor(15);
		gotoxy(110, i + 3); SetColor(0); cout << "*"; SetColor(15);
		gotoxy(111, i + 3); SetColor(0); cout << "*"; SetColor(15);
		gotoxy(112, i + 3); SetColor(0); cout << "*"; SetColor(15);
	}
	for (int i = 1; i <= 12; i++) {
		gotoxy(109 + i, 4); SetColor(0); cout << "*"; SetColor(15);
		gotoxy(109 + i, 5); SetColor(0); cout << "*"; SetColor(15);
		gotoxy(109 + i, 11); SetColor(0); cout << "*"; SetColor(15);
		gotoxy(109 + i, 12); SetColor(0); cout << "*"; SetColor(15);
	}
	for (int i = 1; i <= 12; i++) {
		gotoxy(109 + i, 8); SetColor(0); cout << "*"; SetColor(15);
	}
	for (int i = 1; i <= 3; i++) {
		gotoxy(122, i + 4); SetColor(0); cout << "*"; SetColor(15);
		gotoxy(123, i + 4); SetColor(0); cout << "*"; SetColor(15);
		gotoxy(122, i + 8); SetColor(0); cout << "*"; SetColor(15);
		gotoxy(123, i + 8); SetColor(0); cout << "*"; SetColor(15);
	}

	//Letra B
	for (int i = 1; i <= 9; i++) {
		gotoxy(126, i + 3); SetColor(0); cout << "*"; SetColor(15);
		gotoxy(127, i + 3); SetColor(0); cout << "*"; SetColor(15);
		gotoxy(128, i + 3); SetColor(0); cout << "*"; SetColor(15);
		gotoxy(129, i + 3); SetColor(0); cout << "*"; SetColor(15);
	}

	for (int i = 1; i <= 12; i++) {
		gotoxy(126 + i, 4); SetColor(0); cout << "*"; SetColor(15);
		gotoxy(126 + i, 5); SetColor(0); cout << "*"; SetColor(15);
		gotoxy(126 + i, 11); SetColor(0); cout << "*"; SetColor(15);
		gotoxy(126 + i, 12); SetColor(0); cout << "*"; SetColor(15);
	}
	for (int i = 1; i <= 12; i++) {
		gotoxy(126 + i, 8); SetColor(0); cout << "*"; SetColor(15);
	}

	for (int i = 1; i <= 3; i++) {
		gotoxy(139, i + 4); SetColor(0); cout << "*"; SetColor(15);
		gotoxy(140, i + 4); SetColor(0); cout << "*"; SetColor(15);
		gotoxy(139, i + 8); SetColor(0); cout << "*"; SetColor(15);
		gotoxy(140, i + 8); SetColor(0); cout << "*"; SetColor(15);
	}
}

int menuABB(const char *titulo, const char *opciones[], int n) {
	int OpSelect = 1; //Se posiciona en la primera opcion
	int tecla;
	bool repite = true;

	do {
		system("cls");

		for (int i = 1; i <= 53; i++) {
			gotoxy(20 + i, 15); cout << "=";
			gotoxy(20 + i, 1); cout << "=";
			gotoxy(20 + i, 4);  cout << "_";
		}
		for (int i = 1; i <= 13; i++) {
			gotoxy(74, 1 + i); cout << "|";
			gotoxy(20, 1 + i); cout << "|";
		}

		letrasABB();

		gotoxy(25, 5 + OpSelect); SetColor(10); cout << "===>"; SetColor(15);
		gotoxy(34, 3); cout << titulo;

		for (int i = 0; i < n; i++) {//Muestra las opciones ingresadas en el array opciones[] 
			gotoxy(32, 6 + i); cout << i + 1 << ". " << opciones[i];
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

int mainABB() {
	int dato, opcion, contador = 0;
	bool repite = true;
	char resp;

	system("color 1F"); //Color de la ventana
	ocultarcursor();

	const char *titulo = "MENU ARBOL BINARIO DE BUSQUEDA";
	const char *opciones[] = { "Generar nuevo arbol con un txt", "Mostrar ABB Grafico y Recorridos", "Eliminar Nodos del Arbol",
		"Buscar Nodo", "Contar Nodos", "Contar Hojas", "Sumar Nodos", "Regresar" };
	int n = 8; //Numero de opciones 

	do {
		opcion = menuABB(titulo, opciones, n);
		cout << "\n\n\n\n";

		switch (opcion) {
		case 1:
			arbol = NULL;
			abrirtxt();
			_getch();
			break;

		case 2:
			if (arbol == NULL) {
				SetColor(12); cout << "\n\t El arbol se encuentra vacio!\n\n"; SetColor(15);
			}
			else {
				system("cls");
				mostrarRecorridos1();
				for (int i = 1; i <= 38; i++) {
					gotoxy(9 + i, 16); cout << "*";
					gotoxy(9 + i, 18); cout << "*";
				}

				gotoxy(9, 17); cout << "|";
				gotoxy(48, 17); cout << "|";
				gotoxy(16, 17); cout << "MOSTRANDO ARBOL BINARIO..";
				X = 0;
				mostrarArbol(arbol, 3);
			}_getch();
			break;
		case 3:
			if (arbol == NULL) {
				SetColor(12); cout << "\t Arbol vacio, imposible eliminar nodos\n"; SetColor(15);
			}
			else {
				system("cls");
				for (int i = 1; i <= 50; i++) {
					gotoxy(58 + i, 1); cout << "=";
					gotoxy(58 + i, 3); cout << "=";
				}
				gotoxy(58, 2); cout << "|";
				gotoxy(109, 2); cout << "|";

				gotoxy(75, 2); cout << "ELIMINANDO NODOS...";
				elimtxt();
			}_getch();
			break;
		case 4:
			if (arbol == NULL) {
				SetColor(12); cout << "\n\t El arbol se encuentra vacio!\n\n"; SetColor(15);
			}
			else {
				cout << "\t Ingrese el elemento a buscar: "; cin >> dato;
				if (busqueda(arbol, dato) == true) {
					SetColor(10); cout << "\t Elemento " << dato << " a sido encontrado en el arbol\n";
					SetColor(15);
				}
				else {
					SetColor(12); cout << "\t Elemento no encontrado\n"; SetColor(15);
				}
				cout << endl;
			}
			_getch();
			break;
		case 5:
			if (arbol == NULL) {
				SetColor(12); cout << "\n\t El arbol se encuentra vacio!\n\n"; SetColor(15);
			}
			else {
				int cnodo;
				cnodo = contarNodos(arbol);
				gotoxy(10, 19); cout << "La cantidad de nodos en el ABB es : ";
				SetColor(11); cout << cnodo; SetColor(15);
				for (int i = 1; i <= 38; i++) {
					gotoxy(10 + i, 21); cout << "*";
					gotoxy(10 + i, 23); cout << "*";
				}

				gotoxy(10, 22); cout << "|";
				gotoxy(49, 22); cout << "|";
				gotoxy(17, 22); cout << "MOSTRANDO ARBOL BINARIO..";
				X = 0; mostrarArbol(arbol, 7);
			}
			_getch();
			break;

		case 6:
			if (arbol == NULL) {
				SetColor(12); cout << "\n\t El arbol se encuentra vacio!\n\n"; SetColor(15);
			}
			else {
				int hojas;
				hojas = contarHojas(arbol);
				gotoxy(10, 19); cout << "El numero de nodos hojas es: ";
				SetColor(11); cout << hojas; SetColor(15);
				gotoxy(10, 20); cout << "Los nodos Hojas son: ";
				SetColor(11); mostrarHojas(arbol); SetColor(15);

				for (int i = 1; i <= 38; i++) {
					gotoxy(10 + i, 22); cout << "*";
					gotoxy(10 + i, 24); cout << "*";
				}

				gotoxy(10, 23); cout << "|";
				gotoxy(49, 23); cout << "|";
				gotoxy(17, 23); cout << "MOSTRANDO ARBOL BINARIO..";

				X = 0; mostrarArbol(arbol, 8);
			}
			_getch();
			break;

		case 7:
			if (arbol == NULL) {
				SetColor(12); cout << "\n\t El arbol se encuentra vacio!\n\n"; SetColor(15);
			}
			else {
				int sum;
				sum = sumaNodos(arbol);
				gotoxy(10, 19); cout << "La suma de los nodos es: ";
				SetColor(11); cout << sum; SetColor(15);

				for (int i = 1; i <= 38; i++) {
					gotoxy(10 + i, 21); cout << "*";
					gotoxy(10 + i, 23); cout << "*";
				}

				gotoxy(10, 22); cout << "|";
				gotoxy(49, 22); cout << "|";
				gotoxy(17, 22); cout << "MOSTRANDO ARBOL BINARIO..";
				X = 0; mostrarArbol(arbol, 7);
			}
			_getch();
			break;
		case 8:
			repite = false;
			system("color 9F");
			return 0;
			break;
		}
	} while (repite);
}


#endif