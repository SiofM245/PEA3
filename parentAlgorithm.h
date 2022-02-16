#pragma once
#include "randomGenerator.h"
#include <string>
#include <vector>

class ATSPmatrix;

// abstrakcyjna klasa nadrzêdna definuj¹ca wspólne metody dla algorytmu
class ParentAlgorithm {
protected:
	RandomGenerator randomGenerator;
	ATSPmatrix* matrix;
	int result = 0;
	std::vector<unsigned int> resultRoad;
	
	std::vector<unsigned int> generateStartingRoad();
	int calculateTotalRoadLength(std::vector<unsigned int>& road);
	void printResult(float totalTime);
	virtual void printAlgorithDetails() = 0;
	
public:
	virtual bool solve(float totalTime, bool shouldPrintResults) = 0;
};