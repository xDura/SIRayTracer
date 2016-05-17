#ifndef PHONG_H
#define PHONG_H
#include "material.h"

class Phong : public Material
{
public:
	Phong(Vector3D diff_, Vector3D spec_, float shininess_);
	
	virtual Vector3D getReflectance(const Vector3D &n, const Vector3D &wo, const Vector3D &wi) const;
	virtual bool hasSpecular() const;
	virtual bool hasTransmission() const;
	virtual bool hasDiffuseOrGlossy() const;
	virtual double getIndexOfRefraction() const;

	Vector3D kSpecular;
	Vector3D kDiffuse;
	float shininess;
};

#endif