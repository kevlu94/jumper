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
    m_spaceID = dHashSpaceCreate(0);
    m_contactGroupID = dJointGroupCreate(0);
}

Scene::~Scene()
{
    while (!m_models.empty())
        m_models.pop_back();
    dWorldDestroy(m_worldID);
    dSpaceDestroy(m_spaceID);
    dJointGroupEmpty(m_contactGroupID);
    dCloseODE();
}

void Scene::addModel(Model *model, glm::vec3 position)
{
    m_models.push_back(model);
    model->addToScene(this, position);
}

void Scene::addCreature(Creature *creature, glm::vec3 position)
{
    creature->addToScene(this, position);
    m_creature = creature;
}

void Scene::moveModel(Model *model)
{
    dReal force = 1000.0f;
    
    // lift
    if (glfwGetKey( m_window, GLFW_KEY_SPACE ) == GLFW_PRESS){
        dBodyAddForce(model->bodyID(), 0.0f, force, 0.0f);
    }
    
    // dunk
    if (glfwGetKey( m_window, GLFW_KEY_E ) == GLFW_PRESS){
        dBodyAddForce(model->bodyID(), 0.0f, -force, 0.0f);
    }
    
    // push
    if (glfwGetKey( m_window, GLFW_KEY_W ) == GLFW_PRESS){
        dBodyAddForce(model->bodyID(), 0.0f, 0.0f, -force);
    }
    
    // pull
    if (glfwGetKey( m_window, GLFW_KEY_S ) == GLFW_PRESS){
        dBodyAddForce(model->bodyID(), 0.0f, 0.0f, force);
    }
    
    // left
    if (glfwGetKey( m_window, GLFW_KEY_A ) == GLFW_PRESS){
        dBodyAddForce(model->bodyID(), -force, 0.0f, 0.0f);
    }
    
    // right
    if (glfwGetKey( m_window, GLFW_KEY_D ) == GLFW_PRESS){
        dBodyAddForce(model->bodyID(), force, 0.0f, 0.0f);
    }
    
    
}


void Scene::nearCallback (dGeomID o1, dGeomID o2)
{
    dBodyID b1 = dGeomGetBody(o1);
    dBodyID b2 = dGeomGetBody(o2);
    dContact contact;
    contact.surface.mode = dContactBounce | dContactSoftCFM;
    // friction parameter
    contact.surface.mu = 1000;
    // bounce is the amount of "bouncyness".
    contact.surface.bounce = 0.3;
    // bounce_vel is the minimum incoming velocity to cause a bounce
    contact.surface.bounce_vel = 0.1;
    // constraint force mixing parameter
    contact.surface.soft_cfm = 0.001;
    if (dCollide (o1,o2,1,&contact.geom,sizeof(dContact)))
    {
        dJointID c = dJointCreateContact (m_worldID, m_contactGroupID, &contact);
        dJointAttach (c,b1,b2);
    }
}

void passthroughCB(void *data, dGeomID o1, dGeomID o2)
{
    ((Scene*) data)->nearCallback(o1, o2);
    
}

double elapsedTime()
{
    static double prevTime = 0.0f;
    if (prevTime == 0.0f)
        prevTime = glfwGetTime();
    double curTime = glfwGetTime();
    double ret = curTime - prevTime;
    prevTime = curTime;
    return ret;
}

void Scene::update()
{
    //moveModel(m_models[0]);
    
    double dt = 0.0025f;
    double rendertime = elapsedTime();
    int steps = rendertime / dt + 1;
    for (int i = 0; i < steps; i++)
    {
        m_creature->move(m_window);
        
        // resolve collisions
        dSpaceCollide (m_spaceID, this, passthroughCB);
        // update the world by the calculated time step
        dWorldStep(m_worldID, dt);
        // reset contact joints
        dJointGroupEmpty(m_contactGroupID);
    }
    double updatetime = elapsedTime();
    double wait = steps * dt - updatetime - rendertime;
    if (wait < 0) wait = 0;
    usleep(wait * 1000000);
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