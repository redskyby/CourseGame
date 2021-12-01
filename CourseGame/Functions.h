#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <fstream>


using namespace std;
using namespace sf;

//����� ��� ��������
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

//���������� ������ �� ������� ����
bool DoubleHit(int HitArray[], int& c);
//���������� ��������
void  SortOfVector(int sortArray[], int& thisScore);
//������ �� �����
void ReadIngFromFile(int ReadFromFile[]);
//������ � ����
void WrittenInFile(int WrittenInFile[], int& LoadInFileScore);
