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

double Lania::Vector2::dot(Vector2 operand)
{
	return ((this->x * operand.x) + this->y * operand.y);
}

Lania::Vector2 Lania::Vector2::cross(Vector2 operand)
{

}

Lania::Vector2 Lania::Vector2::operator+(Vector2 operand)
{
	Vector2 result;
	result.x = this->x + operand.x;
	result.y = this->y + operand.y;
	return result;
}

Lania::Vector2 Lania::Vector2::operator-(Vector2 operand)
{
	Vector2 result;
	result.x = this->x - operand.x;
	result.y = this->y - operand.y;
	return result;
}

Lania::Vector2 Lania::Vector2::operator*(double scale)
{
	Vector2 result;
	result.x = this->x * scale;
	result.y = this->y * scale;
	return result;
}