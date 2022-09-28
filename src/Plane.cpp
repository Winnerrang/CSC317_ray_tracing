#include "Plane.h"
#include "Ray.h"
#include <iostream>
bool Plane::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
	assert(this->normal.norm() - 1 < 1e-8);
	if (this->normal.dot(ray.direction) < 1e-8 && this->normal.dot(ray.direction) > -1e-8) return false;

	double result_t = (-1 * this->normal.dot(ray.origin - this->point)) / (this->normal.dot(ray.direction));

	if (result_t < min_t) return false;


	n = this->normal;
	t = result_t;
	return true;
  ////////////////////////////////////////////////////////////////////////////
}

