#ifndef OBJECTS_HPP
#define OBJECTS_HPP

#include "shapes.hpp"

class ColoredBox: public ColoredCube
{
public:
    ColoredBox(dReal density, glm::vec3 color, glm::vec3 size): ColoredCube(color, size) { m_density = density; }
    virtual ~ColoredBox() {}
    
    virtual void addToScene(dWorldID worldID, dSpaceID spaceID, glm::vec3 position);
    virtual glm::vec3 position() const { return *((glm::vec3*) dBodyGetPosition(m_bodyID)); }
};

class ColoredImmovableBox: public ColoredCube
{
public:
    ColoredImmovableBox(glm::vec3 color, glm::vec3 size): ColoredCube(color, size) {}
    virtual ~ColoredImmovableBox() {}

    virtual void addToScene(dWorldID worldID, dSpaceID spaceID, glm::vec3 position);
    virtual glm::vec3 position() const { return *((glm::vec3*) dGeomGetPosition(m_geomID)); }
};



#endif