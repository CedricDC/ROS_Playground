#include "python_cpp_minitest/cpp_number_generator.h"

void init_rand() {
	static bool seed_called = false;
	if (!seed_called) {
		srand(time(NULL));
		seed_called = true;
	}
}

int getInt(const int min, const int max) {
	init_rand();
	return min + (rand() % (max-min+1));
}

int getInt() {
	// Return an integer between 0 and 10
	return getInt(0,10);
}

float getFloat(const float min, const float max) {
	init_rand();
	return min + static_cast<float>(rand())/(static_cast<float>(RAND_MAX)/(max-min));
}

float getFloat() {
	// Return a float between 0.0 and 10.0
	return getFloat(0.0, 10.0);
}
