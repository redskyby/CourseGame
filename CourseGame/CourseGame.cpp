#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>


using namespace std;
using namespace sf;

//класс для спрайтов
class Object {
public:
    Sprite fon, game, exit, block[18], player, ball, gift;

    bool moveGift = false;

    RectangleShape line;

};

//Menu
class Menu {
public:
    bool menu = true;
    bool game = false;
};

//Разрушение блоков со второго раза
bool DoubleHit(int HitArray[], int& c);



int main()
{
    int score = 0;
    double kx = 0;
    double ky = 0;
    double SpeedBoard = 0.2;
    double SpeedBall = 0.05;
    //переменная на пробел , если больше нуля , то игра запускается
    int eventGameStart = 0;
    //Переменная для проверки конца игры
    int endGame = 0;
    //Массив для сверки второго удара
    int HitArray[18];
    for (int q = 0; q < 18; q++) {
        HitArray[q] = 1;

    }

    //создание окна отрисовки
    RenderWindow window(VideoMode(1200, 800), "Arcanoid");

    Object obj;
    Menu men;

    //Текст , цвет , шрифт , жирность.
    Font font;
    font.loadFromFile("CyrilicOld.ttf");
    Text text("", font, 30);
    text.setFillColor(Color::White);
    text.setStyle(Text::Bold);
    text.setPosition(0, 0);



    //Фон
    Texture t1, t2, t3, t4, t5, t6, t7;
    t1.loadFromFile("Paint/fon.png");
    obj.fon.setTexture(t1);

    //Кнопка играть
    t2.loadFromFile("Paint/nac.png");
    obj.game.setTexture(t2);
    obj.game.setPosition(80, 400);

    //Кнопка выхода
    t3.loadFromFile("Paint/exit.png");
    obj.exit.setTexture(t3);
    //Кнопка выхода -> изменение маштаба
    obj.exit.scale(0.7f, 0.7f);
    obj.exit.setPosition(800, 400);

    //Блоки
    t4.loadFromFile("Paint/block.png");
    //Цвет блока
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 3; j++) {
            obj.block[j * 6 + i].setTexture(t4);
            if (j < 1) {
                obj.block[j * 6 + i].setTextureRect(IntRect(140, 0, 140, 26));
            }
            else if (j == 1) {
                obj.block[j * 6 + i].setTextureRect(IntRect(280, 0, 140, 26));
            }
            else {
                obj.block[j * 6 + i].setTextureRect(IntRect(0, 0, 140, 26));
            }
        }
    }

    //Верхняя линия
    obj.line.setSize(Vector2f(1200, 1));
    obj.line.setFillColor(Color::White);
    obj.line.setPosition(0, 100);

    //Игрок
    t5.loadFromFile("Paint/player.png");
    obj.player.setTexture(t5);

    //Мяч
    t6.loadFromFile("Paint/ball.png");
    obj.ball.setTexture(t6);

    //Подарок
    t7.loadFromFile("Paint/pula.png");
    obj.gift.setTexture(t7);



    while (window.isOpen()) {
        Event event;



        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }
        //События на кнопки меню
        if (event.type == Event::MouseButtonPressed) {
            if (event.key.code == Mouse::Left) {
                Vector2i pos = Mouse::getPosition(window);




                if (men.menu) {
                    //Событие на кнопку выхода
                    if (pos.x >= 800 && pos.x <= 1000 &&
                        pos.y >= 410 && pos.y <= 520) {
                        window.close();
                    }
                }

                //Событие на кнопку играть
                if (pos.x >= 50 && pos.x <= 380 &&
                    pos.y >= 400 && pos.y <= 500) {
                    men.menu = false;
                    men.game = true;

                    for (int i = 0; i < 6; i++) {
                        for (int j = 0; j < 3; j++) {
                            obj.block[j * 6 + i].setPosition(25 + 200 * i, 100 + 100 * (j + 1));
                        }
                    }
                    //Координаты игрока и мяча
                    obj.player.setPosition(400, 750);
                    obj.ball.setPosition(510, 660);
                    kx = 1;
                    ky = 1;

                }

            }
        }

        //Если игра == тру , то откликаться на клавиши
        Vector2f BoardEvent = obj.player.getPosition();
        if (men.game) {
            //Правая D
            if (Keyboard::isKeyPressed(Keyboard::D)) {
                if (BoardEvent.x < 870) {
                    obj.player.move(SpeedBoard, 0);
                    if (eventGameStart == 0) {
                        obj.ball.move(SpeedBoard, 0);
                    }
                }
            }

            //Левая A
            if (Keyboard::isKeyPressed(Keyboard::A)) {
                if (BoardEvent.x > 0) {
                    obj.player.move(-SpeedBoard, 0);
                    if (eventGameStart == 0) {
                        obj.ball.move(-SpeedBoard, 0);
                    }
                }
            }

            //Начало игры с нажатие пробела 
            if (Keyboard::isKeyPressed(Keyboard::Space)) {
                eventGameStart = 1;
            }



        }

        //Если игра началась
        if (eventGameStart) {
            obj.ball.move(SpeedBall * -kx, SpeedBall * -ky);

            Vector2f PlayerInGame = obj.player.getPosition();
            Vector2f BallInGame = obj.ball.getPosition();
            //Отскакивание от стен
            if ((BallInGame.y < 0) || (BallInGame.y < 100)) {
                ky *= -1;
            }
            if (BallInGame.x > 1110 || BallInGame.x < 0) {
                kx *= -1;
            }

            //Игрок отбивает мяч
            if (obj.ball.getGlobalBounds().intersects(obj.player.getGlobalBounds())) {
                ky *= -1;

                obj.ball.move(SpeedBall, -0.5);
            }
            //Если мячик упал или все блоки сбиты
            if (BallInGame.y > 800 || endGame > 17) {
                //obj.player.setPosition(400, 750);
               // obj.ball.setPosition(510, 660);
                eventGameStart = 0;
                endGame = 0;
                men.game = false;
                men.menu = true;
            }



            //Скрытие блока
            for (int i = 0; i < 18; i++) {
                if (obj.ball.getGlobalBounds().intersects(obj.block[i].getGlobalBounds())) {
                    ky *= -1;
                    obj.ball.move(SpeedBall, 0.1 * ky);

                    //Проверка какой блок сбит
                    if (i < 6) {
                        //тут проверка на отбитие
                        if (DoubleHit(HitArray, i)) {
                            score += 100;
                            obj.block[i].setPosition(1300, 0);
                            endGame++;
                        }
                        else {
                            obj.ball.move(SpeedBall, 0.1 * -ky);
                        }
                    }
                    else if (i >= 6 && i < 12) {
                        //Приз с красных блоков
                        //(i % 2 == 0) <---- для того , чтобы с соседнего блока не выпадал приз.
                        if (!obj.moveGift && (i % 2 == 0)) {
                            obj.moveGift = true;
                            Vector2f posBlock = obj.block[i].getPosition();
                            obj.gift.setPosition(posBlock.x, posBlock.y);
                        }
                        else {
                            obj.moveGift = false;
                        }
                        score += 50;
                        obj.block[i].setPosition(1300, 0);
                        endGame++;
                    }
                    else {
                        score += 10;
                        obj.block[i].setPosition(1300, 0);
                        endGame++;
                    }
                }
            }

            //Движение и сокрытие блока
            if (obj.moveGift) {
                obj.gift.move(0, SpeedBall);

                //если есть стокновение с игроком
                if (obj.gift.getGlobalBounds().intersects(obj.player.getGlobalBounds())) {
                    obj.gift.setPosition(1800, 400);
                    obj.gift.move(0, 0);
                    score += 400;
                }
                //игрок не вспоймал и приз улетел за экран , то скрыть его
                Vector2f posGift = obj.gift.getPosition();
                if (posGift.y > 850) {
                    obj.gift.setPosition(1800, 400);
                    obj.gift.move(0, 0);
                }
            }

        }



        //Создание текста
        //Создание потока на вывод переменной в тексте
        ostringstream playerScoreString;
        playerScoreString << score;
        //Текст с количеством очков
        text.setString("Твой счет:" + playerScoreString.str());





        window.draw(obj.fon);




        //Если меню true , то видим меню
        if (men.menu) {
            window.draw(obj.game);
            window.draw(obj.exit);
        }
        //Если нажата кнопка "Играть"  , то играем
        if (men.game) {
            window.draw(obj.line);
            for (int i = 0; i < 18; i++) {
                window.draw(obj.block[i]);
            }
            window.draw(obj.ball);
            window.draw(obj.player);
            window.draw(text);
        }
        //Если нажата кнопка "Играть" и булева переменная тру у приза , то видим приз
        if (men.game && obj.moveGift) {
            window.draw(obj.gift);
        }


        window.display();

    }



    return 0;
}


bool DoubleHit(int TestArray[], int& c) {
    if (TestArray[c] == 1) {
        TestArray[c] = 0;
        return false;
    }
    else {
        return true;
    }
};