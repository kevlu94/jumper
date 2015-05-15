#include "objects.hpp"
#include "scene.hpp"

void ColoredBox::addToScene(Scene *scene, glm::vec3 position)
{
    // body
    m_bodyID = dBodyCreate(scene->worldID());
    dMassSetBox(&m_mass, m_density, 2 * m_size[0], 2 * m_size[1], 2 * m_size[2]);
    dBodySetMass(m_bodyID, &m_mass);
    dBodySetPosition(m_bodyID, position[0], position[1], position[2]);
    // geometry
    m_geomID = dCreateBox(scene->spaceID(), 2 * m_size[0], 2 * m_size[1], 2 * m_size[2]);
    dGeomSetBody(m_geomID, m_bodyID);
    dGeomSetPosition(m_geomID, position[0], position[1], position[2]);

}

void ColoredImmovableBox::addToScene(Scene *scene, glm::vec3 position)
{
    m_geomID = dCreateBox(scene->spaceID(), 2 * m_size[0], 2 * m_size[1], 2 * m_size[2]);
    dGeomSetBody(m_geomID, m_bodyID);
    dGeomSetPosition(m_geomID, position[0], position[1], position[2]);
}

Human::Human(glm::vec3 size): Creature(size),
m_torso(1.0f, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.2f, 1.9f, 0.2f)),
m_leftUpperArm(1.0f, glm::vec3(0.3f, 0.3f, 0.0f), glm::vec3(0.1f, 0.9f, 0.1f)),
m_rightUpperArm(1.0f, glm::vec3(0.0f, 0.3f, 0.3f), glm::vec3(0.1f, 0.9f, 0.1f)),
m_leftLowerArm(1.0f, glm::vec3(0.6f, 0.3f, 0.0f), glm::vec3(0.1f, 0.9f, 0.1f)),
m_rightLowerArm(1.0f, glm::vec3(0.0f, 0.3f, 0.6f), glm::vec3(0.1f, 0.9f, 0.1f)),
m_leftUpperLeg(1.0f, glm::vec3(0.3f, 0.0f, 0.0f), glm::vec3(0.1f, 0.7f, 0.1f)),
m_rightUpperLeg(1.0f, glm::vec3(0.0f, 0.0f, 0.3f), glm::vec3(0.1f, 0.7f, 0.1f)),
m_leftLowerLeg(1.0f, glm::vec3(0.6f, 0.0f, 0.0f), glm::vec3(0.1f, 0.7f, 0.1f)),
m_rightLowerLeg(1.0f, glm::vec3(0.0f, 0.0f, 0.6f), glm::vec3(0.1f, 0.7f, 0.1f)),
m_leftFoot(1.0f, glm::vec3(0.9f, 0.0f, 0.0f), glm::vec3(0.3f, 0.1f, 0.7f)),
m_rightFoot(1.0f, glm::vec3(0.0f, 0.0f, 0.9f), glm::vec3(0.3f, 0.1f, 0.8f))
{
    m_parts.push_back(&m_torso);
    m_parts.push_back(&m_leftUpperArm);
    m_parts.push_back(&m_rightUpperArm);
    m_parts.push_back(&m_leftLowerArm);
    m_parts.push_back(&m_rightLowerArm);
    m_parts.push_back(&m_leftUpperLeg);
    m_parts.push_back(&m_rightUpperLeg);
    m_parts.push_back(&m_leftLowerLeg);
    m_parts.push_back(&m_rightLowerLeg);
    m_parts.push_back(&m_leftFoot);
    m_parts.push_back(&m_rightFoot);
}

