#include "utils.h"
#include <algorithm>

Utils::Utils()
{ }

double Utils::degreesToRadians(double degrees)
{
    return degrees * M_PI / 180.0;
}

Vector3D Utils::multiplyPerCanal(const Vector3D &v1, const Vector3D &v2)
{
    return Vector3D(v1.x*v2.x, v1.y*v2.y, v1.z*v2.z);
}

bool Utils::hasIntersection(const Ray &ray, const std::vector<Shape*> &objectsList)
{
    // For each object on the scene...
    for(size_t objIndex = 0; objIndex < objectsList.size(); objIndex ++)
    {
          // Get the current object
          const Shape *obj = objectsList.at(objIndex);
		  Intersection i;
		  if (obj->rayIntersect(ray, i))
			  return true;
    }

    return false;
}

bool Utils::hasIntersection(const Ray &ray, const std::vector<Shape*> &objectsList, const Shape* me)
{
	// For each object on the scene...
	for (size_t objIndex = 0; objIndex < objectsList.size(); objIndex++)
	{
		// Get the current object
		const Shape *obj = objectsList.at(objIndex);
		if (obj == me) continue;

		Intersection i;
		if (obj->rayIntersect(ray, i))
			return true;
	}

	return false;
}

Vector3D Utils::reflect(const Vector3D& n, const Vector3D& i)
{
	//Vector3D reflectedDir = 2 * std::max(0.0f, (float)dot(n, v
	//float aux = 2 * std::max(0.0f, (float)dot(n, v));

	float aux = 2 * dot(n, i);
	Vector3D reflectedDir = n * aux;
	reflectedDir = i - reflectedDir;
	return reflectedDir;
}

bool Utils::getClosestIntersection(const Ray &cameraRay, const std::vector<Shape*> &objectsList, Intersection &its)
{
	if (objectsList.size() == 0) return false;

	float closestDist = INFINITY;
	bool intersected = false;
	for (size_t objIndex = 0; objIndex < objectsList.size(); objIndex++)
	{
		const Shape *obj = objectsList.at(objIndex);
		Intersection inter;
		if (!obj->rayIntersect(cameraRay, inter)) continue;
		intersected = true;
		float currentDist = (inter.itsPoint - cameraRay.o).length();

		if (currentDist < closestDist) 
		{
			closestDist = currentDist;
			its = inter;
		}
	}
    return intersected;
}

double interpolate(double val, double y0, double x0, double y1, double x1 )
{
    return (val-x0)*(y1-y0)/(x1-x0) + y0;
}

double getRed(double value)
{
    if (value > 0.5)
        return interpolate( value, 0.0, 0.5, 1.0, 1.0 );
    else
        return 0.0;
}

double getGreen(double value)
{
    if (value < 0.25)
        return 0.0;
    else if (value < 0.5)
        return interpolate(value, 0.0, 0.25, 1, 0.5);
    else if (value < 0.75)
        return interpolate(value, 1, 0.5, 0, 0.75);
    else
        return 0;
}

double getBlue(double value)
{
    if (value < 0.5)
        return interpolate(value, 1.0, 0.0, 0.0, 0.5);
    else
        return 0;
}


Vector3D Utils::scalarToRGB(double scalar)
{
    return Vector3D( getRed(scalar),
                getGreen(scalar),
                getBlue(scalar) );
}

Vector3D Utils::computeReflectionDirection(const Vector3D &rayDirection, const Vector3D &normal)
{
    // Compute the perfect reflection direction
    return normal * 2 * dot(normal, -rayDirection) + rayDirection;
}

bool Utils::isTotalInternalReflection(const double &eta, const double &cosThetaI,
                                      double &cosThetaT_out)
{
	double radicant = 1.0 + pow(eta, 2) * (pow(cosThetaI, 2) - 1.0);
	//if radicant is negative we are in totalInternalReflection
	if (radicant < 0.0) return true;

	//if not compute the corsThetaT_out
	cosThetaT_out = sqrt(radicant);
    return false;
}

Vector3D Utils::computeTransmissionDirection(const Ray &r, const Vector3D &normal,
                                             const double &eta, const double &cosThetaI,
                                             const double &cosThetaT)
{
	//vector3 T = (n * a_Ray.GetDirection()) + (n * cosI - sqrtf(cosT2)) * N;
	double aux = (eta * cosThetaI) - cosThetaT;
	Vector3D wt = (r.d.normalized() * eta) + (normal * aux);
    return wt;
}

double Utils::computeReflectanceCoefficient(const double &eta, const double &cosThetaI,
                                            const double &cosThetaT)
{
    return 0.0;
}

//method to test intersections with this ray and a triangle
//u and v are the triangle coordinates of the intersection if the return value is true
//IMPORTANT*** THE method is adapted from Moller - Trumbore resource
//we thought it was a good idea that the ray itself could deal with the triangle intersection
bool Utils::intersect(Ray r, const Vector3D& v0, const Vector3D& v1, const Vector3D& v2, Intersection& inter)
{
	float t;

	Vector3D v0v1 = v1 - v0;
	Vector3D v0v2 = v2 - v0;
	Vector3D pvec = cross(r.d, v0v2);
	float det = dot(v0v1, pvec);

	//comment this line if we want to avoid culling in some point
	//we could create a flag to activate/deactivate it in some cases
	if (det < 0.00001f) return false;
	// ray and triangle are parallel if det is close to 0
	if (fabs(det) < 0.000001f) return false;

	float invDet = 1 / det;

	Vector3D tvec = r.o - v0;
	inter.u = dot(tvec, pvec) * invDet;
	if (inter.u < 0 || inter.u > 1) return false;

	Vector3D qvec = cross(tvec, v0v1);
	inter.v = dot(r.d, qvec) * invDet;
	if (inter.v < 0 || (inter.u + inter.v) > 1) return false;

	//fill the info in the intersection
	inter.isTriangle = true;
	t = dot(v0v2, qvec) * invDet;
	//if (t > r.maxT || /*t < r.minT*/) return false;

	inter.itsPoint = r.o + r.d.normalized() * t;
	return true;
}

bool Utils::intersectBB(Ray r, const Vector3D& min, const Vector3D& max)
{
	float t;

	float x_2 = 1.0f / r.d.x;
	float y_2 = 1.0f / r.d.y;
	float z_2 = 1.0f / r.d.z;

	Vector3D invDir = Vector3D(x_2, y_2, z_2);

	Vector3D minimVertex = min;
	Vector3D maximVertex = max;

	float t1 = (minimVertex.x - r.o.x)*invDir.x;
	float t2 = (maximVertex.x - r.o.x)*invDir.x;
	float t3 = (minimVertex.y - r.o.y)*invDir.y;
	float t4 = (maximVertex.y - r.o.y)*invDir.y;
	float t5 = (minimVertex.z - r.o.z)*invDir.z;
	float t6 = (maximVertex.z - r.o.z)*invDir.z;

	//Calculate minimun t and max t
	float tmin = std::max(std::max(std::min(t1, t2), std::min(t3, t4)), std::min(t5, t6));
	float tmax = std::min(std::min(std::max(t1, t2), std::max(t3, t4)), std::max(t5, t6));

	if (tmax < 0.0)
	{
		t = tmax;
		return false;
	}

	//NO collision case
	if (tmin > tmax)
	{
		t = tmax;
		return false;
	}

	t = tmin;
	return true;
}
