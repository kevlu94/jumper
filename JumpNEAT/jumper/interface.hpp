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
    bool failed() { return scene.failed(); }
    glm::vec3 getCenterOfMass();
    GLFWwindow *window() { return m_window; }
    float humanHeight() { return human.height(); }
    bool liftOff(float offset = 0.0f);
    float verticalVelocity() { return human.verticalVelocity(DT * STEPS_PER_INPUT); }
    float verticalAcceleration() { return human.verticalAcceleration(DT * STEPS_PER_INPUT); }
private:
    bool m_render = false;
    Scene scene;
    GLFWwindow* m_window;
    GLuint program;
    Camera camera;
    Human human;
    GLuint VertexArrayID;
    ColoredImmovableBox ground;
};


#endif