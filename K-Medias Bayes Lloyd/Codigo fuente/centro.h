class centro {

private:

	static double e;
	static double k;
	static double g;

	std::string nombre;

	vectorCentral centroActual;
	vectorCentral centroAnterior;

	void recalcularCentroConRespectoMuestra(const vector& muestra) {

		this->centroActual = centroActual +  g * (muestra - centroActual);

	}

public:

	centro(const std::string& nombre, const vectorCentral& centroActual)
		: nombre(nombre) , centroActual(centroActual) {}

	void recalcularCentro(const vector& muestra) {

		for(size_t i = 0 ; i < k ; ++i) {

			centroAnterior = centroActual;

			recalcularCentroConRespectoMuestra(muestra);

		}

	}

	double distanciaDesdeElCentroHastaLaMuestra(const vector& muestra) {

		double solucion = 0;

		for(size_t k = 0 ; k < centroActual.size() ; ++k)

			solucion += std::pow(centroActual[k]-muestra[k],2);

		return solucion;

	}

	void setE(const double& e) {

		this->e = e;

	}

	void setK(const double& k) {

		this->k = k;

	}

	void setG(const double& g) {

		this->g = g;

	}

	double& getE() {

		return this->e;

	}

	const std::string& getNombreClase() {

		return this->nombre;

	}

	const vectorCentral& getCentroActual() {

		return this->centroActual;

	}

	const vectorCentral& getCentroAnterior() {

		return this->centroAnterior;

	}

	size_t getDimensionDelVectorCentral() {

		return this->centroActual.size();

	}

};

double centro::k = 2;
double centro::g = 0.1;
double centro::e = 0.0000000001;
