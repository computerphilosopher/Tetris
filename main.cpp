﻿#include <iostream>
#include <vector>
#include <windows.h>

using namespace std;

const int POINT_COUNT = 4;
enum BlockCode{
	I_BLOCK,
	O_BLOCK,
	T_BLOCK,
	J_BLOCK,
	L_BLOCK,
	S_BLOCK,
	Z_BLOCK,
};

enum KeyCode {
	W = 'w', S, A, D
};

class Point{
private:
	int x, y;

protected:
	
	void Set(int x, int y) {
		this->x = x;
		this->y = y;
	}

public:
	Point() {}

	Point(int x, int y) {
		this->x = x;
		this->y = y;
	}
int GetX(){
		return x;
	}
	int GetY(){
		return y;
	}
	bool operator == (Point op) {
		return (this->GetX() == op.GetX() && this->GetY() == op.GetY());
	}
	bool operator != (Point op) {
		return !(this->GetX() == op.GetX() && this->GetY() == op.GetY());
	}
};

class Vector2D : public Point {
private:
public:
	Vector2D() {}
	Vector2D(int x, int y) {
		Set(x, y);
	}
	Vector2D operator + (Vector2D op) {
		int old_x = this->GetX();
		int old_y = this->GetY();

		int adding_x = op.GetX();
		int adding_y = op.GetY();

		Vector2D temp;
		temp.Set(old_x + adding_x, old_y + adding_y);

		return temp;
	}

	Vector2D operator += (Vector2D op) {
		int before_x = this->GetX();
		int before_y = this->GetY();

		int adding_x = op.GetX();
		int adding_y = op.GetY();

		Vector2D temp;
		temp.Set(before_x + adding_x, before_y + adding_y);

		return temp;
	}

	Vector2D operator - (Vector2D op) {
		int before_x = this->GetX();
		int before_y = this->GetY();

		int sub_x = op.GetX();
		int sub_y = op.GetY();

		Vector2D temp;
		temp.Set(before_x - sub_x, before_y - sub_y);

		return temp;
	}

	void PrintVector() {
		cout << "x:" << GetX() << ", y:" << GetY() << endl;
	}

	Vector2D Rotate90(Vector2D origin) {

		Vector2D rotated(-(origin.GetY() - GetY()), origin.GetX() - GetX());	
		
		return rotated;
	}
	
};

class GameObject {
private:
public:
	GameObject() {

	}
	virtual ~GameObject() {}
	virtual void Update() = 0;
	virtual vector<Point> GetCoordinate() = 0;

};

class Tetrimino : public GameObject {
private:
	Vector2D position[POINT_COUNT];
	int blockType;
	Vector2D origin;
	const Vector2D DOWN;
	const Vector2D RIGHT;
	const Vector2D LEFT;

public:

	Tetrimino() : DOWN(0, 1), RIGHT(1, 0), LEFT(-1, 0) {}

	Tetrimino(int blockType) : DOWN(0, 1), RIGHT(1, 0), LEFT(-1, 0) {

		this->blockType = blockType;
		origin = Vector2D(0, 0);
		switch (blockType) {
		case I_BLOCK:
			for (int i = 0; i < POINT_COUNT; i++) {
				position[i] = Vector2D(i, 0);
			}
			break;
		case O_BLOCK:
			position[0] = Vector2D(0, 0); position[1] = Vector2D(0, 1);
			position[2] = Vector2D(1, 0); position[3] = Vector2D(1, 1);
			break;
		case T_BLOCK:
			position[0] = Vector2D(0, 0); position[1] = Vector2D(1, 0);
			position[2] = Vector2D(1, 1); position[3] = Vector2D(2, 0);
			break;
		case J_BLOCK:
			position[0] = Vector2D(0, 1); position[1] = Vector2D(1, 1);
			position[2] = Vector2D(2, 0); position[3] = Vector2D(2, 1);
			break;
		case L_BLOCK:
			position[0] = Vector2D(0, 1); position[1] = Vector2D(1, 1);
			position[2] = Vector2D(2, 1); position[3] = Vector2D(2, 2);
			break;
		case Z_BLOCK:
			position[0] = Vector2D(0, 0); position[1] = Vector2D(0, 1);
			position[2] = Vector2D(1, 1); position[3] = Vector2D(1, 2);
			break;
		case S_BLOCK:
			position[0] = Vector2D(0, 2); position[1] = Vector2D(0, 1);
			position[2] = Vector2D(1, 0); position[3] = Vector2D(1, 1);
			break;
		}

		for (int i = 0; i < POINT_COUNT; i++) {
			position[i] = position[i]+ RIGHT;
		    origin = origin + RIGHT;
		}
	}

	void Update() {

		for (int i = 0; i < POINT_COUNT; i++) {

			position[i] = position[i].Rotate90(origin);

		}
	
	}

	vector<Point> GetCoordinate() {
		vector<Point> temp;
		for (int i = 0; i < POINT_COUNT; i++) {
			temp.push_back((Point)position[i]);
			//cout << "(" <<temp[i].GetX() << "," <<temp[i].GetY() << ")" << endl;
		}
		return temp;
	}
};

class Renderer {
private:
	vector <Point> oldCoordinate;
	vector <Point> newCoordinate;
public:
	Renderer() {
		oldCoordinate = { Point(-1, -1), Point(-1, -1), Point(-1, -1), Point(-1, -1) };
	}
	~Renderer() {}

	void Update() {
	}

	void Render(GameObject &g) {

		newCoordinate = g.GetCoordinate();

		system("cls");
		
		for (int i = 0; i < POINT_COUNT; i++) {
			gotoxy(newCoordinate[i].GetX(), newCoordinate[i].GetY());
			cout << "#";
		}

	}
	void gotoxy(int x, int y)
	{
		COORD pos = { x, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	}

	void DeleteOldPoint(Point OldPoint) {
	}

};

class Collider {
private:
	
public:
	Collider() {};
	
	bool CollisionChecked() {}
};

int main() {

	Tetrimino t(T_BLOCK);

	Renderer r;

	for (int i = 0; i < 10; i++) {
		t.Update();
		r.Render(t);

		Sleep(800);
	}

	r.Render(t);
}