#include "shape.h"
#include "mesh.h"

Mesh::Mesh(const Matrix4x4 &t_, Material *m_)
//first call your superclass constructor
	:Shape(t_, m_)
{}

Mesh::~Mesh()
{
	//delete verts and stuff
}


bool Mesh::rayIntersectP(const Ray &ray) const
{
	//we dont need them just pass them
	//for this concrete method that just tests if 
	//intersects or not
	float u = 0.0f;
	float v = 0.0f;
	Intersection its;
	return rayIntersect(ray, its);
}

//LEGACY
//bool Mesh::rayIntersect(const Ray &ray, float& u, float& v) const
//{
//	if (vertices.size() % 3 != 0)
//	{
//		//for the moment we only use triangle meshes
//		std::cout << "invalid size of vertices for triangle mesh" << std::endl;
//		return false;
//	}
//
//	Ray r = worldToObject.transformRay(ray);
//
//	for (int i = 0; i < vertices.size(); i += 3)
//	{
//		//Important!! take a look the Intersect method!
//		if (Utils::intersect(r, vertices[i], vertices[i + 1], vertices[i + 2], u, v))
//			return true;
//	}
//	return false;
//}


bool Mesh::rayIntersect(const Ray &ray, Intersection &its) const
{
	if (vertices.size() % 3 != 0)
	{
		//for the moment we only use triangle meshes
		std::cout << "invalid size of vertices for triangle mesh" << std::endl;
		return false;
	}

	Ray r = worldToObject.transformRay(ray);

	float closestDist = INFINITY;
	Intersection auxIts;
	Intersection closestIts;
	bool inter = false;

	for (int i = 0; i < vertices.size(); i += 3)
	{
		//Important!! take a look the Intersect method!
		if (!Utils::intersect(r, vertices[i], vertices[i + 1], vertices[i + 2], auxIts))
			continue;

		inter = true;
		float auxD = (auxIts.itsPoint - r.o).length();
		if (auxD < closestDist) 
		{
			closestDist = auxD;
			closestIts = auxIts;
			//get the interpolated normal
			//and store it in the intersection
			closestIts.normal = (normals[i] * auxIts.u) + (normals[i + 1] * auxIts.v) + (normals[i + 2] * (1.0 - auxIts.u - auxIts.v));
			closestIts.normal = objectToWorld.transformVector(closestIts.normal);
			//closestIts.normal = normals[i];
			closestIts.shape = this;
			//pass the its point to world cordinates
			closestIts.itsPoint = objectToWorld.transformPoint(its.itsPoint);
		}
	}

	its = closestIts;
	return inter;
}

