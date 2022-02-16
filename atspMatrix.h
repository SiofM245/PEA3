#pragma once
#include <vector>
#include <string>

class RandomGenerator;

class ATSPmatrix {
private:
	// Wektor przechowuj�cy macierz z danymi o odleg�o�ciach mi�dzy miastami.
	std::vector<std::vector<unsigned short>> data;
public:
	ATSPmatrix(std::vector<std::vector<unsigned short>>& data);
	ATSPmatrix();
	std::vector<std::vector<unsigned short>>& get();
	std::size_t size();
	void print();

	static ATSPmatrix* newMatrixFromFile(std::wstring filePath);

};