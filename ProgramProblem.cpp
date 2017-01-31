// Labirynt.cpp : Defines the entry point for the console application.
//Read Me
/*
PL
Program znajduj�cy najkr�tsz� �cie�k� w labiryncie gdy do wyj�cia jest tylko jedna droga oraz wyj�cie z labiryntu
gdy jest wiele dr�g.

Format pliku txt z labiryntem w pierwszej lini powinien zawiera� liczbe wierszy labiryntu
za� w drugiej lini liczbe kolumn labiryntu. Nast�pnie sam labirynt gdzie:
S - punkt startowy
W - punk wyj�ciowy
# - �ciany
. - dozwolona scie�ka
Plik musi zosta� zapisany pod nazw�: labirynt.txt.

Wyj�ciem programu jest plik solved_lab.txt gdzie zostaje zapisany rozwi�zany labirynt.

Przyk�adowy labirynt na samym dole pliku.

ENG
Program to finding shortest way in a maze when exist only one way to exit or path to exit when exist many ways to exit.
Format txt file with the maze:
In first line number of rows where defined maze
Second line number of columns where definde maze
And next lanes a maze where:
S - Start point
W - End point (exit)
# - wall ( not allowed area)
. - paths (allowed area)
File must be saved with this name: labirynt.txt

Output of this program is solved_lav.txt file where you find solved maze with path to exit.

Example of maze on the end of this file

------------ History -------------------------
29.12.2016 - Jakub Szczepek - Initial Release

*/

#include "stdafx.h"
#include <string>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <queue>
#include <Windows.h>

using namespace std;

int row, col, start_row, start_col, end_row, end_col, steps = 0, path_r, path_c;  // zmienne globalne global variables

string **LoadLab();	// Funkcja wczytuj�ca labirynt z pliku txt. Function to load maze from txt file
void     ShowLab(string ** lab); // Funkcja wypisuj�ca labirynt na ekranie. Function to write the maze on the screen.
void	 SetPoint(string ** lab); // Funkcja szukaj�ca punktu startu i ko�ca. Function to finding start and end point in the maze.
string **SearchExit(string ** lab); // Funkcja do znalezienia wyj�cia. Function to finding exit of maze.
string **GeneratePath(string **lab); // Funkcja do wygenerowania �cie�ki. This function generate path from start to exit.
string **ClearLab(string **lab); // Funkcja do usuni�cia pozosta�o�ci z znajdywania �cie�ki. Function to clearing maze with useless data.
void	 SaveLab(string **lab); // Funkcja do zapisu labiryntu ze znale�ion� �cie�ka do pliku txt. Function to saving solved maze to txt file.
void     changecolor(int number_color); // Funkcja do zmienia koloru czcionki w consoli. Function to changing color of font in comand window.

int main()
{
	string **lab = LoadLab(); // Wczytanie labiryntu. Loading maze.
	cout << "\nProblem do rozwiazania: " << endl;
	ShowLab(lab); // Wypisanie. Write maze on screen.
	SaveLab(lab);
	SetPoint(lab); // Znalzezienie pkt. startu i ko�ca. Finding the start and and point.
	string **Lab_w_Exit = SearchExit(lab); // Szukanie Wyj�cia. Searching exit. 
	cout << "\n Przeanalizowany Labirynt: " << endl;
	ShowLab(Lab_w_Exit); // Wypisanie. Write maze on screen.
	SaveLab(Lab_w_Exit);
	string **Lab_w_Path = GeneratePath(Lab_w_Exit); // Generacja �cie�ki. Generating path from start to exit.
	cout << "\n Rozwiazany Labirynt: " << endl;
	ShowLab(Lab_w_Path); // Wypisanie. Write maze on screen.
	SaveLab(Lab_w_Path);
	string **CLab = ClearLab(Lab_w_Path); // Czysczenie labiryntu. Clear useless data.
	cout << "\n Rozwiazany Labirynt z wyznaczona sciezka: " << endl;
	ShowLab(CLab); // Wypisanie. Write maze on screen.
	cout << "\n Dlugosc drogi: " << steps << endl;
	SaveLab(CLab);
	getchar();
	getchar();
	return 0;
}


void SaveLab(string **lab) // Funkcja do zapisu labiryntu ze znale�ion� �cie�ka do pliku txt. Function to saving solved maze to txt file.
{
	ofstream plik;
	plik.open("solved_lab.txt", ios::out | ios::app); // Output filename
	plik << endl;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			plik << lab[i][j]<< " ";
		}
		plik << endl;
	}

	plik.close();
}


string **ClearLab(string **lab) // Funkcja do usuni�cia pozosta�o�ci z znajdywania �cie�ki. Function to clearing maze with useless data.
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (lab[i][j] == "D" || lab[i][j] == "U" || lab[i][j] == "L" || lab[i][j] == "R")
			{
				lab[i][j] = " "; //Swap direction signs to the space
			}

		}
	}
	return lab;
}

