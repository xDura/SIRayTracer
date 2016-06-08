#include "ray.h"
#include <iostream>

Ray::Ray() : minT(0), maxT(INFINITY), depth(0)
{}

Ray::Ray(const Vector3D &ori, Vector3D &dir, size_t dep, double start,
	double end)
	: o(ori), d(dir), minT(start), maxT(end), depth(dep)
{
	//in cases of problems with the length we can add this
	//for the moment I dont use it because this is computatinally slow
	//as we construct a lot of rays
	if (dir.length() != 1.0)
		d = dir.normalized();
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
	minT = ((p.y - o.y) / d.y) + Epsilon;
}

std::ostream &operator<<(std::ostream &out, const Ray &r)
{
    out << r.toString();
    return out;
}

