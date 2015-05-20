#include "objects.hpp"
#include "scene.hpp"
#include "shapes.hpp"

extern bool render;

void ColoredBox::setColoredBox(dReal density, glm::vec3 color, glm::vec3 size){
    if (render)
    {
        std::vector<glm::vec3> positionBuffer = this->cube(glm::vec3(0.0f), size);
        std::vector<glm::vec3> colorBuffer;
        m_numVertices = positionBuffer.size();
        for (unsigned long i = 0; i < m_numVertices; i++)
            colorBuffer.push_back(color);
        glGenBuffers(1, &m_positionVBO);
        glGenBuffers(1, &m_colorVBO);
        glBindBuffer(GL_ARRAY_BUFFER, m_positionVBO);
        glBufferData(GL_ARRAY_BUFFER,
                     positionBuffer.size() * sizeof(glm::vec3),
                     &positionBuffer[0],
                     GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, m_colorVBO);
        glBufferData(GL_ARRAY_BUFFER,
                     colorBuffer.size() * sizeof(glm::vec3),
                     &colorBuffer[0],
                     GL_STATIC_DRAW);
    }
    m_size = size;
    m_density = density;
}


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

/******************************************************************************/

void ColoredImmovableBox::addToScene(Scene *scene, glm::vec3 position)
{
    m_geomID = dCreateBox(scene->spaceID(), 2 * m_size[0], 2 * m_size[1], 2 * m_size[2]);
    dGeomSetBody(m_geomID, m_bodyID);
    dGeomSetPosition(m_geomID, position[0], position[1], position[2]);
}

void ColoredImmovableBox::setColoredImmovableBox(glm::vec3 color, glm::vec3 size){
    if (render)
    {
        std::vector<glm::vec3> positionBuffer = this->cube(glm::vec3(0.0f), size);
        std::vector<glm::vec3> colorBuffer;
        m_numVertices = positionBuffer.size();
        for (unsigned long i = 0; i < m_numVertices; i++)
            colorBuffer.push_back(color);
        glGenBuffers(1, &m_positionVBO);
        glGenBuffers(1, &m_colorVBO);
        glBindBuffer(GL_ARRAY_BUFFER, m_positionVBO);
        glBufferData(GL_ARRAY_BUFFER,
                     positionBuffer.size() * sizeof(glm::vec3),
                     &positionBuffer[0],
                     GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, m_colorVBO);
        glBufferData(GL_ARRAY_BUFFER,
                     colorBuffer.size() * sizeof(glm::vec3),
                     &colorBuffer[0],
                     GL_STATIC_DRAW);
    }

    m_size = size;
}
/******************************************************************************/

Human::Human(){

}

