#include "../lib/imagen.h"

imagen::imagen(int width, int height) {
    pixeles = new color * [height];
    for (int i = 0; i < height; ++i) {
        pixeles[i] = new color[width];
    }

	// Para probar que se generan bien los colores
	// Se borrará mas adelante
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (i < 200) {
				if (j < 200) {
					pixeles[i][j].set_r(1);
					pixeles[i][j].set_g(0);
					pixeles[i][j].set_b(0);
				}
				else {
					pixeles[i][j].set_r(0);
					pixeles[i][j].set_g(1);
					pixeles[i][j].set_b(0);
				}
			}
			else {
				pixeles[i][j].set_r(0);
				pixeles[i][j].set_g(0);
				pixeles[i][j].set_b(0);
			}
		}
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
	double max_intensity = 0.;

	FIBITMAP* result = FreeImage_Allocate(imagen_width, imagen_height, 24);
	RGBQUAD color;

	if (!result) {
		FreeImage_DeInitialise();
		cerr << "Error al guardar memoria para el bitmap" << endl;
		exit(1);
	}

	for (int i = 0; i < imagen_height; i++) {
		for (int j = 0; j < imagen_width; j++) {
			max_intensity = max(max_intensity, this->pixeles[i][j].get_r());
			max_intensity = max(max_intensity, this->pixeles[i][j].get_g());
			max_intensity = max(max_intensity, this->pixeles[i][j].get_b());
		}
	}

	for (int i = 0; i < imagen_height; i++) {
		for (int j = 0; j < imagen_width; j++) {

			if (max_intensity > 1) {
				color.rgbRed = (BYTE)(pow(this->pixeles[i][j].get_r() / max_intensity, 0.667) * 255.0);
				color.rgbGreen = (BYTE)(pow(this->pixeles[i][j].get_g() / max_intensity, 0.667) * 255.0);
				color.rgbBlue = (BYTE)(pow(this->pixeles[i][j].get_b() / max_intensity, 0.667) * 255.0);
			}

			else {
				color.rgbRed = (BYTE)(this->pixeles[i][j].get_r() * 255.0);
				color.rgbGreen = (BYTE)(this->pixeles[i][j].get_g() * 255.0);
				color.rgbBlue = (BYTE)(this->pixeles[i][j].get_b() * 255.0);
			}

			FreeImage_SetPixelColor(result, j, i, &color);
		}
	}
	return result;
}