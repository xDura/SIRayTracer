#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "shape.h"

//currently unused
class Triangle : public Shape
{
public:
	Triangle(const Matrix4x4 &t_, Material *material_);
	virtual bool rayIntersect(const Ray &ray, Intersection &its) const;
	virtual bool rayIntersectP(const Ray &ray) const;

	Vector3D v0;
	Vector3D v1;
	Vector3D v2;
};

#endif
