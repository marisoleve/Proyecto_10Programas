#pragma once
#ifndef _AVL_H_
#define _AVL_H_
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

/*ESTRUCTURA ARBOL BALANCEADO*/
struct nodoAVL {
	int dato;
	nodoAVL *izquierdo;
	nodoAVL *derecho;
	int altura;
};
//Prototipos AVL
int altura(nodoAVL *);
int getBalance(nodoAVL *);
nodoAVL *RD(nodoAVL *&);
nodoAVL *RI(nodoAVL *&);
nodoAVL *balance(nodoAVL *, int);
nodoAVL *crearNodoAVL(int);
nodoAVL *insertarAVL(nodoAVL *, int);
bool busquedaAVL(nodoAVL *, int);
nodoAVL *minimoAVL(nodoAVL *); nodoAVL *maximoAVL(nodoAVL *);
void destruirNodoAVL(nodoAVL *);
nodoAVL *eliminarNodoAVL(nodoAVL *, int);
void mostrar(nodoAVL *, int);
int contNodos(nodoAVL *); int sumNodos(nodoAVL *);
int contHojas(nodoAVL *); void mHojas(nodoAVL *);
void preOrdenAVL(nodoAVL *);
void inOrdenAVL(nodoAVL *);
void postOrdenAVL(nodoAVL *);
void abrirTxt(); void elimTxt();

//Prototipos de Diseño
int menuAVL(const char *, const char *[], int);
void letrasAVL(); 

nodoAVL *arbolAVL = NULL; //AVL
int Xa = 0;

/*-------------------------------------- ARBOL BINARIO BALANCEADO --------------------------------------*/

// Altura del arbol AVL
int altura(nodoAVL *N) {
	if (N == NULL)
		return 0;
	return N->altura;
}

//Rotar hacia la derecha 
nodoAVL *RD(nodoAVL *&p)
{
	nodoAVL *temp;
	temp = p->izquierdo;
	p->izquierdo = temp->derecho;
	temp->derecho = p;

	//Actualizar alturas
	p->altura = max(altura(p->izquierdo), altura(p->derecho)) + 1;
	temp->altura = max(altura(temp->izquierdo), p->altura) + 1;

	return temp;
}

//Rotar hacia la izquierda
nodoAVL *RI(nodoAVL *&p)
{
	nodoAVL *temp;
	temp = p->derecho;
	p->derecho = temp->izquierdo;
	temp->izquierdo = p;

	//Actualizar alturas
	p->altura = max(altura(p->izquierdo), altura(p->derecho)) + 1;
	temp->altura = max(altura(p->derecho), p->altura) + 1;

	return temp;
}

//Factor equilibrio del nodo N
int getBalance(nodoAVL *N) {
	if (N == NULL)
		return 0;
	return altura(N->izquierdo) - altura(N->derecho);
}

nodoAVL *balance(nodoAVL *temp, int facE) {
	//4 Casos de desvalanceo del AVL:

	// Caso izquierdo izquierdo 
	if (facE > 1 && getBalance(temp->izquierdo) >= 0) {
		SetColor(10); cout << "* ROTACION II "; SetColor(15);
		return RD(temp);
	}

	// Caso izquierdo derecho
	if (facE > 1 && getBalance(temp->izquierdo) < 0) {
		temp->izquierdo = RI(temp->izquierdo);
		SetColor(10); cout << "* ROTACION ID "; SetColor(15);
		return RD(temp);
	}

	// Caso derecho derecho 
	if (facE < -1 && getBalance(temp->derecho) <= 0) {
		SetColor(10); cout << "* ROTACION DD "; SetColor(15);
		return RI(temp);
	}

	// Caso derecho izquierdo
	if (facE < -1 && getBalance(temp->derecho) > 0) {
		temp->derecho = RD(temp->derecho);
		SetColor(10); cout << "* ROTACION DI "; SetColor(15);
		return RI(temp);
	}

	return temp;
}

