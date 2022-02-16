#include "atspMatrix.h"
#include "randomGenerator.h"
#include <fstream>
#include <iostream>
#include <limits>
#include <iomanip>

ATSPmatrix::ATSPmatrix(std::vector<std::vector<unsigned short>>& data) {
	this->data = data;
}

ATSPmatrix::ATSPmatrix() {
}

std::vector<std::vector<unsigned short>>& ATSPmatrix::get() {
	return data;
}

std::size_t ATSPmatrix::size() {
	return data.size();
}

void ATSPmatrix::print() {
	for (int i = 0; i < data.size(); i++) {
		for (int j = 0; j < data.size(); j++)
			if (data[i][j] == std::numeric_limits<unsigned short>::max())
				std::cout << std::setw(6) << "X";
			else
				std::cout << std::setw(6) << data[i][j];

		std::cout << std::endl;
	}
}

ATSPmatrix* ATSPmatrix::newMatrixFromFile(std::wstring filePath) {
	// Implementacja zak�adaj�ca poprawn� ilo�� liczb ca�kowitych w ka�dej linii

	std::ifstream ifs;
	ifs.open(filePath, std::ios::in);

	if (!ifs.good()) {
		std::cout << "Wystapil blad przy probie otwarcia pliku!" << std::endl;
		// B�ad odczytu sygnalizowany jest przez zwr�cenie nullptr
		return nullptr;
	}
	
	// Pierwsz� liczb� w pliku jest rozmiar problemu
	int size = 0;
	ifs >> size;
	
	// Wczytany rozmiar wykorzystywany jest przy tworzeniu macierzy - rezerwowane
	// jest miejsce na ca�� macierz przez podanie wywo�anie funkcji reserve()
	std::vector<std::vector<unsigned short>> matrix;
	matrix.reserve(size);

	// W�a�ciwa p�tla wczytuj�ca dane z pliku do pami�ci
	for (int i = 0; i < size; i++) {
		// Pobrany rozmiar wykorzysytywany jest r�wnie� do inicjalizacji wierszy z odpowiedni� liczb� element�w
		// W tym przypadku podanie warto�ci w konstruktorze inicjalizuje wektor z zadan� liczb� element�w
		// o domy�lnej warto�ci dla danego typu.
		std::vector<unsigned short> row(size);
		for (int j = 0; j < size; j++) {
			ifs >> row[j];
		}
		matrix.push_back(row);
	}

	// P�tla ustawiaj�ca odleg�o�ci na przek�tnych jako umown� niesko�czono��
	for (int i = 0; i < size; i++) {
		if (matrix[i][i] == 0) {
			matrix[i][i] = std::numeric_limits<unsigned short>::max();
		}
		else {
			std::cout << "Niezgodnosc pliku z formatem - na przekatnej macierzy wartosc rozna od zera" << std::endl;
			return nullptr;
		}
	}

	ifs.close();
	return new ATSPmatrix(matrix);
}

