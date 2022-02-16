#include "timer.h"

void Timer::startTimer() {
	startTime = std::chrono::high_resolution_clock::now();
}

void Timer::stopTimer() {
	endTime = std::chrono::high_resolution_clock::now();
}

// Metoda zwracaj�ca czas w mikrosekundach kt�ry up�yn�� mi�dzy wywo�aniami 
// metod startTimer i stopTimer
long long Timer::executionTime() {
	return std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
}

// Analogicza metoda zwracaj�ca czas w nanosekundach kt�ry up�yn�� mi�dzy wywo�aniami 
// metod startTimer i stopTimer
long long Timer::executionTimeInNanoseconds() {
	return std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
}
