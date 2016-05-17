#ifndef TRANSMISSIVE_H
#define TRANSMISSIVE_H
#include "material.h"

class Transmissive : public Material
{
public:
	Transmissive(Vector3D& kSpecular, float reflactionIndex_);

	virtual Vector3D getReflectance(const Vector3D &n, const Vector3D &wo, const Vector3D &wi) const;
	virtual bool hasSpecular() const;
	virtual bool hasTransmission() const;
	virtual bool hasDiffuseOrGlossy() const;
	virtual double getIndexOfRefraction() const;

	Vector3D kSpec;
	float refractionIndex;

};
#endif
