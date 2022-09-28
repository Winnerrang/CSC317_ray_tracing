#include "raycolor.h"
#include "first_hit.h"
#include "blinn_phong_shading.h"
#include "reflect.h"
#include <assert.h>

#define FUDGE_FACTOR 1e-6

bool raycolor(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector< std::shared_ptr<Light> > & lights,
  const int num_recursive_calls,
  Eigen::Vector3d & rgb)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
	rgb = Eigen::Vector3d(0,0,0);

	int hit_id;
	double t;
	Eigen::Vector3d n;
	if (first_hit(ray, min_t, objects, hit_id, t, n)) {

		assert(hit_id >= 0 && hit_id < objects.size());
		assert(t >= min_t);
		rgb = blinn_phong_shading(ray, hit_id, t, n, objects, lights);

		//if hit the mirror
		if (objects[hit_id]->material->km.norm() > 1e-10) {
			Ray reflected_ray;
			reflected_ray.direction = reflect(ray.direction.normalized(), n);

			//move a little bit away from the point to prevent ray hitting itself 
			reflected_ray.origin = ray.origin + t * ray.direction + FUDGE_FACTOR * reflected_ray.direction;

			Eigen::Vector3d new_rgb(0, 0, 0);
			raycolor(reflected_ray, 0, objects, lights, num_recursive_calls + 1, new_rgb);
			rgb +=  (objects[hit_id]->material->km.array() * new_rgb.array()).matrix();
		}
		
		return true;
	}

	return false;
  ////////////////////////////////////////////////////////////////////////////
}
