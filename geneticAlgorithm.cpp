#include "geneticAlgorithm.h"
#include "timer.h"
#include "atspMatrix.h"

#include <iostream>

GeneticAlgorithm::GeneticAlgorithm(ATSPmatrix* matrix, int populationSize, float mutationProbability, float crossoverProbability, int mutationType) {
	this->matrix = matrix;
	this->populationSize = populationSize;
	this->mutationProbability = mutationProbability;
	this->crossoverProbability = crossoverProbability;
	this->mutationType = mutationType;
}

void GeneticAlgorithm::generateStartingPopulation() {
	for (int i = 0; i < populationSize; i++)
		population.push_back(generateStartingRoad());

	calculatePopulationFitness();
}

void GeneticAlgorithm::calculatePopulationFitness() {
	fitness.clear();
	for (auto chromosome : population)
		fitness.push_back(calculateTotalRoadLength(chromosome));
}

int GeneticAlgorithm::rouletteWheelSelection() {
	int worstFitness = 0;
	for (int i = 0; i < populationSize; i++)
		if (fitness[i] > worstFitness)
			worstFitness = fitness[i];

	// Oblicz alternatywn¹ sprawnoœæ ka¿dego osobnika z populacji,
	// rozumian¹ jako ró¿nica miêdzy sprawnoœci¹ danego osobnika
	// a najgorszym osobnikiem w populacji
	std::vector<int> alt_fitness;
	for (int i = 0; i < populationSize; i++)
		alt_fitness.push_back(-(fitness[i] - worstFitness) + 1);

	int totalAltSumOfAllFitnesses = 0;

	// Oblicz sumê wszystkich sprawnoœci osobników w populacji
	for (int i = 0; i < populationSize; i++)
		totalAltSumOfAllFitnesses += alt_fitness[i];

	int r = randomGenerator.randInt(0, totalAltSumOfAllFitnesses);

	int counting_s = 0;
	for (int i = 0; i < populationSize; i++) {
		counting_s += alt_fitness[i];
		if (counting_s > r)
			return i;
	}
}

void GeneticAlgorithm::generateNewPopulation() {
	// Wygeneruj (populationSize - 1) nowych osobników
	std::vector<std::vector<unsigned int>> new_population;
	for (int i = 0; i < populationSize - 1; i++) {
		// selekcja osobników za pomoc¹ metody "ko³a ruletki" ("Roulette Wheel Selection")
		// metoda zosta³a zmodyfikowana odpowiednio tak, aby wybieraæ najmniejsze wartoœci
		int index1 = rouletteWheelSelection();

		// losowanie liczby ca³kowitej z przedzia³u od 0 do 1
		float chance = randomGenerator.randInt(0, 100001);
		chance /= 100000;

		// jeœli wylosowana szansa jest mniejsza lub równa prawdopodobieñstwu
		// krzy¿owania, to skrzy¿uj dwóch osobników
		if (chance < crossoverProbability) {
			int index2 = rouletteWheelSelection();
			while (index1 == index2)
				index2 = rouletteWheelSelection();
			std::vector<unsigned int> crossovered_chromosome = crossover(population[index1], population[index2]);
			new_population.push_back(crossovered_chromosome);
		}
		else {
			// jeœli wylosowana liczba oznacza, ¿e ma nie dojœæ do skrzy¿owania dwóch osobników
			// to skopiuj jednego z nich (wybranego za pomoc¹ tej samej selekcji co w przypadku
			// krzy¿owania) do nastêpnej populacji
			new_population.push_back(population[index1]);
		}
	}

	// Jeden najlepszy osobnik z ca³ej dotychczasowej populacji pozostaje
	// w niezmienionej formie - mechanizm ten to tzw. elityzm
	std::vector<unsigned int> elitism_chromosome;
	int elitism_chromosome_fitness = std::numeric_limits<int>::max();
	for (int i = 0; i < populationSize; i++) {
		if (fitness[i] < elitism_chromosome_fitness) {
			elitism_chromosome_fitness = fitness[i];
			elitism_chromosome = population[i];
		}
	}
	new_population.push_back(elitism_chromosome);

	// mutacja wszystkich (oprócz wy³onionego w ramach elityzmu) osobników po skrzy¿owaniu
	for (int i = 1; i < populationSize - 1; i++) {
		for (int j = 1; j < matrix->size(); j++) {
			// losowanie liczby ca³kowitej z przedzia³u od 0 do 1
			float chance = randomGenerator.randInt(0, 100001);
			chance /= 100000;

			// jeœli wylosowana szansa jest mniejsza lub równa prawdopodobieñstwu
			// mutacji, to dokonaj mutacji - zamiany miasta z losowym
			if (chance < mutationProbability) {
				int city2 = randomGenerator.randInt(1, matrix->size());
				while (j == city2)
					city2 = randomGenerator.randInt(1, matrix->size());

				if (mutationType == 0) {
					// mutacja typu SWAP
					std::swap(new_population[i][j], new_population[i][city2]);
				}
				else if (mutationType == 1) {
					// mutacja typu INSERT
					unsigned int popped = new_population[i].at(j);
					new_population[i].erase(new_population[i].begin() + j);
					new_population[i].insert(new_population[i].begin() + city2, popped);
				}
			}
		}
	}

	population = new_population;
	calculatePopulationFitness();
}

