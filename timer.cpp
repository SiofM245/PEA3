#include "timer.h"

void Timer::startTimer() {
	startTime = std::chrono::high_resolution_clock::now();
}

void Timer::stopTimer() {
	endTime = std::chrono::high_resolution_clock::now();
}

// Metoda zwracaj¹ca czas w mikrosekundach który up³yn¹³ miêdzy wywo³aniami 
// metod startTimer i stopTimer
long long Timer::executionTime() {
	return std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
}

// Analogicza metoda zwracaj¹ca czas w nanosekundach który up³yn¹³ miêdzy wywo³aniami 
// metod startTimer i stopTimer
long long Timer::executionTimeInNanoseconds() {
	return std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
}
