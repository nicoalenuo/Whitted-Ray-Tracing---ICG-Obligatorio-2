#include "../lib/color.h"

color color::operator*(color c) {
	return color(
		r * c.get_r(),
		g * c.get_g(),
		b * c.get_b()
	);
}

color color::operator+(color c) {
	return color(
		r + c.get_r(),
		g + c.get_g(),
		b + c.get_b()
	);
}

color color::operator-(color c) {
	return color(
		r - c.get_r(),
		g - c.get_g(),
		b - c.get_b()
	);
}

color color::operator*(double t) {
	return color(
		r * t,
		g * t,
		b * t
	);
}

color color::operator/(double t) {
	return color(
		r / t,
		g / t,
		b / t
	);
}