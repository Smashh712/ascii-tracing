#pragma once
#include <vector>

using namespace std;

float Dot(vector<float> a, vector<float> b);

float Norm(vector<float> vector);

vector<float> Normalize(vector<float> vector);

vector<float> Add(vector<float> a, vector<float> b);

vector<float> Sub(vector<float> a, vector<float> b);

vector<float> Multiply(vector<float> a, float c);