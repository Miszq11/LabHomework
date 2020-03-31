#include "../include/game_scene.h"
#include <fstream>

vector2i::vector2i(){
    x = 0;
    y = 0;
}
vector2i::vector2i(int nmx,int nmy){
    x = nmx;
    y = nmy;
}
vector2i::vector2i(vector2i& copy){
    x = copy.x;
    y = copy.y;
}
void vector2i::clampx(int min, int max){
    if(x<min)
        x=min;
    if(x>max)
        x=max;
}
void vector2i::clampy(int min, int max){
    if(y<min)
        y=min;
    if(y>max)
        y=max;
}
game_scene::game_scene(int map_number):
map_line_sizes(),
map(),
scene(),
star_position(),
position(),
info()
{
    time_left = (double)10;
    map_height= 0;
    map_max_width= 0;
    int temp =0;
    std::string filename("assets/maps/map");
    filename+= map_number+'0';
    filename+=".txt";

    std::ifstream input(filename);
    if(!input.is_open())
    {
        std::cerr<<"ERROR: NO ["<<filename<<"] FILE FOUND\n";
        exit(-1);
    }

    for(std::string line;getline(input,line);)
    {
        temp = line.size();
        map_line_sizes.push_back(temp);
        if(temp>map_max_width)
            map_max_width=temp;
        map += line;
        map_height++;
    }
    star_position.x = map.find('*');
    for(auto element:map_line_sizes)
    {
        if(star_position.x>element)
        {
            star_position.x-=element;
            star_position.y++;
        }
    }
    position.x = star_position.x;
    position.y = star_position.y;
    /* odwrotnie
    for(auto element:map_line_sizes)
    {
        if(row>0)
        {
            idx+=element;
            row--;
        }
    }
    */
    input.close();
}
vector2i game_scene::index_to_vec(int index){
    vector2i temp;
    for(auto element:map_line_sizes)
    {
        if(temp.x>element)
        {
            temp.x-=element;
            temp.y++;
        }
    }
    return temp;
}
int game_scene::vec_to_index(vector2i& position) const{
    vector2i self(position);
    int idx =0;
    for(auto element:map_line_sizes)
    {
        if(self.y>0)
        {
            idx +=element;
            self.y--;
        }
    }
    idx+=self.x;
    return idx;
}
void game_scene::update(double time){
    //zmniejszenie czasu pozostalego
    time_left -= time;
    //przypadek kiedy jest cos do zamiany na mapie
    if((position.x != star_position.x)||(position.y != star_position.y))
    {
        position.clampy(0,map_height);
        position.clampx(0,map_line_sizes.at(position.y));
        
        //pobieranie pozycji znaku w stringu na pozycji zmiennej position
        int position_index = vec_to_index(position);
        char sign = '\0';

        //Jeżeli to jest spacja to przesuwa * na position
        if(map.at(position_index)==' ')
        {
        int star_index = vec_to_index(star_position);
        map.replace(static_cast<size_t>(star_index),static_cast<size_t>(1)," ");
        map.replace(static_cast<size_t>(position_index),static_cast<size_t>(1),"*");
        star_position.x = position.x;
        star_position.y = position.y;
        }
        else
        {
            position.x = star_position.x;
            position.y = star_position.y;
        }
        

    }

    info.clear();
    //uzupelnianie ciagu informacyjnego
    info +="Sterowanie [W]-do gory [S]-do dolu [A]-w lewo [D]-w prawo \n"; 
    info +="[o]-wlacz/wylacz silnik [i]-pokaz dane [q]-wyjdz\n";
    
    //kiedy potrzeba dodac do wyswietlania statystyki samochodu
    if(moj_samochod.wyswietlaj_dane)
        info += moj_samochod.zaprezentuj();
}
void game_scene::input(char input_sign){
    bool uruchomiony = moj_samochod.czy_uruchomiony();
    //mapowanie wejscia
    switch (input_sign)
    {
    //gora
    case 'w':
        if(uruchomiony)
            position.y--;
        break;
    //dol
    case 's':
        if(uruchomiony)
            position.y++;
        break;
    //lewo
    case 'a':
        if(uruchomiony)
            position.x-= 2;
        break;
    //prawo
    case 'd':
        if(uruchomiony)
            position.x+= 2;
        break;
    //wlacza/wylacza silnik
    case 'o':
        moj_samochod.czy_uruchomiony()?
                moj_samochod.wylacz():
                moj_samochod.uruchom();
        break;
    //pokazuje/odpokazuje informacje
    case 'i':
        moj_samochod.wyswietlaj_dane=!moj_samochod.wyswietlaj_dane;
        break;
    //wyjscie z gry
    case 'q':
        previous_scene();
        break;

    default:
        break;
    }
}
void game_scene::draw_first(std::string& out_buff){
    int temp= 0;
    int loop_watcher=0;
    for(auto element:map_line_sizes)
    {
        while(loop_watcher++<element)
        {
        out_buff += map.at(temp);
        temp++;
        }
        loop_watcher =0;
        out_buff+='\n';
    }
}
void game_scene::draw_second(std::string& out_buff){
    out_buff += info + '\n';
}
game_scene::~game_scene()
{
}