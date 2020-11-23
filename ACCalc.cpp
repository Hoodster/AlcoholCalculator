#include "ACCalc.h"

int ACCalc::CalculateAlcoholConcentration(
	bool isMale,
	int age,
	int weight,
	int height,
	int beerAmount,
	int vodkaAmount,
	int wineAmount,
	int startHour,
	int endHour) {
	const double alcoholDensity = 0.79;
	double beerAlcohol = (beerAmount * 0.05) * alcoholDensity;
	double vodkaAlcohol = (vodkaAmount * 0.4) * alcoholDensity;
	double wineAlcohol = (wineAmount * 0.11) * alcoholDensity;

	double percentageOfBodyFluids;

	if (isMale) {
		percentageOfBodyFluids = 0.7;
	}
	else {
		percentageOfBodyFluids = 0.6;
	}

	double bodyFluidsWeight = percentageOfBodyFluids * weight;

	if (beerAlcohol + vodkaAlcohol + wineAlcohol == 0) {
		return 0;
	}

}// http://piro.wikidot.com/teoria#toc0