void Human::addToScene(Scene *scene, glm::vec3 position)
{
    scene->addModel(&m_torso, position + glm::vec3(0.0f, 6.0f, 0.0f));
    scene->addModel(&m_leftUpperArm, position + glm::vec3(-1.0f, 7.0f, 0.0f));
    scene->addModel(&m_rightUpperArm, position + glm::vec3(1.0f, 7.0f, 0.0f));
    scene->addModel(&m_leftLowerArm, position + glm::vec3(-1.0f, 5.0f, 0.0f));
    scene->addModel(&m_rightLowerArm, position + glm::vec3(1.0f, 5.0f, 0.0f));
    scene->addModel(&m_leftUpperLeg, position + glm::vec3(-0.45f, 3.0f, 0.0f));
    scene->addModel(&m_rightUpperLeg, position + glm::vec3(0.45f, 3.0f, 0.0f));
    scene->addModel(&m_leftLowerLeg, position + glm::vec3(-0.45f, 1.0f, 0.0f));
    scene->addModel(&m_rightLowerLeg, position + glm::vec3(0.45f, 1.0f, 0.0f));
    scene->addModel(&m_leftFoot, position + glm::vec3(-0.45f, -0.1f, 0.35f));
    scene->addModel(&m_rightFoot, position + glm::vec3(0.45f, -0.1f, 0.35f));
    
    // fix upper body for now
    m_leftShoulderID = dJointCreateFixed(scene->worldID(), 0);
    m_rightShoulderID = dJointCreateFixed(scene->worldID(), 0);
    m_leftElbowID = dJointCreateFixed(scene->worldID(), 0);
    m_rightElbowID = dJointCreateFixed(scene->worldID(), 0);
    //m_leftShoulderID = dJointCreateHinge(scene->worldID(), 0);
    //m_rightShoulderID = dJointCreateHinge(scene->worldID(), 0);
    //m_leftElbowID = dJointCreateHinge(scene->worldID(), 0);
    //m_rightElbowID = dJointCreateHinge(scene->worldID(), 0);
    m_leftAnkleID = dJointCreateHinge(scene->worldID(), 0);
    m_rightAnkleID = dJointCreateHinge(scene->worldID(), 0);
    m_leftFemoralID = dJointCreateHinge(scene->worldID(), 0);
    m_rightFemoralID = dJointCreateHinge(scene->worldID(), 0);
    m_leftKneeID = dJointCreateHinge(scene->worldID(), 0);
    m_rightKneeID = dJointCreateHinge(scene->worldID(), 0);
    dJointAttach(m_leftShoulderID, m_torso.bodyID(), m_leftUpperArm.bodyID());
    dJointAttach(m_rightShoulderID, m_torso.bodyID(), m_rightUpperArm.bodyID());
    dJointAttach(m_leftElbowID, m_leftUpperArm.bodyID(), m_leftLowerArm.bodyID());
    dJointAttach(m_rightElbowID, m_rightUpperArm.bodyID(), m_rightLowerArm.bodyID());
    dJointAttach(m_leftAnkleID, m_leftLowerLeg.bodyID(), m_leftFoot.bodyID());
    dJointAttach(m_rightAnkleID, m_rightLowerLeg.bodyID(), m_rightFoot.bodyID());
    dJointAttach(m_leftFemoralID, m_torso.bodyID(), m_leftUpperLeg.bodyID());
    dJointAttach(m_rightFemoralID, m_torso.bodyID(), m_rightUpperLeg.bodyID());
    dJointAttach(m_leftKneeID, m_leftUpperLeg.bodyID(), m_leftLowerLeg.bodyID());
    dJointAttach(m_rightKneeID, m_rightUpperLeg.bodyID(), m_rightLowerLeg.bodyID());

    //dJointSetHingeAnchor (m_leftShoulderID,     position[0] - 1.0f,     position[1] + 7.2f, position[2] + 0.0f);
    //dJointSetHingeAnchor (m_rightShoulderID,    position[0] + 1.0f,     position[1] + 7.2f, position[2] + 0.0f);
    //dJointSetHingeAnchor (m_leftElbowID,        position[0] - 1.0f,     position[1] + 6.0f, position[2] + 0.0f);
    //dJointSetHingeAnchor (m_rightElbowID,       position[0] + 1.0f,     position[1] + 6.0f, position[2] + 0.0f);
    dJointSetHingeAnchor (m_leftAnkleID,        position[0] - 0.45f,    position[1] + 0.0f, position[2] + 0.0f);
    dJointSetHingeAnchor (m_rightAnkleID,       position[0] + 0.45f,    position[1] + 0.0f, position[2] + 0.0f);
    dJointSetHingeAnchor (m_leftFemoralID,      position[0] - 0.45f,    position[1] + 4.0f, position[2] + 0.0f);
    dJointSetHingeAnchor (m_rightFemoralID,     position[0] + 0.45f,    position[1] + 4.0f, position[2] + 0.0f);
    dJointSetHingeAnchor (m_leftKneeID,         position[0] - 0.45f,    position[1] + 2.0f, position[2] + 0.0f);
    dJointSetHingeAnchor (m_rightKneeID,        position[0] + 0.45f,    position[1] + 2.0f, position[2] + 0.0f);
    //dJointSetHingeAxis (m_leftShoulderID, 1.0f, 0.0f, 0.0f);
    //dJointSetHingeAxis (m_rightShoulderID, 1.0f, 0.0f, 0.0f);
    //dJointSetHingeAxis (m_leftElbowID, 1.0f, 0.0f, 0.0f);
    //dJointSetHingeAxis (m_rightElbowID, 1.0f, 0.0f, 0.0f);
    dJointSetHingeAxis (m_leftAnkleID, 1.0f, 0.0f, 0.0f);
    dJointSetHingeAxis (m_rightAnkleID, 1.0f, 0.0f, 0.0f);
    dJointSetHingeAxis (m_leftFemoralID, 1.0f, 0.0f, 0.0f);
    dJointSetHingeAxis (m_rightFemoralID, 1.0f, 0.0f, 0.0f);
    dJointSetHingeAxis (m_leftFemoralID, 1.0f, 0.0f, 0.0f);
    dJointSetHingeAxis (m_rightFemoralID, 1.0f, 0.0f, 0.0f);
    
    dJointSetHingeParam (m_leftAnkleID, dParamLoStop, -0.5);
    dJointSetHingeParam (m_rightAnkleID, dParamLoStop, -0.5);
    dJointSetHingeParam (m_leftAnkleID, dParamHiStop, 0.5);
    dJointSetHingeParam (m_rightAnkleID, dParamHiStop, 0.5);
    
    dJointSetHingeParam (m_leftFemoralID, dParamLoStop, 0);
    dJointSetHingeParam (m_rightFemoralID, dParamLoStop, 0);
    dJointSetHingeParam (m_leftFemoralID, dParamHiStop, 3);
    dJointSetHingeParam (m_rightFemoralID, dParamHiStop, 3);
    
    
    dJointSetHingeParam (m_leftKneeID, dParamHiStop, 0);
    dJointSetHingeParam (m_rightKneeID, dParamHiStop, 0);
    
    
    dJointSetFixed(m_leftShoulderID);
    dJointSetFixed(m_rightShoulderID);
    dJointSetFixed(m_leftElbowID);
    dJointSetFixed(m_rightElbowID);
}


