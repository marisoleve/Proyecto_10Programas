#pragma once
#ifndef _DISEÑO_H_
#define _DISEÑO_H_

#include <iostream>
#include <windows.h>

#define TECLA_ARRIBA 72
#define TECLA_ABAJO 80
#define ENTER 13

using namespace std;

void gotoxy(int x, int y) {
	HANDLE hcon;
	hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	SetConsoleCursorPosition(hcon, dwPos);
}

void ocultarcursor() {
	HANDLE hCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 1;
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(hCon, &cci);
}

void SetColor(char ForgC) {
	WORD wColor;

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	if (GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
		wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
		SetConsoleTextAttribute(hStdOut, wColor);
	}
	return;
}

void cuadro() {
	for (int i = 1; i <= 158; i++) {
		gotoxy(4 + i, 4); cout << "_";
		gotoxy(4 + i, 24); cout << "_";
		gotoxy(4 + i, 43); cout << "_";
	}

	for (int i = 1; i <= 39; i++) {
		gotoxy(163, 4 + i); cout << "|";
		gotoxy(4, 4 + i); cout << "|";
	}
}
void cuadro2() {
	for (int i = 1; i <= 158; i++) {
		gotoxy(4 + i, 4); cout << "_";
		gotoxy(4 + i, 24); cout << "_";
	}

	for (int i = 1; i <= 20; i++) {
		gotoxy(163, 4 + i); cout << "|";
		gotoxy(4, 4 + i); cout << "|";
	}
}
#endif