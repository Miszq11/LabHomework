#ifndef GAME_HPP
#define GAME_HPP
#include "scene.h"
#include "timer.h"
#include "game_scene.h"
#include "game_input.h"
#include <memory>
#include <iostream>
#include <vector>
#include <unistd.h>

using std::shared_ptr;

class game{
private:
    //wartosc stwierdzajaca czy nalezy oczyscic terminal
    bool refresh;
    //vector scen
    std::vector<shared_ptr<scene>> scene_vector;
    //obecna scena do rysowania
    shared_ptr<scene> current_scene;
    //pierwszy w kolejnosci rysowany ciag znakow 
    std::string out_first_buff;
    //zmienna przechowuje obraz ostatniego ciagu, by ekran nie "migal"
    std::string last_first_output;
    //drugi w kolejnosci rysowany ciag znakow
    std::string out_second_buff;
    //zmienna przechowuje obraz ostatniego ciagu, by ekran nie "migal"
    std::string last_second_output;
    //ostatni znak na strumieniu wejscia
    char last_input;
    //Timer chyba odmierza czas...
    Timer clock;
    //ustalona wartosc klatek na sekunde
    int fixed_fps;
    //liczona z fixed_fps -> 1/fixed_fps
    double target_delta_time;

    //funkcja dodajaca sceny
    void init();
    //funkcja czytajaca strumien wejscia i wywolujaca met. input() w scenie
    void input(char input);
    //funkcja wywolujaca met. update() w scenie i w razie potrzeby zmieniajaca scene na inna
    void update(double elapsed_time);
    //funkcja wywolujaca met. draw() w scenie
    void draw();
public:
    game(int ffixed_fps = 30);
    void start();
    void set_scene();
    //funkcja dodajaca scene do vevtora jezeli jej tam nie ma zmieniajaca current_scene
    void set_scene(shared_ptr<scene> scene_to_register);
    //funckja dodajaca scene do vectora
    void register_scene(shared_ptr<scene> scene_to_register);

};

#endif