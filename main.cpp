#include <iostream>
#include <vector>

using namespace std;

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
		temp.Set(sub_x + sub_x, sub_y + sub_y);
		
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
	virtual void GetCoordinate() = 0;	
};

int main() {

	Vector2D a(2, 5);
	Vector2D b(3, 5);

	Vector2D c = a + b;

	a.PrintVector();
	b.PrintVector();
	c.PrintVector();
	getchar();
}