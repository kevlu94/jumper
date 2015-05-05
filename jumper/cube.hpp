#ifndef CUBE_HPP
#define CUBE_HPP

#include "model.hpp"

class Cube: public Model
{
public:
    Cube();
    virtual ~Cube() {}
    
    virtual bool colored() const { return true; }
    virtual bool textured() const { return false; }
    
};




#endif