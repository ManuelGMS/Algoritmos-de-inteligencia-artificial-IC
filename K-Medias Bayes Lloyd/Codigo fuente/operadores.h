matriz operator + (const matriz& mA, const matriz& mB) {

	matriz solucion(mA.size(),vector(mA.size()));

	for(size_t i = 0 ; i < mA.size() ; ++i)

		for(size_t j = 0 ; j < mA.size() ; ++j)

		solucion[i][j] = mA[i][j] + mB[i][j];

	return solucion;

}

std::vector<double> operator + (const std::vector<double>& vA, const std::vector<double>& vB) {

	std::vector<double> solucion(vA.size());

	for(size_t i = 0 ; i < vA.size() ; ++i)

		solucion[i] = vA[i] + vB[i];

	return solucion;

}

std::vector<double> operator - (const std::vector<double>& vA, const std::vector<double>& vB) {

	std::vector<double> solucion(vA.size());

	for(size_t i = 0 ; i < vA.size() ; ++i)

		solucion[i] = vA[i] - vB[i];

	return solucion;

}

matriz operator * (const std::pair<vector,bool>& pA, const std::pair<vector,bool>& pB) {

	matriz solucion;

	if(!pA.second && pB.second) {

		solucion =  matriz(pA.first.size(),vector(pB.first.size()));

		for(size_t i = 0 ; i < pA.first.size() ; ++i)

			for(size_t j = 0 ; j < pB.first.size() ; ++j)

				solucion[i][j] = pA.first[i] * pB.first[j];

	} else {

		solucion =  matriz(1,vector(1));

		for(size_t i = 0 ; i < pA.first.size() ; ++i)

			solucion[0][0] += pA.first[i] * pB.first[i];

	}

	return solucion;

}

vector operator * (const vector& v, const matriz& m) {

	vector solucion(v.size());

	for(size_t j = 0 ; j < v.size() ; ++j)

		for(size_t i = 0 ; i < v.size() ; ++i)

			solucion[j] += v[i] * m[i][j];

	return solucion;

}

vector operator / (const std::vector<double>& vectorial, const double& escalar) {

	vector solucion = vectorial;

	for(double& e : solucion)

		e /= escalar;

	return solucion;

}

vector operator * (const double& escalar, const std::vector<double> vectorial) {

	vector solucion = vectorial;

	for(double& e : solucion)

		e *= escalar;

	return solucion;

}
