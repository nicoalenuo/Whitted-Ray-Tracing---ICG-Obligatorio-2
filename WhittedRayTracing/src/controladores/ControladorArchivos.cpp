#include "../../lib/controladores/ControladorArchivos.h"

ControladorArchivos* ControladorArchivos::instancia = nullptr;

ControladorArchivos::ControladorArchivos() {

}

ControladorArchivos* ControladorArchivos::getInstance() {
	if (instancia == nullptr)
		instancia = new ControladorArchivos();
	return instancia;
}

ControladorArchivos::~ControladorArchivos() {

}

void ControladorArchivos::cargar_xml(vector<objeto*>& objetos_out, vector<luz*>& luces_out, camara*& camara_out) {
	tinyxml2::XMLDocument configuracion_xml;
	configuracion_xml.LoadFile(DIRECCION_CONFIGURACION_XML.c_str());
	tinyxml2::XMLElement* configuracion = configuracion_xml.RootElement();

	if (configuracion == NULL) {
		cerr << "Error al cargar el archivo de configuracion" << endl;
		exit(1);
	}

	objetos_out = cargar_objetos(configuracion);
	luces_out = cargar_luces(configuracion);
	camara_out = cargar_camara(configuracion);
}

vector<objeto*> ControladorArchivos::cargar_objetos(tinyxml2::XMLElement* configuracion) {
	vector <objeto*> objetos;

	tinyxml2::XMLElement* esferas_xml = configuracion->FirstChildElement("objetos")->FirstChildElement("esferas");
	tinyxml2::XMLElement* cilindros_xml = configuracion->FirstChildElement("objetos")->FirstChildElement("cilindros");
	tinyxml2::XMLElement* mallas_poligonales_xml = configuracion->FirstChildElement("objetos")->FirstChildElement("mallas_poligonales");

	if (esferas_xml == NULL || cilindros_xml == NULL || mallas_poligonales_xml == NULL) {
		cerr << "Error al cargar los objetos" << endl;
		exit(1);
	}

	float pos_x, pos_y, pos_z;
	float radio;
	float altura;
	double difuso_r, difuso_g, difuso_b, difuso_a;
	double especular_r, especular_g, especular_b, especular_a;
	float coeficiente_ambiente, coeficiente_difuso, coeficiente_especular, coeficiente_transmicion;
	int material; 

	//Carga de esferas 
	//----------------

	tinyxml2::XMLElement* esfera_xml = esferas_xml->FirstChildElement("esfera");
	while (esfera_xml) {
		esfera_xml->FirstChildElement("posicion")->FirstChildElement("x")->QueryFloatText(&pos_x);
		esfera_xml->FirstChildElement("posicion")->FirstChildElement("y")->QueryFloatText(&pos_y);
		esfera_xml->FirstChildElement("posicion")->FirstChildElement("z")->QueryFloatText(&pos_z);
		
		esfera_xml->FirstChildElement("color_difuso")->FirstChildElement("r")->QueryDoubleText(&difuso_r);
		esfera_xml->FirstChildElement("color_difuso")->FirstChildElement("g")->QueryDoubleText(&difuso_g);
		esfera_xml->FirstChildElement("color_difuso")->FirstChildElement("b")->QueryDoubleText(&difuso_b);
		esfera_xml->FirstChildElement("color_difuso")->FirstChildElement("a")->QueryDoubleText(&difuso_a);
		
		esfera_xml->FirstChildElement("color_especular")->FirstChildElement("r")->QueryDoubleText(&especular_r);
		esfera_xml->FirstChildElement("color_especular")->FirstChildElement("g")->QueryDoubleText(&especular_g);
		esfera_xml->FirstChildElement("color_especular")->FirstChildElement("b")->QueryDoubleText(&especular_b);
		esfera_xml->FirstChildElement("color_especular")->FirstChildElement("a")->QueryDoubleText(&especular_a);

		esfera_xml->FirstChildElement("coeficiente_ambiente")->QueryFloatText(&coeficiente_ambiente);
		esfera_xml->FirstChildElement("coeficiente_difuso")->QueryFloatText(&coeficiente_difuso);
		esfera_xml->FirstChildElement("coeficiente_especular")->QueryFloatText(&coeficiente_especular);
		esfera_xml->FirstChildElement("coeficiente_transmicion")->QueryFloatText(&coeficiente_transmicion);
		esfera_xml->FirstChildElement("material")->QueryIntText(&material);

		esfera_xml->FirstChildElement("radio")->QueryFloatText(&radio);

		objetos.push_back(new esfera(
			vector_3(pos_x, pos_y, pos_z),
			{ difuso_r, difuso_g, difuso_b, difuso_a },
			{ especular_r, especular_g, especular_b, especular_a },
			coeficiente_ambiente, coeficiente_difuso, coeficiente_especular, coeficiente_transmicion,
			tipo_material(material),
			radio
		));

		esfera_xml = esfera_xml->NextSiblingElement("esfera");
	}

	//Carga de cilindros 
	//----------------

	tinyxml2::XMLElement* cilindro_xml = cilindros_xml->FirstChildElement("cilindro");
	while (cilindro_xml) {
		cilindro_xml->FirstChildElement("posicion")->FirstChildElement("x")->QueryFloatText(&pos_x);
		cilindro_xml->FirstChildElement("posicion")->FirstChildElement("y")->QueryFloatText(&pos_y);
		cilindro_xml->FirstChildElement("posicion")->FirstChildElement("z")->QueryFloatText(&pos_z);

		cilindro_xml->FirstChildElement("color_difuso")->FirstChildElement("r")->QueryDoubleText(&difuso_r);
		cilindro_xml->FirstChildElement("color_difuso")->FirstChildElement("g")->QueryDoubleText(&difuso_g);
		cilindro_xml->FirstChildElement("color_difuso")->FirstChildElement("b")->QueryDoubleText(&difuso_b);
		cilindro_xml->FirstChildElement("color_difuso")->FirstChildElement("a")->QueryDoubleText(&difuso_a);

		cilindro_xml->FirstChildElement("color_especular")->FirstChildElement("r")->QueryDoubleText(&especular_r);
		cilindro_xml->FirstChildElement("color_especular")->FirstChildElement("g")->QueryDoubleText(&especular_g);
		cilindro_xml->FirstChildElement("color_especular")->FirstChildElement("b")->QueryDoubleText(&especular_b);
		cilindro_xml->FirstChildElement("color_especular")->FirstChildElement("a")->QueryDoubleText(&especular_a);

		cilindro_xml->FirstChildElement("coeficiente_ambiente")->QueryFloatText(&coeficiente_ambiente);
		cilindro_xml->FirstChildElement("coeficiente_difuso")->QueryFloatText(&coeficiente_difuso);
		cilindro_xml->FirstChildElement("coeficiente_especular")->QueryFloatText(&coeficiente_especular);
		cilindro_xml->FirstChildElement("coeficiente_transmicion")->QueryFloatText(&coeficiente_transmicion);
		cilindro_xml->FirstChildElement("material")->QueryIntText(&material);

		cilindro_xml->FirstChildElement("radio")->QueryFloatText(&radio);
		cilindro_xml->FirstChildElement("altura")->QueryFloatText(&altura);

		objetos.push_back(new cilindro(
			vector_3(pos_x, pos_y, pos_z),
			{ difuso_r, difuso_g, difuso_b, difuso_a },
			{ especular_r, especular_g, especular_b, especular_a },
			coeficiente_ambiente, coeficiente_difuso, coeficiente_especular, coeficiente_transmicion,
			tipo_material(material),
			radio,
			altura
		));

		cilindro_xml = cilindro_xml->NextSiblingElement("cilindro");
	}

	//Carga de mallas poligonales
	//----------------

	tinyxml2::XMLElement* malla_poligonal_xml = mallas_poligonales_xml->FirstChildElement("malla_poligonal");
	while (malla_poligonal_xml) {	
		malla_poligonal_xml->FirstChildElement("color_difuso")->FirstChildElement("r")->QueryDoubleText(&difuso_r);
		malla_poligonal_xml->FirstChildElement("color_difuso")->FirstChildElement("g")->QueryDoubleText(&difuso_g);
		malla_poligonal_xml->FirstChildElement("color_difuso")->FirstChildElement("b")->QueryDoubleText(&difuso_b);
		malla_poligonal_xml->FirstChildElement("color_difuso")->FirstChildElement("a")->QueryDoubleText(&difuso_a);
		
		malla_poligonal_xml->FirstChildElement("color_especular")->FirstChildElement("r")->QueryDoubleText(&especular_r);
		malla_poligonal_xml->FirstChildElement("color_especular")->FirstChildElement("g")->QueryDoubleText(&especular_g);
		malla_poligonal_xml->FirstChildElement("color_especular")->FirstChildElement("b")->QueryDoubleText(&especular_b);
		malla_poligonal_xml->FirstChildElement("color_especular")->FirstChildElement("a")->QueryDoubleText(&especular_a);

		malla_poligonal_xml->FirstChildElement("coeficiente_ambiente")->QueryFloatText(&coeficiente_ambiente);
		malla_poligonal_xml->FirstChildElement("coeficiente_difuso")->QueryFloatText(&coeficiente_difuso);
		malla_poligonal_xml->FirstChildElement("coeficiente_especular")->QueryFloatText(&coeficiente_especular);
		malla_poligonal_xml->FirstChildElement("coeficiente_transmicion")->QueryFloatText(&coeficiente_transmicion);
		malla_poligonal_xml->FirstChildElement("material")->QueryIntText(&material);

		vector<poligono_triangulo*> poligonos;
		tinyxml2::XMLElement* triangulos = malla_poligonal_xml->FirstChildElement("triangulos");
		tinyxml2::XMLElement* triangulo = triangulos->FirstChildElement("triangulo");
		while (triangulo) {
			vector<vector_3> coordenadas;
			tinyxml2::XMLElement* coord = triangulo->FirstChildElement("coord");
			while (coord) {
				coord->FirstChildElement("x")->QueryFloatText(&pos_x);
				coord->FirstChildElement("y")->QueryFloatText(&pos_y);
				coord->FirstChildElement("z")->QueryFloatText(&pos_z);

				coordenadas.push_back(vector_3(pos_x, pos_y, pos_z));

				coord = coord->NextSiblingElement("coord");
			}
			poligonos.push_back(new poligono_triangulo(
				coordenadas[0],
				coordenadas[1],
				coordenadas[2]
			));
			triangulo = triangulo->NextSiblingElement("triangulo");
		}
		
		objetos.push_back(new malla_poligonal(
			vector_3(),
			{ difuso_r, difuso_g, difuso_b, difuso_a },
			{ especular_r, especular_g, especular_b, especular_a },
			coeficiente_ambiente, coeficiente_difuso, coeficiente_especular, coeficiente_transmicion,
			tipo_material(material),
			poligonos
		));

		malla_poligonal_xml = malla_poligonal_xml->NextSiblingElement("malla_poligonal");
	}

	return objetos;
}

