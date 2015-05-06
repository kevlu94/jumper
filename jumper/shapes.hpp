#ifndef SHAPES_HPP
#define SHAPES_HPP

#include "model.hpp"

class Cube: public Model
{
public:
    Cube(dReal density, glm::vec3 color, glm::vec3 size);
    virtual ~Cube() {}
    
    virtual bool colored() const { return true; }
    virtual bool textured() const { return false; }
};

class Plane: public Model
{
public:
    Plane(dReal density, glm::vec3 color, glm::vec2 size);
    virtual ~Plane() {}
    
    virtual bool colored() const { return true; }
    virtual bool textured() const { return false; }
};


#endif