#include "triangle.h"

Triangle::Triangle(const Matrix4x4 &t_, Material *material_)
	:Shape(t_, material_)
{}

bool Triangle::rayIntersect(const Ray &ray, Intersection &its) const
{
	return false;
}

bool Triangle::rayIntersectP(const Ray &ray) const
{
	return false;
}