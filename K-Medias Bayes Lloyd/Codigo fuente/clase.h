class clase {

private:

	vectorMedia m;

	nombreClase nombre;

	matrizDeCobarianza mcb;

	conjuntoDeMuestras muestras;

	subMatricesDeCobarianza smcb;

	matrizDeCobarianzaInversa mcbi;

	void calcularVectorM() {

		vectorMedia m(muestras[0].size());

		for(const vector& mstr : muestras)

			m = m + mstr;

		for(double& valor : m)

			valor /= muestras.size();

		this->m = m;

	}

	void calcularSubMatricesDeCobarianza() {

		for(const vector& mstr : muestras)

			smcb.push_back( std::make_pair((mstr - m),false) * std::make_pair((mstr - m),true) );

	}

	void calcularMatrizDeCobarianza() {

		matriz mcb(smcb[0].size(),vector(smcb[0].size()));

		for(const matriz& sm : smcb)

			mcb = mcb + sm;

		this->mcb = mcb;

	}

	matriz generarMatrizIdentidad(const int& filasColumnas) {

		matriz mtrx(filasColumnas,vector(filasColumnas,0));

		for(int i = 0 ; i < filasColumnas ; ++i)

			mtrx[i][i] = 1;

		return mtrx;

	}

	void calcularMatrizDeCobarianzaInversa() {

		matriz original = this->mcb;

		matriz identidad = generarMatrizIdentidad(mcb.size());

		for(size_t d = 0 ; d < original.size() ; ++d) {

			double n = original[d][d];

			for(size_t j = 0 ; j < original.size() ; ++j) {

				original[d][j] /= n;

				identidad[d][j] /= n;

			}

			for(size_t i = 0 ; i < d ; ++i) {

				double w = original[i][d];

				if(w != 0)

					for(size_t j = 0 ; j < original.size() ; ++j) {

						original[i][j] -= w * original[d][j];

						identidad[i][j] -= w * identidad[d][j];

					}

			}

			for(size_t i = d + 1 ; i < original.size() ; ++i) {

				double w = original[i][d];

				if(w != 0)

					for(size_t j = 0 ; j < original.size() ; ++j) {

						original[i][j] -= w * original[d][j];

						identidad[i][j] -= w * identidad[d][j];

					}

			}

		}

		this->mcbi = identidad;

	}

public:

	clase(const std::string& nombre, const conjuntoDeMuestras& muestras) : nombre(nombre) , muestras(muestras) {

		calcularVectorM();

		calcularSubMatricesDeCobarianza();

		calcularMatrizDeCobarianza();

		calcularMatrizDeCobarianzaInversa();

	}

	double distanciaDeMahalanobis(const vector& x) {

		return (std::make_pair((x - m) * mcbi,true) * std::make_pair((x - m),false))[0][0];

	}

	const std::string& getNombreClase() {

		return this->nombre;

	}

	size_t getDimensionDelVectorM() {

		return this->m.size();

	}

};