Human::Human(glm::vec3 size): Creature(size),
m_head(2.0f, glm::vec3(0.3f, 0.3f, 0.3f), glm::vec3(0.25f, 0.5f, 0.25f)),
m_torso(1.0f, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.2f, 1.6f, 0.2f)),
m_leftUpperArm(1.0f, glm::vec3(0.3f, 0.3f, 0.0f), glm::vec3(0.1f, 0.8f, 0.1f)),
m_rightUpperArm(1.0f, glm::vec3(0.0f, 0.3f, 0.3f), glm::vec3(0.1f, 0.8f, 0.1f)),
m_leftLowerArm(1.0f, glm::vec3(0.6f, 0.3f, 0.0f), glm::vec3(0.1f, 0.8f, 0.1f)),
m_rightLowerArm(1.0f, glm::vec3(0.0f, 0.3f, 0.6f), glm::vec3(0.1f, 0.8f, 0.1f)),
m_leftUpperLeg(1.0f, glm::vec3(0.3f, 0.0f, 0.0f), glm::vec3(0.1f, 0.7f, 0.1f)),
m_rightUpperLeg(1.0f, glm::vec3(0.0f, 0.0f, 0.3f), glm::vec3(0.1f, 0.7f, 0.1f)),
m_leftLowerLeg(1.0f, glm::vec3(0.6f, 0.0f, 0.0f), glm::vec3(0.1f, 0.7f, 0.1f)),
m_rightLowerLeg(1.0f, glm::vec3(0.0f, 0.0f, 0.6f), glm::vec3(0.1f, 0.7f, 0.1f)),
m_leftFoot(1.0f, glm::vec3(0.9f, 0.0f, 0.0f), glm::vec3(0.3f, 0.1f, 0.7f)),
m_rightFoot(1.0f, glm::vec3(0.0f, 0.0f, 0.9f), glm::vec3(0.3f, 0.1f, 0.7f))
{
    m_parts.push_back(&m_head);
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

void Human::setHuman(glm::vec3 size)
{
    
    m_size=size; //Creature(size);
    
    m_head.setColoredBox(2.0f, glm::vec3(0.3f, 0.3f, 0.3f), glm::vec3(0.25f, 0.5f, 0.25f));
    m_torso.setColoredBox(1.0f, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.2f, 1.6f, 0.2f));
    m_leftUpperArm.setColoredBox(1.0f, glm::vec3(0.3f, 0.3f, 0.0f), glm::vec3(0.1f, 0.8f, 0.1f));
    m_rightUpperArm.setColoredBox(1.0f, glm::vec3(0.0f, 0.3f, 0.3f), glm::vec3(0.1f, 0.8f, 0.1f));
    m_leftLowerArm.setColoredBox(1.0f, glm::vec3(0.6f, 0.3f, 0.0f), glm::vec3(0.1f, 0.8f, 0.1f));
    m_rightLowerArm.setColoredBox(1.0f, glm::vec3(0.0f, 0.3f, 0.6f), glm::vec3(0.1f, 0.8f, 0.1f));
    m_leftUpperLeg.setColoredBox(1.0f, glm::vec3(0.3f, 0.0f, 0.0f), glm::vec3(0.1f, 0.7f, 0.1f));
    m_rightUpperLeg.setColoredBox(1.0f, glm::vec3(0.0f, 0.0f, 0.3f), glm::vec3(0.1f, 0.7f, 0.1f));
    m_leftLowerLeg.setColoredBox(1.0f, glm::vec3(0.6f, 0.0f, 0.0f), glm::vec3(0.1f, 0.7f, 0.1f));
    m_rightLowerLeg.setColoredBox(1.0f, glm::vec3(0.0f, 0.0f, 0.6f), glm::vec3(0.1f, 0.7f, 0.1f));
    m_leftFoot.setColoredBox(1.0f, glm::vec3(0.9f, 0.0f, 0.0f), glm::vec3(0.3f, 0.1f, 0.7f));
    m_rightFoot.setColoredBox(1.0f, glm::vec3(0.0f, 0.0f, 0.9f), glm::vec3(0.3f, 0.1f, 0.7f));
    
    // parts of the creature
    m_parts.push_back(&m_head);
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
    scene->addModel(&m_head, position + glm::vec3(0.0f, 7.7f, -0.1f));
    scene->addModel(&m_torso, position + glm::vec3(0.0f, 5.7f, 0.0f));
    scene->addModel(&m_leftUpperArm, position + glm::vec3(-1.0f, 6.8f, 0.0f));
    scene->addModel(&m_rightUpperArm, position + glm::vec3(1.0f, 6.8f, 0.0f));
    scene->addModel(&m_leftLowerArm, position + glm::vec3(-1.0f, 4.9f, 0.0f));
    scene->addModel(&m_rightLowerArm, position + glm::vec3(1.0f, 4.9f, 0.0f));
    scene->addModel(&m_leftUpperLeg, position + glm::vec3(-0.45f, 3.0f, 0.0f));
    scene->addModel(&m_rightUpperLeg, position + glm::vec3(0.45f, 3.0f, 0.0f));
    scene->addModel(&m_leftLowerLeg, position + glm::vec3(-0.45f, 1.0f, 0.0f));
    scene->addModel(&m_rightLowerLeg, position + glm::vec3(0.45f, 1.0f, 0.0f));
    scene->addModel(&m_leftFoot, position + glm::vec3(-0.45f, 0.1f, -0.35f));
    scene->addModel(&m_rightFoot, position + glm::vec3(0.45f, 0.1f, -0.35f));
    
    scene->setOwner(m_head.geomID(), this);
    scene->setOwner(m_torso.geomID(), this);
    scene->setOwner(m_leftUpperArm.geomID(), this);
    scene->setOwner(m_rightUpperArm.geomID(), this);
    scene->setOwner(m_leftLowerArm.geomID(), this);
    scene->setOwner(m_rightLowerArm.geomID(), this);
    scene->setOwner(m_leftUpperLeg.geomID(), this);
    scene->setOwner(m_rightUpperLeg.geomID(), this);
    scene->setOwner(m_leftLowerLeg.geomID(), this);
    scene->setOwner(m_rightLowerLeg.geomID(), this);
    scene->setOwner(m_leftFoot.geomID(), this);
    scene->setOwner(m_rightFoot.geomID(), this);



    // fix upper body for now
    m_neckID = dJointCreateFixed(scene->worldID(), 0);
    //m_leftShoulderID = dJointCreateFixed(scene->worldID(), 0);
    //m_rightShoulderID = dJointCreateFixed(scene->worldID(), 0);
    m_leftElbowID = dJointCreateFixed(scene->worldID(), 0);
    m_rightElbowID = dJointCreateFixed(scene->worldID(), 0);
    m_leftShoulderID = dJointCreateHinge(scene->worldID(), 0);
    m_rightShoulderID = dJointCreateHinge(scene->worldID(), 0);
    //m_leftElbowID = dJointCreateHinge(scene->worldID(), 0);
    //m_rightElbowID = dJointCreateHinge(scene->worldID(), 0);
    m_leftAnkleID = dJointCreateHinge(scene->worldID(), 0);
    m_rightAnkleID = dJointCreateHinge(scene->worldID(), 0);
    m_leftFemoralID = dJointCreateHinge(scene->worldID(), 0);
    m_rightFemoralID = dJointCreateHinge(scene->worldID(), 0);
    m_leftKneeID = dJointCreateHinge(scene->worldID(), 0);
    m_rightKneeID = dJointCreateHinge(scene->worldID(), 0);
    dJointAttach(m_neckID, m_head.bodyID(), m_torso.bodyID());
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

    dJointSetHingeAnchor (m_leftShoulderID,     position[0] - 1.0f,     position[1] + 7.5f, position[2] + 0.0f);
    dJointSetHingeAnchor (m_rightShoulderID,    position[0] + 1.0f,     position[1] + 7.5f, position[2] + 0.0f);
    //dJointSetHingeAnchor (m_leftElbowID,        position[0] - 1.0f,     position[1] + 6.0f, position[2] + 0.0f);
    //dJointSetHingeAnchor (m_rightElbowID,       position[0] + 1.0f,     position[1] + 6.0f, position[2] + 0.0f);
    dJointSetHingeAnchor (m_leftAnkleID,        position[0] - 0.45f,    position[1] + 0.0f, position[2] + 0.0f);
    dJointSetHingeAnchor (m_rightAnkleID,       position[0] + 0.45f,    position[1] + 0.0f, position[2] + 0.0f);
    dJointSetHingeAnchor (m_leftFemoralID,      position[0] - 0.45f,    position[1] + 4.0f, position[2] + 0.0f);
    dJointSetHingeAnchor (m_rightFemoralID,     position[0] + 0.45f,    position[1] + 4.0f, position[2] + 0.0f);
    dJointSetHingeAnchor (m_leftKneeID,         position[0] - 0.45f,    position[1] + 2.0f, position[2] + 0.0f);
    dJointSetHingeAnchor (m_rightKneeID,        position[0] + 0.45f,    position[1] + 2.0f, position[2] + 0.0f);
    dJointSetHingeAxis (m_leftShoulderID, 1.0f, 0.0f, 0.0f);
    dJointSetHingeAxis (m_rightShoulderID, 1.0f, 0.0f, 0.0f);
    //dJointSetHingeAxis (m_leftElbowID, 1.0f, 0.0f, 0.0f);
    //dJointSetHingeAxis (m_rightElbowID, 1.0f, 0.0f, 0.0f);
    dJointSetHingeAxis (m_leftAnkleID, 1.0f, 0.0f, 0.0f);
    dJointSetHingeAxis (m_rightAnkleID, 1.0f, 0.0f, 0.0f);
    dJointSetHingeAxis (m_leftFemoralID, 1.0f, 0.0f, 0.0f);
    dJointSetHingeAxis (m_rightFemoralID, 1.0f, 0.0f, 0.0f);
    dJointSetHingeAxis (m_leftFemoralID, 1.0f, 0.0f, 0.0f);
    dJointSetHingeAxis (m_rightFemoralID, 1.0f, 0.0f, 0.0f);
    
    dJointSetHingeParam(m_leftShoulderID, dParamHiStop, 0.5);
    dJointSetHingeParam(m_rightShoulderID, dParamHiStop, 0.5);
    dJointSetHingeParam(m_leftShoulderID, dParamLoStop, -3);
    dJointSetHingeParam(m_rightShoulderID, dParamLoStop, -3);
    
    
    dJointSetHingeParam (m_leftAnkleID, dParamLoStop, -0.5);
    dJointSetHingeParam (m_rightAnkleID, dParamLoStop, -0.5);
    dJointSetHingeParam (m_leftAnkleID, dParamHiStop, 0.5);
    dJointSetHingeParam (m_rightAnkleID, dParamHiStop, 0.5);
    
    dJointSetHingeParam (m_leftFemoralID, dParamLoStop, -2.5);
    dJointSetHingeParam (m_rightFemoralID, dParamLoStop, -2.5);
    dJointSetHingeParam (m_leftFemoralID, dParamHiStop, 0.1);
    dJointSetHingeParam (m_rightFemoralID, dParamHiStop, 0.1);
    
    
    dJointSetHingeParam (m_leftKneeID, dParamLoStop, -0.1);
    dJointSetHingeParam (m_rightKneeID, dParamLoStop, -0.1);
    dJointSetHingeParam (m_leftKneeID, dParamHiStop, 3);
    dJointSetHingeParam (m_rightKneeID, dParamHiStop, 3);
    
    
    // for debugging
    /*
     dJointSetHingeParam (m_leftAnkleID, dParamLoStop, -0.01);
     dJointSetHingeParam (m_rightAnkleID, dParamLoStop, -0.01);
     dJointSetHingeParam (m_leftAnkleID, dParamHiStop, 0.01);
     dJointSetHingeParam (m_rightAnkleID, dParamHiStop, 0.01);
     dJointSetHingeParam (m_leftFemoralID, dParamLoStop, -0.01);
     dJointSetHingeParam (m_rightFemoralID, dParamLoStop, -0.01);
     dJointSetHingeParam (m_leftKneeID, dParamHiStop, 0.01);
     dJointSetHingeParam (m_rightKneeID, dParamHiStop, 0.01);
     */
    
    dJointSetFixed(m_neckID);
    //dJointSetFixed(m_leftShoulderID);
    //dJointSetFixed(m_rightShoulderID);
    dJointSetFixed(m_leftElbowID);
    dJointSetFixed(m_rightElbowID);


    scene->addGeomToA(m_head.geomID());
    scene->addGeomToA(m_torso.geomID());
    scene->addGeomToA(m_leftUpperArm.geomID());
    scene->addGeomToA(m_rightUpperArm.geomID());
    scene->addGeomToA(m_leftLowerArm.geomID());
    scene->addGeomToA(m_rightLowerArm.geomID());
    scene->addGeomToA(m_leftUpperLeg.geomID());
    scene->addGeomToA(m_rightUpperLeg.geomID());
    scene->addGeomToA(m_leftLowerLeg.geomID());
    scene->addGeomToA(m_rightLowerLeg.geomID());
}