vector<luz*> ControladorArchivos::cargar_luces(tinyxml2::XMLElement* configuracion) {
	vector <luz*> luces;

	tinyxml2::XMLElement* luces_xml = configuracion->FirstChildElement("luces");

	if (luces_xml == NULL) {
		cerr << "Error al cargar las luces" << endl;
		exit(1);
	}

	float pos_x, pos_y, pos_z;
	double color_r, color_g, color_b, color_a;

	tinyxml2::XMLElement* luz_xml = luces_xml->FirstChildElement("luz");
	while (luz_xml) {
		luz_xml->FirstChildElement("posicion")->FirstChildElement("x")->QueryFloatText(&pos_x);
		luz_xml->FirstChildElement("posicion")->FirstChildElement("y")->QueryFloatText(&pos_y);
		luz_xml->FirstChildElement("posicion")->FirstChildElement("z")->QueryFloatText(&pos_z);

		luz_xml->FirstChildElement("color")->FirstChildElement("r")->QueryDoubleText(&color_r);
		luz_xml->FirstChildElement("color")->FirstChildElement("g")->QueryDoubleText(&color_g);
		luz_xml->FirstChildElement("color")->FirstChildElement("b")->QueryDoubleText(&color_b);
		luz_xml->FirstChildElement("color")->FirstChildElement("a")->QueryDoubleText(&color_a);

		luces.push_back(new luz(
			vector_3(pos_x, pos_y, pos_z),
			{ color_r, color_g, color_b, color_a }
		));

		luz_xml = luz_xml->NextSiblingElement("luz");
	}

	return luces;
}

