#include "first_hit.h"
#include <assert.h>
#include <iostream>

bool first_hit(
	const Ray& ray,
	const double min_t,
	const std::vector< std::shared_ptr<Object> >& objects,
	int& hit_id,
	double& t,
	Eigen::Vector3d& n)
{
	////////////////////////////////////////////////////////////////////////////
	// Replace with your code here:
	double t_result = std::numeric_limits<double>::infinity();
	int index_result = -1;
	Eigen::Vector3d normal_result;
	assert(t_result > 0);

	for (int i = 0; i < objects.size(); i++) {
		double new_t;
		Eigen::Vector3d new_normal;
		if (objects[i]->intersect(ray, min_t, new_t, new_normal) == false) continue;



		assert(new_t > min_t);

		if (new_t < t_result) {
			t_result = new_t;
			index_result = i;

			normal_result = new_normal;
		}

	}

	//did not find anything
	if (index_result == -1) return false;

	t = t_result;
	hit_id = index_result;
	n = normal_result;
	return true;
	////////////////////////////////////////////////////////////////////////////
}
