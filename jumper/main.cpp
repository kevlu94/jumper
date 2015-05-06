//
//  main.cpp
//  jumper
//
//  Created by Kevin on 5/4/15.
//  Copyright (c) 2015 UCLA. All rights reserved.
//

#include <ode/ode.h>
#include "scene.hpp"
#include "common/shader.hpp"
#include "globals.hpp"
#include "model.hpp"
#include "shapes.hpp"
#include "objects.hpp"

using namespace glm;

GLFWwindow* window;

int initializeGL()
{
    // Initialise GLFW
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        return -1;
    }
    
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    // Open a window and create its OpenGL context
    window = glfwCreateWindow( WINDOW_WIDTH, WINDOW_HEIGHT, "Picking Test", NULL, NULL);
    if( window == NULL ){
        fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
    }
    
    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_FALSE);
    
    // Dark blue background
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    
    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Enable depth buffer for writing
    glDepthMask(GL_TRUE);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);
    // Set range
    glDepthRange(0.0f, 1.0f);
    
    return 0;
}


int main()
{
    // prepare GL environment
    if (initializeGL() == -1)
        return -1;
    
    // prepare vertex/fragment shader programs
    GLuint program;
    program = LoadShaders( "shaders/vertexshader", "shaders/fragmentshader" );
    glUseProgram(program);
    
    // initialize camera, scene, and objects to draw
    Camera camera(window, vec3(0,8,20), 0.0f, 0.0f);
    Scene scene(&camera, program);
    
    
    
    ColoredBox torso(1.0f, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.75f, 1.95f, 0.4f));
    ColoredBox leftUpperArm(1.0f, glm::vec3(0.3f, 0.3f, 0.0f), glm::vec3(0.2f, 0.95f, 0.2f));
    ColoredBox rightUpperArm(1.0f, glm::vec3(0.0f, 0.3f, 0.3f), glm::vec3(0.2f, 0.95f, 0.2f));
    ColoredBox leftLowerArm(1.0f, glm::vec3(0.6f, 0.3f, 0.0f), glm::vec3(0.2f, 0.95f, 0.2f));
    ColoredBox rightLowerArm(1.0f, glm::vec3(0.0f, 0.3f, 0.6f), glm::vec3(0.2f, 0.95f, 0.2f));
    
    ColoredBox leftUpperLeg(1.0f, glm::vec3(0.3f, 0.0f, 0.0f), glm::vec3(0.3f, 0.95f, 0.4f));
    ColoredBox rightUpperLeg(1.0f, glm::vec3(0.0f, 0.0f, 0.3f), glm::vec3(0.3f, 0.95f, 0.4f));
    ColoredBox leftLowerLeg(1.0f, glm::vec3(0.6f, 0.0f, 0.0f), glm::vec3(0.3f, 0.95f, 0.4f));
    ColoredBox rightLowerLeg(1.0f, glm::vec3(0.0f, 0.0f, 0.6f), glm::vec3(0.3f, 0.95f, 0.4f));
    ColoredBox leftFoot(1.0f, glm::vec3(0.9f, 0.0f, 0.0f), glm::vec3(0.3f, 0.1f, 0.8f));
    ColoredBox rightFoot(1.0f, glm::vec3(0.0f, 0.0f, 0.9f), glm::vec3(0.3f, 0.1f, 0.8f));
    
    
    
    scene.addModel(&torso, glm::vec3(0.0f, 6.0f, 0.0f));
    scene.addModel(&leftUpperArm, glm::vec3(-1.0f, 7.0f, 0.0f));
    scene.addModel(&rightUpperArm, glm::vec3(1.0f, 7.0f, 0.0f));
    scene.addModel(&leftLowerArm, glm::vec3(-1.0f, 5.0f, 0.0f));
    scene.addModel(&rightLowerArm, glm::vec3(1.0f, 5.0f, 0.0f));
    
    scene.addModel(&leftUpperLeg, glm::vec3(-0.45f, 3.0f, 0.0f));
    scene.addModel(&rightUpperLeg, glm::vec3(0.45f, 3.0f, 0.0f));
    scene.addModel(&leftLowerLeg, glm::vec3(-0.45f, 1.0f, 0.0f));
    scene.addModel(&rightLowerLeg, glm::vec3(0.45f, 1.0f, 0.0f));
    scene.addModel(&leftFoot, glm::vec3(-0.45f, -0.1f, 0.35f));
    scene.addModel(&rightFoot, glm::vec3(0.45f, -0.1f, 0.35f));
    
    
    dJointID leftShoulderID = dJointCreateHinge(scene.worldID(), 0);
    dJointID rightShoulderID = dJointCreateHinge(scene.worldID(), 0);
    dJointID leftElbowID = dJointCreateHinge(scene.worldID(), 0);
    dJointID rightElbowID = dJointCreateHinge(scene.worldID(), 0);
    
    dJointID leftFemoralID = dJointCreateHinge(scene.worldID(), 0);
    dJointID rightFemoralID = dJointCreateHinge(scene.worldID(), 0);
    dJointID leftKneeID = dJointCreateHinge(scene.worldID(), 0);
    dJointID rightKneeID = dJointCreateHinge(scene.worldID(), 0);
    dJointID leftAnkleID = dJointCreateHinge(scene.worldID(), 0);
    dJointID rightAnkleID = dJointCreateHinge(scene.worldID(), 0);
    
    
    dJointAttach(leftShoulderID, torso.bodyID(), leftUpperArm.bodyID());
    dJointAttach(rightShoulderID, torso.bodyID(), rightUpperArm.bodyID());
    dJointAttach(leftElbowID, leftUpperArm.bodyID(), leftLowerArm.bodyID());
    dJointAttach(rightElbowID, rightUpperArm.bodyID(), rightLowerArm.bodyID());
    
    dJointAttach(leftFemoralID, torso.bodyID(), leftUpperLeg.bodyID());
    dJointAttach(rightFemoralID, torso.bodyID(), rightUpperLeg.bodyID());
    dJointAttach(leftKneeID, leftUpperLeg.bodyID(), leftLowerLeg.bodyID());
    dJointAttach(rightKneeID, rightUpperLeg.bodyID(), rightLowerLeg.bodyID());
    dJointAttach(leftAnkleID, leftLowerLeg.bodyID(), leftFoot.bodyID());
    dJointAttach(rightAnkleID, rightLowerLeg.bodyID(), rightFoot.bodyID());
    
    dJointSetHingeAnchor (leftShoulderID, -1.0f, 7.2f, 0.0f);
    dJointSetHingeAxis (leftShoulderID, 1.0f, 0.0f, 0.0f);
    dJointSetHingeAnchor (rightShoulderID, 1.0f, 7.2f, 0.0f);
    dJointSetHingeAxis (rightShoulderID, 1.0f, 0.0f, 0.0f);
    dJointSetHingeAnchor (leftElbowID, -1.0f, 6.0f, 0.0f);
    dJointSetHingeAxis (leftElbowID, 1.0f, 0.0f, 0.0f);
    dJointSetHingeAnchor (rightElbowID, 1.0f, 6.0f, 0.0f);
    dJointSetHingeAxis (rightElbowID, 1.0f, 0.0f, 0.0f);
    
    dJointSetHingeAnchor (leftFemoralID, -0.45f, 4.0f, 0.0f);
    dJointSetHingeAxis (leftFemoralID, 1.0f, 0.0f, 0.0f);
    dJointSetHingeAnchor (rightFemoralID, 0.45f, 4.0f, 0.0f);
    dJointSetHingeAxis (rightFemoralID, 1.0f, 0.0f, 0.0f);
    dJointSetHingeAnchor (leftKneeID, -0.45f, 2.0f, 0.0f);
    dJointSetHingeAxis (leftFemoralID, 1.0f, 0.0f, 0.0f);
    dJointSetHingeAnchor (rightKneeID, 0.45f, 2.0f, 0.0f);
    dJointSetHingeAxis (rightFemoralID, 1.0f, 0.0f, 0.0f);
    dJointSetHingeAnchor (leftAnkleID, -0.45f, 0.0f, 0.0f);
    dJointSetHingeAxis (leftAnkleID, 1.0f, 0.0f, 0.0f);
    dJointSetHingeAnchor (rightAnkleID, 0.45f, 0.0f, 0.0f);
    dJointSetHingeAxis (rightAnkleID, 1.0f, 0.0f, 0.0f);
    
    
    ColoredImmovableBox ground(glm::vec3(0.4f, 0.8f, 0.5f), glm::vec3(100.0f, 10.0f, 100.0f));
    scene.addModel(&ground, glm::vec3(0.0f, -10.0f, 0.0f));
    
    // create vertex array
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);
    
    fprintf(stderr, "error code before loop: %x\n", glGetError());
    
    int error = 0;
    // continuously draw the scene we've created
    while(glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose(window) == 0)
    {
        camera.update();
        scene.update();
        scene.draw();
        if ((error = glGetError()))
        {
            fprintf(stderr, "error: %x\n", error);
            break;
        }
    }
    
    // Cleanup shader
    glDeleteProgram(program);
    glDeleteVertexArrays(1, &VertexArrayID);
    
    // Close OpenGL window and terminate GLFW
    glfwTerminate();
    
    return 0;
}