#include "Vector3.hpp"
#include <math.h>

double Lania::Vector3::length()
{
	return sqrt((this->x * this->x) + (this->y * this->y) + (this->z * this->z));
}

Lania::Vector3 Lania::Vector3::direction()
{
	Vector3 result;
	return result;
}

Lania::Vector3 Lania::Vector3::normalized()
{
	Vector3 normalizedVector;
	double normalizationScale = 1.0 / this->length();
	normalizedVector.x = normalizationScale * this->x;
	normalizedVector.y = normalizationScale * this->y;
	normalizedVector.z = normalizationScale * this->z;
	return normalizedVector;
}

double Lania::Vector3::dot(Vector3 operand)
{
	return ((this->x * operand.x) + (this->y * operand.y) + (this->z * operand.z));
}

Lania::Vector3 Lania::Vector3::cross(Vector3 operand)
{
	Vector3 result;
	return result;
}

Lania::Vector3 Lania::Vector3::operator+(Vector3 operand)
{
	Vector3 result;
	result.x = this->x + operand.x;
	result.y = this->y + operand.y;
	result.z = this->z + operand.z;
	return result;
}

Lania::Vector3 Lania::Vector3::operator-(Vector3 operand)
{
	Vector3 result;
	result.x = this->x - operand.x;
	result.y = this->y - operand.y;
	result.z = this->z - operand.z;
	return result;
}

Lania::Vector3 Lania::Vector3::operator*(double scale)
{
	Vector3 result;
	result.x = this->x * scale;
	result.y = this->y * scale;
	result.z = this->z * scale;
	return result;
}