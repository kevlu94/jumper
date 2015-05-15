//
//  main.cpp
//  jumper
//
//  Created by Kevin on 5/4/15.
//  Copyright (c) 2015 UCLA. All rights reserved.
//

#include "interface.hpp"
#include "scene.hpp"

int main(int argc, char *argv[])
{
    //fprintf(stderr,"first line\n");
    //usleep(10000000);
    /*
    GLuint program;
    GLuint VertexArrayID;
    Scene scene;
    */
    
    // start at 0 degrees
    // ?
    dReal knee_angle=0;
    dReal knee_velocity=0;
    dReal hip_angle=0;
    dReal hip_velocity=0;
    
    dReal next_knee_angle;
    dReal next_hip_angle;
    dReal delta_next_knee_angle;
    dReal delta_next_hip_angle;
    
    dReal torqueKnee;
    dReal torqueHip;
    
    Simulator sim;
    
    FILE *f;
    
    //fprintf(stderr,"--> before init\n");
    
    
    sim.initilizeSimulator();
    //program=initilizeSimulator(&VertexArrayID,&scene);
    
    //fprintf(stderr,"--> init complete\n");
    f=fopen(argv[1],"r");
    
    int i;
    //for (i=0; i<100; i++) {
    while(!feof(f)) {
        // network
        // inputs: knee_angle, knee_velocity, hip_angle, hip_velocity,
        // outputs: out1, out2 [between 0,1]
        
        // net outputs torques (after scaling and offset)
        // scaled from the ouputs of the network
        //torqueKnee=-5.0f; //out1*scale1-offset1
        //torqueHip=0.0f; //out2*scale2-offset2
        
        fscanf(f,"%f %f\n",&torqueKnee,&torqueHip);
        
        printf("torques: %f %f\n",torqueKnee,torqueHip);
        
        // net outputs change in torques
        // ?
        
        // net outputs angels
        // ?
        
        // net outputs change in angles
        // This is not necessarely the desired change in angle
        // but some value that when put through the equations
        // gives the desired torque which drives the simulator
        // since this is a linear formula a network with 3 layers
        // should be able to lear it
        /*
        delta_next_knee_angle=0.05; //out1*scale1-offset1
        delta_next_hip_angle=0; // out1*scale1-offset1
        next_knee_angle=knee_angle+delta_next_knee_angle;
        next_hip_angle=hip_angle+delta_next_hip_angle;
        double k1=100; //2
        double k2=0.05;
        torqueKnee = k1*(next_knee_angle-knee_angle)+k2*(knee_velocity);
        torqueHip = k1*(next_hip_angle-hip_angle)+k2*(hip_velocity);
        */
        
        // applies the torques, measures the resulting angles adn rates
        sim.runSimulator(torqueKnee,torqueHip, &knee_angle, &knee_velocity, &hip_angle, &hip_velocity);
        
        glm::vec3 com;
        com=sim.getCenterOfMass();
        printf("center of mass: (%f, %f, %f)\n", com[0], com[1], com[2]);
        printf("angels: (%f, %f, %f %f)\n", knee_angle, knee_velocity, hip_angle, hip_velocity);
        
        // test and kill off pupulation
        if (!sim.isBalanced())
            printf("Out of Balance\n");
    }
    
    //fprintf(stderr,"--> run complete\n");
    
    sim.closeSimulator();

    fclose(f);

    return 0;
}
