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
	objetos_out = cargar_objetos();
	luces_out = cargar_luces();
	camara_out = cargar_camara();
}

vector<objeto*> ControladorArchivos::cargar_objetos() {
	vector <objeto*> objetos;

	tinyxml2::XMLDocument configuracion_xml;
	configuracion_xml.LoadFile(DIRECCION_CONFIGURACION_XML.c_str());
	tinyxml2::XMLElement* configuracion = configuracion_xml.RootElement();

	if (configuracion == NULL) {
		cerr << "Error al cargar los objetos" << endl;
		exit(1);
	}

	tinyxml2::XMLElement* esferas_xml = configuracion->FirstChildElement("objetos")->FirstChildElement("esferas");
	tinyxml2::XMLElement* cilindros_xml = configuracion->FirstChildElement("objetos")->FirstChildElement("cilindros");
	tinyxml2::XMLElement* meshes_xml = configuracion->FirstChildElement("objetos")->FirstChildElement("meshes");

	if (esferas_xml == NULL || cilindros_xml == NULL || meshes_xml == NULL) {
		cerr << "Error al cargar los objetos" << endl;
		exit(1);
	}

	//Carga de esferas 
	//----------------

	tinyxml2::XMLElement* esfera_xml = esferas_xml->FirstChildElement("esfera");
	while (esfera_xml) {
		//Crear objeto con propiedades de objeto_xml
		//Agregarlo a objetos

		esfera_xml = esfera_xml->NextSiblingElement("objeto");
	}

	//Carga de cilindros 
	//----------------

	tinyxml2::XMLElement* cilindro_xml = cilindros_xml->FirstChildElement("cilindro");
	while (cilindro_xml) {
		//Crear objeto con propiedades de objeto_xml
		//Agregarlo a objetos

		cilindro_xml = cilindro_xml->NextSiblingElement("cilindro");
	}

	//Carga de meshes
	//----------------

	tinyxml2::XMLElement* mesh_xml = meshes_xml->FirstChildElement("mesh");
	while (mesh_xml) {
		//Crear objeto con propiedades de objeto_xml
		//Agregarlo a objetos

		mesh_xml = mesh_xml->NextSiblingElement("mesh");
	}

	return objetos;
}

vector<luz*> ControladorArchivos::cargar_luces() {
	vector <luz*> luces;

	tinyxml2::XMLDocument configuracion_xml;
	configuracion_xml.LoadFile(DIRECCION_CONFIGURACION_XML.c_str());
	tinyxml2::XMLElement* configuracion = configuracion_xml.RootElement();

	if (configuracion == NULL) {
		cerr << "Error al cargar las luces" << endl;
		exit(1);
	}

	tinyxml2::XMLElement* luces_xml = configuracion->FirstChildElement("luces");

	if (luces_xml == NULL) {
		cerr << "Error al cargar las luces" << endl;
		exit(1);
	}

	tinyxml2::XMLElement* luz_xml = luces_xml->FirstChildElement("luz");
	while (luz_xml) {
		//Crear objeto con propiedades de luz_xml
		//Agregarlo a luces

		luz_xml = luz_xml->NextSiblingElement("luz");
	}

	return luces;
}

camara* ControladorArchivos::cargar_camara() {
	camara* camara_out = new camara(vector_3(), vector_3());

	tinyxml2::XMLDocument configuracion_xml;
	configuracion_xml.LoadFile(DIRECCION_CONFIGURACION_XML.c_str());
	tinyxml2::XMLElement* configuracion = configuracion_xml.RootElement();

	if (configuracion == NULL) {
		cerr << "Error al cargar la camara" << endl;
		exit(1);
	}

	tinyxml2::XMLElement* camara_xml = configuracion->FirstChildElement("camara");

	if (camara_xml == NULL) {
		cerr << "Error al cargar la camara" << endl;
		exit(1);
	}

	//Crear camara con propiedades de camara_xml

	return camara_out;
}


bool ControladorArchivos::guardar_resultado(imagen* img_resultado) {
	bool resultado;

	time_t rawtime;
	struct tm timeinfo;
	char buffer[80];

	time(&rawtime);
	localtime_s(&timeinfo, &rawtime);

	strftime(buffer, sizeof(buffer), "%Y-%m-%d_%H-%M-%S", &timeinfo);
	string str(buffer);

	str = DIRECCION_RESULTADOS + str;
	if (CreateDirectoryW(wstring(str.begin(), str.end()).c_str(), NULL) == 0) {
		return false;
	}

	str = str + "\\resultado.png";

	FIBITMAP* bitmap = img_resultado->float_to_bitmap();

	cout << "Guardado en : " << str << endl;

	resultado = FreeImage_Save(FIF_PNG, bitmap, str.c_str(), 0);

	FreeImage_Unload(bitmap);

	return resultado;
}