void Human::move(dReal torqueKnee, dReal torqueHip)
{
    //dReal torque = 50.0f;
    

    
    dJointAddHingeTorque (m_leftKneeID, torqueKnee);
    dJointAddHingeTorque (m_rightKneeID, torqueKnee);
    dJointAddHingeTorque (m_leftFemoralID, torqueHip);
    dJointAddHingeTorque (m_rightFemoralID, torqueHip);
    
    /*
    
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
    //if (glfwGetKey( window, GLFW_KEY_SPACE ) == GLFW_PRESS){
    //    glm::vec3 com = centerOfMass();
    //    printf("center of mass: (%f, %f, %f)\n", com[0], com[1], com[2]);
    //}
    
    // check balance
    if (glfwGetKey( window, GLFW_KEY_SPACE ) == GLFW_PRESS){
        printf("feetdown? %s\n", feetDown() ? "yes" : "no");
        printf("balanced? %s\n", balanced() ? "yes" : "no");
        
    }
    
    // lift
    if (glfwGetKey( window, GLFW_KEY_C ) == GLFW_PRESS){
        dBodyAddForce(m_torso.bodyID(), 0.0f, 50.0f, 0.0f);
    }
    */
}

void Human::getJointAngles(dReal *cur_knee_angle, dReal *cur_knee_velocity, dReal *cur_hip_angle, dReal *cur_hip_velocity){
    *cur_knee_angle=dJointGetHingeAngle(m_leftKneeID);
    *cur_knee_velocity=dJointGetHingeAngleRate(m_leftKneeID);
    *cur_hip_angle=dJointGetHingeAngle(m_leftFemoralID);
    *cur_hip_velocity=dJointGetHingeAngleRate(m_leftFemoralID);
}

