#include "mirror.h"
#include "../core/utils.h"
#include <algorithm>

Mirror::Mirror(Vector3D& kSpecular)
	:kSpec(kSpecular)
{}

//unused for the moment
Vector3D Mirror::getReflectance(const Vector3D &n, const Vector3D &wo, const Vector3D &wi) const
{
	//r(wi, wo) = ks(wo*wr)s
	Vector3D reflectedDir = Utils::reflect(n, -wi);

	Vector3D specularTerm = kSpec * dot(reflectedDir, wo);
	return specularTerm;
}

bool Mirror::hasSpecular() const
{
	return true;
}

bool Mirror::hasTransmission() const
{
	return false;
}

bool Mirror::hasDiffuseOrGlossy() const
{
	return false;
}

double Mirror::getIndexOfRefraction() const
{
	return 0;
}
