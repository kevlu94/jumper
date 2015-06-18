#include "globals.hpp"
#include "model.hpp"


using namespace std;

Model::Model()
{

}

Model::~Model()
{
    if (m_bodyID)
        dBodyDestroy(m_bodyID);
    if (m_geomID)
        dGeomDestroy(m_geomID);
}

glm::mat4 Model::model() const
{
    const dReal *e = dGeomGetRotation(m_geomID);
    glm::mat4 rotationMatrix = glm::mat4(e[0], e[4], e[8], 0.0f,
                                         e[1], e[5], e[9], 0.0f,
                                         e[2], e[6], e[10], 0.0f,
                                         0.0f, 0.0f, 0.0f, 1.0f);
                                         
    glm::mat4 translateMatrix = glm::translate(glm::mat4(1.0f), position());
    return (translateMatrix * rotationMatrix);
}


void Model::setAttribute(GLuint program, const GLchar *name, unsigned int size, GLuint vbo) const
{
    if (program == 0)
      return;
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

glm::vec3 Creature::centerOfMass() const
{
    glm::vec3 ret(0.0f);
    dReal totalMass = 0.0f;
    for (unsigned int i = 0; i < m_parts.size(); i++)
    {
        ret += (m_parts[i]->mass() * m_parts[i]->position());
        totalMass += m_parts[i]->mass();
    }
    return (ret / totalMass);
}






