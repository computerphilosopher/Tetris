#include <iostream>
#include <vector>

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

class Point{
private:
	int x, y;

protected:
	int GetX(){
		return x;
	}
	int GetY(){
		return y;
	}

public:
	Point(){}
	
	Point(int x, int y) {
		this->x = x;
		this->y = y;
	}
	void Set(int x, int y) {
		this->x = x;
		this->y = y;
	}
};

class Vector2D : private Point{
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
	virtual ~GameObject() = 0;	
	virtual void Update() = 0;	
	virtual vector<Point> GetPoint() = 0;

};

class Tetrimino : public GameObject {
private:
	Vector2D position[POINT_COUNT];
	const Vector2D DOWN;
	const Vector2D RIGHT;
	const Vector2D LEFT;

public:

	Tetrimino(): DOWN(0, 1), RIGHT(1, 0), LEFT(-1,0) {}
	
	Tetrimino(){
		DOWN(0, 1);
		RIGHT(0, 1);
	}
	
	Tetrimino(int block) : DOWN(0, 1), RIGHT(1, 0), LEFT(-1,0){
		switch(block){
		case I_BLOCK:
			for (int i = 0; i < POINT_COUNT; i++) {
				position[i] = Vector2D(i,0);
			}
			break;
		case O_BLOCK:
			position[0] = Vector2D(0, 0); position[1] = Vector2D(0, 1);
			position[2] = Vector2D(1, 0); position[3] = Vector2D(1, 1);
			break;
		case T_BLOCK:
			position[0] = Vector2D(0, 0); position[1] = Vector2D(1, 0);
			position[2] = Vector2D(2, 0); position[3] = Vector2D(1, 1);
			break;
		case J_BLOCK:
			position[0] = Vector2D(0, 1); position[1] = Vector2D(1, 1);
			position[2] = Vector2D(0, 2); position[3] = Vector2D(1, 2);
			break;
		case L_BLOCK:
			position[0] = Vector2D(0, 1); position[1] = Vector2D(1, 1);
			position[2] = Vector2D(2, 2); position[3] = Vector2D(1, 2);
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

	void Update(){

	}	

	vector<Point> GetPoint() {
		vector <Point> *temp = &position;
	}

};

int main() {

	Vector2D a(2, 5);
	Vector2D b(3, 5);
	Tetrimino t;

	getchar();
}