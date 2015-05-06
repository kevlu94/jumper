#include "objects.hpp"

void ColoredBox::addToScene(dWorldID worldID, dSpaceID spaceID, glm::vec3 position)
{
    // body
    m_bodyID = dBodyCreate(worldID);
    dMassSetBox(&m_mass, m_density, 2 * m_size[0], 2 * m_size[1], 2 * m_size[2]);
    dBodySetMass(m_bodyID, &m_mass);
    dBodySetPosition(m_bodyID, position[0], position[1], position[2]);
    // geometry
    m_geomID = dCreateBox(spaceID, 2 * m_size[0], 2 * m_size[1], 2 * m_size[2]);
    dGeomSetBody(m_geomID, m_bodyID);
    dGeomSetPosition(m_geomID, position[0], position[1], position[2]);

}

void ColoredImmovableBox::addToScene(dWorldID worldID, dSpaceID spaceID, glm::vec3 position)
{
    m_geomID = dCreateBox(spaceID, 2 * m_size[0], 2 * m_size[1], 2 * m_size[2]);
    dGeomSetBody(m_geomID, m_bodyID);
    dGeomSetPosition(m_geomID, position[0], position[1], position[2]);
}