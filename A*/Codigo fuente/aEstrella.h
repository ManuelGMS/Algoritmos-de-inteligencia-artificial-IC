class aEstrella {

private:

	bool ejecutarPorPasos;

	bool solucionEncontrada;

	rejilla& rejillaObjetivo;

	bool problemaInsatisfactible;

	std::vector<Nodo*> redDeNodos;

	std::vector<Nodo*> vectorDeReciclaje;

	std::priority_queue<Nodo*,std::vector<Nodo*>,comparador> listaAbierta;

	void recorridoDescendente(Nodo& padre) {

		for(Nodo* hijo : padre.getHijo()) {

			hijo->setCosteDesdeInicioHastaMi(padre.getCosteDesdeInicioHastaMi() + hijo->getCosteDeDesplazarseDesdePadreHastaMi());

			hijo->setCosteTotal(hijo->getPenalizacion() + hijo->getCosteDesdeInicioHastaMi() + hijo->getCosteDesdeMiHastaLaMeta());

			recorridoDescendente(*hijo);

		}

	}

	void resolverConflictoPara(Nodo& nodoConflictivo) {

		double costeDelDesplazamiento = 0;

		// COMPROBACION ORTOGONAL

		// ARRIBA
		if(nodoConflictivo.getPosicion().first + 1 == nodoConflictivo.getPadre()[1]->getPosicion().first && nodoConflictivo.getPosicion().second == nodoConflictivo.getPadre()[1]->getPosicion().second)

			costeDelDesplazamiento = 1;

		// ABAJO
		if(nodoConflictivo.getPosicion().first - 1 == nodoConflictivo.getPadre()[1]->getPosicion().first && nodoConflictivo.getPosicion().second == nodoConflictivo.getPadre()[1]->getPosicion().second)

			costeDelDesplazamiento = 1;

		// IZQUIERDA
		if(nodoConflictivo.getPosicion().first == nodoConflictivo.getPadre()[1]->getPosicion().first && nodoConflictivo.getPosicion().second - 1 == nodoConflictivo.getPadre()[1]->getPosicion().second)

			costeDelDesplazamiento = 1;

		// DERECHA
		if(nodoConflictivo.getPosicion().first == nodoConflictivo.getPadre()[1]->getPosicion().first && nodoConflictivo.getPosicion().second + 1 == nodoConflictivo.getPadre()[1]->getPosicion().second)

			costeDelDesplazamiento = 1;

		// COMPROBACION DIAGONAL

		// ARRIBA DERECHA
		if(nodoConflictivo.getPosicion().first + 1 == nodoConflictivo.getPadre()[1]->getPosicion().first && nodoConflictivo.getPosicion().second + 1 == nodoConflictivo.getPadre()[1]->getPosicion().second)

			costeDelDesplazamiento = SQRT2;

		// ABAJO IZQUIERDA
		if(nodoConflictivo.getPosicion().first - 1 == nodoConflictivo.getPadre()[1]->getPosicion().first && nodoConflictivo.getPosicion().second - 1 == nodoConflictivo.getPadre()[1]->getPosicion().second)

			costeDelDesplazamiento = SQRT2;

		// ARRIBA IZQUIERDA
		if(nodoConflictivo.getPosicion().first + 1 == nodoConflictivo.getPadre()[1]->getPosicion().first && nodoConflictivo.getPosicion().second - 1 == nodoConflictivo.getPadre()[1]->getPosicion().second)

			costeDelDesplazamiento = SQRT2;

		// ABAJO DERECHA
		if(nodoConflictivo.getPosicion().first - 1 == nodoConflictivo.getPadre()[1]->getPosicion().first && nodoConflictivo.getPosicion().second + 1 == nodoConflictivo.getPadre()[1]->getPosicion().second)

			costeDelDesplazamiento = SQRT2;

		if(nodoConflictivo.getPadre()[1]->getCosteDesdeInicioHastaMi() + costeDelDesplazamiento < nodoConflictivo.getCosteDesdeInicioHastaMi()) {

			nodoConflictivo.setcosteDeDesplazarseDesdePadreHastaMi(costeDelDesplazamiento);

			nodoConflictivo.setCosteDesdeInicioHastaMi(nodoConflictivo.getPadre()[1]->getCosteDesdeInicioHastaMi() + nodoConflictivo.getCosteDeDesplazarseDesdePadreHastaMi());

			nodoConflictivo.setCosteTotal(nodoConflictivo.getPenalizacion() + nodoConflictivo.getCosteDesdeInicioHastaMi() + nodoConflictivo.getCosteDesdeMiHastaLaMeta());

			nodoConflictivo.getPadre()[0]->eliminarHijo(nodoConflictivo);

			nodoConflictivo.getPadre()[1]->nuevoHijo(nodoConflictivo);

			recorridoDescendente(nodoConflictivo);

			nodoConflictivo.intercambiarPadres();

		}

		nodoConflictivo.eliminarUltimoPadre();

	}

	int existeNodo(const int& y, const int& x) {

		int i = 0;

		bool noEncontrado = true;

		while (i < redDeNodos.size() && noEncontrado) {

			if(redDeNodos[i]->getPosicion().first == y && redDeNodos[i]->getPosicion().second == x)

				noEncontrado = false;

			else ++i;

		}

		return i;

	}

	void resuelveCaso(Nodo& padre, const int& desplY, const int& desplX, const double& coste) {

		if(rejillaObjetivo.getRepresentacionInterna()[padre.getPosicion().first+desplY][padre.getPosicion().second+desplX] != C_PROHIBIDO) {

			int i = existeNodo(padre.getPosicion().first+desplY,padre.getPosicion().second+desplX);

			if(i < redDeNodos.size()) {

				if(redDeNodos[i]->getPosicion().first != padre.getPosicion().first && redDeNodos[i]->getPosicion().second != padre.getPosicion().second) {

					redDeNodos[i]->nuevoPadre(padre);
					resolverConflictoPara(*redDeNodos[i]);

				}

			} else {

				Nodo* nuevo = new Nodo(&padre,{padre.getPosicion().first+desplY,padre.getPosicion().second+desplX},coste,rejillaObjetivo.getInformacionInterna()[padre.getPosicion().first+desplY][padre.getPosicion().second+desplX],rejillaObjetivo.getMetas());

				padre.nuevoHijo(*nuevo);

				listaAbierta.push(nuevo);

				redDeNodos.push_back(nuevo);

				vectorDeReciclaje.push_back(nuevo);

			}

		}

	}

	void expandir(Nodo& padre) {

		// NODO(FILA,COLUMNA)

		// DESPLAZAMIENTOS ORTOGONALES

		if(padre.getPosicion().first - 1 >= 0)

			resuelveCaso(padre,-1,0,1); // ABAJO

		if(padre.getPosicion().first + 1 < rejillaObjetivo.getAlto())

			resuelveCaso(padre,1,0,1); // ARRIBA

		if(padre.getPosicion().second - 1 >= 0)

			resuelveCaso(padre,0,-1,1); // IZQUIERDA

		if(padre.getPosicion().second + 1 < rejillaObjetivo.getAncho())

			resuelveCaso(padre,0,1,1); // DERECHA

		// DESPLAZAMIENTOS DIAGONALES

		if(padre.getPosicion().first - 1 >= 0 && padre.getPosicion().second - 1 >= 0)

			resuelveCaso(padre,-1,-1,SQRT2); // ABAJO IZQUIERDA

		if(padre.getPosicion().first + 1 < rejillaObjetivo.getAlto() && padre.getPosicion().second - 1 >= 0)

			resuelveCaso(padre,1,-1,SQRT2); // ARRIBA IZQUIERDA

		if(padre.getPosicion().first - 1 >= 0 && padre.getPosicion().second + 1 < rejillaObjetivo.getAncho())

			resuelveCaso(padre,-1,1,SQRT2); // ABAJO DERECHA

		if(padre.getPosicion().first + 1 < rejillaObjetivo.getAlto() && padre.getPosicion().second + 1 < rejillaObjetivo.getAncho())

			resuelveCaso(padre,1,1,SQRT2); // ARRIBA DERECHA


	}

	void reconstruirElCamino() {

		coordenadas recorridoInverso;

		Nodo* nodoActual = redDeNodos[redDeNodos.size()-1];

		while(nodoActual->getPadre()[0] != nullptr) {

			recorridoInverso.push_back(nodoActual->getPadre()[0]->getPosicion());

			nodoActual = nodoActual->getPadre()[0];

		}

		if(ejecutarPorPasos) {

			for (int i = recorridoInverso.size() - 1 ; i > -1 ; --i) {

				rejillaObjetivo.setElementoInterno(C_RECORRIDO,recorridoInverso[i]);

				std::cout << rejillaObjetivo << std::endl;
				std::cout << "PRESIONA 'ENTER' PARA CONTINUAR." << std::endl << std::endl;
				std::cout << "-----------------------------------------------" << std::endl;

				getchar();

			}

		} else {

			for (int i = recorridoInverso.size() - 1 ; i > -1 ; --i)

				rejillaObjetivo.setElementoInterno(C_RECORRIDO,recorridoInverso[i]);

		}

		rejillaObjetivo.setElementoInterno(C_SALIDA,rejillaObjetivo.getSalida());

		for(const coordenada& meta : rejillaObjetivo.getMetas())

			rejillaObjetivo.setElementoInterno(C_META,meta);

		for(const coordenada& puntoDePaso : rejillaObjetivo.getPuntosDePaso())

			rejillaObjetivo.setElementoInterno(C_PUNTO_DE_PASO,puntoDePaso);

		std::cout << rejillaObjetivo << std::endl;

	}

public:

	aEstrella(rejilla& r, bool pasos) : solucionEncontrada(false) , problemaInsatisfactible(false) , rejillaObjetivo(r) , ejecutarPorPasos(pasos) {

	}

	~aEstrella() {

		for(Nodo* nodo : vectorDeReciclaje)

			delete nodo;

	}

	void resolverConPuntosDePaso() {

		double costeTotalDelRecorrido = 0;

		coordenadas metasIniciales = rejillaObjetivo.getMetas();

		for (int i = 0; i < rejillaObjetivo.getPuntosDePaso().size() && !problemaInsatisfactible ; ++i) {

			rejillaObjetivo.setMetas({rejillaObjetivo.getPuntosDePaso()[i]});

			resolver();

			costeTotalDelRecorrido += redDeNodos[redDeNodos.size()-1]->getCosteTotal();

			if(solucionEncontrada)

				solucionEncontrada = false;

			while(!listaAbierta.empty())

				listaAbierta.pop();

			while(!redDeNodos.empty())

				redDeNodos.pop_back();

			rejillaObjetivo.setSalida(rejillaObjetivo.getPuntosDePaso()[i]);

		}

		if(!problemaInsatisfactible) {

			rejillaObjetivo.setMetas(metasIniciales);

			resolver();

			if(!problemaInsatisfactible) {

				costeTotalDelRecorrido += redDeNodos[redDeNodos.size()-1]->getCosteTotal();

				std::cout << "EL COSTE TOTAL DEL RECORRIDO ES: " << costeTotalDelRecorrido << std::endl << std::endl;

			}

		}

	}

	void resolver() {

		Nodo* inicial = new Nodo(nullptr,rejillaObjetivo.getSalida(),0,0,rejillaObjetivo.getMetas());

		listaAbierta.push(inicial);

		vectorDeReciclaje.push_back(inicial);

		while(!solucionEncontrada && !problemaInsatisfactible) {

			if(!listaAbierta.empty()) {

				Nodo* nodoActual = listaAbierta.top();

				listaAbierta.pop();

				redDeNodos.push_back(nodoActual);

				for(const coordenada& c : rejillaObjetivo.getMetas())

					if(nodoActual->getPosicion().first == c.first && nodoActual->getPosicion().second == c.second)

						solucionEncontrada = true;

				if(!solucionEncontrada)

					expandir(*nodoActual);

			} else {

				problemaInsatisfactible = true;

			}

		}

		if(!problemaInsatisfactible) {

			reconstruirElCamino();

			std::cout << "EL COSTE DEL RECORRIDO ES: " << redDeNodos[redDeNodos.size()-1]->getCosteTotal() << std::endl << std::endl;

		} else {

			std::cout << "EL PROBLEMA ES INSATISFACTIBLE." << std::endl << std::endl;

		}

	}

};
