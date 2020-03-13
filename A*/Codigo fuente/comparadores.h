class comparador {

public:

	bool operator () (const Nodo* n1, const Nodo* n2) {
		return n1->getCosteTotal() > n2->getCosteTotal();
	}

};