std::vector<unsigned int> GeneticAlgorithm::crossover(const std::vector<unsigned int>& parent1, const std::vector<unsigned int>& parent2) {
	// algorytm krzy¿owania, który zosta³ zaimplementowany to "single point crossover"

	std::vector<unsigned int> child;
	int point = randomGenerator.randInt(1, matrix->size());

	// skopiuj czêœæ genomu pierwszego rodzica
	// (od pocz¹tku do losowo wybranego momentu)
	for (int i = 0; i < point; i++)
		child.push_back(parent1[i]);

	// reszta genomu dziecka bêdzie pochodziæ od drugiego rodzica
	for (int j = 1; j < matrix->size(); j++) {
		unsigned int x = parent2[j];

		// sprawdzenie, czy miasto nie pojawi³o siê ju¿ w dziecku
		bool next_number = false;
		for (int k = 0; k < point; k++) {
			if (x == child[k]) {
				next_number = true;
				break;
			}
		}

		if (next_number)
			continue;

		// jeœli nie pojawi³o siê, dodaj je do dziecka
		child.push_back(x);
	}

	return child;
}

void GeneticAlgorithm::printAlgorithDetails() {
	std::cout << "Algorytm: Algorytm genetyczny (GA)" << std::endl;
	std::cout << "Rozmiar populacji: " << populationSize << std::endl;
}

bool GeneticAlgorithm::solve(float totalTime, bool shouldPrintResults) {
	Timer timer;
	long long totalTimeinNanoseconds = totalTime * 1000000000;
	long long nanosecondsElapsed = 0;

	// wygeneruj losowo populacjê pocz¹tkow¹
	// chromosomy kodowane s¹ pomoc¹ kodowania permutacyjnego
	generateStartingPopulation();
	
	while (nanosecondsElapsed < totalTimeinNanoseconds) {
		timer.startTimer();

		generateNewPopulation();

		timer.stopTimer();
		nanosecondsElapsed += timer.executionTimeInNanoseconds();
	}

	// Ostateczny rezultat jest aktualizowany na koniec
	// wykonywania algorytmu, dlatego pocz¹tkowo ustawiamy d³ugoœæ 
	// obecnego najlepszego rozwi¹zania jako symboliczn¹ nieskoñczonoœæ 
	result = std::numeric_limits<int>::max();

	// Po zakonczeniu dzialania algorytmu najlepsze rozwiazanie zostaje zapisane
	for (int i = 0; i < populationSize; i++) {
		if (fitness[i] < result) {
			result = fitness[i];
			resultRoad = population[i];
		}
	}

	if (shouldPrintResults)
		printResult(totalTime);

	return false;
}

