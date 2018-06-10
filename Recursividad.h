#pragma once
#ifndef _RECURSIVIDAD_H_
#define _RECURSIVIDAD_H_

#include <iostream>
#include <stdio.h>
#include <conio.h>

using namespace std;

int potencia(int x, int n) {
	int aux;
	if (n == 0) {
		return 1;
	}
	else {
		aux = potencia(x, n / 2);
		if (n % 2 == 0)
			return aux * aux;
		else
			return x * aux*aux;
	}
}

void recu() {
	int numero, potenciar = 0;
	system("cls");
	cout << "Ingrese la el numero que desea elevar: \n";
	cin >> numero;
	cout << "Imgrese la potencia a la que lo elevara: \n";
	cin >> potenciar;
	cout << potencia(numero, potenciar);
	_getch();
}
int mainRec() {
	system("color 1F");
	recu();
	system("color 9F");
	return 0;
}

#endif // _RECURSIVIDAD_H_