#ifndef GLOBALISHADER_H
#define GLOBALISHADER_H
#include "shader.h"

class GlobalIlumination :public Shader
{
public:
	GlobalIlumination() = delete;
	GlobalIlumination(Vector3D& bgColor_, int nSamples_);
	virtual Vector3D computeColor(const Ray &r, const std::vector<Shape*> &objList, const std::vector<PointLightSource> &lsList) const;
	Vector3D computeIndirectTerm(const Ray &normalRay, const std::vector<Shape*> &objList, const std::vector<PointLightSource> &lsList, const Material& currentMat) const;

	int nSamples;
};
#endif
