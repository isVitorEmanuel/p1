/**
 * @file life_game.cpp
 *
 * @description
 * This program simulates the Conway's Game of Life.
 * It reads a initial game configuration from a input file and
 * keeps updating it, if the user so whishes.
 *
 * @author	Selan R dos Santos, <selan.rds@gmail.com>
 * @date	2015, updated 2015-04-03, updated 2024-05-31
 *
 * @remark On 2015-09-19 changed the way stability is verified.
 * In the previous version we just looked back one configuration and compare it
 * with the current configuration.
 * Now, the stability may span more than one configuration. Because of that we
 * need to keep track of all configurations and check whether the current
 * configuration has already been generated.
 * If this is the case, the game has reached stability and must stop.
 */

#include <cstdlib>  // EXIT_SUCCESS
#include <iostream>

#include "life.h"

using namespace life;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Missing path to configuration file!" << std::endl;
        std::cerr << "  Usage: glife setting.ini" << std::endl;
        return EXIT_FAILURE;
    }

    Config conf;
    conf.load(argv[1]);

    LifeCfg cfg;
    cfg.load_from_file(conf);  

    cfg.generation_loop(conf);

    return EXIT_SUCCESS;
}