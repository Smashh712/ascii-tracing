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

float Dot(vector<float> a, vector<float> b);
float Norm(vector<float> vector);

vector<float> Normalize(vector<float> vector);

vector<float> Add(vector<float> a, vector<float> b);
vector<float> Sub(vector<float> a, vector<float> b);
vector<float> Multiply(vector<float> a, float c);


vector<float> Reflected(vector<float> l, vector <float> normal);

float SphereIntersect(vector<float> center, float radius, vector<float> ray_origin,
	vector<float> ray_direction);

vector<float> NearestIntersectedObject(vector<Sphere> objects, vector<float> ray_origin,
	vector<float> ray_direction);

int FloatToAsciiIndex(float f, int AsciiNum);
