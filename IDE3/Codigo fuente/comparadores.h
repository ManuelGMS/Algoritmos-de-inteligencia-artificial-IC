class comparador {

public:

	bool operator()(const atributo& atr1, const atributo& atr2) const {

		return atr1.getMerito() > atr2.getMerito();

	}

};
