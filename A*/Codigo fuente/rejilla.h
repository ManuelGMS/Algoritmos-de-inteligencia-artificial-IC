class rejilla {

private:

	int alto;
	int ancho;
	coordenada salida;
	coordenadas metas;
	coordenadas obstaculos;
	coordenadas puntosDePaso;
	dMatriz informacionInterna;
	cMatriz representacionInterna;

	bool caracteresCorrectos() {

		bool rejillaCorrecta = true;

		for (int fila = 0 ; fila < alto && rejillaCorrecta ; ++fila) {

			for (int columna = 0 ; columna < ancho && rejillaCorrecta ; ++columna) {

				switch(representacionInterna[fila][columna]) {
					case '#': break;
					case '.': break;
					case 'S': break;
					case 'M': break;
					default: rejillaCorrecta = false; break;
				}


			}

		}

		return rejillaCorrecta;

	}

	bool dimensionCorrecta() {

		bool rejillaCorrecta = true;

		for (int fila = 0 ; fila < alto - 1 && rejillaCorrecta ; ++fila)

			rejillaCorrecta = (representacionInterna[fila].size() == representacionInterna[fila+1].size());

		return rejillaCorrecta;

	}

public:

	void leerDeFichero() {

		int fil = 0;
		int col = 0;

		std::string linea;

		std::ifstream in("Tablero.txt");
		auto cinbuf = std::cin.rdbuf(in.rdbuf());

		do {

			std::getline(std::cin,linea);

			if(!std::cin) {
				std::cin.rdbuf(cinbuf);
				throw std::logic_error("\nERROR AL CARGAR EL FICHERO: NO SE ENCONTRO LA MARCA DE CIERRE DE LA REJILLA.\n");
			}

			if(linea.compare("FINAL_DE_REJILLA") != 0) {

				cFila f;

				col = 0;

				for(char& c : linea) {

					f.push_back(c);

					c = toupper(c);

					if(c == C_SALIDA)

						salida = { fil , col };

					if(c == C_META)

						metas.push_back({ fil , col });

					++col;

				}

				++fil;

				this->representacionInterna.push_back(f);

			}

		} while(linea.compare("FINAL_DE_REJILLA") != 0);

		alto = fil;

		ancho = col;

		if(!caracteresCorrectos()) {
			std::cin.rdbuf(cinbuf);
			throw std::logic_error("\nERROR AL CARGAR EL FICHERO: HAY UN CARACTER DISTINTO DE { . , # , M , S } EN LA REJILLA.\n");
		}

		if(!dimensionCorrecta()) {
			std::cin.rdbuf(cinbuf);
			throw std::logic_error("\nERROR AL CARGAR EL FICHERO: EL NUMERO DE COLUMNAS NO ES IGUAL PARA TODAS LAS FILAS.\n");
		}

		do {

			std::cin >> col >> fil;

			if(!std::cin) {
				std::cin.rdbuf(cinbuf);
				throw std::logic_error("\nERROR AL CARGAR EL FICHERO: NO SE ENCONTRO LA MARCA DE CIERRE DE LOS PUNTOS DE PASO.\n");
			}

			if((col < 0 || col > ancho) || (fil < 0 || fil > alto) || (col == 0 && fil != 0) || (col != 0 && fil == 0)) {
				std::cin.rdbuf(cinbuf);
				throw std::logic_error("\nERROR AL CARGAR EL FICHERO: SE INTENTO PONER UN PUNTO DE PASO FUERA DE LA REJILLA.\n");
			}

			if(!(fil == 0 && col == 0) && this->representacionInterna[fil-1][col-1] != '.') {
				std::cin.rdbuf(cinbuf);
				throw std::logic_error("\nERROR AL CARGAR EL FICHERO: SE INTENTO PONER UN PUNTO DE PASO EN UNA CASILLA YA OCUPADA.\n");
			}

			if(!(fil == 0 && col == 0)) {

				puntosDePaso.push_back({ fil - 1 , col - 1 });
				representacionInterna[fil - 1][col - 1] = C_PUNTO_DE_PASO;

			}

		} while(!(fil == 0 && col == 0));

		double porcentajeDePenalizacion;
		informacionInterna = dMatriz(alto,dFila(ancho,D_LIBRE));

		do {

			std::cin >> col >> fil >> porcentajeDePenalizacion;

			if(!std::cin) {
				std::cin.rdbuf(cinbuf);
				throw std::logic_error("\nERROR AL CARGAR EL FICHERO: NO SE ENCONTRO LA MARCA DE CIERRE DE LAS PENALIZACIONES.\n");
			}

			if((col < 0 || col > ancho) || (fil < 0 || fil > alto) || (col == 0 && fil != 0) || (col != 0 && fil == 0)) {
				std::cin.rdbuf(cinbuf);
				throw std::logic_error("\nERROR AL CARGAR EL FICHERO: SE INTENTO PONER UNA PENALIZACION FUERA DE LA REJILLA.\n");
			}

			if(!(fil == 0 && col == 0) && this->representacionInterna[fil-1][col-1] != '.') {
				std::cin.rdbuf(cinbuf);
				throw std::logic_error("\nERROR AL CARGAR EL FICHERO: SE INTENTO PONER UNA PENALIZACION EN UNA CASILLA YA OCUPADA.\n");
			}

			if((porcentajeDePenalizacion < 0 || porcentajeDePenalizacion > 100) || (fil != 0 && col != 0 && porcentajeDePenalizacion == 0) ) {
				std::cin.rdbuf(cinbuf);
				throw std::logic_error("\nERROR AL CARGAR EL FICHERO: SE INTENTO PONER UN PORCENTAJE DE PENALIZACION FUERA DEL RANGO (1-100).\n");
			}

			if(!(fil == 0 && col == 0 && porcentajeDePenalizacion == 0)) {

				this->representacionInterna[fil - 1][col - 1] = C_PENALIZACION;
				this->informacionInterna[fil - 1][col - 1] = (alto * ancho) * (porcentajeDePenalizacion / 100);

			}

		} while(!(fil == 0 && col == 0 && porcentajeDePenalizacion == 0));

		std::cin.rdbuf(cinbuf);

	}

	void introducirPorConsola() {

		std::cout << std::endl;

		do {

			std::cout << "INTRODUCE EL ALTO Y EL ANCHO X _ Y (1-20/1-20): ";
			std::cin >> alto >> ancho;

			if(alto < 1 || alto > 20 || ancho < 1 || ancho > 20)

				std::cout << "DIMENSION DE LA REJILLA INCORRECTA, REINTRODUZCA OTRA DIMENSION." << std::endl;

			else

				std::cout << "SE HA ESTABLECIDO LA DIMENSION DE LA REJILLA EN: " << alto << " FILAS Y " << ancho << " COLUMNAS." << std::endl << std::endl;

		} while(alto < 1 || alto > 20 || ancho < 1 || ancho > 20);

		informacionInterna = dMatriz(alto,dFila(ancho,D_LIBRE));
		representacionInterna = cMatriz(alto,cFila(ancho,C_LIBRE));

		int x , y;

		do {

			std::cout << "INTRODUCE LA COORDENADA DE SALIDA X _ Y: ";
			std::cin >> x >> y;

			if(x < 1 || x > ancho || y < 1 || y > alto)

				std::cout << "POSICION DE LA SALIDA FUERA DEL TABLERO, REINTRODUZCA OTRA POSICION." << std::endl;

			else

				std::cout << "SE HA ESTABLECIDO LA POSICION DE SALIDA EN: ( " << x << " , " << y << " )" << std::endl << std::endl;

		} while(x < 1 || x > ancho || y < 1 || y > alto);

		this->salida = { y - 1 , x - 1 };
		this->representacionInterna[y - 1][x - 1] = C_SALIDA;

		do {

			do {

				std::cout << "INTRODUCE LAS COORDENADAS DE LA META X _ Y / 0 _ 0 , DEBE INTRODUCIR AL MENOS UNA: ";
				std::cin >> x >> y;

				if((x < 0 || x > ancho) || (y < 0 || y > alto) || (x == 0 && y != 0) || (x != 0 && y == 0)) {

					std::cout << "POSICION DE LA META FUERA DEL TABLERO, REINTRODUZCA OTRA POSICION." << std::endl;

				} else if((!(x == 0 && y == 0) && this->representacionInterna[y - 1][x - 1] != C_LIBRE)) {

					std::cout << "POSICION OCUPADA, REINTRODUZCA OTRA POSICION." << std::endl;

				} else if(!(x == 0 && y == 0)) {

					std::cout << "SE HA ESTABLECIDO UNA POSICION DE META EN: ( " << x << " , " << y << " )" << std::endl;

				} else {

					if(metas.size() > 0)

						std::cout << std::endl;

				}

			} while(((x < 0 || x > ancho) || (y < 0 || y > alto) || (x == 0 && y != 0) || (x != 0 && y == 0)) || (!(x == 0 && y == 0) && this->representacionInterna[y - 1][x - 1] != C_LIBRE));

			if(!(x == 0 && y == 0)) {

				metas.push_back({ y - 1, x - 1 });
				this->representacionInterna[y - 1][x - 1] = C_META;

			}

		} while((metas.size() == 0) || !(x == 0 && y == 0));

		do {

			do {

				std::cout << "COORDENADA PARA CASILLA PROHIBIDA X _ Y / 0 _ 0 : ";
				std::cin >> x >> y;

				if((x < 0 || x > ancho) || (y < 0 || y > alto) || (x == 0 && y != 0) || (x != 0 && y == 0)) {

					std::cout << "POSICION DEL OBSTACULO FUERA DEL TABLERO, REINTRODUZCA OTRA POSICION." << std::endl;

				} else if((!(x == 0 && y == 0) && this->representacionInterna[y - 1][x - 1] != C_LIBRE)) {

					std::cout << "POSICION OCUPADA, REINTRODUZCA OTRA POSICION." << std::endl;

				} else if(!(x == 0 && y == 0)) {

					std::cout << "SE HA ESTABLECIDO UN OBSTACULO EN LA POSICION: ( " << x << " , " << y << " )" << std::endl;

				} else {

					std::cout << std::endl;

				}

			} while(((x < 0 || x > ancho) || (y < 0 || y > alto) || (x == 0 && y != 0) || (x != 0 && y == 0)) || (!(x == 0 && y == 0) && this->representacionInterna[y - 1][x - 1] != C_LIBRE));

			if(x != 0 && y != 0)

				this->representacionInterna[y - 1][x - 1] = C_PROHIBIDO;

		} while(!(x == 0 && y == 0));

		do {

			do {

				std::cout << "INTRODUCE LOS PUNTOS DE PASO X _ Y / 0 _ 0 : ";
				std::cin >> x >> y;

				if((x < 0 || x > ancho) || (y < 0 || y > alto) || (x == 0 && y != 0) || (x != 0 && y == 0)) {

					std::cout << "POSICION DEL PUNTO DE PASO FUERA DEL TABLERO, REINTRODUZCA OTRA POSICION." << std::endl;

				} else if((!(x == 0 && y == 0) && this->representacionInterna[y - 1][x - 1] != C_LIBRE)) {

					std::cout << "POSICION OCUPADA, REINTRODUZCA OTRA POSICION." << std::endl;

				} else if(!(x == 0 && y == 0)) {

					std::cout << "SE HA ESTABLECIDO UN PUNTO DE PASO EN LA POSICION: ( " << x << " , " << y << " )" << std::endl;

				} else {

					std::cout << std::endl;

				}

			} while(((x < 0 || x > ancho) || (y < 0 || y > alto) || (x == 0 && y != 0) || (x != 0 && y == 0)) || (!(x == 0 && y == 0) && this->representacionInterna[y - 1][x - 1] != C_LIBRE));

			if(x != 0 && y != 0) {

				this->puntosDePaso.push_back({ y - 1, x - 1 });
				this->representacionInterna[y - 1][x - 1] = C_PUNTO_DE_PASO;

			}

		} while(!(x == 0 && y == 0));

		double porcentajeDePenalizacion;

		do {

			do {

				std::cout << "INTRODUCE LAS PENALIZACIONES X _ Y _ P / 0 _ 0 _ 0 : ";
				std::cin >> x >> y >> porcentajeDePenalizacion;

				if((x < 0 || x > ancho) || (y < 0 || y > alto) || (x == 0 && y != 0) || (x != 0 && y == 0)) {

					std::cout << "POSICION DE LA PENALIZACION FUERA DEL TABLERO, REINTRODUZCA OTRA POSICION." << std::endl;

				} else if((!(x == 0 && y == 0) && this->representacionInterna[y - 1][x - 1] != C_LIBRE)) {

					std::cout << "POSICION OCUPADA, REINTRODUZCA OTRA POSICION." << std::endl;

				} else if(porcentajeDePenalizacion < 0 || porcentajeDePenalizacion > 100 || (x != 0 && y != 0 && porcentajeDePenalizacion == 0)) {

					std::cout << "EL PORCENTAJE DE PENALIZACION NO ESTA EN EL RANGO (1-100), REINTRODUZCA OTRO PORCENTAJE." << std::endl;

				} else if(!(x == 0 && y == 0)) {

					std::cout << "SE HA ESTABLECIDO LA PENALIZACION: ( " << x << " , " << y << " , " << porcentajeDePenalizacion << " )" << std::endl;

				}

			} while(((x < 0 || x > ancho) || (y < 0 || y > alto) || (x == 0 && y != 0) || (x != 0 && y == 0)) || (porcentajeDePenalizacion < 0 || porcentajeDePenalizacion > 100 || (x != 0 && y != 0 && porcentajeDePenalizacion == 0)) || (!(x == 0 && y == 0) && this->representacionInterna[y - 1][x - 1] != C_LIBRE));

			if(!(x == 0 && y == 0 && porcentajeDePenalizacion == 0)) {

				this->representacionInterna[y - 1][x - 1] = C_PENALIZACION;
				this->informacionInterna[y - 1][x - 1] = (alto * ancho) * (porcentajeDePenalizacion / 100);

			}

		} while(!(x == 0 && y == 0 && porcentajeDePenalizacion == 0));

	}

	int getAlto() const {
		return alto;
	}

	int getAncho() const {
		return ancho;
	}

	const coordenadas& getMetas() const {
		return metas;
	}

	const coordenada& getSalida() const {
		return salida;
	}

	const coordenadas& getObstaculos() const {
		return obstaculos;
	}

	const coordenadas& getPuntosDePaso() const {
		return puntosDePaso;
	}

	const dMatriz& getInformacionInterna() const {
		return informacionInterna;
	}

	const cMatriz& getRepresentacionInterna() const {
		return representacionInterna;
	}

	void setMetas(const coordenadas& metas) {
		this->metas = metas;
	}

	void setSalida(const coordenada& salida) {
		this->salida = salida;
	}

	void setElementoInterno(const char& elemento, const coordenada& coord) {
		this->representacionInterna[coord.first][coord.second] = elemento;
	}

	void setRepresentacionInterna(const cMatriz& representacionInterna) {
		this->representacionInterna = representacionInterna;
	}

	friend std::ostream& operator<<(std::ostream& os, const rejilla& miRejilla);

};

inline std::ostream& operator << (std::ostream& os, const rejilla& miRejilla) {

	for(const auto& fila : miRejilla.getRepresentacionInterna()) {

		for(const auto& celda : fila)

			std::cout << celda << " ";

		std::cout << std::endl;

	}

	return os;

}
