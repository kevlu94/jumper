#ifndef SHAPES_HPP
#define SHAPES_HPP

#include "model.hpp"

class ColoredCube: public Model
{
public:
    ColoredCube(glm::vec3 color, glm::vec3 size);
    virtual ~ColoredCube() {}
        
    virtual bool colored() const { return true; }
    virtual bool textured() const { return false; }
};


#endif