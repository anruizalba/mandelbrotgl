/*
 * @file ControlCost.hpp
 *
 * @author Cyber-Physical Real-Time Systems Group
 * @author Research and Development Department
 * @author Instituto Tecnologico de Informatica
 *
 * @brief
 *    ControlCost federate
 */

#ifndef INCLUDE_CONTROLLER_HPP_
#define INCLUDE_CONTROLLER_HPP_

#include "dispmap.hpp"


    class ControlCost {

    public:

        /**
         * Default constructor
         */
        ControlCost();

        /**
         * Execute simulation process
         */
        void simulate();


    private:




        /** Iteration number */
        int N{0};

        /**
         * Simulation Step
         */
        void step();
        drawArray state;
        int index{0};

    };
#endif // INCLUDE_CONTROLLER_HPP_
