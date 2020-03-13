
void cargarDatosParaBayes(std::unordered_map<nombreClase,conjuntoDeMuestras>& claseMuestras, std::vector<clase>& clases) {

	claseMuestras = cargarDatosBayesLloyd();

	for(const auto& cM : claseMuestras)

		clases.push_back(clase(cM.first,cM.second));

	std::cout << "Las clases y las muestras se han cargado correctamente." << std::endl;

}

void clasificarMuestraBayes(std::vector<clase>& clases) {

	if(clases.empty())

		throw "ERROR: Primero debe cargar los datos mediante la Opcion 1.";

	double dato;
	vector muestra;

	std::priority_queue<std::pair<std::string,double>,std::vector<std::pair<std::string,double>>,cmp> proximidadDeLaMuestra;

	std::cout << "INTRODUCE " << clases[0].getDimensionDelVectorM() << " VALORES PARA LA MUESTRA: " << std::endl;

	do {

		std::cout << "VALOR: ";
		std::cin >> dato;

		muestra.push_back(dato);

	} while(clases[0].getDimensionDelVectorM() != muestra.size());

	for(clase& c : clases)

		proximidadDeLaMuestra.push({c.getNombreClase(),c.distanciaDeMahalanobis(muestra)});

	std::cout << std::endl;
	std::cout << "La muestra pertenece a " << proximidadDeLaMuestra.top().first;
	std::cout << ", con una distancia a la clase de: " << proximidadDeLaMuestra.top().second << std::endl;

}

void cargarDatosParaKmedias(matrizU& mU, std::vector<representante>& representantes, conjuntoDeMuestras& muestras) {

	mU = matrizU();

	muestras = conjuntoDeMuestras();

	representantes = std::vector<representante>();

	muestras = cargarMuestrasKmedias();

	kMediasConfig kmcfg = cargarConfiguracionkMedias();

	for(const auto& rpstt : kmcfg.claseCentro)

		representantes.push_back(representante(rpstt.first,rpstt.second));

	representantes[0].setClaseCentro(kmcfg.claseCentro);

	if(kmcfg.b != 2)

		representantes[0].setB(kmcfg.b);

	if(kmcfg.e != 0.01)

		representantes[0].setE(kmcfg.e);

	mU = calcularMatrizU(muestras,representantes);

	std::cout << "Las muestras y las clases se han cargado correctamente." << std::endl;

}

void calibrarCentrosKmedias(matrizU mU, const conjuntoDeMuestras muestras, std::vector<representante>& representantes) {

	if(mU.empty() && muestras.empty() && representantes.empty())

		throw "ERROR: Primero ha de cargar los datos mediante la Opcion 3.";

	bool centrosCalibrados;

	imprimirMatrizU(mU,representantes);

	do {

		for(auto& r : representantes)

			r.recalcularCentro(muestras,mU);

		mU = calcularMatrizU(muestras,representantes);

		imprimirMatrizU(mU,representantes);

		centrosCalibrados = true;

		for(size_t r = 0 ; r < representantes.size() && centrosCalibrados ; ++r)

			centrosCalibrados = representantes[r].iterarDeNuevo();

	} while(!centrosCalibrados);

}

void clasificarMuestraKmedias(const conjuntoDeMuestras muestras, std::vector<representante>& representantes) {

	if(muestras.empty() && representantes.empty())

		throw "ERROR: Primero ha de cargar los datos mediante la Opcion 3.";

	double dato;
	vector muestra;

	std::priority_queue<std::pair<std::string,double>,std::vector<std::pair<std::string,double>>,cmp> proximidadDeLaMuestra;

	std::cout << "INTRODUCE " << muestras[0].size() << " VALORES PARA LA MUESTRA: " << std::endl;

	do {

		std::cout << "VALOR: ";
		std::cin >> dato;

		muestra.push_back(dato);

	} while(muestras[0].size() != muestra.size());

	for(representante& representante : representantes)

		proximidadDeLaMuestra.push({representante.getNombre(),representante.distanciaDesdeLaMuestraHastaLaClase(muestra)});

	std::cout << std::endl;
	std::cout << "La muestra pertenece a " << proximidadDeLaMuestra.top().first;
	std::cout << ", con una distancia a la clase de: " << proximidadDeLaMuestra.top().second << std::endl;

}

void cargarDatosParaLloyd(std::vector<centro>& centros, std::unordered_map<nombreClase,conjuntoDeMuestras>& claseMuestras) {

	claseMuestras = cargarDatosBayesLloyd();

	lloydConfig llcfg = cargarConfiguracionLloyd();

	for(const auto& rpstt : llcfg.claseCentro)

		centros.push_back(centro(rpstt.first,rpstt.second));

	if(llcfg.k != 2)

		centros[0].setK(llcfg.k);

	if(llcfg.g != 0.1)

		centros[0].setK(llcfg.g);

	if(llcfg.e != 0.0000000001)

		centros[0].setE(llcfg.e);

	for(centro& centro : centros)

		for(const vector& muestra : claseMuestras[centro.getNombreClase()])

			centro.recalcularCentro(muestra);

	double distancia;

	bool centrosCalibrados = true;

	for(size_t c = 0 ; c < centros.size() && centrosCalibrados ; ++c) {

		distancia = 0;

		for(size_t k = 0 ; k < centros[c].getDimensionDelVectorCentral() ; ++k)

			distancia += std::pow( centros[c].getCentroActual()[k] - centros[c].getCentroAnterior()[k] , 2 );

		centrosCalibrados = distancia < centros[0].getE();

	}

	std::cout << "Las muestras y las clases se han cargado correctamente." << std::endl;

	std::cout << (
		(centrosCalibrados)? "El numero de iteraciones es adecuado." : "El numero de iteraciones es insuficiente."
				 ) << std::endl;

}

void clasificarMuestraLloyd(std::vector<centro>& centros) {

	if(centros.empty())

		throw "ERROR: Primero debe cargar los datos mediante la Opcion 6.";

	double dato;
	vector muestra;

	std::priority_queue<std::pair<std::string,double>,std::vector<std::pair<std::string,double>>,cmp> proximidadDeLaMuestra;

	std::cout << "INTRODUCE " << centros[0].getDimensionDelVectorCentral() << " VALORES PARA LA MUESTRA: " << std::endl;

	do {

		std::cout << "VALOR: ";
		std::cin >> dato;

		muestra.push_back(dato);

	} while(centros[0].getDimensionDelVectorCentral() != muestra.size());

	for(centro& c : centros)

		proximidadDeLaMuestra.push({c.getNombreClase(),c.distanciaDesdeElCentroHastaLaMuestra(muestra)});

	std::cout << std::endl;
	std::cout << "La muestra pertenece a " << proximidadDeLaMuestra.top().first;
	std::cout << ", con una distancia a la clase de: " << proximidadDeLaMuestra.top().second << std::endl;

}
