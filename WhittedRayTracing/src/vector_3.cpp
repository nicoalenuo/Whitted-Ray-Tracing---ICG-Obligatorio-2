#include "../lib/vector_3.h"

vector_3 vector_3::operator+(vector_3 v) {
	return vector_3(
		x + v.get_x(),
		y + v.get_y(),
		z + v.get_z()
	);
}

vector_3 vector_3::operator-(vector_3 v) {
	return vector_3(
		x - v.get_x(),
		y - v.get_y(),
		z - v.get_z()
	);
}

vector_3 vector_3::operator-(void) {
	return vector_3(
		-x,
		-y,
		-z
	);
}

vector_3 vector_3::operator*(vector_3 v) {
	return vector_3(
		y * v.z - z * v.y,
		z * v.x - x * v.z,
		x * v.y - y * v.x
	);
}

vector_3 vector_3::operator*(float t) {
	return vector_3(
		x * t,
		y * t,
		z * t
	);
}

vector_3 vector_3::operator/(float t) {
	return vector_3(
		x / t,
		y / t,
		z / t
	);
}

vector_3 vector_3::normalizado() {
	return vector_3(
		x / norma(),
		y / norma(),
		z / norma()
	);
}

float vector_3::norma() {
	return sqrt(x*x + y*y + z*z);
}