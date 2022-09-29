#include "Triangle.h"
#include "Ray.h"
#include <Eigen/Geometry>
#include <Eigen/Dense>
#include <iostream>

bool Triangle::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
	Eigen::Vector3d A = std::get<0>(this->corners);

	Eigen::Vector3d AB = std::get<1>(this->corners) - std::get<0>(this->corners);
	Eigen::Vector3d AC = std::get<2>(this->corners) - std::get<0>(this->corners);

	Eigen::Vector3d normal = (AB).cross(AC);
	normal.normalize();

	double t_result;
	Eigen::Matrix3d M;
	M << AB, AC, -1 * ray.direction;

	if (std::fabs(M.determinant()) < 1e-8) return false;
	Eigen::Vector3d result = M.inverse() * (ray.origin - A);
	double a = result.x();
	double b = result.y();
	t_result = result.z();

	if (a + b <= 1 && a >= 0 && b >= 0 && t_result >= min_t) {
		n = normal;
		t = t_result;
		return true;
	}
	else {
		return false;
	}
  ////////////////////////////////////////////////////////////////////////////
}


