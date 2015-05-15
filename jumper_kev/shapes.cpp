#include "shapes.hpp"


std::vector<glm::vec3> cube(glm::vec3 center, glm::vec3 size)
{
    std::vector<glm::vec3> p = {
        center + glm::vec3(size[0], -size[1], -size[2]),
        center + glm::vec3(size[0], -size[1], size[2]),
        center + glm::vec3(-size[0], -size[1], size[2]),
        center + glm::vec3(-size[0], -size[1], -size[2]),
        center + glm::vec3(size[0], size[1], -size[2]),
        center + glm::vec3(size[0], size[1], size[2]),
        center + glm::vec3(-size[0], size[1], size[2]),
        center + glm::vec3(-size[0], size[1], -size[2])
    };
    std::vector<glm::vec3> ret = {
        p[4], p[0], p[3],
        p[4], p[3], p[7],
        p[2], p[6], p[7],
        p[2], p[7], p[3],
        p[1], p[5], p[2],
        p[5], p[6], p[2],
        p[0], p[4], p[1],
        p[4], p[5], p[1],
        p[4], p[7], p[5],
        p[7], p[6], p[5],
        p[0], p[1], p[2],
        p[0], p[2], p[3]
    };
    return ret;
}

ColoredCube::ColoredCube(glm::vec3 color, glm::vec3 size)
{
    std::vector<glm::vec3> positionBuffer = cube(glm::vec3(0.0f), size);
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
    m_size = size;
}