//this method is used to load a mesh from an ase file
//it takes things that we are not currently using like the 
//uvs and the normals
//but we will
bool Mesh::loadFromASE(const char* fileName)
{
	TextParser parser;
	bool found = parser.create(fileName);

	if (found) {

		//get the name in the future?

		//MATERIALS
		//if (parser.countword("*MATERIAL_LIST") != 0) {

		//	parser.seek("*MATERIAL_COUNT");
		//	int nMats = parser.getint();
		//	numMaterials = nMats;
		//	matIDs.resize(nMats);
		//	matIndex.resize(nMats);
		//	for (unsigned int i = 0; i < nMats; i++) {
		//		parser.seek("*MATERIAL_AMBIENT");
		//		Vector3D amb;
		//		amb.x = parser.getfloat();
		//		amb.y = parser.getfloat();
		//		amb.z = parser.getfloat();

		//		parser.seek("*MATERIAL_DIFFUSE");
		//		Vector3D diff;
		//		diff.x = parser.getfloat();
		//		diff.y = parser.getfloat();
		//		diff.z = parser.getfloat();

		//		parser.seek("*MATERIAL_SPECULAR");
		//		Vector3D spec;
		//		spec.x = parser.getfloat();
		//		spec.y = parser.getfloat();
		//		spec.z = parser.getfloat();

		//		parser.seek("*MATERIAL_SHINE");
		//		float shine = parser.getfloat();


		//		int mid = Manager::createMaterial(spec, diff, amb, shine);
		//		matIDs[i] = mid;
		//	}

		//}
		//else {
		//	matIDs.resize(1);
		//	numMaterials = 1;
		//	matIDs[0] = 0;
		//}

		//NUM VERTS
		parser.seek("*MESH_NUMVERTEX");
		int nVerts = parser.getint();

		//NUM FACES
		parser.seek("*MESH_NUMFACES");
		int nFaces = parser.getint();

		//FIND THE VERTICES PART AND
		//SAVE VERTICES
		std::vector< Vector3D > auxVerts;
		auxVerts.resize(nVerts);
		int id;
		for (unsigned int i = 0; i < nVerts; i++) {
			parser.seek("*MESH_VERTEX");
			id = parser.getint();
			float x = parser.getfloat();
			float y = parser.getfloat();
			float z = parser.getfloat();
			auxVerts[id] = Vector3D(x, z, -y);
		}

		//FIND THE FACES PART
		//USE THE FACES AND FILL THE MESH->vertices
		int vCounter = 0;
		vertices.resize(nFaces * 3);
		for (unsigned int i = 0; i < nFaces; i++) {
			parser.seek("*MESH_FACE");
			parser.getword();
			for (unsigned int j = 0; j < 3; j++) {
				parser.getword();
				int index = parser.getint();
				vertices[vCounter] = auxVerts[index];
				vCounter++;
			}
		}
		//*******			 *******


		//****		UVS PART		*******
		//parser.seek("*MESH_NUMTVERTEX");
		//int nTVerts = parser.getint();
		//std::vector< Vector2D > auxTVerts;
		//auxTVerts.resize(nTVerts);
		//int tv;
		//for (unsigned int i = 0; i < nTVerts; i++) {
		//	parser.seek("*MESH_TVERT");
		//	tv = parser.getint();
		//	float u = parser.getfloat();
		//	float v = parser.getfloat();
		//	auxTVerts[tv] = Vector2D(u, v);
		//}

		//parser.seek("*MESH_NUMTVFACES");
		//int nTFaces = parser.getint();
		//uvs.resize(nTFaces * 3);
		//int tCounter = 0;
		//for (unsigned int i = 0; i < nTFaces; i++) {
		//	parser.seek("*MESH_TFACE");
		//	parser.getint();
		//	for (unsigned int j = 0; j < 3; j++) {
		//		int index = parser.getint();
		//		uvs[tCounter] = auxTVerts[index];
		//		tCounter++;
		//	}
		//}
		//*********			 ***********


		//******	NORMALS PART	********
		normals.resize(nFaces * 3);
		for (unsigned int i = 0; i < nFaces * 3; i++) {
			parser.seek("*MESH_VERTEXNORMAL");
			parser.getword();
			float x = parser.getfloat();
			float y = parser.getfloat();
			float z = parser.getfloat();

			normals[i] = Vector3D(x, z, y);
		}
		//*******				 **************

		//*******	COMPUTE AABB	*******
		//for the moment we dont need it here
		computeAABB();

		return true;
	}

	return false;
}

void Mesh::computeAABB()
{
	Vector3D aux_min = vertices[0];
	Vector3D aux_max = aux_min;
	Vector3D m_center = aux_min;

	for (unsigned int i = 1; i < vertices.size(); i++) {
		Vector3D v = vertices[i];
		m_center = m_center + v;

		if (v.x > aux_max.x)
			aux_max.x = v.x;
		if (v.y > aux_max.y)
			aux_max.y = v.y;
		if (v.z > aux_max.z)
			aux_max.z = v.z;

		if (v.x < aux_min.x)
			aux_min.x = v.x;
		if (v.y < aux_min.y)
			aux_min.y = v.y;
		if (v.z < aux_min.z)
			aux_min.z = v.z;
	}

	m_center = m_center / vertices.size();
	center = m_center;

	this->max = aux_max;
	this->min = aux_min;
}