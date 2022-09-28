#include "viewing_ray.h"

void screenToCamera(int i, int j, double width, double height, int nx, int ny, double& u, double& v);
void viewing_ray(
	const Camera& camera,
	const int i,
	const int j,
	const int width,
	const int height,
	Ray& ray)
{
	////////////////////////////////////////////////////////////////////////////
	// Add your code here
	double u, v;
	Eigen::Matrix3d R_temp, R;
	R << camera.u, camera.v, camera.w;


	screenToCamera(i, j, camera.width, camera.height, width, height, u, v);
	ray.origin = camera.e;

	ray.direction = Eigen::Vector3d(u, v, -1 * std::fabs(camera.d));

	ray.direction = R * ray.direction;

	////////////////////////////////////////////////////////////////////////////
}

//screen space to camera space
void screenToCamera(int i, int j, double width, double height, int nx, int ny, double& u, double& v) {
	//coordinate of i and j when origin is at bottom left
	int i_normal, j_normal;
	i_normal = j;
	j_normal = ny - 1 - i;

	assert(i_normal >= 0 && i_normal < nx);
	assert(j_normal >= 0 && j_normal < ny);

	u = (width / nx) * (i_normal + 0.5) - (width / 2.0);
	v = (height / ny) * (j_normal + 0.5) - (height / 2.0);
}

