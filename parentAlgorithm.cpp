#include "ParentAlgorithm.h"
#include "atspMatrix.h"
#include <iostream>
#include <algorithm>

std::vector<unsigned int> ParentAlgorithm::generateStartingRoad() {
	std::vector<unsigned int> road;

	for (int i = 0; i < matrix->size(); i++)
		road.push_back(i);

	std::random_shuffle(road.begin() + 1, road.end());

	return road;
}

int ParentAlgorithm::calculateTotalRoadLength(std::vector<unsigned int>& road) {
	int result = 0;

	for (int i = 0; i < road.size() - 1; i++)
		result += matrix->get()[road[i]][road[i + 1]];

	result += matrix->get()[road[road.size() - 1]][0];

	return result;
}

void ParentAlgorithm::printResult(float totalTime) {
	printAlgorithDetails();
	std::cout << "Czas wykonywania: " << totalTime << " [s]" << std::endl;
	std::cout << "	Length: " << result << std::endl;
	std::cout << "Path: ";
	for (int i = 0; i < resultRoad.size(); i++)
		std::cout << resultRoad[i] << " ";

	std::cout << "0" << std::endl << std::endl;
}