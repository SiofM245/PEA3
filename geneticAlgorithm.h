#pragma once
#include "parentAlgorithm.h"

class GeneticAlgorithm : public ParentAlgorithm {
private:
	int populationSize;
	float mutationProbability;
	float crossoverProbability;
	int mutationType;

	std::vector<std::vector<unsigned int>> population;
	std::vector<int> fitness;

	void printAlgorithDetails();
	void generateStartingPopulation();
	void calculatePopulationFitness();
	void generateNewPopulation();

	int rouletteWheelSelection();
	std::vector<unsigned int> crossover(const std::vector<unsigned int>& parent1, const std::vector<unsigned int>& parent2);
public:
	bool solve(float totalTime, bool shouldPrintResults);
	GeneticAlgorithm(ATSPmatrix* matrix, int populationSize, float mutationProbability, float crossoverProbability, int mutationType);
};