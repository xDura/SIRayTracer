#ifndef GLOBALISHADER_H
#define GLOBALISHADER_H
#include "shader.h"

class GlobalIlumination : Shader
{
public:
	GlobalIlumination() = delete;
	GlobalIlumination(Vector3D& bgColor_);
	virtual Vector3D computeColor(const Ray &r, const std::vector<Shape*> &objList, const std::vector<PointLightSource> &lsList) const;
};
#endif
