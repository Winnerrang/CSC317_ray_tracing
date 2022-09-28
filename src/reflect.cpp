#include <Eigen/Core>
#include <assert.h>
#include <math.h>
Eigen::Vector3d reflect(const Eigen::Vector3d & in, const Eigen::Vector3d & n)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
	assert(std::fabs(in.norm() - 1) < 1e-10);
	assert(std::fabs(n.norm()) - 1 < 1e-10);
	Eigen::Vector3d result;

	result = 2 * n.dot(-1 * in) * n - (-1 * in);
	result.normalize();
	return result;
  ////////////////////////////////////////////////////////////////////////////
}
