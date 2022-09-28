#include "blinn_phong_shading.h"
// Hint:
#include "first_hit.h"
#include <iostream>
#include <limits>

#define AMBIENT_INTENSITY 0.1
#define FUDGE_FACTOR 1e-6

Eigen::Vector3d blinn_phong_shading(
  const Ray & ray,
  const int & hit_id, 
  const double & t,
  const Eigen::Vector3d & n,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector<std::shared_ptr<Light> > & lights)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
	Eigen::Vector3d result = objects[hit_id]->material->ka * AMBIENT_INTENSITY;
	Eigen::Vector3d kd = objects[hit_id]->material->kd;
	Eigen::Vector3d ks = objects[hit_id]->material->ks;
	double p = objects[hit_id]->material->phong_exponent;
	
	Eigen::Vector3d v = -1 * ray.direction.normalized();	//let the view direction start from the surface point

	// get the point on the object
	Eigen::Vector3d hit_point = ray.origin + ray.direction * t;

	// loop through all the light
	for (auto light:lights) {
		Ray shadow_ray;
		double max_t;
		
		//make a new ray start from the surface hit point to the light
		light->direction(hit_point, shadow_ray.direction, max_t);
		shadow_ray.origin = hit_point + FUDGE_FACTOR * shadow_ray.direction;

		int shadow_id;
		double shadow_t;
		Eigen::Vector3d shadow_n;

		// check for shadow
		if (first_hit(shadow_ray, 0, objects, shadow_id, shadow_t, shadow_n)) {
			if (shadow_t > 0 && shadow_t <= max_t) continue;
		}

		//diffuse shading = ks * I * max(n dot l, 0)
		Eigen::Vector3d Ld = (kd.array() * light->I.array()).matrix() * std::fmax(n.dot(shadow_ray.direction), 0);
		if (max_t != std::numeric_limits<double>::infinity()) Ld /= max_t * max_t;

		//specular shadding = ka * I * max(0, n dot h)^p
		
		Eigen::Vector3d h = (v + shadow_ray.direction).normalized();

		Eigen::Vector3d Ls = (ks.array() * light->I.array()).matrix() * std::pow(std::fmax(n.dot(h), 0), p);
		if (max_t != std::numeric_limits<double>::infinity()) Ls /= max_t * max_t;

		result += Ld + Ls;

	}


	return result;
  ////////////////////////////////////////////////////////////////////////////
}