void Human::move(GLFWwindow *window)
{
    dReal torque = 50.0f;
    
    // left femoral pos
    if (glfwGetKey( window, GLFW_KEY_1 ) == GLFW_PRESS){
        dJointAddHingeTorque (m_leftFemoralID, torque);
    }
    
    // left femoral neg
    if (glfwGetKey( window, GLFW_KEY_Q ) == GLFW_PRESS){
        dJointAddHingeTorque (m_leftFemoralID, -torque);
    }
    
    // right femoral pos
    if (glfwGetKey( window, GLFW_KEY_2 ) == GLFW_PRESS){
        dJointAddHingeTorque (m_rightFemoralID, torque);
    }
    
    // right femoral neg
    if (glfwGetKey( window, GLFW_KEY_W ) == GLFW_PRESS){
        dJointAddHingeTorque (m_rightFemoralID, -torque);
    }
    
    // left knee pos
    if (glfwGetKey( window, GLFW_KEY_A ) == GLFW_PRESS){
        dJointAddHingeTorque (m_leftKneeID, torque);
    }
    
    // left knee neg
    if (glfwGetKey( window, GLFW_KEY_Z ) == GLFW_PRESS){
        dJointAddHingeTorque (m_leftKneeID, -torque);
    }
    
    // right knee pos
    if (glfwGetKey( window, GLFW_KEY_S ) == GLFW_PRESS){
        dJointAddHingeTorque (m_rightKneeID, torque);
    }
    
    // right knee neg
    if (glfwGetKey( window, GLFW_KEY_X ) == GLFW_PRESS){
        dJointAddHingeTorque (m_rightKneeID, -torque);
    }
    
    // get center of mass
    if (glfwGetKey( window, GLFW_KEY_SPACE ) == GLFW_PRESS){
        glm::vec3 com = centerOfMass();
        printf("center of mass: (%f, %f, %f)\n", com[0], com[1], com[2]);
    }
    
}




