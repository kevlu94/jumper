#ifndef SCENE_HPP
#define SCENE_HPP



#include "globals.hpp"
#include "camera.hpp"
#include "model.hpp"



class Scene
{
public:
    Scene(); //added to get a pointer to scene object
    Scene(Camera *camera, GLuint program);
    ~Scene();
    
    void setScene(Camera *camera, GLuint program); //initializer same as Scene
    void addModel(Model *model, glm::vec3 position);
    void addCreature(Creature *creature, glm::vec3 position);
    void update(dReal torqueKnee,dReal torqueHip);
    void draw();
    glm::mat4 MVP(Model *model) const { return projection() * view() * model->model(); }
    
    glm::mat4 view() const;
    glm::mat4 projection() const { return m_projection_matrix; }
    dWorldID worldID() const { return m_worldID; }
    dSpaceID spaceID() const { return m_spaceID; }
    
    void nearCallback(dGeomID o1, dGeomID o2);
    
private:
    
    // private functions
    void moveModel(Model *model);
    
    
    // private variables
    GLuint m_program;
    GLFWwindow* m_window;
    glm::mat4 m_projection_matrix;
    Camera *m_camera;
    std::vector<Model*> m_models;
    Creature *m_creature;
    
    dWorldID m_worldID;
    dSpaceID m_spaceID;
    dJointGroupID m_contactGroupID;
};




#endif