//Funcion para crear un nuevo nodo 
nodoAVL* crearNodoAVL(int dato) {
	nodoAVL* nuevoNodo = (struct nodoAVL*)
		malloc(sizeof(struct nodoAVL));

	nuevoNodo->dato = dato;
	nuevoNodo->izquierdo = NULL;
	nuevoNodo->derecho = NULL;
	//altura de la raiz del arbol
	nuevoNodo->altura = 1;
	return(nuevoNodo);
}

//Funcion para insertar elementos en el arbol
nodoAVL *insertarAVL(nodoAVL* nodo, int dato) {

	if (nodo == NULL)
		return(crearNodoAVL(dato));
	//Si el elemento es menor, insertamos en la izq.
	if (dato < nodo->dato)
		nodo->izquierdo = insertarAVL(nodo->izquierdo, dato);
	//Si el elemento es mayor, insertamos en la der.
	else if (dato > nodo->dato)
		nodo->derecho = insertarAVL(nodo->derecho, dato);
	else // Los datos de valor igual no se aceptan
		return nodo;

	nodo->altura = 1 + max(altura(nodo->izquierdo),
		altura(nodo->derecho));

	//Obtener el factor de equilibrio para 
	//verificar si no se realizo un desvalanceo en el arbol
	nodo = balance(nodo, getBalance(nodo));

	return nodo;
}

