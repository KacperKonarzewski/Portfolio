#include "Point.h"

float area(Point const *a, Point const *b, Point const *c)
{
	float x1 = a->getX().toFloat();
    float y1 = a->getY().toFloat();
    float x2 = b->getX().toFloat();
    float y2 = b->getY().toFloat();
    float x3 = c->getX().toFloat();
    float y3 = c->getY().toFloat();

    float computed_area = (x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)) / 2.0f;

    return computed_area < 0 ? -computed_area : computed_area;
}
  
bool bsp(Point const a, Point const b, Point const c, Point const point)
{
	float A = area(&a, &b, &c);

	float A1 = area(&point, &b, &c);

	float A2 = area(&a, &point, &c);

	float A3 = area(&a, &b, &point);

	return (A == A1 + A2 + A3) && (A1 != 0 && A2 != 0 && A3 != 0);
}