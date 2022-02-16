#include "menu.h"
#include "atspMatrix.h"
#include "randomGenerator.h"
#include "geneticAlgorithm.h"

#include <iostream>

int Menu::getMaxRandomValue() {
	std::cout << "Podaj maksymalna wage ktora moze zostac wylosowana (od 0 do 65535): ";
	int amount = 0;
	std::cin >> amount;
	if (amount < 1 || amount > 65535) {
		std::cout << "Podano niepoprawna wartosc" << std::endl;
		return -1;
	}

	return amount;
}



float Menu::getTimeLimit() {
	std::cout << "Podaj maksymalny czas wykonywania algorytmu (w sekundach): ";
	float amount = 0;
	std::cin >> amount;
	if (amount <= 0) {
		std::cout << "Podano niepoprawna wartosc (czas musi byc wiekszy niz zero)" << std::endl;
		return -1.0f;
	}

	std::cout << "Ustawiono czas wykonywania algorytmu: " << amount << " s" << std::endl;
	return amount;
}

int Menu::getPopulationSize() {
	std::cout << "Podaj rozmiar populacji poczatkowej (od 2 do 4096): ";
	int amount = 0;
	std::cin >> amount;
	if (amount <= 2 || amount > 4096) {
		std::cout << "Podano niepoprawna wartosc" << std::endl;
		return -1;
	}

	std::cout << "Ustawiona wielkosc populacji: " << amount << std::endl;
	return amount;
}





void Menu::printMenuCommands() {
	std::cout << "1. Wyswietl wczytane dane" << std::endl;
	std::cout << "2. Wczytaj dane z pliku" << std::endl;
	std::cout << "3. Ustawienie wielkosci populacji poczatkowej" << std::endl;
	std::cout << "4. Wprowadzenie kryterium stopu" << std::endl;
	std::cout << "5. Uruchomienie algorytmu genetycznego (GA)" << std::endl;
	std::cout << "0. Wyjscie" << std::endl;
}

int Menu::menu() {


	ATSPmatrix* matrix = nullptr;
	float timeLimit = -1.0f;
	int populationSize = -1;
	float mutationProbability = -1.0f;
	float crossoverProbability = -1.0f;
	int mutationType = 0;

	printMenuCommands();

	while (true) {
		std::cout << "> ";
		char choice = '\x00';
		std::cin >> choice;

		switch (choice) {
		case '0':
			return 0;
		case '1':
			if (matrix != nullptr)
				matrix->print();
			else
				std::cout << "Nie zaladowano zadnych danych!" << std::endl;
			break;
		case '2': {
			if (matrix != nullptr)
				delete matrix;

			std::wstring fileName;
			std::cout << "Podaj nazwe pliku: ";
			std::wcin >> fileName;
			std::wcout << "Nastapi proba otwarcia pliku w nastepujacej lokalizacji: " << fileName << std::endl;

			matrix = ATSPmatrix::newMatrixFromFile(fileName);

			if (matrix == nullptr) {
				std::cout << "Ladowanie danych zakonczone niepowodzeniem" << std::endl;
				break;
			}

			std::cout << "Zaladowano dane" << std::endl;
			break;
		}
		
		case '3': {
			// Rozmiar populacji
			populationSize = getPopulationSize();
			break;
		}


		case '4': {
			// Wybor kryterium stopu - limit czasowy
			timeLimit = getTimeLimit();
			break;
		}
		case '5': {
			if (matrix == nullptr) {
				std::cout << "Nie zaladowano zadnych danych!" << std::endl;
				break;
			}

			if (timeLimit == -1.0f) {
				std::cout << "Nie wprowadzono limitu czasowego!" << std::endl;
				break;
			}

			GeneticAlgorithm geneticAlgorithm(matrix, populationSize, mutationProbability, crossoverProbability, mutationType);
			geneticAlgorithm.solve(timeLimit, true);

			break;
		}
		

		default:
			std::cout << "Niewlasciwy wybor! Wpisz \'?\' aby wyswietlic dostepne opcje" << std::endl;
			break;
		}
	}

	return 0;
}