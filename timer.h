#pragma once
#include <chrono>

// Klasa odpowiedzialna za mierzenie czasu wykonywania operacji
// Operująca na mikrosekundach i wykorzystująca bibliotekę std::chrono
class Timer {
private:
	std::chrono::high_resolution_clock::time_point startTime;
	std::chrono::high_resolution_clock::time_point endTime;
public:
	void startTimer();
	void stopTimer();

	long long executionTime();
	long long executionTimeInNanoseconds();
};
