#include "model.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>



using namespace std;


glm::mat4 Model::model() const
{
    glm::quat quaternion = glm::quat(glm::vec3(m_pitch, m_yaw, m_roll));
    glm::mat4 rotationMatrix = glm::mat4_cast(quaternion);
    glm::mat4 translateMatrix = glm::translate(glm::mat4(1.0f), position());
    return translateMatrix * rotationMatrix;
    
}

void Model::addBodyToWorld(dWorldID worldID)
{
    m_bodyID = dBodyCreate(worldID);
    dMassSetBox(&m_mass, 1.0f, 1.0f, 1.0f, 1.0f);
    dBodySetMass(m_bodyID, &m_mass);
    dBodySetPosition(m_bodyID, 0.0f, 0.0f, 0.0f);
}

void Model::removeBodyFromWorld()
{
    dBodyDestroy(m_bodyID);
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








