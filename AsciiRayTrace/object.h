#pragma once
#include <vector>
#include "main.h"
using namespace std;


vector<float> Reflected(vector<float> l, vector <float> normal);

float SphereIntersect(vector<float> center, float radius, vector<float> ray_origin,
	vector<float> ray_direction);

vector<float> NearestIntersectedObject(Sphere* objects, int object_num, vector<float> ray_origin,
	vector<float> ray_direction);