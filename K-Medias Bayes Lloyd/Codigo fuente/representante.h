class representante {

private:

	static double b;
	static double e;

	std::string nombre;

	vectorCentral centroActual;
	vectorCentral centroAnterior;

	static std::unordered_map<std::string,vector> claseCentro;

	double sumatoriaDeLasInversasDeLasDistanciasDeLaClaseHastaLaMuestra(const vector& muestra) const {

		double componentes;
		double solucion = 0;

		for(const auto& c : claseCentro) {

			componentes = 0;

			for(size_t k = 0 ; k < muestra.size() ; ++k)

				componentes += std::pow( muestra[k] - c.second[k] , 2 );

			solucion += std::pow( 1/componentes , 1/(b-1) );

		}

		return solucion;

	}

	double inversaDeLaDistanciaDesdeLaClaseHastaMuestra(const vector& muestra) const {

		double solucion = 0;

		for(size_t i = 0 ; i < centroActual.size() ; ++i)

			solucion += std::pow( muestra[i] - centroActual[i]  , 2 );

		return std::pow( 1/solucion , 1/(b-1) );

	}

public:

	representante(const std::string& nombre, const vectorCentral& vctrCntrl)
		: nombre(nombre) , centroActual(vctrCntrl) {}

	double calcularGradoDePertenencia(const vector& muestra) const {

		double numerador = inversaDeLaDistanciaDesdeLaClaseHastaMuestra(muestra);

		double denominador = sumatoriaDeLasInversasDeLasDistanciasDeLaClaseHastaLaMuestra(muestra);

		return numerador / denominador;

	}

	void recalcularCentro(const conjuntoDeMuestras& muestras, matrizU& mU) {

		double denominador = 0;

		this->centroAnterior = this->centroActual;

		vector numerador(muestras[0].size());

		for(size_t muestra = 0 ; muestra < muestras.size() ; ++muestra)

			numerador = numerador + std::pow(mU[this->nombre][muestra],b) * muestras[muestra];

		for(size_t muestra = 0 ; muestra < mU[this->nombre].size() ; ++muestra)

			denominador += std::pow(mU[this->nombre][muestra],b);

		this->centroActual = numerador / denominador;

		claseCentro[this->nombre] = this->centroActual;

	}

	bool iterarDeNuevo() {

		double solucion = 0;

		for(size_t k = 0 ; k < this->centroActual.size() ; ++k)

			solucion += std::pow( this->centroActual[k] - this->centroAnterior[k] , 2 );

		return solucion < this->e;

	}

	double distanciaDesdeLaMuestraHastaLaClase(const vector& muestra) {

		double solucion = 0;

		for(size_t k = 0 ; k < this->centroActual.size() ; ++k)

			solucion += std::pow( this->centroActual[k] - muestra[k] , 2 );

		return solucion;

	}

	const std::string& getNombre() const {

		return this->nombre;

	}

	const vector& getCentro() const {

		return this->centroActual;

	}

	void setClaseCentro(const std::unordered_map<std::string,vector>& claseCentro) {

		this->claseCentro = claseCentro;

	}

	void setB(const double& b) {

		this->b = b;

	}

	void setE(const double& e) {

		this->e = e;

	}

};

double representante::b = 2;
double representante::e = 0.01;
std::unordered_map<std::string,vector> representante::claseCentro = std::unordered_map<std::string,vector>();
