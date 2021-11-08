/*
 * @file ControlCost.cpp
 *
 * @author Cyber-Physical Real-Time Systems Group
 * @author Research and Development Department
 *
 * @author Instituto Tecnologico de Informatica
 *
 * @brief
 *    ControlCost federate
 */

#include <iostream>
#include "ControlCost.hpp"
#include "dispmap.hpp"
#include <math.h>
#include <unistd.h>

/**
 * Default constructor
 */

ControlCost::ControlCost (

) :
        N(1000),
        state{index, {0.0f, 0.0f, 0.0f, 0.0f}},
	    index(0)
{
}



/**
 * Execute simulation process
 */
void ControlCost::simulate (

)
{

    dispmap* map = dispmap::getInstance();
    map->init();

    while (N>0) {

        // Process the events with the timestamp order
       // step();
        map->render(&state);
        N--;
    }

    map->shutdown();
}


/**
 * Simulation Step
 */
void ControlCost::step (

)
{
    /*
	usleep(1E5);

    if (N >= 800)
    {
        state.index = 0;
        state.JValue[0] = float(1000 - N) * 2.0E-3 ;
    }
    else if(600 <= N && N < 800)
    {
        state.index = 1;
        state.JValue[1] = float(1000 - N) * 2.0E-3 ;
    }
    else if (400 <= N && N <600)
    {
        state.index = 2;
        state.JValue[2] = float(1000 - N) * 2.0E-3 ;
    }
    else if (200 <= N && N < 400)
    {
        state.index = 3;
        state.JValue[3] = float(1000 - N) * 2.0E-3 ;
    }
    else if (N < 200)
    {
        state.index = 4;
        state.JValue[4] = float(1000 - N) * 2.0E-3 ;
    }
   */ 
    dispmap* map = dispmap::getInstance();
    map->render(&state);
    
}

