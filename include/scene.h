#ifndef SCENE_CPP
#define SCENE_CPP
#include <chrono>
#include <iostream>
#include <time.h>

class scene{
private:
    bool paused;
    bool wait_for_input;
    int change_scene;
    void init();
public:
    scene();
    virtual void update(double time) =0;
    virtual void input(char input_sign) =0;
    virtual void draw_first(std::string& out_buff) =0;
    virtual void draw_second(std::string& out_buff) =0;
    void previous_scene();
    void next_scene();
    int get_scene_state();
};

#endif