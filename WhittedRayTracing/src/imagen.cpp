#include "../lib/imagen.h"

imagen::imagen() {
    pixeles = new color * [IMAGEN_HEIGHT];
    for (int i = 0; i < IMAGEN_HEIGHT; ++i) {
        pixeles[i] = new color[IMAGEN_WIDTH];
    }

	// Para probar que se generan bien los colores
	// Se borrará mas adelante
	for (int i = 0; i < IMAGEN_HEIGHT; i++) {
		for (int j = 0; j < IMAGEN_WIDTH; j++) {
			if (i < 200) {
				if (j < 200) {
					pixeles[i][j].r = 100;
					pixeles[i][j].g = 100;
					pixeles[i][j].b = 100;
				}
				else {
					pixeles[i][j].r = 255;
					pixeles[i][j].g = 255;
					pixeles[i][j].b = 255;
				}
			}
			else {
				pixeles[i][j].r = 0;
				pixeles[i][j].g = 0;
				pixeles[i][j].b = 0;
			}
		}
	}
}

imagen::~imagen() {
    for (int i = 0; i < IMAGEN_HEIGHT; ++i) {
        delete[] pixeles[i];
    }
    delete[] pixeles;
}

FIBITMAP* imagen::obtener_bitmap() {
	double max_intensity = 0.;

	FIBITMAP* result = FreeImage_Allocate(IMAGEN_WIDTH, IMAGEN_HEIGHT, 24);
	RGBQUAD color;
	if (!result) {
		FreeImage_DeInitialise();
		cerr << "Error al guardar memoria para el bitmap" << endl;
		exit(1);
	}

	// Get highest color value for normalization 0..1
	for (size_t i = 0; i < IMAGEN_HEIGHT; i++) {
		for (size_t j = 0; j < IMAGEN_WIDTH; j++) {
			max_intensity = max(max_intensity, this->pixeles[i][j].r);
			max_intensity = max(max_intensity, this->pixeles[i][j].g);
			max_intensity = max(max_intensity, this->pixeles[i][j].b);
		}
	}

	// Normalize and convert to Byte
	for (unsigned int i = 0; i < IMAGEN_HEIGHT; i++) {
		for (unsigned int j = 0; j < IMAGEN_WIDTH; j++) {

			// Apply gamma correction if max intensity gets over 1
			if (max_intensity > 1) {
				color.rgbRed = (BYTE)(pow(this->pixeles[i][j].r / max_intensity, 0.667) * 255.0);
				color.rgbGreen = (BYTE)(pow(this->pixeles[i][j].g / max_intensity, 0.667) * 255.0);
				color.rgbBlue = (BYTE)(pow(this->pixeles[i][j].b / max_intensity, 0.667) * 255.0);
			}

			// If not, just convert to byte
			else {
				color.rgbRed = (BYTE)(this->pixeles[i][j].r * 255.0);
				color.rgbGreen = (BYTE)(this->pixeles[i][j].g * 255.0);
				color.rgbBlue = (BYTE)(this->pixeles[i][j].b * 255.0);
			}
			FreeImage_SetPixelColor(result, j, IMAGEN_HEIGHT - 1 - i, &color);
		}
	}
	return result;
}