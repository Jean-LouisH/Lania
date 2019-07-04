#ifndef OBJMeshExtractor_h
#define OBJMeshExtractor_h

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

typedef struct
{
	float* data;
	uint32_t size;
}PolygonalMesh;

char* readOBJFile(const char* filepath);
PolygonalMesh parseForOBJGeometricVectors(char* OBJFileContents);
PolygonalMesh extractMeshFromOBJFile(const char* filepath);
void freePolygonalMesh(PolygonalMesh* mesh);

#ifdef __cplusplus
}
#endif

#endif /*OBJMeshExtractor_h*/