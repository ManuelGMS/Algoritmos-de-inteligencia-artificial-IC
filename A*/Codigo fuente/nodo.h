class Nodo {

private:

	double costeTotal;
	double penalizacion;
	coordenada posicion;
	std::vector<Nodo*> hijo;
	std::vector<Nodo*> padre;
	double costeDesdeInicioHastaMi;
	double costeDesdeMiHastaLaMeta;
	double costeDeDesplazarseDesdePadreHastaMi;

public:

	Nodo(Nodo* p, const coordenada& pos, const double& coste, const double& penaliza, const coordenadas& metas) :
	costeDesdeInicioHastaMi( (p != nullptr)? ((*p).getCosteDesdeInicioHastaMi() + coste) : 0 ) ,
	costeDeDesplazarseDesdePadreHastaMi(coste) ,
	padre(std::vector<Nodo*>(1,p)) ,
	costeDesdeMiHastaLaMeta(0) ,
	penalizacion(penaliza) ,
	posicion(pos) ,
	costeTotal(0) {

		double distanciaMejor = MAS_INFINITO;

		for (const coordenada& posicion : metas)

			distanciaMejor = std::min(distanciaEuclidea(this->posicion,posicion),distanciaMejor);

		this->costeDesdeMiHastaLaMeta = distanciaMejor;

		this->costeTotal = this->penalizacion + this->costeDesdeInicioHastaMi + this->costeDesdeMiHastaLaMeta;

	}

	double distanciaEuclidea(const coordenada& p1, const coordenada& p2) {
		return sqrt(pow(p1.first-p2.first,2)+pow(p1.second-p2.second,2));
	}

	void nuevoPadre(Nodo& nodoPadre) {
		this->padre.push_back(&nodoPadre);
	}

	void nuevoHijo(Nodo& nodoHijo) {
		this->hijo.push_back(&nodoHijo);
	}

	void intercambiarPadres() {
		std::swap(padre[0],padre[1]);
	}

	void eliminarUltimoPadre() {
		padre.pop_back();
	}

	void eliminarHijo(const Nodo& nodoHijo) {

		bool encontrado = false;

		for (int i = 0 ; i < hijo.size() && !encontrado ; ++i) {

			if(hijo[i]->getPosicion().first == nodoHijo.getPosicion().first && hijo[i]->getPosicion().second == nodoHijo.getPosicion().second) {

				std::swap(hijo[i],hijo[hijo.size()-1]);

				encontrado = true;

				hijo.pop_back();

			}

		}

	}

	double getCosteTotal() const {
		return costeTotal;
	}

	double getPenalizacion() const {
		return penalizacion;
	}

	const coordenada& getPosicion() const {
		return posicion;
	}

	std::vector<Nodo*> getHijo() const {
		return hijo;
	}

	std::vector<Nodo*> getPadre() const {
		return padre;
	}

	double getCosteDesdeInicioHastaMi() const {
		return costeDesdeInicioHastaMi;
	}

	double getCosteDesdeMiHastaLaMeta() const {
		return costeDesdeMiHastaLaMeta;
	}

	double getCosteDeDesplazarseDesdePadreHastaMi() const {
		return costeDeDesplazarseDesdePadreHastaMi;
	}

	void setCosteTotal(const double& costeTotal) {
		this->costeTotal = costeTotal;
	}

	void setcosteDeDesplazarseDesdePadreHastaMi(const double& coste) {
		this->costeDeDesplazarseDesdePadreHastaMi = coste;
	}

	void setCosteDesdeInicioHastaMi(const double& costeDesdeInicioHastaMi) {
		this->costeDesdeInicioHastaMi = costeDesdeInicioHastaMi;
	}

};
