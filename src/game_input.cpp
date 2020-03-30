#include "../include/game_input.h"

game_input::game_input():
initialSetHolder()
{
    //Wylaczanie blokowania na strumieniu wejscia
    SetKeyboardNonBlock(initialSetHolder);
}
struct termios& game_input::getInitTerminalSettings(){  return initialSetHolder; }
void game_input::RestoreInputBlock(struct termios& initial_settings)
{
    //Restoring normal boring terminal func.
	tcsetattr(0, TCSANOW, &initial_settings);
}

void game_input::SetKeyboardNonBlock(struct termios& initial_settings)
{
    std::cout<<"configuring terminal\n";
    struct termios new_settings;
    tcgetattr(0,&initial_settings);
    //copying initial terminal setings to restore them at the end
    new_settings = initial_settings;
    // setting Flags for not cannonical mod, not echo-ing and sig
    new_settings.c_lflag &= ~(ICANON | ECHO | ISIG);
    //new_settings.c_lflag &= ~ECHO;
    //new_settings.c_lflag &= ~ISIG;

    // VMIN && VTIME == 0 <==> data from read(stream,buff) is returned immidiately when available
    new_settings.c_cc[VMIN] = 0;
    new_settings.c_cc[VTIME] = 0;
    
    //applying settings
    tcsetattr(0, TCSANOW, &new_settings);
}

game_input::~game_input(){
    std::cout<<"restoring previous terminal options\n";
    RestoreInputBlock(initialSetHolder);
}
//pretty obvious
char game_input::getInputTab(){
    char buffer[2]={0,0};
    int length = read(STDIN_FILENO,buffer,1);
    if(length>0)
        return buffer[0];
    return EOF;
}