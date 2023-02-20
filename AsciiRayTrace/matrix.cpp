#include "matrix.h"

float Dot(vector<float> a, vector<float> b) {
	float result = 0;
	for (int i = 0; i < 3; ++i) {
		result += a[i] * b[i];
	}
	return result;
}

vector<float> Add(vector<float> a, vector<float> b) {
	std::vector<float> rVector(a);
	for (int i = 0; i < rVector.size(); ++i) {
		rVector[i] += b[i];
	}
	return rVector;
}

vector<float> Sub(vector<float> a, vector<float> b) {
	std::vector<float> rVector(a);
	for (int i = 0; i < rVector.size(); ++i) {
		rVector[i] -= b[i];
	}
	return rVector;
}


vector<float> Multiply(vector<float> a, float c) {
	std::vector<float> rVector(a);
	for (int i = 0; i < rVector.size(); ++i) {
		rVector[i] *= c;
	}
	return rVector;
}


vector<float> Normalize(vector<float> vector) {
	std::vector<float> vNormalized(vector);
	float vdot = Dot(vector, vector);
	for (auto i = vNormalized.begin(); i != vNormalized.end(); ++i) {
		*i = *i / vdot;
	}

	return vNormalized;
}

float Norm(vector<float> vector) {
	std::vector<float> rNorm(vector);
	float vdot = Dot(vector, vector);
	return sqrt(vdot);
}
