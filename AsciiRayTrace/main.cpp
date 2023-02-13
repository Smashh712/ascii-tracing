#include <iostream>
#include <string.h>
#include <windows.h>
#include <vector>
#include <functional>
#include <numeric>
#include <math.h>       
#include "main.h"

#define WIDTH 200
#define HEIGHT 80

string alphabets = " `.-':_,^=;><+!rc*/z?sLTv)J7(|Fi{C}fI31tlu[neoZ5Yxjya]2ESwqkP6h9d4VpOGbUAKXHm8RD#$Bg0MNWQ%&@";
int alphabets_len = 91;

int main() {
	using namespace std;
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	std::cout.tie(NULL);
	char asciiImage[HEIGHT][WIDTH] = { '0' };
	//int init_color = 0;

	//int color = init_color;
	//for (int y = 0; y < HEIGHT; ++y) {
	//	for (int x = 0; x < WIDTH; ++x) {
	//		asciiImage[y][x] = alphabets[color];
	//	}
	//	if (color < alphabets_len - 1) {
	//		color++;
	//	}
	//}

	//for (int y = 0; y < HEIGHT; ++y) {
	//	for (int x = 0; x < WIDTH; ++x) {
	//		printf("%c", asciiImage[y][x]);
	//	}
	//	printf("\n");
	//}


	vector<float> camera{ 1, 1, 1 };
	float ratio = float(WIDTH) / HEIGHT;
	vector<float> screen{ -1, 1 / ratio, 1, -1 / ratio };

	cout << dot(camera, camera) << '\n';
	vector<float> temp = norm(camera);

	cout << temp[0] << temp[1] << temp[2] << '\n';
	vector<float> b({ 0,0,1 });
	temp = sub(temp, b);
	cout << temp[0] << temp[1] << temp[2];

	return 0;
}

float dot(vector<float> a, vector<float> b) {
	float result = inner_product(a.begin(), a.end(), b.begin(), 0);
	return sqrt(result);
}

vector<float> sub(vector<float> a, vector<float> b) {
	std::vector<float> rVector(a);
	for (int i = 0; i < rVector.size(); ++i) {
		rVector[i] -= b[i];
	}
	return rVector;
}

vector<float> norm(vector<float> vector) {
	std::vector<float> rNorm(vector);
	float vdot = dot(vector, vector);
	for (auto i = rNorm.begin(); i != rNorm.end(); ++i) {
		*i = *i / vdot;
	}

	return rNorm;
}

float sphere_intersect(
	vector<float> center, float radius,
	vector<float> ray_origin,
	vector<float> ray_direction) {
	return 0;
	/*float b = 2 * dot(ray_direction, subvector(ray_origin - center))*/
}