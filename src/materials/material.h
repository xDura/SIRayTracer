#ifndef MATERIAL
#define MATERIAL

#include "../core/vector3d.h"
#include <iostream>
#include "../core/intersection.h"
#include "../core/image.h"

class Material
{
public:
    Material();
	Image* texture;
    virtual Vector3D getReflectance(const Vector3D &n, const Vector3D &wo,
                                    const Vector3D &wi) const = 0;
	virtual Vector3D getReflectance(const Vector3D &n, const Vector3D &wo,
		const Vector3D &wi, const Intersection& its) const;

	virtual Vector3D getColor(const Intersection& its) const;
    virtual bool hasSpecular() const = 0;
    virtual bool hasTransmission() const = 0;
    virtual bool hasDiffuseOrGlossy() const = 0;
    virtual double getIndexOfRefraction() const;
	virtual Vector3D getDiffuseCoefficient() const
	{
		std::cout << "Warning!"
			<< "Calling material::getDiffuseCoefficient()"
			<< " in one material that does not override that method!"
			<< std::endl;
		return Vector3D(-1);
	}
};


#endif // MATERIAL
