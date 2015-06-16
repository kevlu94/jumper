#ifndef SHAPES_HPP
#define SHAPES_HPP

#include "model.hpp"

class ColoredCube: public Model
{
public:
    ColoredCube() {}
    ColoredCube(glm::vec3 color, glm::vec3 size);
    virtual ~ColoredCube() {}
    
    std::vector<glm::vec3> cube(glm::vec3 center, glm::vec3 size);
    virtual bool colored() const { return true; }
    virtual bool textured() const { return false; }
};


#endif