#include "shapes.hpp"


std::vector<glm::vec3> ColoredCube::cube(glm::vec3 center, glm::vec3 size)
{
/*    std::vector<glm::vec3> p = {
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
 */
    std::vector<glm::vec3> p(8);
    p[0]=center + glm::vec3(size[0], -size[1], -size[2]);
    p[1]=center + glm::vec3(size[0], -size[1], size[2]);
    p[2]=center + glm::vec3(-size[0], -size[1], size[2]);
    p[3]=center + glm::vec3(-size[0], -size[1], -size[2]);
    p[4]=center + glm::vec3(size[0], size[1], -size[2]);
    p[5]=center + glm::vec3(size[0], size[1], size[2]);
    p[6]=center + glm::vec3(-size[0], size[1], size[2]);
    p[7]=center + glm::vec3(-size[0], size[1], -size[2]);
    
    std::vector<glm::vec3> ret(36);
    ret[0]=p[4];
    ret[1]=p[0],
    ret[2]=p[3],
    ret[3]=p[4];
    ret[4]=p[3];
    ret[5]=p[7];
    ret[6]=p[2];
    ret[7]=p[6];
    ret[8]=p[7];
    ret[9]=p[2];
    ret[10]=p[7];
    ret[11]=p[3];
    ret[12]=p[1];
    ret[13]=p[5];
    ret[14]=p[2];
    ret[15]=p[5];
    ret[16]=p[6];
    ret[17]=p[2];
    ret[18]=p[0];
    ret[19]=p[4];
    ret[20]=p[1];
    ret[21]=p[4];
    ret[22]=p[5];
    ret[23]=p[1];
    ret[24]=p[4];
    ret[25]=p[7];
    ret[26]=p[5];
    ret[27]=p[7];
    ret[28]=p[6];
    ret[29]=p[5];
    ret[30]=p[0];
    ret[31]=p[1];
    ret[32]=p[2];
    ret[33]=p[0];
    ret[34]=p[2];
    ret[35]=p[3];

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