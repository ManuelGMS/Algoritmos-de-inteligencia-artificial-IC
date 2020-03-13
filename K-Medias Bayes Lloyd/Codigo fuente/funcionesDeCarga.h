typedef struct {
	double e;
	double b;
	std::unordered_map<std::string,vector> claseCentro;
} kMediasConfig;

typedef struct {
	double e;
	double k;
	double g;
	std::unordered_map<std::string,vector> claseCentro;
} lloydConfig;

std::unordered_map<nombreClase,conjuntoDeMuestras> cargarDatosBayesLloyd() {

	size_t posicion;
	std::string dato;
	std::string linea;
	std::string nombre;

	std::unordered_map<nombreClase,conjuntoDeMuestras> claseMuestras;

	std::ifstream in("Datos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());

	do {

		getline(std::cin,linea);

		if(std::cin) {

			posicion = linea.find_last_of(',');

			nombre = linea.substr(posicion+1,linea.size());

			linea.erase(posicion,linea.size());

			std::stringstream ss(linea);

			std::vector<double> muestra;

			while(getline(ss,dato,','))

				muestra.push_back(std::stod(dato));

			claseMuestras[nombre].push_back(muestra);

		}

	} while(std::cin);

	std::cin.rdbuf(cinbuf);

	size_t elementos = (*claseMuestras.begin()).second[0].size();

	for(auto it = claseMuestras.begin() ; it != claseMuestras.end() ; ++it)

		for(auto itrt = (*it).second.begin() ; itrt != (*it).second.end() ; ++itrt)

			if((*itrt).size() != elementos)

				throw "ERROR: Las muestras en el fichero no tienen el mismo numero de componentes.";

	return claseMuestras;

}

conjuntoDeMuestras cargarMuestrasKmedias() {

	size_t posicion;
	std::string dato;
	std::string linea;
	conjuntoDeMuestras muestras;

	std::ifstream in("Datos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());

	do {

		getline(std::cin,linea);

		if(std::cin) {

			posicion = linea.find_last_of(',');

			linea.erase(posicion,linea.size());

			std::stringstream ss(linea);

			std::vector<double> muestra;

			while(getline(ss,dato,','))

				muestra.push_back(std::stod(dato));

			muestras.push_back(muestra);

		}

	} while(std::cin);

	std::cin.rdbuf(cinbuf);

	size_t elementos = muestras[0].size();

	for(auto it = muestras.begin() ; it != muestras.end() ; ++it)

		if((*it).size() != elementos)

			throw "ERROR: Las muestras en el fichero no tienen el mismo numero de componentes.";

	return muestras;

}

kMediasConfig cargarConfiguracionkMedias() {

	size_t posicion;
	std::string dato;
	std::string linea;
	std::string nombre;
	kMediasConfig configuracionInicial;

	std::ifstream in("K-Medias-Config.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());

	getline(std::cin,linea);

	posicion = linea.find_first_of(':');

	linea.erase(0,posicion+1);

	configuracionInicial.e = std::stod(linea);

	getline(std::cin,linea);

	posicion = linea.find_first_of(':');

	linea.erase(0,posicion+1);

	configuracionInicial.b = std::stod(linea);

	do {

		getline(std::cin,linea);

		if(std::cin) {

			posicion = linea.find_last_of(',');

			nombre = linea.substr(posicion+1,linea.size());

			linea.erase(posicion,linea.size());

			std::stringstream ss(linea);

			vector centro;

			while(getline(ss,dato,','))

				centro.push_back(std::stod(dato));

			configuracionInicial.claseCentro[nombre] = centro;

		}

	} while(std::cin);

	std::cin.rdbuf(cinbuf);

	return configuracionInicial;

}

lloydConfig cargarConfiguracionLloyd() {

	size_t posicion;
	std::string dato;
	std::string linea;
	std::string nombre;
	lloydConfig configuracionInicial;

	std::ifstream in("Lloyd-Config.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());

	getline(std::cin,linea);

	posicion = linea.find_first_of(':');

	linea.erase(0,posicion+1);

	configuracionInicial.e = std::stod(linea);

	getline(std::cin,linea);

	posicion = linea.find_first_of(':');

	linea.erase(0,posicion+1);

	configuracionInicial.k = std::stod(linea);

	getline(std::cin,linea);

	posicion = linea.find_first_of(':');

	linea.erase(0,posicion+1);

	configuracionInicial.g = std::stod(linea);


	do {

		getline(std::cin,linea);

		if(std::cin) {

			posicion = linea.find_last_of(',');

			nombre = linea.substr(posicion+1,linea.size());

			linea.erase(posicion,linea.size());

			std::stringstream ss(linea);

			vector centro;

			while(getline(ss,dato,','))

				centro.push_back(std::stod(dato));

			configuracionInicial.claseCentro[nombre] = centro;

		}

	} while(std::cin);

	std::cin.rdbuf(cinbuf);

	return configuracionInicial;

}
