#include "../include/scene.h"
scene::scene(){
    paused = 0;
    wait_for_input = 0;
    change_scene = 0;
}
void scene::previous_scene(){
    if(change_scene==0)
        change_scene =1;
}
void scene::next_scene(){
    if(change_scene==0)
        change_scene =-1;
}
int scene::get_scene_state() {  return change_scene;    }
