#include "Sphere.h"
#include "Ray.h"

bool Sphere::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
	Eigen::Vector3d normal;
	double a, b, c, r, t_result;

	r = this->radius;
	a = ray.direction.dot(ray.direction);
	b = 2 * ray.direction.dot(ray.origin - this->center);
	c = (ray.origin - this->center).dot(ray.origin - this->center) - r * r;
	double determinent = b * b - 4 * a * c;

	if (determinent < 0) return false;


	double first, second;
	first = (-1 * b + std::sqrt(determinent)) / (2 * a);
	second = (-1 * b - std::sqrt(determinent)) / (2 * a);
	//std::cout << first << " " << second << std::endl;

	if (first < min_t && second < min_t) return false;

	if (first < min_t) t_result = second;
	else if (second < min_t) t_result = first;
	else if (first < second) t_result = first;
	else t_result = second;

	assert(t_result > min_t);

	normal = (ray.origin + ray.direction * t_result - this->center).normalized();

	t = t_result;
	n = normal;
	return true;
  ////////////////////////////////////////////////////////////////////////////
}

