#ifndef SCENE_HPP
#define SCENE_HPP

// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Include Open Dynamics Engine
#include <ode/ode.h>

#include "camera.hpp"
#include "model.hpp"



class Scene
{
public:
    Scene(Camera *camera, GLuint program);
    ~Scene();
    
    void addModel(Model *model);
    void update();
    void draw();
    glm::mat4 MVP(Model *model) const { return projection() * view() * model->model(); }
    
    glm::mat4 view() const;
    glm::mat4 projection() const { return m_projection_matrix; }
    dWorldID worldID() const { return m_worldID; }
    
private:
    
    // private functions
    void moveModel(Model *model);
    
    
    // private variables
    GLuint m_program;
    GLFWwindow* m_window;
    glm::mat4 m_projection_matrix;
    Camera *m_camera;
    std::vector<Model*> m_models;
    
    dWorldID m_worldID;
};




#endif