string **GeneratePath(string **lab) // Funkcja do wygenerowania �cie�ki. This function generate path from start to exit.
{

	string direction, one_step_back;
	if (lab[end_row][end_col] != ".")
	{
		int i = end_row;
		int j = end_col;
		int stop = 0;

		// Finding closest point with direction sign 
		while (true)
		{
			one_step_back = lab[end_row][end_col - 1];
			if (one_step_back == "#" || one_step_back == ".")
			{
				one_step_back = lab[end_row][end_col + 1];
			}
			else
			{
				j = j - 1;
				//cout << " 1 " << endl;
				break;
			}
			if (one_step_back == "#" || one_step_back == ".")
			{
				one_step_back = lab[end_row - 1][end_col];
			}
			else
			{
				j = j + 1;
				//cout << " 2 " << endl;
				break;
			}
			if (one_step_back == "#" || one_step_back == ".")
			{
				one_step_back = lab[end_row + 1][end_col];
			}
			else
			{
				i = i - 1;
				//cout << " 3 " << endl;
				break;
			}
			if (one_step_back == "#" || one_step_back == ".")
			{
				cout << " Z�A DEFINICJA WYJSCIA Z LABIRYNTU" << endl;
				break;
			}
			else
			{
				i = i + 1;
				//cout << " 4 " << endl;
				break;
			}
		}
		//cout << i << " BEFORE WHILE " << j << endl;

		// Generating path from exit to start
		while ((i != start_row) || (j != start_col))
		{
			direction = lab[i][j];
			
			lab[i][j] = "+";
			steps++;
			if (direction == "D")
			{
				i++;
			}
			if (direction == "U")
			{
				i--;
			}
			if (direction == "R")
			{
				j++;
			}
			if (direction == "L")
			{
				j--;

			}
			//ShowLab(lab);
			//Sleep(2000);
		}
		lab[end_row][end_col] = "W";
		cout << "\n Wykonanych krokow: " << steps << endl;
	}
	return lab;
}
string **SearchExit(string ** lab) // Funkcja do znalezienia wyj�cia. Function to finding exit of maze.
{
	queue < int > node;
	int row, col; // definicja indeksu wiersza i kolumny
	node.push(start_row); // umieszczenie w kolejce wiersza startu
	node.push(start_col); // umieszczenie w kolejce kolumny startu

	while (!node.empty())
	{
		row = node.front(); // pobranie wsp�rz�dnej wiersza
		node.pop(); // usuni�cie ws�rz�dnej wiersza
		col = node.front(); // pobranie ws�rz�dnej kolumny
		node.pop(); // usuni�cie wsp�rz�dnej kolumny

		// Sprawdzenie czy o�iagneli�my rozwi�zanie

		if ((row == end_row) && (col == end_col))
		{
			break;
		}

		// Przegl�damy s�siad�w bie��cego wierzcho�ka

		for (int i = -1; i <= 1; i++)
			for (int j = -1; j <= 1; j++)
				if ((i != j) && (!i || !j))
				{
					if (lab[row + i][col + j] == ".")
					{
						// Nadpisanie sk�d przybyli�my

						if (i == -1)      lab[row + i][col + j] = "D";  // z do�u
						else if (i == 1)  lab[row + i][col + j] = "U";  // z g�ry
						else if (j == -1) lab[row + i][col + j] = "R";  // z prawej
						else              lab[row + i][col + j] = "L";  // z lewej

						node.push(row + i);       // zapis wsp�rzednych do kolejki
						node.push(col + j);
					}
				}
	}

	return lab;
}

void ShowLab(string **lab) // Funkcja wypisuj�ca labirynt na ekranie. Function to write the maze on the screen.
{
	cout << endl;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (lab[i][j] == "+") changecolor(4);
			else if (lab[i][j] == "D" || lab[i][j] == "U" || lab[i][j] == "L" || lab[i][j] == "R") changecolor(2);
			else changecolor(7);
			cout << lab[i][j] << " ";
		}
		cout << endl;
	}
}

string **LoadLab() // Funkcja wczytuj�ca labirynt z pliku txt. Function to load maze from txt file
{
	ifstream plik;
	plik.open("labirynt.txt");
	plik >> row >> col;
	cout << "Wierszy: " << row << " Kolumn:  " << col << endl;
	string **Labirynt = new string *[row];
	string buff;

	for (int i = 0; i < row; i++)
	{
		plik >> buff;
		Labirynt[i] = new string[col];

		for (int j = 0; j < col; j++)
		{
			Labirynt[i][j] = buff[j];
		}
	}

	plik.close();
	return Labirynt;
}

void SetPoint(string **lab) // Funkcja szukaj�ca punktu startu i ko�ca. Function to finding start and end point in the maze.
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (lab[i][j] == "S")
			{
				start_row = i;
				start_col = j;
			}

			if (lab[i][j] == "W")
			{
				end_row = i;
				end_col = j;
			}
		}
	}

	cout << "Start x = " << start_row << " Start y = " << start_col << endl;
	cout << "End x = " << end_row << " End y = " << end_col << endl;
}

void changecolor(int number_color) // Funkcja do zmienia koloru czcionki w consoli. Function to changing color of font in comand window.
{
	HANDLE handle;
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, number_color);
}


/* Example of maze:
21
40
########################################
#S.##..#.....###.................##....#
##.#.....#.#...#.######.###..###.#..####
#..#.###.#.#.###.#....###.##.#.........#
##...#.###.#.#...#.#.##......###########
####.....###.#.###.#.#..#..#..#........#
#.....##.#...#.....#.##.#.############.#
#####..###.#########.#..#.#............#
#........#.#.........##.#.##.###.#####.#
#.###.##.#.#.#######..#.#..#.#.#.....#.#
#...#..#.#.#.#........#.####.#.#####.#.#
###.####.#.#.###.#.#..#......#.......#.#
#...#....#.#.....#######.#####.#####.#.#
###.#.#.##.#####.#.....#.......#.....#.#
#...###....###.#.#.#.#.###############.#
#.#...########.#.#.#.#.................#
###.#.#........#.#.#########.###########
#...#....#####.#.#...#.....#.......#...#
#.########...###.#.#.#.#####.#.###.#.###
#..........#.....#.#.........#...#....W#
########################################

*/