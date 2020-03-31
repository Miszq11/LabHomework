#include "../include/game.h"

game::game(int ffixed_fps):
fixed_fps(ffixed_fps),
target_delta_time(1/ffixed_fps),
out_first_buff(""),
out_second_buff(""),
current_scene(),
scene_vector(),
clock()
{
    init();
}
void game::init(){
    auto game_sc = std::make_shared<game_scene>(1);
    register_scene(game_sc);
    current_scene = *(scene_vector.begin());
}
void game::update(double elapsed_time){
    if(current_scene->get_scene_state() == 0)
    {
        current_scene->update(elapsed_time);
    }
    if(current_scene->get_scene_state() == 1)
    {
        bool stop_next =0;

        for(auto element : scene_vector)
        {
            if(stop_next)
            {
                current_scene = element;
                break;
            }
            if(element == current_scene)
            {
                if(element == scene_vector.back())
                {
                    current_scene = scene_vector.front();
                    break;
                }
                stop_next = true;
            }
        }
    }
    if(current_scene->get_scene_state() == -1)
    {
        shared_ptr<scene> prev_scene = scene_vector.front();
        for(auto element : scene_vector)
        {
            if(current_scene == element)
            {
                if(element == prev_scene)
                {
                    current_scene = scene_vector.back();
                    break;
                }
                current_scene = prev_scene;
                break;
            }
        }
    }
    
}
void game::draw(){
    //czyszczenie bufforów wyjścia
    last_first_output.clear();
    last_second_output.clear();
    //last_first_output. out_first_buff;
    //last_second_output+= out_second_buff;
    last_first_output.insert(0,out_first_buff);
    last_second_output.insert(0,out_second_buff);
    out_first_buff.clear();
    out_second_buff.clear();
    //wpisanie zawartości do buforów
    current_scene->draw_first(out_first_buff);
    current_scene->draw_second(out_second_buff);

    //sprawdzenie, czy na terminal trzeba odswiezyc
    if(last_first_output.compare(out_first_buff)!=0 ||
             last_second_output.compare(out_second_buff)!=0)
        {
            system("clear");
        }
        else
        {
            return;
        }
        
        
    //wypisanie bufforów w terminal
        std::cout<<out_first_buff;
        std::cout<<out_second_buff;
}
void game::input(char input){
    if(current_scene->get_scene_state() == 0)
        {
            current_scene->input(input);
        }
}
void game::start(){
    clock.restart();
    double time_elapsed = double(0);
    while((last_input = game_input::getInputTab())!='q')
    {
        time_elapsed = clock.restart();
        if(current_scene.get()==nullptr)
            {
                std::cerr<<"NO SCENES INITIALIZED\n";
                break;
            }
        input(last_input);
        update(time_elapsed);
        draw();
    }
}
void game::register_scene(shared_ptr<scene> scene_to_register){
    scene_vector.push_back(scene_to_register);
}
void game::set_scene(shared_ptr<scene> scene_to_register){
    bool push_back = true;
    for(auto element:scene_vector)
    {
        int position= 0;
        
        if(element == scene_to_register)
        {
            push_back = false;
        }
        position++;
    }
    if(push_back)
        scene_vector.push_back(scene_to_register);
}