camara* ControladorArchivos::cargar_camara(tinyxml2::XMLElement* configuracion) {
	tinyxml2::XMLElement* camara_xml = configuracion->FirstChildElement("camara");

	if (camara_xml == NULL) {
		cerr << "Error al cargar la camara" << endl;
		exit(1);
	}

	float pos_x, pos_y, pos_z;
	float pos_x_imagen, pos_y_imagen, pos_z_imagen;
	int width, height;

	camara_xml->FirstChildElement("posicion_camara")->FirstChildElement("x")->QueryFloatText(&pos_x);
	camara_xml->FirstChildElement("posicion_camara")->FirstChildElement("y")->QueryFloatText(&pos_y);
	camara_xml->FirstChildElement("posicion_camara")->FirstChildElement("z")->QueryFloatText(&pos_z);

	camara_xml->FirstChildElement("posicion_imagen")->FirstChildElement("x")->QueryFloatText(&pos_x_imagen);
	camara_xml->FirstChildElement("posicion_imagen")->FirstChildElement("y")->QueryFloatText(&pos_y_imagen);
	camara_xml->FirstChildElement("posicion_imagen")->FirstChildElement("z")->QueryFloatText(&pos_z_imagen);

	camara_xml->FirstChildElement("imagen_width")->QueryIntText(&width);
	camara_xml->FirstChildElement("imagen_height")->QueryIntText(&height);

	return new camara(
		vector_3(
			pos_x,
			pos_y,
			pos_z
		),
		vector_3(
			pos_x_imagen,
			pos_y_imagen,
			pos_z_imagen
		),
		width, height
	);
}

void ControladorArchivos::guardar_resultado(imagen* img_resultado) {
	FreeImage_Initialise();

	time_t in_time_t = chrono::system_clock::to_time_t(chrono::system_clock::now());
	tm buf;
	localtime_s(&buf, &in_time_t);
	ostringstream oss;
	oss << put_time(&buf, "%d %B - %H-%M-%S");
	string direccion = DIRECCION_RESULTADOS + oss.str();

	// Crear el directorio
	if (!filesystem::create_directory(direccion)) {
		cerr << "Error al crear el directorio: " << direccion << endl;
		exit(1);
	}

	direccion += "\\resultado.png";

	FIBITMAP* bitmap = img_resultado->obtener_bitmap();
	if (!FreeImage_Save(FIF_PNG, bitmap, direccion.c_str(), 0)) {
		FreeImage_Unload(bitmap);
		FreeImage_DeInitialise();
		cerr << "Error al guardar la imagen en: " << direccion << endl;
		exit(1);
	} else {
		FreeImage_Unload(bitmap);
		FreeImage_DeInitialise();
		cout << "Resultado guardado en: " << direccion << endl;
	}
}


