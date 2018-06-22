#include "Vector2.hpp"

double Lania::Vector2::length()
{
	return sqrt((this->x * this->x) + (this->y * this->y));
}

Lania::Vector2 Lania::Vector2::normalized()
{
	Vector2 normalizedVector;
	double normalizationScale = 1.0 / this->length();
	normalizedVector.x = normalizationScale * this->x;
	normalizedVector.y = normalizationScale * this->y;
	return normalizedVector;
}