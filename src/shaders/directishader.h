#ifndef DIRECTISHADER_H
#define DIRECTISHADER_H
#include "shader.h"

class DirectIlumination : public Shader
{
public:
	DirectIlumination() = delete;
	DirectIlumination(Vector3D bgColor_);
	virtual Vector3D computeColor(const Ray &r, const std::vector<Shape*> &objList, const std::vector<PointLightSource> &lsList) const;
};
#endif