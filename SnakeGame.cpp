// SnakeGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <conio.h>
#include <Windows.h>

using namespace std;
bool gameOver;
const int width = 30;
const int height = 16;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;

enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };

eDirection dir;

void setup() {
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruitX = (rand() % (width - 1)) + 1;
	fruitY = (rand() % (height - 1)) + 1;
	score = 0;
}

void draw() {
	system("cls");
	for (int i = 0; i < width; i++)
		cout << "#";
	cout << endl;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0 || j == (width - 1))
				cout << "#";
			else if (j == x && i == y)
				cout << "0";
			else if (j == fruitX && i == fruitY)
				cout << "@";
			else
			{
				bool print = false;
				for (int k = 0; k < nTail; k++) {
					
					if (tailX[k] == j && tailY[k] == i) {
						cout << "o";
						print = true;
					}
				}

				if(!print)
				cout << " ";
			}

		}
		cout << endl;
	}

	for (int i = 0; i < width; i++)
		cout << "#";
	cout << endl;
	cout << "Score: " << score << endl;
}

void input() {
	if (_kbhit()) {
		switch (_getch()) {
		case 'a':
			dir = LEFT;
			break;
		case'd':
			dir = RIGHT;
			break;
		case'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			gameOver = true;
		}
	}
}

void logic() {
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++) {
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}

	switch (dir) {
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}
	if (x == width || x == 0 || y == height || y == 0)
		gameOver = true;
	for(int i = 0; i < nTail; i++) {
		if (tailX[i] == x && tailY[i] == y)
		gameOver = true;
	}
	if (x == fruitX && y == fruitY) {
		score++;
		fruitX = (rand() % (width - 1)) + 1;
		fruitY = (rand() % (height - 1)) + 1;
		nTail++;
	}
}

int main() {
	setup();
	while (!gameOver) {
		draw();
		input();
		logic();
		if (dir == UP || dir == DOWN)
			Sleep(40);
		else
			Sleep(20);
	}
}


