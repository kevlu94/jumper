#ifndef OBJECTS_HPP
#define OBJECTS_HPP

#include "shapes.hpp"

class Scene;

class ColoredBox: public ColoredCube
{
public:
    ColoredBox() {}
    ColoredBox(dReal density, glm::vec3 color, glm::vec3 size): ColoredCube(color, size) { m_density = density; }
    virtual ~ColoredBox() {}
    
    void setColoredBox(dReal density, glm::vec3 color, glm::vec3 size);
    virtual void addToScene(Scene *scene, glm::vec3 position);
    virtual glm::vec3 position() const { return *((glm::vec3*) dBodyGetPosition(m_bodyID)); }
};

class ColoredImmovableBox: public ColoredCube
{
public:
    ColoredImmovableBox() {}
    ColoredImmovableBox(glm::vec3 color, glm::vec3 size): ColoredCube(color, size) {}
    virtual ~ColoredImmovableBox() {}

    void setColoredImmovableBox(glm::vec3 color, glm::vec3 size);
    virtual void addToScene(Scene *scene, glm::vec3 position);
    virtual glm::vec3 position() const { return *((glm::vec3*) dGeomGetPosition(m_geomID)); }
};


class Human: public Creature
{
public:
    Human();
    Human(glm::vec3 size);
    
    void setHuman(glm::vec3 size);
    virtual ~Human() {}
    virtual void addToScene(Scene *scene, glm::vec3 position);
    //virtual void move(GLFWwindow *window);
    virtual void move(dReal torqueKnee, dReal torqueHip);
    virtual void takeInput();
    virtual void printOutput();
    bool balanced() const;
    void getJointAngles(dReal *cur_knee_angle, dReal *cur_knee_velocity, dReal *cur_hip_angle, dReal *cur_hip_velocity);
    float height() { return m_head.position()[1]; }
    std::vector<glm::vec3> pivots() const;
    float verticalVelocity(float timestep);
    float verticalAcceleration(float timestep);

private:
    bool feetDown() const;
    ColoredBox m_head;
    ColoredBox m_torso;
    ColoredBox m_leftUpperArm;
    ColoredBox m_rightUpperArm;
    ColoredBox m_leftLowerArm;
    ColoredBox m_rightLowerArm;
    ColoredBox m_leftUpperLeg;
    ColoredBox m_rightUpperLeg;
    ColoredBox m_leftLowerLeg;
    ColoredBox m_rightLowerLeg;
    ColoredBox m_leftFoot;
    ColoredBox m_rightFoot;
    dJointID m_neckID;
    dJointID m_leftShoulderID;
    dJointID m_rightShoulderID;
    dJointID m_leftElbowID;
    dJointID m_rightElbowID;
    dJointID m_leftFemoralID;
    dJointID m_rightFemoralID;
    dJointID m_leftKneeID;
    dJointID m_rightKneeID;
    dJointID m_leftAnkleID;
    dJointID m_rightAnkleID;
};


#endif