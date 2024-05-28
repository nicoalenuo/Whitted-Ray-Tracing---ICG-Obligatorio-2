#pragma once

#ifndef VECTOR_3_H
#define VECTOR_3_H

#include <cmath>
#include <iostream>

using namespace std;

class vector_3 {
private:
	float x, y, z;
public:
	vector_3() : x(0), y(0), z(0) {}
	vector_3(float x, float y, float z) : x(x), y(y), z(z) {}

	float get_x() const { return x; };
	float get_y() const { return y; };
	float get_z() const { return z; };

	vector_3 operator+(vector_3 v);
	vector_3 operator-(vector_3 v);
	vector_3 operator*(vector_3 v);
	vector_3 operator*(float t);
	vector_3 operator/(float t);
	vector_3 operator-(void);

	float producto_interno(vector_3 v);

	vector_3 normalizado();
	float norma();
};

#endif