/*
 * @file Main.cpp
 *
 * @author Cyber-Physical Real-Time Systems Group
 * @author Research and Development Department
 * @author Instituto Tecnologico de Informatica
 *
 * @brief
 *    Controller main
 */

#include "ControlCost.hpp"
#include "dispmap.hpp"

/** Shaders Base directory */
static const std::string SHADERSDIR = SHADERS_PATH;

int main(int argc, char **argv) {

    dispmap::setShadersPath(SHADERSDIR);

    ControlCost controlCost;

    controlCost.simulate();
}
