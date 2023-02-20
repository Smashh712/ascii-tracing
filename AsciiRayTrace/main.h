#pragma once
#include <vector>
using namespace std;

struct Sphere {
	vector<float> center;
	float radius;
	float ambient;
	float diffuse;
	float specular;
	float reflection;
	float shininess;
};