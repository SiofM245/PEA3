#pragma once
#include <vector>
#include <string>

class RandomGenerator;

class ATSPmatrix {
private:
	// Wektor przechowujący macierz z danymi o odległościach między miastami.
	std::vector<std::vector<unsigned short>> data;
public:
	ATSPmatrix(std::vector<std::vector<unsigned short>>& data);
	ATSPmatrix();
	std::vector<std::vector<unsigned short>>& get();
	std::size_t size();
	void print();

	static ATSPmatrix* newMatrixFromFile(std::wstring filePath);

};