#include "ACCalc.h"

double ACCalc::CalculateAlcoholConcentration(
	bool isMale,
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
	double generalAlcoholCapacity = beerAlcohol + vodkaAlcohol + wineAlcohol;

	if (generalAlcoholCapacity == 0.0) {
		return 0;
	}

	double percentageOfBodyFluids;
	double BMIAdditionalWeight = CalculateBMIFluidWeight(weight, height);

	if (isMale) {
		percentageOfBodyFluids = 0.7;
	}
	else {
		percentageOfBodyFluids = 0.6;
	}

	int alcoholCapacityOverTime = CalculateAlcoholFillOverTime(startHour, endHour, generalAlcoholCapacity);
	double bodyFluidsWeight = (percentageOfBodyFluids * weight) + (BMIAdditionalWeight * 0.15);

	return alcoholCapacityOverTime / bodyFluidsWeight;
}

int ACCalc::CalculateBMIFluidWeight(int weight, int height) {
	double percentageOfBodyFluids;

	double BMI = weight / ((height / 100) ^ 2);

	if (BMI < 18.5) {
		return (int)(18.5 - BMI) * (height / 100) ^ 2;
	}
	else if (BMI > 25) {
		return (int)(BMI - 25) * (height / 100) ^ 2;
	}
	else {
		return 0;
	}
}

int ACCalc::CalculateAlcoholFillOverTime(int startHour, int endHour, double generalAlcoholCapacity) {
	int timeDifference = endHour - startHour;
	int quaterIntervals = (timeDifference * 60) / 15;
	int alcoholCapacityPerQuater = generalAlcoholCapacity / 15;
	int alcoholCapacityAfterTime = alcoholCapacityPerQuater * quaterIntervals;

	if (alcoholCapacityAfterTime > generalAlcoholCapacity) {
		alcoholCapacityAfterTime = generalAlcoholCapacity;
	}

	return alcoholCapacityAfterTime;
}