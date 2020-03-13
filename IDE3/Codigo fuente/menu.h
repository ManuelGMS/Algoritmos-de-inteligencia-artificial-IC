
void menuPrincipal() {

	std::string opcion;

	tabla principal("");

	std::vector<std::string> reglasInferidas;

	do {

		std::cout << std::endl;
		std::cout << "1) ITERAR EN ID3 UNA VEZ." << std::endl;
		std::cout << "2) RESOLVER COMPLETAMENTE MEDIANTE ID3." << std::endl;
		std::cout << "3) MOSTRAR REGLAS INFERIDAS." << std::endl;
		std::cout << "4) INTRODUCIR DATOS PARA CLASIFICACION." << std::endl;
		std::cout << "5) SALIR DEL PROGRAMA." << std::endl;
		std::cout << "INTRODUCE UNA OPCION: ";
		std::cin >> opcion;
		std::cout << std::endl;

		try {

			if(opcion.compare("1") == 0)

				resolverMedianteId3(principal = tabla(""),reglasInferidas,true);

			else if(opcion.compare("2") == 0)

				resolverMedianteId3(principal = tabla(""),reglasInferidas,false);

			else if(opcion.compare("3") == 0)

				mostrarReglas(reglasInferidas);

			else if(opcion.compare("4") == 0)

				clasificarDatos(principal,reglasInferidas);

			else if(opcion.compare("5") != 0)

				std::cout << "OPCION INCORRECTA." << std::endl;

		} catch(const char* motivo) {

			std::cout << motivo << std::endl;

		}

	} while(opcion.compare("5") != 0);

}
