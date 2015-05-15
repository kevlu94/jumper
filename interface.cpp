#include "interface.hpp"

#include "scene.hpp"
#include "common/shader.hpp"
#include "globals.hpp"
#include "model.hpp"
#include "shapes.hpp"
#include "objects.hpp"

using namespace glm;

GLFWwindow* window;
//GLuint program;

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

void initilizeSimulator()
{
    
    // prepare GL environment
    initializeGL();
    //if (initializeGL() == -1)
    //    return NULL;
    
    
    printf("");
    
    // prepare vertex/fragment shader programs
    GLuint program;
    program = LoadShaders( "shaders/vertexshader", "shaders/fragmentshader" );
    glUseProgram(program);
    
    // initialize camera, scene, and objects to draw
    Camera camera(window, vec3(0,8,20), 0.0f, 0.0f);
    Scene scene(&camera, program);
    
    Human human(glm::vec3(0.0f));
    scene.addCreature(&human, glm::vec3(0.0f, 5.0f, 0.0f));
    
    
    ColoredImmovableBox ground(glm::vec3(0.4f, 0.8f, 0.5f), glm::vec3(100.0f, 10.0f, 100.0f));
    scene.addModel(&ground, glm::vec3(0.0f, -11.0f, 0.0f));
    
    // create vertex array
    //GLuint VertexArrayID;
    //glGenVertexArrays(1, &VertexArrayID);
    //glBindVertexArray(VertexArrayID);
    
    fprintf(stderr, "error code before loop: %x\n", glGetError());

    int error = 0;
    // continuously draw the scene we've created
    while(glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose(window) == 0)
    //
    {
        camera.update();
        scene.update(); //<--------------------
        
        scene.draw(); //<--------------------
        
        if ((error = glGetError()))
        {
            fprintf(stderr, "error: %x\n", error);
            break;
        }
    }
    
    printf("Time to close");
    
    closeSimulator(program);
    
    //return scene;
}

/*

// given a target angle
void runSimulator(Scene scene,double *knee_angle, double *knee_velocity, double *hip_angle, double *hip_velocity) {
    
    double k1=2;
    double k2=0.05;
    
    
    double cur_knee_angle=dJointGetHingeAngle(scene.m_creature->m_leftKneeID);
    //double cur_knee_velocity=dJointGetHingeAngleRate(m_leftKneeID);
    double cur_hip_angle=dJointGetHingeAngle(scene.m_creature->m_leftFemoralID);
    //double cur_hip_velocity=dJointGetHingeAngleRate(m_leftFemoralID);
    
    dReal torqueKnee = k1*(*knee_angle-cur_knee_angle)+k2*(*knee_velocity);
    dReal torqueHip = k1*(*hip_angle-cur_hip_angle)+k2*(*hip_velocity);
    
    // draw the scene
    scene.draw();
    
    // symetric joints
    scene.move(torqueKnee,torqueHip);
    
    // run the simulation for 1 step
    scene.update();
    scene.draw();
    
    // get the output
    *knee_angle=dJointGetHingeAngle(m_leftKneeID);
    *knee_velocity=dJointGetHingeAngleRate(m_leftKneeID);
    *hip_angle=dJointGetHingeAngle(m_leftFemoralID);
    *hip_velocity=dJointGetHingeAngleRate(m_leftFemoralID);
    
}

int checkForFall(void){
    // centerOfMass
    glm::vec3 com = centerOfMass();
    
    return 0;
}
*/

void closeSimulator(GLuint program) {
    // Cleanup shader
    glDeleteProgram(program);
    //glDeleteVertexArrays(1, &VertexArrayID);
    
    // Close OpenGL window and terminate GLFW
    glfwTerminate();
}