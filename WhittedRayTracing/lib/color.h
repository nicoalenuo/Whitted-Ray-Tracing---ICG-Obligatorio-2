#pragma once

#ifndef COLOR_H
#define COLOR_H

#include <iostream>

using namespace std;

class color {
private:
	double r, g, b;
public:
	color() : r(0), g(0), b(0) { }
	color(double r, double g, double b) : r(r), g(g), b(b) { }

	void set_r(double r) { this->r = r; };
	void set_g(double g) { this->g = g; };
	void set_b(double b) { this->b = b; };

	double get_r() const { return r; };
	double get_g() const { return g; };
	double get_b() const { return b; };

	color operator*(color c);
	color operator+(color c);
	color operator-(color c);
	color operator*(double t);
	color operator/(double t);

	void imprimir() { cout << r << " " << g << " " << b << endl; }; // Imprimir color para debugear
};

#endif
