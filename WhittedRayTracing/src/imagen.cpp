#include "../lib/imagen.h"

imagen::imagen(int width, int height) {
    pixeles = new color * [height];
    for (int i = 0; i < height; ++i) {
        pixeles[i] = new color[width];
    }

	imagen_width = width;
	imagen_height = height;
}

imagen::~imagen() {
    for (int i = 0; i < imagen_height; ++i) {
        delete[] pixeles[i];
    }
    delete[] pixeles;
}

FIBITMAP* imagen::obtener_bitmap() {
	double intensidad_mas_alta = 0.0f;

	FIBITMAP* bitmap_resultado = FreeImage_Allocate(imagen_width, imagen_height, 24);
	
	if (!bitmap_resultado) {
		FreeImage_DeInitialise();
		cerr << "Error al guardar memoria para el bitmap" << endl;
		exit(1);
	}

	for (int i = 0; i < imagen_height; i++) {
		for (int j = 0; j < imagen_width; j++) {
			intensidad_mas_alta = max(intensidad_mas_alta, pixeles[i][j].get_r());
			intensidad_mas_alta = max(intensidad_mas_alta, pixeles[i][j].get_g());
			intensidad_mas_alta = max(intensidad_mas_alta, pixeles[i][j].get_b());
		}
	}

	RGBQUAD color;

	for (int i = 0; i < imagen_height; i++) {
		for (int j = 0; j < imagen_width; j++) {

			if (intensidad_mas_alta > 1) {
				color.rgbRed = BYTE (pixeles[i][j].get_r() / intensidad_mas_alta * 255.0);
				color.rgbGreen = BYTE(pixeles[i][j].get_g() / intensidad_mas_alta * 255.0);
				color.rgbBlue = BYTE(pixeles[i][j].get_b() / intensidad_mas_alta * 255.0);
			}

			else {
				color.rgbRed = BYTE(pixeles[i][j].get_r() * 255.0);
				color.rgbGreen = BYTE(pixeles[i][j].get_g() * 255.0);
				color.rgbBlue = BYTE(pixeles[i][j].get_b() * 255.0);
			}

			FreeImage_SetPixelColor(bitmap_resultado, j, i, &color);
		}
	}
	return bitmap_resultado;
}