class tabla {

private:

	bool esTablaFinal;
	std::string nombre;
	std::vector<tabla> subTablas;
	std::set<std::string> decisiones;
	std::vector<std::string> atributos;
	std::vector<std::vector<std::string>> datos;
	std::priority_queue<atributo,std::vector<atributo>,comparador> ordenarPorEntropia;

	void cargarAtributos() {

		std::string linea;
		std::string atributo;

		std::ifstream in("Atributos.txt");
		auto cinbuf = std::cin.rdbuf(in.rdbuf());

		getline(std::cin,linea);

		std::cin.rdbuf(cinbuf);

		std::stringstream lin(linea);

		while(getline(lin,atributo,','))

			atributos.push_back(atributo);

	}

	void cargarDatos() {

		std::string linea;
		std::string valor;

		std::ifstream in("Datos.txt");
		auto cinbuf = std::cin.rdbuf(in.rdbuf());

		getline(std::cin,linea,'\n');

		while(std::cin) {

			std::stringstream l(linea);

			datos.push_back(std::vector<std::string>());

			while(std::cin && getline(l,valor,','))

				datos[datos.size()-1].push_back(valor);

			getline(std::cin,linea,'\n');

		}

		std::cin.rdbuf(cinbuf);

	}

	void cargarDecisiones() {

		for(size_t fila = 0 ; fila < datos.size() ; ++fila)

			decisiones.insert(datos[fila][datos[fila].size()-1]);

	}

public:

	tabla(const std::string& nom) : esTablaFinal(false) , nombre(nom) {}

	void cargarTablaDesdeLaEntrada() {

		cargarAtributos();
		cargarDatos();
		cargarDecisiones();

		esTablaFinal = (decisiones.size() == 1);

		if(esTablaFinal)

			nombre = "--> " + *decisiones.begin();

		if(decisiones.size() < 1 || decisiones.size() > 2)

			throw "ERROR: EL NUMERO DE CLASIFICADORES DEBE SER 1 O 2.";

		for(size_t i = 0 ; i < datos.size() ; ++i)

			if(datos[i].size() != atributos.size())

				throw "ERROR: EL NUMERO DE COLUMNAS DE ATRIBUTOS Y DATOS NO SON COINCIDENTES.";

	}

	void mostrarAtributosDatos() {

		for(size_t i = 0 ; i < atributos.size() ; ++i)

			std::cout << "+" << std::setfill('*') << std::setw(20) << "+";

		std::cout << std::endl;

		std::cout << "+ " << this->nombre << std::endl;

		for(size_t i = 0 ; i < atributos.size() ; ++i)

			std::cout << "+" << std::setfill('*') << std::setw(20) << "+";

		std::cout << std::endl;

		for(const std::string& r : atributos)

			std::cout << "+" << std::setfill(' ') << std::setw(18) << r << " +";

		std::cout << std::endl;

		for(size_t i = 0 ; i < atributos.size() ; ++i)

			std::cout << "+" << std::setfill('*') << std::setw(20) << "+";

		std::cout << std::endl;

		for(const std::vector<std::string>& fila : datos) {

			for(std::string columna : fila)

				std::cout << "+" << std::setfill(' ') << std::setw(18) << columna << " +";

			std::cout << std::endl;

		}

		for(size_t i = 0 ; i < atributos.size() ; ++i)

			std::cout << "+" << std::setfill('*') << std::setw(20) << "+";

		std::cout << std::endl << std::endl;

	}

	void resolverTabla() {

		for (size_t columna = 0 ; columna < atributos.size() - 1 ; ++columna) {

			atributo atributo(atributos[columna]);

			for (size_t fila = 0 ; fila < datos.size() ; ++fila)

				for (const auto& decision : decisiones)

					atributo.inicializarValor(datos[fila][columna],decision);

			for (size_t fila = 0 ; fila < datos.size() ; ++fila)

				atributo.insertarValor(datos[fila][columna],datos[fila][datos[fila].size()-1]);

			atributo.calcularMerito();

			ordenarPorEntropia.push(atributo);

		}

		bool continuar = true;
		size_t posicionDelAtributo = 0;

		while(posicionDelAtributo < atributos.size() && continuar) {

			if(atributos[posicionDelAtributo].compare(ordenarPorEntropia.top().getNombre()) == 0)

				continuar = false;

			else

				++posicionDelAtributo;

		}

		for(const std::string& nombreRama : ordenarPorEntropia.top().getValores()) {

			tabla t((this->nombre == "")? (atributos[posicionDelAtributo] + ":" + nombreRama) : (this->nombre + "^" + atributos[posicionDelAtributo] + ":" + nombreRama));

			std::vector<std::string> tAtributos = atributos;
			tAtributos.erase(tAtributos.begin()+posicionDelAtributo);
			t.setAtributos(tAtributos);

			std::vector<std::vector<std::string>> tDatos = datos;

			for (size_t fila = 0 ; fila < tDatos.size() ; ++fila) {

				if (tDatos[fila][posicionDelAtributo].compare(nombreRama) != 0) {

					tDatos.erase(tDatos.begin()+fila);

					--fila;

				}

			}

			for(std::vector<std::string>& fila : tDatos)

				fila.erase(fila.begin()+posicionDelAtributo);

			t.setDatos(tDatos);

			t.cargarDecisiones();

			t.esTablaFinal = (t.decisiones.size() == 1);

			if(t.esTablaFinal)

				t.nombre += "-->" + t.atributos[t.atributos.size()-1] + ":" + t.datos[0][t.datos[0].size()-1];

			this->subTablas.push_back(t);

		}

	}

	void setAtributos(const std::vector<std::string>& atributos) {
		this->atributos = atributos;
	}

	void setDatos(const std::vector<std::vector<std::string>>& datos) {
		this->datos = datos;
	}

	std::vector<tabla> getSubTablas() const {
		return this->subTablas;
	}

	bool getEsTablaFinal() const {
		return this->esTablaFinal;
	}

	const std::string& getNombre() const {
		return this->nombre;
	}

	const std::vector<std::string>& getAtributos() const {
		return atributos;
	}

};
