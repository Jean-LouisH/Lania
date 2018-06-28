#include "Vector2.hpp"
#include <math.h>

double Lania::Vector2::length()
{
	return sqrt((this->x * this->x) + (this->y * this->y));
}

double Lania::Vector2::direction()
{
	return atan(this->y / this->x);
}

Lania::Vector2 Lania::Vector2::normalized()
{
	Vector2 normalizedVector;
	double normalizationScale = 1.0 / this->length();
	normalizedVector.x = normalizationScale * this->x;
	normalizedVector.y = normalizationScale * this->y;
	return normalizedVector;
}