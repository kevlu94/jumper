#include "scene.hpp"


Scene::Scene(Camera *camera, GLuint program)
{
    m_camera = camera;
    m_window = camera->window();
    m_program = program;
    
    // default projection matrix
    m_projection_matrix = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
    
    // Initialize world for ODE
    dInitODE();
    m_worldID = dWorldCreate();
    dWorldSetGravity(m_worldID, 0.0f, -9.8f, 0.0f);
}

Scene::~Scene()
{
    while (!m_models.empty())
    {
        m_models.back()->removeBodyFromWorld();
        m_models.pop_back();
    }
    dWorldDestroy(m_worldID);
    dCloseODE();
}

void Scene::addModel(Model *model)
{
    m_models.push_back(model);
    model->addBodyToWorld(m_worldID);
}

void Scene::moveModel(Model *model)
{
    // push upward
    if (glfwGetKey( m_window, GLFW_KEY_W ) == GLFW_PRESS){
        dBodyAddForce(model->bodyID(), 0.0f, 20.0f, 0.0f);
    }
    
}


 
void Scene::update()
{
    for (unsigned long i = 0; i < m_models.size(); i++)
        moveModel(m_models[i]);
    
    static double prevTime = 0.0f;
    if (prevTime == 0.0f) // very first time instant
    {
        prevTime = glfwGetTime();
        return;
    }
    
    double curTime = glfwGetTime();
    double dt = curTime - prevTime;

    // update the world by the calculated time step
    dWorldStep(m_worldID, dt);
    
    prevTime = curTime;
}

void Scene::draw()
{
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    Model *model;
    unsigned long numModels = m_models.size();
    for (unsigned long i = 0; i < numModels; i++)
    {
        model = m_models[i];
        glBindBuffer(GL_ARRAY_BUFFER, model->positionVBO());
        glUniformMatrix4fv(glGetUniformLocation(m_program, "MVP"), 1, GL_FALSE, &(MVP(model))[0][0]);
        model->setAttribute(m_program, "vertexPosition", 3, model->positionVBO());
        
        if (model->colored())
        {
            model->setAttribute(m_program, "vertexColor", 3, model->colorVBO());
        }
        
        if (model->textured())
        {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, model->texture());
            glUniform1i(glGetUniformLocation(m_program, "textureSampler"), 0);
            model->setAttribute(m_program, "vertexTexture", 2, model->textureVBO());
        }
        
        
        glDrawArrays(GL_TRIANGLES, 0, (int) model->numVertices());
    }
    
    glDisableVertexAttribArray(glGetAttribLocation(m_program, "vertexPosition"));
    glDisableVertexAttribArray(glGetAttribLocation(m_program, "vertexColor"));
    glDisableVertexAttribArray(glGetAttribLocation(m_program, "vertexTexture"));
    
    // Swap buffers
    glfwSwapBuffers(m_window);
    glfwPollEvents();
}


glm::mat4 Scene::view() const
{
    return glm::lookAt(m_camera->position(),
                       m_camera->position() + m_camera->direction(),
                       glm::vec3(0,1,0));
}