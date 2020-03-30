#include "../include/game_input.h"




int main(){
    game_input inctr;
    char n =' ';
    int remove = 0;
    while ((n=inctr.getInputTab())!='q')
    {
        remove = 0;
        if(n==EOF) continue;
        switch (n)
        {
        case KEY_UP:
            std::cout<<"\nkey_up";
            remove = 8;
            break;
        
        default:
            break;
        }
        std::cout<<n;
        std::cout.flush();
    }
    inctr.RestoreInputBlock(inctr.getInitTerminalSettings());
}