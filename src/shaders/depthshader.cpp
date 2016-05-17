#include "depthshader.h"

DepthShader::DepthShader(Vector3D color_, double maxDist_, Vector3D bgColor_)
	:Shader(bgColor_), color(color_), maxDist(maxDist_)
{}

Vector3D DepthShader::computeColor(const Ray &r, const std::vector<Shape*> &objList, const std::vector<PointLightSource> &lsList) const 
{
	Intersection closestIntersection;
	if (!Utils::getClosestIntersection(r, objList, closestIntersection))
		return bgColor;

	float depth = (closestIntersection.itsPoint - r.o).length();
	return color *(1.0 - depth/maxDist);
}