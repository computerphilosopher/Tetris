#include <iostream>
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
};

class Vector2D : public Point {
private:
public:
	Vector2D() {}
	Vector2D(int x, int y) {
		Set(x, y);
	}
	Vector2D operator + (Vector2D op) {
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
	const Vector2D DOWN;
	const Vector2D RIGHT;
	const Vector2D LEFT;

public:

	Tetrimino() : DOWN(0, 1), RIGHT(1, 0), LEFT(-1, 0) {}

	Tetrimino(int block) : DOWN(0, 1), RIGHT(1, 0), LEFT(-1, 0) {
		switch (block) {
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
	}

	void Update() {

		for (int i = 0; i < POINT_COUNT; i++) {
			position[i] = position[i] + DOWN;
		}

	}

	vector<Point> GetCoordinate() {
		vector<Point> temp;
		for (int i = 0; i < POINT_COUNT; i++) {
			temp.push_back ((Point)position[i]);
			//cout << "(" <<temp[i].GetX() << "," <<temp[i].GetY() << ")" << endl;
		}
		return temp;
	}

};

class Renderer{
private:
public:
	Renderer() {
	}
	~Renderer() {}

	void Update() {
	}
	void Render(GameObject &g) {
		
		vector<Point> coordinate = g.GetCoordinate();

		for (int i = 0; i < POINT_COUNT; i++) {
			gotoxy(coordinate[i].GetX(), coordinate[i].GetY());
			//cout << "(" << coordinate[i].GetX() << "," << coordinate[i].GetY() << ")" << endl;
			cout << "a" ;
		}

	}
	void gotoxy(int x, int y)
	{
		COORD pos = { x, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	}
};

int main() {

	Vector2D a(2, 5);
	Vector2D b(3, 5);
	Tetrimino t(J_BLOCK);

	Renderer r;
	r.Render(t);

	Sleep(1000);
	t.Update(); t.Update();

	r.Render(t);

}