#ifndef MESH_H
#define MESH_H
#include <vector>
#include "../extra/textparser.h"

class Mesh : public Shape
{
public:
	Mesh(const Matrix4x4 &t_, Material* m_);
	~Mesh();
	virtual bool rayIntersect(const Ray &ray, Intersection &its) const;
	virtual bool rayIntersectP(const Ray &ray) const;
	bool loadFromASE(const char* fileName);
	void setMaterial(Material* m) { material = m; }
	void computeAABB();

	std::vector<Vector3D> vertices;
	std::vector<Vector3D> normals;
	std::vector<Vector2D> uvs;
	Vector3D min;
	Vector3D max;
	Vector3D center;
};

#endif
