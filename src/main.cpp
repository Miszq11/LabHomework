#include "../include/game_input.h"
#include "../include/game.h"
#include <ios>
#include <iostream>


int main(){
    game_input inctr;

    game instance(50);
    instance.start();

    inctr.RestoreInputBlock(inctr.getInitTerminalSettings());
}