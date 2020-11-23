#pragma once
class ACCalc
{
	public:
		double CalculateAlcoholConcentration(
			bool isMale, 
			int age,
			int weight,
			int height,
			int beerAmount,
			int vodkaAmount,
			int wineAmount,
			int startHour,
			int endHour);
	private:
		int CalculateBMIFluidWeight(int weight, int height);
		int CalculateAlcoholLossOverTime(int startHour, int endHour, int gramsPerHour);
};

