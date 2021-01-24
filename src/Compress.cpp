//
// Created by Markus Le Roux on 2021-01-23.
//

#include "Compress.h"
#include "Model.h"
#include "Update.h"

#define q 10
#define B 0.5
#define Delta 5

Compress::Compress(Model &model,
				   unsigned int v,
				   const boost::dynamic_bitset<>& bs_A) : Update(model, v, bs_sample(~bs_A)) {};

long double Compress::gammaCutoff() const {
	std::vector<long double> weights = computeWeights(B, model.getNeighbourhoodColourCount(v));
	long double Z = std::accumulate(weights.begin(), weights.end(), (long double) 0.0);
	return (q - Delta) * weights[c_1] / Z;
}

unsigned int Compress::sampleFromA() const {
	std::vector<long double> weights = computeWeights(B, model.getNeighbourhoodColourCount(v));

	long double Z = 0;
	for (int i = 0; i < weights.size(); i++) {
		if (A[i]) { Z += weights[i]; }
	}

	long double gammaTimesDenominator = gamma * Z;
	long double total = 0;
	for (unsigned int c : Model::getIndexVector<boost::dynamic_bitset<>>(A)) {
		if (total + weights[c] > gammaTimesDenominator) {
			return c;
		} else { total += weights[c]; }
	}

	throw std::runtime_error("No sample generated from A (likely caused by rounding error).");
}
