#include "../../lib/objetos/poligono_triangulo.h"

vector_3 poligono_triangulo::normal() {
	return ((coord_1 - coord_2)*(coord_1 - coord_3)).normalizado();
}