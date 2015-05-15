//
//  main.cpp
//  jumper
//
//  Created by Kevin on 5/4/15.
//  Copyright (c) 2015 UCLA. All rights reserved.
//

#include "interface.hpp"
#include "scene.hpp"

int main()
{
    fprintf(stderr,"first line\n");
    //usleep(10000000);
    /*
    GLuint program;
    GLuint VertexArrayID;
    Scene scene;
    */
    
    Simulator sim;
    
    fprintf(stderr,"--> before init\n");
    
    
    sim.initilizeSimulator();
    //program=initilizeSimulator(&VertexArrayID,&scene);
    
    fprintf(stderr,"--> init complete\n");
    
    sim.runSimulator();
    //runSimulator(&scene);
    
    fprintf(stderr,"--> run complete\n");
    
    sim.closeSimulator();
    //closeSimulator(program,&VertexArrayID);
    
    return 0;
}