//funcion para abrir un txt
void abrirTxt() {
	string arch, extension, x;
	string nomba, abrir;
	ifstream archivo;
	char cadena[100], resp;
	int dato;
	int contador = 0;
	int max = 0;
	string linea;
	char no[60] = { 'A', 'B', 'C','D','E','F','G','H','I','J','K','L','M','N','Ñ','O','P','Q','R','S','T','U','V','W','X','Y','Z',
		'a','b','c','d','e','f','g','h','i','j','k','l','m','n','ñ','o','p','q','r','s','t','u','v','w','x','y','z',',',' ','.',';' };//cadena de caracteres que no van a ingresarse al arbol

	char* token = (char*)malloc(sizeof(char));
	char* tok = (char*)malloc(sizeof(char));
	char num[10] = { '1', '2', '3', '4', '5', '6', '7', '8', '9', '0' };

	arch = "C:/Users/Evelyn/Desktop/"; //Dirección de donde se buscara el archivo
	extension = ".txt";//Extensión que abrira el archivo
	cout << "\t Archivo de donde desea extraer el arbol: ";
	cin >> nomba;
	abrir = arch + nomba + extension;
	archivo.open(abrir.c_str());

	if (archivo.is_open()) {
		while (!archivo.eof()) {
			while (getline(archivo, linea)) { //lectura de linea
				if (max == contador) {// max= numero de linea del archivo, contador= variable auxiliar para posicionarse e ingresar al condicional
					strcpy(cadena, linea.c_str()); //conversion de dato, haciendo que la cadena sea tipo string para ingresar lo que hay en la variable linea
					token = strtok(cadena, no); //Divide la cadena del archivo por los carecteres indeseados y los que se utilizaran y los ingresa a la variable token
					cout << "\n\t Desea mostrar la ingresion de los nodos paso a paso? (s/n): ";
					cin >> resp;
					cout << "\t Nodos Ingresados: ";
					while (token != NULL) {//se crea un ciclo que mientras token no este vacio se realizara el proceso
						if (token != NULL) {
							dato = atoi(token);//conversion de la variable token que es char a tipo entero

						}

						//Si la respuesta es s (si) se muestra paso a paso como se van ingresando los datos en el arbol
						if (resp == 's') {
							system("cls");
							for (int i = 1; i <= 50; i++) {
								gotoxy(58 + i, 1); cout << "=";
								gotoxy(58 + i, 3); cout << "=";
							}
							gotoxy(58, 2); cout << "|";
							gotoxy(109, 2); cout << "|";

							gotoxy(75, 2); cout << "INGRESANDO NODOS...";

							if (arbolAVL != NULL) {
								cuadro();
								gotoxy(7, 6); cout << "MOSTRANDO AVL ANTERIOR:";
								Xa = 20;
								mostrar(arbolAVL, -10);
								gotoxy(7, 27);
								arbolAVL = insertarAVL(arbolAVL, dato);
								gotoxy(7, 26); cout << "MOSTRANDO AVL ACTUALIZADO AL INSERTAR: ";
								SetColor(7); cout << dato; SetColor(15);
								Xa = 40; mostrar(arbolAVL, 10);
							}

							//Insertar y mostrar primer nodo 
							if (arbolAVL == NULL) {
								arbolAVL = insertarAVL(arbolAVL, dato);
								gotoxy(7, 6); cout << "INSERTANDO PRIMER NODO: " << dato;
								cuadro2();
								Xa = 20;
								mostrar(arbolAVL, -10);
							}
							_getch();
						}
						else {
							cout << token << " ";
							arbolAVL = insertarAVL(arbolAVL, dato);
						}
						token = strtok(NULL, no); //al momento que los parametros esten vacios, guarda la utlima cadena y palabra y lo devuelve y continua con la siguiente
					}

					if (resp == 'n') {
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
				}
				contador++; //incrementa el contador en caso se quisisera leer otra linea
			}
		}
		if (resp == 's') {
			gotoxy(9, 44); SetColor(10); cout << "Cadena de numeros cargada al arbol con exito!\n"; SetColor(15);
		}
		else {
			SetColor(10); cout << "\n\t Cadena de numeros cargada al arbol con exito!\n"; SetColor(15);
		}
		archivo.close();
	}
	else {
		cout << "\n\t Error no se pudo abrir el archivo!\n";
	}
}

//Funcion para buscar un elemento en el arbol 
bool busquedaAVL(nodoAVL *arbolAVL, int n) {
	if (arbolAVL == NULL) { //si el arbol esta vacio
		return false;
	}
	else if (arbolAVL->dato == n) {//si el nodo es igual al elemento
		return true;
	}
	else if (n<arbolAVL->dato) { //si el nodo es menor al elemento entonces busca por la izquierda
		return busquedaAVL(arbolAVL->izquierdo, n);
	}
	else if (n>arbolAVL->dato) { //Si el nodo es mayor al elemento entonces busca por la derecha
		return busquedaAVL(arbolAVL->derecho, n);
	}
}

//ELIMINACION
void mostrarActualizado(nodoAVL *arbolAVL, int dato) {

	for (int i = 1; i <= 50; i++) {
		gotoxy(58 + i, 1); cout << "=";
		gotoxy(58 + i, 3); cout << "=";
	}
	gotoxy(58, 2); cout << "|";
	gotoxy(109, 2); cout << "|";
	gotoxy(75, 2); cout << "ELIMINANDO NODOS...";

	gotoxy(7, 6); cout << "MOSTRANDO AVL ANTERIOR:";
	Xa = 10; mostrar(arbolAVL, -10);

	//Busca el nodo antes de llamar a la funcion eliminar para verificar que el nodo si existe en el arbol
	if (busquedaAVL(arbolAVL, dato) == true) {
		cuadro();
		gotoxy(7, 27);
		arbolAVL = eliminarNodoAVL(arbolAVL, dato);
		gotoxy(7, 26); cout << "MOSTRANDO AVL ACTUALIZADO AL ELIMINAR: " << dato;
		Xa = 30; mostrar(arbolAVL, 10);
	}
	else
	{	//Si el nodo no se encuentra muestra un mensaje de error
		cuadro2();
		gotoxy(7, 7); SetColor(12); cout << "*El nodo " << dato << " no se encuentra en el arbol"; SetColor(15);
	}

	_getch();
}

void elimTxt() {
	string local, ext, arb;
	ifstream arch; //poder abrir un fichero para leerlo
	int cont = 0;//variable auxiliar para posicionarse en la linea a leer
	int max = 1;//segunda linea del archivo
	int dato;
	int i = 0, j = 0;
	char cadena[100];
	string linea;
	//Cadena de caracteres que se deben de omitir a la hora de leer el archivo
	char no[60] = { 'A', 'B', 'C','D','E','F','G','H','I','J','K','L','M','N','Ñ','O','P','Q','R','S','T','U','V','W','X','Y','Z',
		'a','b','c','d','e','f','g','h','i','j','k','l','m','n','ñ','o','p','q','r','s','t','u','v','w','x','y','z',',',' ','.',';' };

	char* token = (char*)malloc(sizeof(char));

	local = "C:/Users/Evelyn/Desktop/"; //Dirección de donde se buscara el archivo
	ext = ".txt"; //extension del archivo
	gotoxy(5, 6); cout << "Archivo donde desea eliminar nodos: ";
	cin >> arb;
	abrir = local + arb + ext;
	arch.open(abrir.c_str());

	//Si el archivo se encuentra abierto
	if (arch.is_open()) {
		while (!arch.eof()) { //Mientras no se haya llegado al final del archivo
			while (getline(arch, linea)) {
				if (max == cont) {
					//conversion de dato, haciendo que la cadena sea tipo string para ingresar lo que hay en la variable linea
					strcpy(cadena, linea.c_str());
					//Divide la cadena del archivo por los carecteres indeseados y los que se utilizaran y los ingresa a la variable token
					token = strtok(cadena, no);
					while (token != NULL) {//se crea un ciclo que mientras token no este vacio se realizara el proceso
						if (token != NULL) {
							dato = atoi(token);//Conversion de la variable ´token a int
						}
						system("cls");
						mostrarActualizado(arbolAVL, dato);
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

//Funcion para determinar el nodo mas izquierdo posible
nodoAVL *minimoAVL(nodoAVL* arbolAVL) {
	if (arbolAVL == NULL) {
		return NULL;
	}

	if (arbolAVL->izquierdo) { //si tiene hijo izquierdo
							   //buscamos la parte mas izq posible 
		return minimoAVL(arbolAVL->izquierdo);
	}
	else { //si no tiene hijo izq
		return arbolAVL; //retornamos al mismo nodo
	}
}

//Funcion para determinar el nodo mas derecho posible
nodoAVL *maximoAVL(nodoAVL *arbolAVL) {
	if (arbolAVL == NULL) {
		return NULL;
	}

	if (arbolAVL->derecho) { //si tiene hijo derecho
							 //buscamos la parte mas derecha posible 
		return maximoAVL(arbolAVL->derecho);
	}
	else { //si no tiene hijo derecho
		return arbolAVL; //retornamos al mismo nodoAVL
	}
}

//Funcion para destruir un nodo
void destruirNodoAVL(nodoAVL *nodo) {
	nodo->izquierdo = NULL;
	nodo->derecho = NULL;

	delete nodo; //elimina el nodo
}

//Funcion para eliminar el nodo encontrado
nodoAVL *eliminarNodoAVL(nodoAVL* arbolAVL, int dato) {
	if (arbolAVL == NULL)
		return arbolAVL;
	//Si el dato a eliminar es menor entonces busca el dato por la izquierda
	if (dato < arbolAVL->dato)
		arbolAVL->izquierdo = eliminarNodoAVL(arbolAVL->izquierdo, dato);
	//Si el dato a eliminar es mayor entonces busca el dato por la derecha
	else if (dato > arbolAVL->dato)
		arbolAVL->derecho = eliminarNodoAVL(arbolAVL->derecho, dato);

	else//si se encuentra el valor
	{
		// nodo con un hijo o sin hijos (nodo hoja)
		if ((arbolAVL->izquierdo == NULL) || (arbolAVL->derecho == NULL)) {
			struct nodoAVL *temp = arbolAVL->izquierdo ? arbolAVL->izquierdo :
				arbolAVL->derecho;

			// Nodo hoja
			if (temp == NULL)
			{
				temp = arbolAVL;
				arbolAVL = NULL;
			}
			else // Nodo con un hijo (izquierdo o derecho)
				*arbolAVL = *temp; // Remplaza el valor por el de su hijo

			destruirNodoAVL(temp);// elimina el nodo
		}
		else //Si el nodo tiene hijo izq y der
		{
			int opcion;
			nodoAVL* menor; nodoAVL* mayor;

			gotoxy(110, 26); cout << "Eliminar " << dato
				<< " por Derecha(1) / Izquierda(2): "; cin >> opcion;

			switch (opcion) {
			case 1://El nodo a eliminar se sustiuye por el nodo que se 
				   //encuentra más a la izq del subarbol der
				menor = minimoAVL(arbolAVL->derecho);
				arbolAVL->dato = menor->dato;
				arbolAVL->derecho = eliminarNodoAVL(arbolAVL->derecho, menor->dato);
				break;
			case 2://El nodo a eliminar se sustiuye por el nodo que se encuentra 
				   //más a la der del subarbol izq
				mayor = maximoAVL(arbolAVL->izquierdo);
				arbolAVL->dato = mayor->dato;
				arbolAVL->izquierdo = eliminarNodoAVL(arbolAVL->izquierdo, mayor->dato);
				break;
			default:
				gotoxy(110, 27);
				SetColor(12); cout << "Opcion no valida! Error al Eliminar el nodo " << arbolAVL->dato << endl;
				SetColor(15);
				break;
			}
		}
	}

	// Si el arbol solo tenia un nodo entonces retorna
	if (arbolAVL == NULL)
		return arbolAVL;

	//Actualiza la altura del nodo actual
	arbolAVL->altura = 1 + max(altura(arbolAVL->izquierdo), altura(arbolAVL->derecho));
	arbolAVL = balance(arbolAVL, getBalance(arbolAVL));//obtiene el balance de este nodo para verificar 
													   //si no de produjo un desvalanceo en el AVL

	return arbolAVL;
}

//Funcion que cuenta  los nodos que hay en el arbol
int contNodos(nodoAVL *arbolAVL) {
	if (arbolAVL == NULL) {
		return 0;
	}
	else {
		return 1 + contNodos(arbolAVL->izquierdo)
			+ contNodos(arbolAVL->derecho);
	}
}

//Funcion que cuenta los nodos terminales
int contHojas(nodoAVL *arbolAVL) {
	if (arbolAVL == NULL)
		return 0;

	if (arbolAVL->izquierdo == NULL && arbolAVL->derecho == NULL) {
		return 1;
	}
	else {
		return contHojas(arbolAVL->izquierdo) +
			contHojas(arbolAVL->derecho);
	}
}

void mHojas(nodoAVL *arbolAVL) {
	if (arbolAVL == NULL)
		return;

	//Si el nodo no tiene hijo derecho ni izquierdo entonces es un nodo hoja
	if (arbolAVL->izquierdo == NULL && arbolAVL->derecho == NULL)
		cout << arbolAVL->dato << " ";

	mHojas(arbolAVL->derecho);
	mHojas(arbolAVL->izquierdo);
}

//Suma el valor del dato que se encuentra almacenado en cada nodo
int sumNodos(nodoAVL *arbolAVL) {
	if (arbolAVL == NULL)
		return 0;
	else {
		return arbolAVL->dato +
			sumNodos(arbolAVL->derecho) + sumNodos(arbolAVL->izquierdo);
	}
}

//RECORRIDOS
void preOrdenAVL(nodoAVL *arbolAVL) {
	if (arbolAVL == NULL) {
		return;
	}
	else {
		/*Visita la raiz
		Recorre el subarbol izquierdo
		Recorre el subarbol derecho*/
		cout << arbolAVL->dato << "  ";
		preOrdenAVL(arbolAVL->izquierdo);
		preOrdenAVL(arbolAVL->derecho);
	}
}

void inOrdenAVL(nodoAVL *arbolAVL) {
	if (arbolAVL == NULL) {
		return;
	}
	else {
		/*Recorre el suarbol izquierdo
		Visita la raiz
		Recorre el subarbol derecho*/
		inOrdenAVL(arbolAVL->izquierdo);
		cout << arbolAVL->dato << "  ";
		inOrdenAVL(arbolAVL->derecho);
	}
}

void postOrdenAVL(nodoAVL *arbolAVL) {
	if (arbolAVL == NULL) {
		return;
	}
	else {
		/*Recorre el subarbol izquierdo
		Recorre el subarbol derecho
		Visitia la raiz*/
		postOrdenAVL(arbolAVL->izquierdo);
		postOrdenAVL(arbolAVL->derecho);
		cout << arbolAVL->dato << "  ";
	}
}


void mostrar(nodoAVL *arbolAVL, int Y) {
	if (arbolAVL == NULL) {
		return;
	}

	Xa += 5;//variable que permite posicionarse en el eje X
	mostrar(arbolAVL->izquierdo, Y + 2);//Se para hasta el nodoAVL mas a la izquierda del árbol construye primero el subarbol izq porque sus valores en X son menores
	gotoxy(10 + Xa - Y, 18 + Y);//posiciona el nodoAVL segun sus variables en X y en Y
	cout << "[" << arbolAVL->dato << "]" << endl;//Muestra el dato del nodoAVL respectivo
	mostrar(arbolAVL->derecho, Y + 2);//Se para hasta el nodoAVL mas a la derecho del árbol
}


//DISEÑO
void letrasAVL() {
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

	//Letra V
	for (int i = 1; i <= 9; i++) {
		gotoxy(105 + i, i + 3); SetColor(0); cout << "*"; SetColor(15);
		gotoxy(106 + i, i + 3); SetColor(0); cout << "*"; SetColor(15);
		gotoxy(107 + i, i + 3); SetColor(0); cout << "*"; SetColor(15);
		gotoxy(108 + i, i + 3); SetColor(0); cout << "*"; SetColor(15);
		gotoxy(125 - i, i + 3); SetColor(0); cout << "*"; SetColor(15);
		gotoxy(124 - i, i + 3); SetColor(0); cout << "*"; SetColor(15);
		gotoxy(123 - i, i + 3); SetColor(0); cout << "*"; SetColor(15);
		gotoxy(126 - i, i + 3); SetColor(0); cout << "*"; SetColor(15);
	}

	//Letra L
	for (int i = 1; i <= 9; i++) {
		gotoxy(127, i + 3); SetColor(0); cout << "*"; SetColor(15);
		gotoxy(128, i + 3); SetColor(0); cout << "*"; SetColor(15);
		gotoxy(129, i + 3); SetColor(0); cout << "*"; SetColor(15);
		gotoxy(130, i + 3); SetColor(0); cout << "*"; SetColor(15);
	}

	for (int i = 1; i <= 10; i++) {
		gotoxy(129 + i, 10); SetColor(0); cout << "*"; SetColor(15);
		gotoxy(129 + i, 11); SetColor(0); cout << "*"; SetColor(15);
		gotoxy(129 + i, 12); SetColor(0); cout << "*"; SetColor(15);
	}
}
void mostrarRecorridos2() {

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

	gotoxy(10, 8); SetColor(10); cout << "Pre-Orden: "; SetColor(15); preOrdenAVL(arbolAVL);
	gotoxy(10, 10); SetColor(10); cout << "In-Orden: "; SetColor(15); inOrdenAVL(arbolAVL);
	gotoxy(10, 12); SetColor(10); cout << "Post-Orden: "; SetColor(15); postOrdenAVL(arbolAVL);

}

int menuAVL(const char *titulo, const char *opciones[], int n) {
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

		letrasAVL();

		gotoxy(25, 5 + OpSelect); SetColor(10); cout << "===>"; SetColor(15);
		gotoxy(37, 3); cout << titulo;

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

int mainAVL()
{
	int dato, opcion, contador = 0;
	bool repite = true;
	char resp;

	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE); //Maximiza la pantalla
	system("color 1F");
	ocultarcursor();

	const char *titulo = "MENU ARBOL BALANCEADO";
	const char *opciones[] = { "Generar nuevo arbol con un txt", "Mostrar AVL Grafico y Recorridos",
		"Eliminar Nodos del Arbol", "Buscar Nodo", "Contar Nodos", "Contar Hojas", "Sumar Nodos", "Regresar" };
	int n = 8; //Numero de opciones 

	do
	{
		opcion = menuAVL(titulo, opciones, n);
		cout << "\n\n\n\n";

		switch (opcion)
		{
		case 1:
			arbolAVL = NULL;
			abrirTxt();
			cout << "\t "; system("pause");
			break;
		case 2:
			if (arbolAVL == NULL) {
				SetColor(12); cout << "\n\t El arbol se encuentra vacio!\n\n"; SetColor(15);
			}
			else {
				system("cls");
				mostrarRecorridos2();
				for (int i = 1; i <= 38; i++) {
					gotoxy(9 + i, 16); cout << "*";
					gotoxy(9 + i, 18); cout << "*";
				}

				gotoxy(9, 17); cout << "|";
				gotoxy(48, 17); cout << "|";
				gotoxy(15, 17); cout << "MOSTRANDO ARBOL BALANCEADO..";
				Xa = 0;
				mostrar(arbolAVL, 3);
			}
			_getch();
			break;
		case 3:
			if (arbolAVL == NULL) {
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
				elimTxt();
			}
			_getch();
			break;
		case 4:
			if (arbolAVL == NULL) {
				SetColor(12); cout << "\n\t El arbol se encuentra vacio!\n\n"; SetColor(15);
			}
			else {
				cout << "\t Ingrese el elemento a buscar: "; cin >> dato;
				if (busquedaAVL(arbolAVL, dato) == true) {
					SetColor(10); cout << "\t Elemento " << dato << " a sido encontrado en el arbol AVL\n";
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
			if (arbolAVL == NULL) {
				SetColor(12); cout << "\n\t El arbol se encuentra vacio!\n\n"; SetColor(15);
			}
			else {
				int cnodo;
				cnodo = contNodos(arbolAVL);
				gotoxy(10, 19); cout << "La cantidad de nodos en el ABB es : ";
				SetColor(11); cout << cnodo; SetColor(15);
				for (int i = 1; i <= 38; i++) {
					gotoxy(10 + i, 21); cout << "*";
					gotoxy(10 + i, 23); cout << "*";
				}

				gotoxy(10, 22); cout << "|";
				gotoxy(49, 22); cout << "|";
				gotoxy(16, 22); cout << "MOSTRANDO ARBOL BALANCEADO..";
				Xa = 0; mostrar(arbolAVL, 7);
			}
			_getch();
			break;

		case 6:
			if (arbolAVL == NULL) {
				SetColor(12); cout << "\n\t El arbol se encuentra vacio!\n\n"; SetColor(15);
			}
			else {
				int hojas;
				hojas = contHojas(arbolAVL);
				gotoxy(10, 19); cout << "El numero de nodos hojas es: ";
				SetColor(11); cout << hojas; SetColor(15);
				gotoxy(10, 20); cout << "Los nodos Hojas son: ";
				SetColor(11); mHojas(arbolAVL); SetColor(15);
				for (int i = 1; i <= 38; i++) {
					gotoxy(10 + i, 22); cout << "*";
					gotoxy(10 + i, 24); cout << "*";
				}

				gotoxy(10, 23); cout << "|";
				gotoxy(49, 23); cout << "|";
				gotoxy(16, 23); cout << "MOSTRANDO ARBOL BALANCEADO..";

				Xa = 0; mostrar(arbolAVL, 8);
			}
			_getch();
			break;
		case 7:
			if (arbolAVL == NULL) {
				SetColor(12); cout << "\n\t El arbol se encuentra vacio!\n\n"; SetColor(15);
			}
			else {
				int sum;
				sum = sumNodos(arbolAVL);
				gotoxy(10, 19); cout << "La suma de los nodos es: ";
				SetColor(11); cout << sum; SetColor(15);

				for (int i = 1; i <= 38; i++) {
					gotoxy(10 + i, 21); cout << "*";
					gotoxy(10 + i, 23); cout << "*";
				}

				gotoxy(10, 22); cout << "|";
				gotoxy(49, 22); cout << "|";
				gotoxy(16, 22); cout << "MOSTRANDO ARBOL BALANCEADO..";
				Xa = 0; mostrar(arbolAVL, 7);
			}
			_getch();
			break;
		case 8:
			repite = false;
			break;
		}
	} while (repite);
	system("color 9F");
	return 0;
}

#endif