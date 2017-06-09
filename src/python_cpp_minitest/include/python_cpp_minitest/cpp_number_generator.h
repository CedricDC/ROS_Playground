#ifndef CPP_NUMBER_GENERATOR_H
#define CPP_NUMBER_GENERATOR_H

#include <cstdlib>
#include <time.h>

void init_rand();

int getInt(const int min, const int max);
int getInt();

float getFloat(const float min, const float max);
float getFloat();

#endif // CPP_NUMBER_GENERATOR_H
