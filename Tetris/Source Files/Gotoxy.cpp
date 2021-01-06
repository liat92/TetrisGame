#include <iostream>
using namespace std;

#include <windows.h>
#include <process.h>

/*
   Credit for this function goes to: Yoav  Aharoni
   [yoav_ah@netvision.net.il]
   function definition -- requires windows.h
*/
void gotoxy(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	cout.flush();
	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput,dwCursorPosition);
}

void clearScreen()
{
	system("cls");
}