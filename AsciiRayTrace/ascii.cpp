#include "ascii.h"

int FloatToAsciiIndex(float f, int AsciiNum) {
	int result = floor(f * AsciiNum);
	if (result >= AsciiNum)
		return AsciiNum - 1;
	return result;
};