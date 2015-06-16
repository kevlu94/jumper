#ifndef SCENE_HPP
#define SCENE_HPP



#include "globals.hpp"
#include "camera.hpp"
#include "model.hpp"

#include <unordered_map>
#include <unordered_set>


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
    void setOwner(dGeomID geom, Creature *creature);
    Creature *owner(dGeomID geom);

    bool failed() const { return m_failed; }
    void addGeomToA(dGeomID geom) { m_geomsA.insert(geom); }
    void addGeomToB(dGeomID geom) { m_geomsB.insert(geom); }
private:
    
    // private functions
    void initPhysics();
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

    std::unordered_map<dGeomID, Creature*> m_geomMap;

    bool m_failed = false;
    std::unordered_set<dGeomID> m_geomsA;
    std::unordered_set<dGeomID> m_geomsB;
};




#endif