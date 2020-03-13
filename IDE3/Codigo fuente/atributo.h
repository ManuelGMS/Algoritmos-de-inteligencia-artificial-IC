class atributo {

private:

	double merito;
	std::string nombre;
	std::map<std::string,std::map<std::string,int>> valorDecisionContador;

	double informacion(const double& p, const double& n) {

		return (-1) * (p * ((p == 0)? 0 : log2(p)) + n * ((n == 0)? 0 : log2(n)) );

	}

public:

	atributo(const std::string& nom) : merito(0) , nombre(nom) {}

	void inicializarValor(const std::string& valor, const std::string& decision) {

		valorDecisionContador[valor][decision] = 0;

	}

	void insertarValor(const std::string& valor, const std::string& decision) {

		valorDecisionContador[valor][decision]++;

	}

	void calcularMerito() {

		int N = 0;
		int contador = 0;
		bool estado = true;
		std::vector<int> a;
		std::vector<double> r;
		std::vector<double> p;
		std::vector<double> n;

		for(const auto& claveValor : valorDecisionContador) {

			a.push_back(0);

			for(const auto& cV : claveValor.second) {

				a[a.size()-1] += cV.second;

				N += cV.second;

			}

		}

		for(const auto& claveValor : valorDecisionContador) {

			for(const auto& cV : claveValor.second) {

				if(estado)

					p.push_back(double(cV.second)/double(a[contador]));

				else

					n.push_back(double(cV.second)/double(a[contador]));

				estado = !estado;

			}

			++contador;

		}

		for (size_t i = 0 ; i < a.size() ; ++i)

			r.push_back(double(a[i])/double(N));

		for (size_t i = 0; i < r.size() ; ++i)

			merito += r[i] * informacion(p[i],n[i]);

	}

	double getMerito() const {

		return merito;

	}

	const std::string& getNombre() const {

		return nombre;

	}

	std::vector<std::string> getValores() const {

		std::vector<std::string> valores;

		for(auto it = valorDecisionContador.begin() ; it != valorDecisionContador.end() ; ++it)

			valores.push_back((*it).first);

		return valores;

	}

};
