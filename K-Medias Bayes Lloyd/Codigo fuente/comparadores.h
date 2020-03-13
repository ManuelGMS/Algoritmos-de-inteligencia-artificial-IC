class cmp {

public:

	bool operator() (const std::pair<std::string,double>& pA, const std::pair<std::string,double>& pB) {

		return pA.second > pB.second;

	}

};
