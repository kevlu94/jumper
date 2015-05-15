#ifndef MODEL_HPP
#define MODEL_HPP

#include "globals.hpp"


class Scene;

class Model
{
public:
    Model();
    virtual ~Model();

    unsigned long numVertices() { return m_numVertices; }
    glm::mat4 model() const;
    void setAttribute(GLuint program, const GLchar *name, unsigned int size, GLuint vbo) const;

    // pure virtual functions
    virtual void addToScene(Scene *scene, glm::vec3 position) = 0;
    virtual glm::vec3 position() const = 0;
    virtual bool colored() const = 0;
    virtual bool textured() const = 0;
    
    // accessor functions
    dReal mass() const { return m_mass.mass; }
    glm::vec3 size() const { return m_size; }
    GLuint positionVBO() const { return m_positionVBO; }
    GLuint colorVBO() const { return m_colorVBO; }
    GLuint textureVBO() const { return m_textureVBO; }
    GLuint texture() const { return m_texture; }
    dBodyID bodyID() const { return m_bodyID; }
    
protected:
    // ODE fields not set until model is added to a scene
    dBodyID m_bodyID = 0;
    dGeomID m_geomID = 0;
    
    dMass m_mass;
    dReal m_density = 0;
    glm::vec3 m_size;
    
    unsigned long m_numVertices = 0;
    GLuint m_positionVBO = 0;
    GLuint m_colorVBO = 0;
    GLuint m_textureVBO = 0;
    GLuint m_texture = 0;
};

class Creature
{
public:
    Creature() {}
    Creature(glm::vec3 size): m_size(size) {}
    void setCreature(glm::vec3 size) {m_size=size;}
    virtual ~Creature() {}
    virtual void addToScene(Scene *scene, glm::vec3 position) = 0;
    virtual void move(GLFWwindow *window) = 0;
    virtual void takeInput() = 0;
    virtual void printOutput() = 0;
    glm::vec3 centerOfMass() const;
protected:
    glm::vec3 m_size;
    std::vector<Model*> m_parts;
};

#endif