void Human::takeInput()
{
    int lfem, rfem, lknee, rknee;
    
    std::cin >> lfem >> rfem >> lknee >> rknee;
    
    dJointAddHingeTorque (m_leftFemoralID, (dReal) lfem);
    dJointAddHingeTorque (m_rightFemoralID, (dReal) rfem);
    dJointAddHingeTorque (m_leftKneeID, (dReal) lknee);
    dJointAddHingeTorque (m_rightKneeID, (dReal) rknee);
}

void Human::printOutput()
{
    printf("%f %f %f %f %f %s\n", dJointGetHingeAngle(m_leftFemoralID), dJointGetHingeAngle(m_rightFemoralID), dJointGetHingeAngle(m_leftKneeID), dJointGetHingeAngle(m_rightKneeID), centerOfMass()[1], (balanced() ? "balanced" : "OFF BALANCE!"));
}

std::vector<glm::vec3> Human::pivots() const
{
    std::vector<glm::vec3> ret;
    glm::vec3 footSize = m_leftFoot.size();
    
    // front left corner
    ret.push_back(glm::vec3(m_leftFoot.model() *
                            glm::vec4(-footSize[0], -footSize[1], -footSize[2], 1.0f)));
    
    // back left corner
    ret.push_back(glm::vec3(m_leftFoot.model() *
                            glm::vec4(-footSize[0], -footSize[1], footSize[2], 1.0f)));
    
    // back right corner
    ret.push_back(glm::vec3(m_rightFoot.model() *
                            glm::vec4(footSize[0], -footSize[1], footSize[2], 1.0f)));
    
    // front right corner
    ret.push_back(glm::vec3(m_rightFoot.model() *
                            glm::vec4(footSize[0], -footSize[1], -footSize[2], 1.0f)));
    
    return ret;
}

glm::vec3 normal(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3)
{
    glm::vec3 v1 = p2 - p1;
    glm::vec3 v2 = p3 - p2;
    return glm::cross(v1, v2);
}

bool Human::feetDown() const
{
    std::vector<glm::vec3> p = pivots();
    unsigned long psize = p.size();
    for (unsigned long i = 0; i < psize; i++)
    {
        if (normal(p[i], p[(i+1) % psize], p[(i+2) % psize])[1] < 0)
            return false;
    }
    return true;
}

bool Human::balanced() const
{
    if (!feetDown())
        return false;
    
    glm::vec3 com = centerOfMass();
    com[1] = 0.0f;
    std::vector<glm::vec3> p = pivots();
    
    unsigned long psize = p.size();
    
    for (unsigned long i = 0; i < psize; i++)
        p[i][1] = 0.0f;
    
    for (unsigned long i = 0; i < psize; i++)
    {
        if (normal(p[i], p[(i+1) % psize], com)[1] < 0)
            return false;
    }
    return true;
}
