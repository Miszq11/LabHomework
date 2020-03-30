#ifndef GAME_INPUT_H
#define GAME_INPUT_H
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER 13
#define KEY_BACKSPACE 8
#define KEY_ESCAPE 27

class game_input{
private:
    struct termios initialSetHolder;
    void SetKeyboardNonBlock(struct termios& );
public:
    game_input();
    virtual ~game_input();
    struct termios& getInitTerminalSettings();
    void RestoreInputBlock(struct termios& initSettings);
    char getInputTab();
};
#endif