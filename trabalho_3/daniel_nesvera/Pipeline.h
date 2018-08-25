#ifndef PIPELINE_H
#define PIPELINE_H

#include "math.h"

#include "matrix4.h"
#include "Vector3.h"

using namespace std;

class Pipeline
{

public:
    Pipeline(float fov, float zNear, float zFar);
    void setProjection(float fov, float zNear, float zFar);
    Matrix4 getProjection();
    Matrix4 lookAt(Vector3 eye, Vector3 center, Vector3 tmp);


    Matrix4 m_ProjectionMatrix;

private:

};

#endif // PIPELINE_H
