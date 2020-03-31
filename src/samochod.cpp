
#include "../include/samochod.h"

samochod::samochod(/* args */):
uruchomiony(false),
wyswietlaj_dane(true),
moc(2)
{
}

samochod::~samochod()
{
}

void samochod::uruchom(){
    uruchomiony = true;
}
void samochod::wylacz(){
    uruchomiony = false;
}
std::string& samochod::zaprezentuj(){
    informacje.clear();
    if(uruchomiony)
    {
        informacje+="Samochod wlaczony jedz!\nmoc samochodu: ";
        informacje+= std::to_string(moc);
        informacje+= '\n';
    }
    else
        informacje+="Samochod wylaczony, wlacz silnik!\n";
    return informacje;
}
bool samochod::czy_uruchomiony(){
    return uruchomiony;
}