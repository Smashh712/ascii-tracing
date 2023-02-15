#include <iostream>
#include <string.h>
#include <windows.h>
#include <vector>
#include <functional>
#include <numeric>
#include <math.h>       
#include "main.h"

#define WIDTH 300
#define HEIGHT 200

const string kALPHABET = " `.-':_,^=;><+!rc*/z?sLTv)J7(|Fi{C}fI31tlu[neoZ5Yxjya]2ESwqkP6h9d4VpOGbUAKXHm8RD#$Bg0MNWQ%&@";
const int ALPHABET_LEN = 91;



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

vector<float> Reflected(vector<float> v, vector<float> normal) {
	return Sub(v, Multiply(normal, Dot(v, normal) * 2));
}

float SphereIntersect(
	vector<float> center, float radius,
	vector<float> ray_origin,
	vector<float> ray_direction) {

	float b = 2 * Dot(ray_direction, Sub(ray_origin, center));
	float ray_norm = Norm(Sub(ray_origin, center));
	float c = ray_norm * ray_norm - radius * radius;
	float delta = b * b - 4 * c;

	if (delta > 0) {
		float t1 = (-b + std::sqrt(delta)) / 2;
		float t2 = (-b - std::sqrt(delta)) / 2;
		//std::cout << t1 << " " << t2 << '\n';

		if (t1 > t2 && t2 > 0) {
			return t2;
		}
		else if (t2 >= t1 && t1 > 0) {
			return t1;
		}
	}

	return -1;
}

vector<float> NearestIntersectedObject(Sphere* objects, int object_num, vector<float> ray_origin,
	vector<float> ray_direction) {

	float distance;
	float nearest_object = -1;
	float min_distance = 999999999;

	for (int i = 0; i < object_num; ++i) {
		distance = SphereIntersect(objects[i].center, objects[i].radius, ray_origin,
			ray_direction);
		if (distance > -1 && min_distance > distance) {
			nearest_object = i;
			min_distance = distance;
		}
	}
	return { nearest_object, min_distance };
}

int FloatToAsciiIndex(float f, int AsciiNum) {
	int result = floor(f * AsciiNum);
	if (result >= AsciiNum)
		return AsciiNum - 1;
		return result;
};

float ratio = float(WIDTH) / HEIGHT;
vector<float> screen{ -1, 1 / ratio, 1, -1 / ratio };
vector<float> light_position = { 5,5,5 };
vector<float> light_value = { 1,1,1 };

int main() {
	using namespace std;
	ios::sync_with_stdio(false);
	std::cout.tie(NULL);
	char ascii_image[HEIGHT][WIDTH] = { ' ' };
	//-0.2, 0, -1]), 'radius': 0.7
	Sphere sphere_one;
	sphere_one.center = { -0.7, 0, -1 };
	sphere_one.radius = 0.7;
	sphere_one.ambient = 0.1;
	sphere_one.diffuse = 0.7;
	sphere_one.specular = 1;
	sphere_one.shininess = 100;
	sphere_one.reflection = 0.5;

	Sphere sphere_two;
	sphere_two.center = { 0.7, -0.5, -2 };
	sphere_two.radius = 1;
	sphere_two.ambient = 0.1;
	sphere_two.diffuse = 0.7;
	sphere_two.specular = 1;
	sphere_two.shininess = 100;
	sphere_two.reflection = 0.5;

	Sphere sphere_three;
	sphere_three.center = { 0, -9000, 0 };
	sphere_three.radius = 9000 - 0.7;
	sphere_three.ambient = 0.1;
	sphere_three.diffuse = 0.7;
	sphere_three.specular = 1;
	sphere_three.shininess = 100;
	sphere_three.reflection = 0.5;

	Sphere objects[4] = { sphere_one, sphere_two,sphere_three, };
	//cout << screen[1] << '\n';
	//cout << screen[3] << '\n';
	//cout << (screen[3] - screen[1]) / HEIGHT << '\n';

	float temp = 0;
	while (1) {
		float y = screen[1];
		float delta_y = (screen[3] - screen[1]) / HEIGHT;
		float x = screen[0];
		float delta_x = (screen[2] - screen[0]) / WIDTH;


		float illumination;
		vector<float> camera{ 0, temp, 1 };
		temp += 0.1;
		bool is_break = false;
		while (y > screen[3]) {
			y += delta_y;
			x = screen[0];
			while (x < screen[2]) {
				is_break = false;
				x += delta_x;
				illumination = 0;
				float brightness = 0;
				vector<float> origin(camera);
				vector<float> pixel({ x,y,0 });
					//cout << x << "," << y << "," << '\n';


				vector<float> direction = Normalize(Sub(pixel, origin));

				float reflection = 1;
				for (int k = 0; k < 5; ++k) {
					vector<float> nearest = NearestIntersectedObject(objects, 3, origin, direction);
					int nearest_object_idx = (int)nearest[0];
					float min_distance = nearest[1];
					if (nearest_object_idx == -1) {
						std::cout << " ";
						is_break = true;
						break;
					}

					vector<float> intersection = Add(origin, Multiply(direction, min_distance));
					//cout << intersection[0] << "," << intersection[1] << "," << intersection[2] << '\n';

					vector<float> normal_to_surface = Normalize(Sub(intersection,
						objects[nearest_object_idx].center));

					vector<float> shifted_point = Add(intersection, Multiply(normal_to_surface, 0.0001));

					vector<float> intersection_to_light = Normalize(Sub(light_position, shifted_point));

					nearest = NearestIntersectedObject(objects, 3, shifted_point, intersection_to_light);
					float intersection_to_light_distance = Norm(Sub(light_position, intersection));

					if (nearest[1] < intersection_to_light_distance) {
						std::cout << " ";
						is_break = true;
						break;
					}

					

					illumination += objects[nearest_object_idx].ambient * light_value[0];
					illumination += objects[nearest_object_idx].diffuse * light_value[1] *
						Dot(intersection_to_light, normal_to_surface);


					vector<float> intersection_to_camera = Normalize(Sub(origin, intersection));
					vector<float> H = Normalize(Add(intersection_to_light, intersection_to_camera));
					//illumination += objects[nearest_object_idx].specular * light_value[2] *
					//	pow(Dot(normal_to_surface, H), objects[nearest_object_idx].shininess / 4);
					
					brightness += reflection * illumination;
					reflection *= objects[nearest_object_idx].reflection;

					//origin = shifted_point;
					//direction = Reflected(direction, normal_to_surface);
				//ascii_image[y_i][x_i] = kALPHABET[ascii_index];
				//x_i++;
				}
				if (!is_break) {
					int ascii_index = FloatToAsciiIndex(brightness, ALPHABET_LEN);
					std::cout << kALPHABET[ascii_index];
				}
			}
			printf("\n");

			//y_i++;
			//x_i = 0;
		}


		//for (int y = 0; y < HEIGHT; ++y) {
		//	for (int x = 0; x < WIDTH; ++x) {
		//		printf("%c", ascii_image[y][x]);
		//	}
		//	printf("\n");
		//}
		cin.get();
	}
	return 0;
}
