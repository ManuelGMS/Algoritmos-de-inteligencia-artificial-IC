void menuPrincipal() {

	std::string opcion;

	matrizU mU;

	std::vector<clase> clases;

	conjuntoDeMuestras muestras;

	std::vector<centro> centros;

	std::vector<representante> representantes;

	std::unordered_map<nombreClase,conjuntoDeMuestras> claseMuestras;

	do {

		std::cout << std::endl;
		std::cout << "1º) CARGAR DATOS PARA ESTIMACION PARAMETRICA DE BAYES." << std::endl;
		std::cout << "2º) INTRODUCIR UNA MUESTRA PARA CLASIFICACION BAYESIANA." << std::endl;
		std::cout << "3º) CARGAR DATOS PARA K-MEDIAS DIFUSO." << std::endl;
		std::cout << "4º) RECALCULAR CENTROS PARA K-MEDIAS DIFUSO." << std::endl;
		std::cout << "5º) INTRODUCIR UNA MUESTRA PARA CLASIFICACION CON K-MEDIAS DIFUSO." << std::endl;
		std::cout << "6º) CARGAR DATOS PARA LLOYD." << std::endl;
		std::cout << "7º) INTRODUCIR UNA MUESTRA PARA CLASIFICARLA CON LLOYD." << std::endl;
		std::cout << "8º) SALIR DEL PROGRAMA." << std::endl;
		std::cout << "INTRODUCE UNA OPCION: ";
		std::cin >> opcion;
		std::cout << std::endl;

		try {

			if(opcion.compare("1") == 0) {

				cargarDatosParaBayes(claseMuestras,clases);

			} else if(opcion.compare("2") == 0) {

				clasificarMuestraBayes(clases);

			} else if(opcion.compare("3") == 0) {

				cargarDatosParaKmedias(mU,representantes,muestras);

			} else if(opcion.compare("4") == 0) {

				calibrarCentrosKmedias(mU,muestras,representantes);

			} else if(opcion.compare("5") == 0) {

				clasificarMuestraKmedias(muestras,representantes);

			} else if(opcion.compare("6") == 0) {

				cargarDatosParaLloyd(centros,claseMuestras);

			} else if(opcion.compare("7") == 0) {

				clasificarMuestraLloyd(centros);

			}

		} catch(const char* e) {

			std::cout << e << std::endl;

		}

	} while(opcion.compare("8") != 0);

}
