#ifndef MODEL_HPP
#define MODEL_HPP

#include <stdio.h>
#include <vector>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <ode/ode.h>

class Model
{
public:
    Model() {}
    virtual ~Model();


    unsigned long numVertices() { return m_numVertices; }
    glm::mat4 model() const;
    void addBodyToWorld(dWorldID worldID, glm::vec3 position);
    void removeBodyFromWorld();
    
    virtual bool colored() const = 0;
    virtual bool textured() const = 0;
    
    // accessor functions
    //glm::vec3 position() const { return m_position; }
    glm::vec3 position() const { return *((glm::vec3*) dBodyGetPosition(m_bodyID)); }
    GLuint positionVBO() const { return m_positionVBO; }
    GLuint colorVBO() const { return m_colorVBO; }
    GLuint textureVBO() const { return m_textureVBO; }
    GLuint texture() const { return m_texture; }
    dBodyID bodyID() const { return m_bodyID; }
    
    // mutator functions
    //void shift(glm::vec3 distance) { m_position += distance; }
    void yawBy(GLfloat angle) { m_yaw = fmod(m_yaw + angle, 2.0 * M_PI); }
    void pitchBy(GLfloat angle) { m_pitch = fmod(m_pitch + angle, 2.0 * M_PI); }
    void rollBy(GLfloat angle) { m_roll = fmod(m_roll + angle, 2.0 * M_PI); }
    void setAttribute(GLuint program, const GLchar *name, unsigned int size, GLuint vbo) const;

    
    
    
protected:
    // ODE fields not set until model is added to a scene
    dBodyID m_bodyID = 0;
    dGeomID m_geomID = 0;
    
    dMass m_mass;
    dReal m_density = 0;
    dReal m_xSize = 0;
    dReal m_ySize = 0;
    dReal m_zSize = 0;
    
    
    
    unsigned long m_numVertices = 0;
    GLuint m_positionVBO = 0;
    GLuint m_colorVBO = 0;
    GLuint m_textureVBO = 0;
    GLuint m_texture = 0;
    
    //glm::vec3 m_position;
    glm::vec4 m_quaternion;
    GLfloat m_yaw = 0.0f;
    GLfloat m_pitch = 0.0f;
    GLfloat m_roll = 0.0f;
    
};

#endif