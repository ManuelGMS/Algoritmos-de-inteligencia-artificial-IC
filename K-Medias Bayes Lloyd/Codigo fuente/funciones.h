matrizU calcularMatrizU(const conjuntoDeMuestras& muestras, const std::vector<representante>& rpstt) {

	matrizU mU;

	for(size_t r = 0 ; r < rpstt.size() ; ++r)

		for(const auto& muestra : muestras)

			mU[rpstt[r].getNombre()].push_back(rpstt[r].calcularGradoDePertenencia(muestra));

	return mU;

}

void imprimirMatrizU(matrizU& mU, const std::vector<representante>& representantes) {

	std::cout << std::fixed;
	std::cout << std::setprecision(8);

	for(const auto& r : representantes) {

		std::cout << std::setw(72) << std::setfill('+') << "+";

		for(size_t i = 0 ; i < mU[r.getNombre()].size() ; ++i)

			std::cout << std::setw(14) << std::setfill('+') << "+";

		std::cout << std::endl;

		std::cout << "+ ";

		std::cout << std::setw(20) << std::setfill(' ') << r.getNombre();

		std::cout << " ( ";

		for(const double& d : r.getCentro())

			std::cout << d << " ";

		std::cout << ") +";

		for(const auto& d : mU[r.getNombre()])

			std::cout << "+ " << d << " +";

		std::cout << std::endl;

		std::cout << std::setw(72) << std::setfill('+') << "+";

		for(size_t i = 0 ; i < mU[r.getNombre()].size() ; ++i)

			std::cout << std::setw(14) << std::setfill('+') << "+";

		std::cout << std::endl;

	}

	std::cout << std::endl;

}
