#include <queue>
#include <cmath>
#include <vector>
#include <limits>
#include <fstream>
#include <iostream>
#include <exception>
#include <algorithm>

#include "constantes.h"
#include "tipos.h"
#include "nodo.h"
#include "comparadores.h"
#include "rejilla.h"
#include "aEstrella.h"

bool ejecutarPorPasos() {

	std::string opcion;

	std::cout << std::endl;

	do {

		std::cout << "EJECUTAR POR PASOS EL ALGORITMO [SI/NO] : ";
		std::cin >> opcion;

		std::transform(opcion.begin(),opcion.end(),opcion.begin(),toupper);

	} while(opcion.compare("SI") != 0 && opcion.compare("NO") != 0);

	std::cout << std::endl;

	getchar();

	return !opcion.compare("SI");

}

void comenzarPrograma() {

	std::string opcion;

	rejilla* miRejilla = nullptr;

	aEstrella* algoritmo = nullptr;

	do {

		std::cout << "1 -- LEER TABLERO DE UN FICHERO." << std::endl;
		std::cout << "2 -- INTRODUCIR TABLERO DESDE CONSOLA." << std::endl;
		std::cout << "3 -- SALIR DEL PROGRAMA." << std::endl;
		std::cout << "INTRODUCE UNA OPCION: ";
		std::cin >> opcion;

		if(!opcion.compare("1")) {

			miRejilla = new rejilla();

			try {

				miRejilla->leerDeFichero();

				algoritmo = new aEstrella(*miRejilla,ejecutarPorPasos());

				if(miRejilla->getPuntosDePaso().size() > 0)

					algoritmo->resolverConPuntosDePaso();

				else

					algoritmo->resolver();

				delete algoritmo;

			} catch(const std::exception& e) {

				std::cout << e.what() << std::endl;

			}

			delete miRejilla;

		}

		if(!opcion.compare("2")) {

			miRejilla = new rejilla();

			miRejilla->introducirPorConsola();

			algoritmo = new aEstrella(*miRejilla,ejecutarPorPasos());

			if(miRejilla->getPuntosDePaso().size() > 0)

				algoritmo->resolverConPuntosDePaso();

			else

				algoritmo->resolver();

			delete algoritmo;

			delete miRejilla;

		}

	} while(opcion.compare("3") != 0);

}

int main() {

	comenzarPrograma();

	return 0;

}
