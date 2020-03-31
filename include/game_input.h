#ifndef GAME_INPUT_H
#define GAME_INPUT_H
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>

class game_input{
private:
    struct termios initialSetHolder;
    void SetKeyboardNonBlock(struct termios& );
public:
    game_input();
    virtual ~game_input();
    struct termios& getInitTerminalSettings();
    void RestoreInputBlock(struct termios& initSettings);
    static char getInputTab();
};
#endif
