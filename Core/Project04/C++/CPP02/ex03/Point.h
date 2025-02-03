#pragma once

#include "Fixed.h"

class Point
{
private:
	const Fixed x;
	const Fixed y;
public:
	Point();
	Point(const Point& p);
	Point(const Fixed x, const Fixed y);
	Point& operator=(const Point& p);
	const Fixed& getX() const;
	const Fixed& getY() const;
	~Point();
};

bool bsp(Point const a, Point const b, Point const c, Point const point);
