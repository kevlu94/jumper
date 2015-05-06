#include "model.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>



using namespace std;

Model::~Model()
{
    if (m_bodyID)
        dBodyDestroy(m_bodyID);
    if (m_geomID)
        dGeomDestroy(m_geomID);
}

glm::mat4 Model::model() const
{
    glm::quat quaternion = glm::quat(glm::vec3(m_pitch, m_yaw, m_roll));
    glm::mat4 rotationMatrix = glm::mat4_cast(quaternion);
    glm::mat4 translateMatrix = glm::translate(glm::mat4(1.0f), position());
    return translateMatrix * rotationMatrix;
    
}

void Model::addBodyToWorld(dWorldID worldID, glm::vec3 position)
{
    m_bodyID = dBodyCreate(worldID);
    dBodySetMass(m_bodyID, &m_mass);
    dBodySetPosition(m_bodyID, position[0], position[1], position[2]);
}

void Model::removeBodyFromWorld()
{
    // unimplemented
}


// Private functions



void Model::setAttribute(GLuint program, const GLchar *name, unsigned int size, GLuint vbo) const
{
    GLint attribLoc = glGetAttribLocation(program, name);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glEnableVertexAttribArray(attribLoc);
    glVertexAttribPointer(attribLoc,
                          size,
                          GL_FLOAT,
                          GL_FALSE,
                          0,
                          (void*)0);
}








