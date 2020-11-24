#pragma once
class ACCalc
{
	public:
		double CalculateAlcoholConcentration(
			bool isMale,
			int weight,
			int height,
			int beerAmount,
			int vodkaAmount,
			int wineAmount,
			int startHour,
			int endHour);
	private:
		int CalculateBMIFluidWeight(int weight, int height);
		int CalculateAlcoholFillOverTime(int startHour, int endHour, double generalAlcoholCapacity);
};

