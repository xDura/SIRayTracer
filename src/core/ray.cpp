#include "ray.h"
#include <iostream>

Ray::Ray() : minT(0), maxT(INFINITY), depth(0)
{}

Ray::Ray(const Vector3D &ori, const Vector3D &dir, size_t dep, double start,
	double end)
	: o(ori), d(dir), minT(start), maxT(end), depth(dep)
{
	/*if (dir.length() != 1.0)
		std::cout << "non normalized dir in one ray" << std::endl;
*/
}


std::string Ray::toString() const
{
    std::ostringstream out;
    out << "origin: " << o << std::endl;
    out << "direction: " << d << std::endl;
    out << "minT = " << minT << ", maxT = " << maxT << std::endl;
    return out.str();
}

void Ray::setMaxTInPoint(const Vector3D& p)
{
	maxT = (p.x - o.x) / d.x;
}

void Ray::setMinTInPoint(const Vector3D& p)
{
	minT = ((p.y - o.y) / d.y) + 1.0;
}

std::ostream &operator<<(std::ostream &out, const Ray &r)
{
    out << r.toString();
    return out;
}

