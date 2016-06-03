#include "globalishader.h"
#include "../samplers/hemisphericalsampler.h"

GlobalIlumination::GlobalIlumination(Vector3D& bgColor_, int nSamples_)
	:Shader(bgColor_), nSamples(nSamples_)
{}

Vector3D GlobalIlumination::computeColor(const Ray &r, const std::vector<Shape*> &objList, const std::vector<PointLightSource> &lsList) const
{
	Vector3D finalColor(bgColor);
	Intersection closestIntersection;
	if (!Utils::getClosestIntersection(r, objList, closestIntersection)) return finalColor;

	if (r.depth > 50) return finalColor;

	//for each light lets compute the reflectance
	//and sum it to the final color
	Vector3D directTerm;
	Vector3D normal;
	Vector3D wo;
	Vector3D wi;
	Vector3D lightIntensity;
	Intersection aux;
	const Material& currentMat = closestIntersection.shape->getMaterial();
	//i think this could be r.d instead
	wo = (r.o - closestIntersection.itsPoint).normalized();
	normal = closestIntersection.normal.normalized();

	#pragma region PERFECT_SPECULAR
	//specular mirror like reflections part
	if (currentMat.hasSpecular())
	{
		//base case
		/*if (r.depth > 4)
			return finalColor;*/

		Vector3D perfSpecDir = Utils::reflect(normal, r.d);
		Ray rSpec = Ray(closestIntersection.itsPoint, perfSpecDir.normalized(), r.depth + 1);
		directTerm = computeColor(rSpec, objList, lsList);
	}
	#pragma endregion

	#pragma region TRANSMISSION

	if (currentMat.hasTransmission())
	{
		//base case
		/*if (r.depth > 4) {
			std::cout << "TOO MUCH ITERATIONS";
			return finalColor;
		}*/

		//for the moment we consider that the medium in
		//the ambient is air
		double eta = currentMat.getIndexOfRefraction();
		double cosThetaI = dot(-r.d.normalized(), normal);
		double cosThetaT = 0.0;
		//case Going out of the medium
		if (cosThetaI < 0.0)
		{
			normal = -normal;
			eta = 1 / eta;
			cosThetaI = dot(-r.d.normalized(), normal);
		}

		if (!Utils::isTotalInternalReflection(eta, cosThetaI, cosThetaT))
		{
			Vector3D transMissionDir = Utils::computeTransmissionDirection(r, normal, eta, cosThetaI, cosThetaT);
			Ray rTrans = Ray(closestIntersection.itsPoint, transMissionDir.normalized(), r.depth);
			directTerm = computeColor(rTrans, objList, lsList);
		}
		else
		{
			Vector3D perfSpecDir = Utils::reflect(normal, r.d);
			Ray rSpec = Ray(closestIntersection.itsPoint, perfSpecDir.normalized(), r.depth + 1);
			directTerm = computeColor(rSpec, objList, lsList);
		}
	}

#pragma endregion

	#pragma region DIRECT_ILUMINATION_OTHERMATS

	if (currentMat.hasDiffuseOrGlossy())
	{
		for (int i = 0; i < lsList.size(); i++)
		{
			PointLightSource pl = lsList[i];
			Vector3D lightPos = pl.getPosition();
			Vector3D itsPoint = closestIntersection.itsPoint;
			//compute vars
			wi = (lightPos - itsPoint).normalized();
			lightIntensity = pl.getIntensity(itsPoint);

			//shadowRay to know if this light
			//can iluminate this intersection point
			Ray shadowRay = Ray(itsPoint, (lightPos - itsPoint).normalized());
			//we set the maxT as the place of the light because 
			//we want only oclusions that closer than the light

			shadowRay.setMaxTInPoint(lightPos);
			if (Utils::hasIntersection(shadowRay, objList))
				continue;

			Vector3D contribution = currentMat.getReflectance(normal, wo, wi);
			directTerm += Utils::multiplyPerCanal(lightIntensity, contribution);

		}
	}
	#pragma endregion

	#pragma region INDIRECT_ILUMINATION

	if (currentMat.hasDiffuseOrGlossy()) 
	{
		Ray normalRay = Ray(closestIntersection.itsPoint, normal.normalized(), r.depth);
		Vector3D indirectTerm = computeIndirectTerm(normalRay, objList, lsList, currentMat);
		return directTerm + indirectTerm;
	}

	#pragma endregion

	return directTerm;
}

//r is the ray in the normals direction
Vector3D GlobalIlumination::computeIndirectTerm(const Ray &normalRay, const std::vector<Shape*> &objList, const std::vector<PointLightSource> &lsList, const Material& currentMat) const
{
	int secondaryDepth = normalRay.depth;
	if (secondaryDepth > 0) 
	{
		Vector3D kamb = Vector3D(0.2, 0.2, 0.2);
		return Utils::multiplyPerCanal(kamb, currentMat.getDiffuseCoefficient());
	}

	//if we are in a phong one then depth +1 
	secondaryDepth += 1;

	//remove this integer and use it as a parameter
	//on the constructor of globalShader
	HemisphericalSampler sampler;
	Vector3D sample;
	Vector3D indirect = Vector3D(0.0);
	for (int i = 0; i < nSamples; i++)
	{
		sample = sampler.getSample(normalRay.d);
		Ray sampleRay = Ray(normalRay.o, sample, secondaryDepth);
		Vector3D contribution = computeColor(sampleRay, objList, lsList);
		indirect += contribution;
	}
	indirect = Utils::multiplyPerCanal(indirect, currentMat.getDiffuseCoefficient());

	return indirect / nSamples;
}