#pragma once

class Menu {
private:
	static int getMaxRandomValue();
	//static int getSizeToGenerate();
	static float getTimeLimit();
	static int getPopulationSize();
//	static float getMutationProbability();
//	static float getCrossoverProbability();
	static int getMutationType();

	static void printMenuCommands();
public:
	static int menu();
};