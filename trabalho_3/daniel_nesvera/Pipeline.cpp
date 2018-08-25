/**
 * @file    pipeline.cpp
 * @date    14/05/2018
 * @author  Daniel André Nesvera
 *
 *    Classe responsavel pela camera e visualização
 *
 */

#include "Pipeline.h"

Pipeline::Pipeline(float fov, float zNear, float zFar)
{

    // Initialize the matrices

    setProjection(fov, zNear, zFar);


}

// Left-Handed
void Pipeline::setProjection(float fov, float zNear, float zFar){
    m_ProjectionMatrix = Matrix4();
    m_ProjectionMatrix.mat[0][0] = std::atan((fov/2.0f)*(M_PI/180));
    m_ProjectionMatrix.mat[0][1] = 0;
    m_ProjectionMatrix.mat[0][2] = 0;
    m_ProjectionMatrix.mat[0][3] = 0;
    m_ProjectionMatrix.mat[1][0] = 0;
    m_ProjectionMatrix.mat[1][1] = std::atan((fov/2.0f)*(M_PI/180));
    m_ProjectionMatrix.mat[1][2] = 0;
    m_ProjectionMatrix.mat[1][3] = 0;
    m_ProjectionMatrix.mat[2][0] = 0;
    m_ProjectionMatrix.mat[2][1] = 0;
    m_ProjectionMatrix.mat[2][2] = -((zFar+zNear)/(zFar-zNear));
    m_ProjectionMatrix.mat[2][3] = -(2*(zFar*zNear)/(zFar-zNear));
    m_ProjectionMatrix.mat[3][0] = 0;
    m_ProjectionMatrix.mat[3][1] = 0;
    m_ProjectionMatrix.mat[3][2] = -1;
    m_ProjectionMatrix.mat[3][3] = 0;
}

Matrix4 Pipeline::getProjection(){
    return m_ProjectionMatrix;
}

Matrix4 Pipeline::lookAt(Vector3 eye, Vector3 center, Vector3 tmp = Vector3(0, 1, 0)){
    Vector3 forward = Vector3(eye - center).normalize();
    Vector3 right = tmp.normalize()^forward;
    Vector3 up = forward^right;

    Matrix4 camToWorld;

    camToWorld.mat[0][0] = right.x;
    camToWorld.mat[0][1] = right.y;
    camToWorld.mat[0][2] = right.z;
    camToWorld.mat[1][0] = up.x;
    camToWorld.mat[1][1] = up.y;
    camToWorld.mat[1][2] = up.z;
    camToWorld.mat[2][0] = forward.x;
    camToWorld.mat[2][1] = forward.y;
    camToWorld.mat[2][2] = forward.z;

    camToWorld.mat[0][3] = -(right*(eye));
    camToWorld.mat[1][3] = -(up*(eye));
    camToWorld.mat[2][3] = -(forward*(eye));

    camToWorld.mat[3][3] = 1;

    return camToWorld;
}
