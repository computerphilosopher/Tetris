#include <iostream>
#include <vector>
#include <windows.h>

using namespace std;

const int POINT_COUNT = 4;

enum CanvasSize {
	WIDTH = 40,
	HEIGHT = 30
};
enum BlockCode {
	I_BLOCK,
	O_BLOCK,
	T_BLOCK,
	J_BLOCK,
	L_BLOCK,
	S_BLOCK,
	Z_BLOCK,
	RANDOM
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

		Vector2D rotated(GetX(), GetY());	
		rotated = rotated - origin;
		rotated.Set(-rotated.GetY(), rotated.GetX());

		rotated = rotated + origin;
		
		return rotated;
	}
	
};

class Tetrimino{
private:
	vector<Vector2D> position;
	int blockType;
	Vector2D origin;
	const Vector2D DOWN;
	const Vector2D RIGHT;
	const Vector2D LEFT;

public:

	Tetrimino() : DOWN(0, 1), RIGHT(1, 0), LEFT(-1, 0) {}

	~Tetrimino() { cout << "Destoryed" << endl; }

	Tetrimino(int blockType) : DOWN(0, 1), RIGHT(1, 0), LEFT(-1, 0) {

		this->blockType = blockType;
		origin = Vector2D(1, 1);

		switch (blockType){
		case I_BLOCK:
			origin = Vector2D(2, 2);
			for (int i = 0; i < POINT_COUNT; i++) {
				position[i] = Vector2D(i, 1);
			}
			break;
		case O_BLOCK:
			position[0] = Vector2D(0, 1); position[1] = Vector2D(0, 2);
			position[2] = Vector2D(1, 1); position[3] = Vector2D(1, 2);
			break;
		case T_BLOCK:
			position[0] = Vector2D(0, 1); position[1] = Vector2D(1, 0);
			position[2] = Vector2D(1, 1); position[3] = Vector2D(1, 2);
			break;
		case J_BLOCK:
			position[0] = Vector2D(0, 0); position[1] = Vector2D(1, 0);
			position[2] = Vector2D(1, 1); position[3] = Vector2D(1, 2);
			break;
		case L_BLOCK:
			position[0] = Vector2D(0, 3); position[1] = Vector2D(1, 0);
			position[2] = Vector2D(1, 1); position[3] = Vector2D(1, 2);
			break;
		case Z_BLOCK:
			position[0] = Vector2D(0, 0); position[1] = Vector2D(0, 1);
			position[2] = Vector2D(1, 1); position[3] = Vector2D(1, 2);
			break;
		case S_BLOCK:
			position[0] = Vector2D(0, 1); position[1] = Vector2D(0, 2);
			position[2] = Vector2D(1, 0); position[3] = Vector2D(1, 1);
			break;
		default:
			cout << "wrong block type" << endl;
			break;
		}

		origin = origin + RIGHT;

		for (int i = 0; i < POINT_COUNT; i++) {
			position[i] = position[i] + RIGHT;
			position[i] = position[i] + DOWN;
		}

	}

	void Control() {
		for (int i = 0; i < POINT_COUNT; i++) {
			position[i] = position[i] + RIGHT;
		}
	}
	
	void Rotate() {
		
		for (int i = 0; i < POINT_COUNT; i++) {
			position[i] = position[i].Rotate90(origin);
		}

	}

	vector<Vector2D> GetCoordinate() {
		return position;
	}
};

class Board{
private:
	vector< vector<bool> > Grid;

public:
	Board(){
		Grid = vector< vector<bool> >(WIDTH);
		for (int i = 0; i < WIDTH; i++) {
			for (int j = 0; j < HEIGHT; j++) {
				Grid[i].push_back(false);
			}
		}
	}

	bool IsWall(vector<Vector2D> &tetrimino){  

		for (int i = 0; tetrimino.size(); i++) {
			if (tetrimino[i].GetX() >= WIDTH || 
				tetrimino[i].GetX() <= 0) {
				return true;
			}
		}
		return false;	
	} 
	bool IsLand(vector<Vector2D> &tetrimino ) {
		for (int i = 0; tetrimino.size(); i++) {
			if (tetrimino[i].GetY() >= HEIGHT ||
				Grid[tetrimino[i].GetX()][tetrimino[i].GetY()]) {
				return true;
			}
		}
		return false;
	}

	vector < vector <bool> > GetCoordinate() {
		return Grid;
	}

	~Board() {}

};

class Renderer {
private:
	vector <Vector2D> tetriminoPosition;
	vector < vector <bool> > boardGrid;
public:
	Renderer() {
		
	}
	~Renderer() {}

	void Update(Tetrimino tetrimino, Board board) {
		this->tetriminoPosition = tetrimino.GetCoordinate();
		this->boardGrid = board.GetCoordinate();
		
	}

	void Render() {

		system("cls");
		
		for (int i = 0; i < POINT_COUNT; i++) {
			gotoxy(tetriminoPosition[i].GetX(), tetriminoPosition[i].GetY());
			cout << "#";
		}

		gotoxy(0, CanvasSize::HEIGHT);
		
		for (int i = 0; i < POINT_COUNT; i++) {
			cout << "(" << tetriminoPosition[i].GetX() << "," << tetriminoPosition[i].GetY() << ")" << endl;
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


int main() {

	Tetrimino t(I_BLOCK);

	Renderer r;
	Board board;

	for (int i = 0; i < 100; i++) {
		t.Control();
		r.Update(t, board);
		r.Render();

		Sleep(100);
	}

	r.Render();
}