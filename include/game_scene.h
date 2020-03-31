#ifndef GAME_SCENE_H
#define GAME_SCENE_H
#include <iostream>
#include <vector>
#include "scene.h"
#include "samochod.h"

struct vector2i{
    int x;
    int y;
    vector2i();
    vector2i(int nmx,int nmy);
    vector2i(vector2i& );
    void clampx(int min, int max);
    void clampy(int min, int max);
};

class game_scene:public scene
{
private:
    //zmienna przechowujaca liczebnosc znakow w kazdej linijce map_line_sizes
    std::vector<int> map_line_sizes;
    //wysokosc mapy (ilosc wierszy zmiennej map)
    int map_height;
    //maksymalna szerokosc mapy (ilosc kolumn zmiennej map)
    int map_max_width;
    //zmienna przechowujaca mape
    std::string map;
    //zmienna przechowujaca zestaw klawiszy do sterowania oraz wyswietlajaca statystyki samochodu
    std::string info;
    //zmienna przechowujaca pozostaly czas gry
    double time_left;
    //zmienna przechowujaca obiekt samochodu
    samochod moj_samochod;
    //zmienna typu vektor2i przechowujaca pozycje '*' w zmiennej map
    vector2i star_position;
    //zmienna przechowujaca pozycje do ktorej zmienic ma sie znak '*'
    vector2i position;
    //funkcja zamieniajaca wartosc indeksu stringu do pozycji vektorowej
    vector2i index_to_vec(int index);
    //funkcja zamieniajaca podany vektor na index w stringu map
    int vec_to_index(vector2i& ) const;
public:
    game_scene(int map =1);
    ~game_scene();
    void update(double time);
    void input(char input_sign);
    void draw_first(std::string& out_buff);
    void draw_second(std::string& out_buff);
};

#endif