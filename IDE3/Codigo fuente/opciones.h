
void resolverMedianteId3(tabla& principal, std::vector<std::string>& reglasInferidas, const bool& unaIteracion) {

	reglasInferidas.clear();

	principal.cargarTablaDesdeLaEntrada();

	principal.mostrarAtributosDatos();

	if(unaIteracion)

		id3(principal);

	else

		id3(principal,reglasInferidas);

}

void mostrarReglas(const std::vector<std::string>& reglasInferidas) {

	if(!reglasInferidas.empty()) {

		for(const std::string regla : reglasInferidas)

			std::cout << regla << std::endl;

	} else

		std::cout << "PRIMERO RESUELVA COMPLETAMENTE ALGUN EJEMPLO MEDIANTE ID3." << std::endl;

}

static std::pair<std::map<std::string,std::string>,std::string> transformarRegla(std::string regla) {

	std::map<std::string,std::string> soluciones;

	std::string valor = regla.substr(regla.find("-->")+3,regla.size());

	regla.erase(regla.begin()+regla.find("-->"),regla.end());

	while(regla.find("^") < regla.size()) {

		std::string condicion = regla.substr(0,regla.find("^"));

		soluciones[condicion.substr(0,condicion.find(":"))] = condicion.substr(condicion.find(":")+1,condicion.size());

		regla.erase(regla.begin(),regla.begin()+regla.find("^")+1);

	}

	soluciones[regla.substr(0,regla.find(":"))] = regla.substr(regla.find(":")+1,regla.size());

	return { soluciones , valor };

}

void clasificarDatos(tabla& principal, std::vector<std::string>& reglasInferidas) {

	if(reglasInferidas.empty())

		std::cout << "PRIMERO RESUELVA COMPLETAMENTE ALGUN EJEMPLO MEDIANTE ID3." << std::endl;

	else {

		std::string valor;

		bool coincide = false;

		std::map<std::string,std::string> usuarioClaveValor;

		for(size_t i = 0 ; i < principal.getAtributos().size() - 1 ; ++i) {

			std::cout << "INTRODUCE UN VALOR PARA EL ATRIBUTO '" << principal.getAtributos()[i] << "' O INTRODUCE '#' PARA DESCARTARLO: ";
			std::cin >> valor;

			if(valor.compare("#") != 0)

				usuarioClaveValor[principal.getAtributos()[i]] = valor;

		}

		for(size_t i = 0 ; i < reglasInferidas.size() && !coincide ; ++i) {

			auto reglaValor = transformarRegla(reglasInferidas[i]);

			if(usuarioClaveValor.size() == reglaValor.first.size()) {

				coincide = true;

				for(auto it = reglaValor.first.begin() ; it != reglaValor.first.end() && coincide ; ++it)

					if(!(usuarioClaveValor.count((*it).first) && usuarioClaveValor[(*it).first] == (*it).second))

						coincide = false;

				if(coincide)

					std::cout << std::endl << "CONCLUSION ==> " << reglaValor.second << std::endl;

			}

		}

		if(!coincide)

			std::cout << std::endl << "CONCLUSION ==> LOS DATOS INTRODUCIDOS NO SE CORRESPONDEN CON NINGUNA REGLA." << std::endl;

	}

}
