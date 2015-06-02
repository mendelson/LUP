#ifndef SRC_POINT_H_
#define SRC_POINT_H_

class Point {
public:
	float x;
	float y;

	Point();
	Point(float aux_x, float aux_y);
	void setX(float aux_x);
	void setY(float aux_y);
	float getX();
	float getY();
	float getDist(Point ponto);
	void somaPonto(Point ponto);
	float getInclinationFromTop();
	float getInclinationFromBottom();
	void vetMultEscalar(float esc);
	void rotateVector(float angle);
	void rotateVectorFromBottom(float angle);
	void negateVector();
	float magVector();

	Point operator+(const Point& rhs) const {
		return Point(x + rhs.x, y + rhs.y);
	}

	Point operator-(const Point& rhs) const {
		return Point(x - rhs.x, y - rhs.y);
	}

};

#endif /* SRC_POINT_H_ */
