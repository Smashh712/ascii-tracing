#include "object.h"
#include "matrix.h"
#include <math.h>

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
		float t1 = (-b + sqrt(delta)) / 2;
		float t2 = (-b - sqrt(delta)) / 2;
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
