#ifndef OBJECTS_HPP
#define OBJECTS_HPP

#include "shapes.hpp"

class Scene;

class ColoredBox: public ColoredCube
{
public:
    ColoredBox(dReal density, glm::vec3 color, glm::vec3 size): ColoredCube(color, size) { m_density = density; }
    virtual ~ColoredBox() {}
    
    virtual void addToScene(Scene *scene, glm::vec3 position);
    virtual glm::vec3 position() const { return *((glm::vec3*) dBodyGetPosition(m_bodyID)); }
};

class ColoredImmovableBox: public ColoredCube
{
public:
    ColoredImmovableBox(glm::vec3 color, glm::vec3 size): ColoredCube(color, size) {}
    virtual ~ColoredImmovableBox() {}

    virtual void addToScene(Scene *scene, glm::vec3 position);
    virtual glm::vec3 position() const { return *((glm::vec3*) dGeomGetPosition(m_geomID)); }
};


class Human: public Creature
{
public:
    Human(glm::vec3 size);
    virtual ~Human() {}
    virtual void addToScene(Scene *scene, glm::vec3 position);
    virtual void move(GLFWwindow *window);
//private:
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