#pragma once

#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

struct color {
	double r;
	double g;
	double b;
	double a;
};

//En el xml, 0 es reflectante, 1 es transparente
enum tipo_material {
	REFLECTANTE,
	TRANSPARENTE
};

#endif