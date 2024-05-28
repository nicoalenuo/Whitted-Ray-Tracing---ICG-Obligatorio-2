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
		y * v.get_z() - z * v.get_y(),
		z * v.get_x() - x * v.get_z(),
		x * v.get_y() - y * v.get_x()
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

float vector_3::producto_interno(vector_3 v) {
	return x * v.get_x() + y * v.get_y() + z * v.get_z();
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