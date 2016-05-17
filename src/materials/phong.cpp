#include "phong.h"
#include "../core/utils.h"
#include <algorithm>

Phong::Phong(Vector3D diff_, Vector3D spec_, float shininess_)
	:kDiffuse(diff_), kSpecular(spec_), shininess(shininess_)
{}

Vector3D Phong::getReflectance(const Vector3D &n, const Vector3D &wo, const Vector3D &wi) const
{
	//r(wi, wo) = kd(wi*n) + ks(wo*wr)s
	Vector3D reflectedDir = Utils::reflect(n, -wi);

	Vector3D diffuseTerm = kDiffuse * std::max(0.0, (dot(n, wi)));
	Vector3D specularTerm = kSpecular * pow(std::max(0.0, dot(reflectedDir, wo)), shininess);

	Vector3D reflectance = diffuseTerm + specularTerm;
	return reflectance;
}

bool Phong::hasSpecular() const
{
	return false;
}

bool Phong::hasTransmission() const
{
	return false;
}

bool Phong::hasDiffuseOrGlossy() const
{
	return true;
}

double Phong::getIndexOfRefraction() const
{
	//TODO:
	return 0.0f;
}