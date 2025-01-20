#include <iostream>
#include <fmt/printf.h>
#include <pdg/demo/player.hpp>


int main(int argc, char **argv) {

    pdg::demo::Player player{"pdg-demo-game"};
    return player.play(argc, argv);
}
