#ifndef SAMOCHOD_H
#define SAMOCHOD_H

#include <iostream>

class samochod
{
private:
    bool uruchomiony;
    //moc okresla ilosc mozliwych ruchow na sekunde
    int moc;
    std::string informacje;
public:
    bool wyswietlaj_dane;
    bool czy_uruchomiony();
    samochod(/* args */);
    ~samochod();
    void uruchom();
    void wylacz();
    std::string& zaprezentuj();
};



#endif