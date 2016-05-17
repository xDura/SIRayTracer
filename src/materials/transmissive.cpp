#include "transmissive.h"
#include "../core/utils.h"

Transmissive::Transmissive(Vector3D& kSpecular, float reflactionIndex_)
	:refractionIndex(reflactionIndex_), kSpec(kSpecular)
{}

//unused for the moment
Vector3D Transmissive::getReflectance(const Vector3D &n, const Vector3D &wo, const Vector3D &wi) const
{
	//r(wi, wo) = ks(wo*wr)s
	Vector3D reflectedDir = Utils::reflect(n, -wi);

	Vector3D specularTerm = kSpec * dot(reflectedDir, wo);
	return specularTerm;
}

bool Transmissive::hasSpecular() const
{
	return false;
}

bool Transmissive::hasTransmission() const
{
	return true;
}

bool Transmissive::hasDiffuseOrGlossy() const
{
	return false;
}

double Transmissive::getIndexOfRefraction() const
{
	//TODO: crear atributo con esto
	return refractionIndex;
}
