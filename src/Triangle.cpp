#include "Triangle.h"
#include "Ray.h"
#include <Eigen/Geometry>
#include <iostream>

bool Triangle::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
	Eigen::Vector3d A = std::get<0>(this->corners);
	Eigen::Vector3d B = std::get<1>(this->corners);
	Eigen::Vector3d C = std::get<2>(this->corners);

	Eigen::Vector3d AB = B - A;
	Eigen::Vector3d AC = C - A;

	Eigen::Vector3d normal = (AB).cross(AC);
	normal = normal.normalized();

	double t_result;
	Eigen::Matrix3d M;
	M << AB.x(), AC.x(), -1 * ray.direction.x(),
		AB.y(), AC.y(), -1 * ray.direction.y(),
		AB.z(), AC.z(), -1 * ray.direction.z();

	if (M.determinant() < 1e-8 && M.determinant() > -1 * 1e-8) return false;
	Eigen::Vector3d result = M.colPivHouseholderQr().solve(ray.origin - A);
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


