#include "material.h"
#include "../core/utils.h"
#include <iostream>

Material::Material()
{ }

double Material::getIndexOfRefraction() const
{
    std::cout << "Warning! Calling \"Material::getIndexOfRefraction()\" for a non-transmissive material"
              << std::endl;

    return -1;
}

Vector3D Material::getReflectance(const Vector3D &n, const Vector3D &wo,
	const Vector3D &wi, const Intersection& its) const
{
	Vector3D baseReflectance = getReflectance(n, wo, wi);
	if (!texture || !its.isTriangle) 
	{
		std::cout << "Warning!"
			<< "using the getReflectance overload for textures"
			<< " in one material that does not have a texture!"
			<< std::endl;
		return baseReflectance;
	}

	//the 1.0 - its.v its needed because of how the uvs are stored in the ase file
	Vector2D texCoords = Vector2D((its.u) * texture->width, (1.0 - its.v) * texture->height);
	Vector3D texColor = texture->getPixelSafe(texCoords.x, texCoords.y);
	texColor = texColor / 255.0;
	return Utils::multiplyPerCanal(texColor, baseReflectance);
}

Vector3D Material::getColor(const Intersection& its) const
{
	if (!texture || !its.isTriangle)
	{
		std::cout << "Warning!"
			<< "using the getcolor overload for materials with texture"
			<< " in one material that does not have a texture!"
			<< std::endl;
		return Vector3D(0);
	}

	Vector2D texCoords = Vector2D((its.u) * texture->width, (1.0 - its.v) * texture->height);
	Vector3D texColor = texture->getPixelSafe(texCoords.x, texCoords.y);
	texColor = texColor / 255.0;
	return texColor;
}
