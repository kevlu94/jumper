#ifndef INTERFACE_HPP
#define INTERFACE_HPP



#include "globals.hpp"
#include "scene.hpp"
#include "model.hpp"
#include "shapes.hpp"
#include "objects.hpp"

using namespace glm;


class Simulator {
public:
    Simulator();
    int initializeGL();
    void closeGL();
    void initilizeSimulator();
    void runSimulator(dReal torqueKnee,dReal torqueHip, dReal *knee_angle, dReal *knee_velocity, dReal *hip_angle, dReal *hip_velocity);
    void closeSimulator();
    bool isBalanced();
    glm::vec3 getCenterOfMass();
private:
    bool m_render = false;
    Scene scene;
    GLFWwindow* window;
    GLuint program;
    Camera camera;
    Human human;
    GLuint VertexArrayID;
    ColoredImmovableBox ground;
};


#endif