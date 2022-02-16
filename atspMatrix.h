#pragma once
#include <vector>
#include <string>

class RandomGenerator;

class ATSPmatrix {
private:
	// Wektor przechowuj¹cy macierz z danymi o odleg³oœciach miêdzy miastami.
	std::vector<std::vector<unsigned short>> data;
public:
	ATSPmatrix(std::vector<std::vector<unsigned short>>& data);
	ATSPmatrix();
	std::vector<std::vector<unsigned short>>& get();
	std::size_t size();
	void print();

	static ATSPmatrix* newMatrixFromFile(std::wstring filePath);

};