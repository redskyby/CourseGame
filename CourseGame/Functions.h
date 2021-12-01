#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <fstream>


using namespace std;
using namespace sf;

//класс для спрайтов
class Object {
public:
    Sprite fon, game, exit, block[18], player, ball, gift, buttonTableScore, buttonBack;

    bool moveGift = false;

    RectangleShape line;

};

//Menu
class Menu {
public:
    bool menu = true;
    bool game = false;
    bool tableSrore = false;
    bool buttonBack = false;
};

//Разрушение блоков со второго раза
bool DoubleHit(int HitArray[], int& c);
//Сортировка массиваы
void  SortOfVector(int sortArray[], int& thisScore);
//Чтение из файла
void ReadIngFromFile(int ReadFromFile[]);
//Запись в файл
void WrittenInFile(int WrittenInFile[], int& LoadInFileScore);
