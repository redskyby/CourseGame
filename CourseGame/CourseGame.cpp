#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>


using namespace std;
using namespace sf;

//����� ��� ��������
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

//���������� ������ �� ������� ����
bool DoubleHit(int HitArray[], int& c);



int main()
{
    int score = 0;
    double kx = 0;
    double ky = 0;
    double SpeedBoard = 0.2;
    double SpeedBall = 0.05;
    //���������� �� ������ , ���� ������ ���� , �� ���� �����������
    int eventGameStart = 0;
    //���������� ��� �������� ����� ����
    int endGame = 0;
    //������ ��� ������ ������� �����
    int HitArray[18];
    for (int q = 0; q < 18; q++) {
        HitArray[q] = 1;

    }

    //�������� ���� ���������
    RenderWindow window(VideoMode(1200, 800), "Arcanoid");

    Object obj;
    Menu men;

    //����� , ���� , ����� , ��������.
    Font font;
    font.loadFromFile("CyrilicOld.ttf");
    Text text("", font, 30);
    text.setFillColor(Color::White);
    text.setStyle(Text::Bold);
    text.setPosition(0, 0);



    //���
    Texture t1, t2, t3, t4, t5, t6, t7;
    t1.loadFromFile("Paint/fon.png");
    obj.fon.setTexture(t1);

    //������ ������
    t2.loadFromFile("Paint/nac.png");
    obj.game.setTexture(t2);
    obj.game.setPosition(80, 400);

    //������ ������
    t3.loadFromFile("Paint/exit.png");
    obj.exit.setTexture(t3);
    //������ ������ -> ��������� �������
    obj.exit.scale(0.7f, 0.7f);
    obj.exit.setPosition(800, 400);

    //�����
    t4.loadFromFile("Paint/block.png");
    //���� �����
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

    //������� �����
    obj.line.setSize(Vector2f(1200, 1));
    obj.line.setFillColor(Color::White);
    obj.line.setPosition(0, 100);

    //�����
    t5.loadFromFile("Paint/player.png");
    obj.player.setTexture(t5);

    //���
    t6.loadFromFile("Paint/ball.png");
    obj.ball.setTexture(t6);

    //�������
    t7.loadFromFile("Paint/pula.png");
    obj.gift.setTexture(t7);



    while (window.isOpen()) {
        Event event;



        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }
        //������� �� ������ ����
        if (event.type == Event::MouseButtonPressed) {
            if (event.key.code == Mouse::Left) {
                Vector2i pos = Mouse::getPosition(window);




                if (men.menu) {
                    //������� �� ������ ������
                    if (pos.x >= 800 && pos.x <= 1000 &&
                        pos.y >= 410 && pos.y <= 520) {
                        window.close();
                    }
                }

                //������� �� ������ ������
                if (pos.x >= 50 && pos.x <= 380 &&
                    pos.y >= 400 && pos.y <= 500) {
                    men.menu = false;
                    men.game = true;

                    for (int i = 0; i < 6; i++) {
                        for (int j = 0; j < 3; j++) {
                            obj.block[j * 6 + i].setPosition(25 + 200 * i, 100 + 100 * (j + 1));
                        }
                    }
                    //���������� ������ � ����
                    obj.player.setPosition(400, 750);
                    obj.ball.setPosition(510, 660);
                    kx = 1;
                    ky = 1;

                }

            }
        }

        //���� ���� == ��� , �� ����������� �� �������
        Vector2f BoardEvent = obj.player.getPosition();
        if (men.game) {
            //������ D
            if (Keyboard::isKeyPressed(Keyboard::D)) {
                if (BoardEvent.x < 870) {
                    obj.player.move(SpeedBoard, 0);
                    if (eventGameStart == 0) {
                        obj.ball.move(SpeedBoard, 0);
                    }
                }
            }

            //����� A
            if (Keyboard::isKeyPressed(Keyboard::A)) {
                if (BoardEvent.x > 0) {
                    obj.player.move(-SpeedBoard, 0);
                    if (eventGameStart == 0) {
                        obj.ball.move(-SpeedBoard, 0);
                    }
                }
            }

            //������ ���� � ������� ������� 
            if (Keyboard::isKeyPressed(Keyboard::Space)) {
                eventGameStart = 1;
            }



        }

        //���� ���� ��������
        if (eventGameStart) {
            obj.ball.move(SpeedBall * -kx, SpeedBall * -ky);

            Vector2f PlayerInGame = obj.player.getPosition();
            Vector2f BallInGame = obj.ball.getPosition();
            //������������ �� ����
            if ((BallInGame.y < 0) || (BallInGame.y < 100)) {
                ky *= -1;
            }
            if (BallInGame.x > 1110 || BallInGame.x < 0) {
                kx *= -1;
            }

            //����� �������� ���
            if (obj.ball.getGlobalBounds().intersects(obj.player.getGlobalBounds())) {
                ky *= -1;

                obj.ball.move(SpeedBall, -0.5);
            }
            //���� ����� ���� ��� ��� ����� �����
            if (BallInGame.y > 800 || endGame > 17) {
                //obj.player.setPosition(400, 750);
               // obj.ball.setPosition(510, 660);
                eventGameStart = 0;
                endGame = 0;
                men.game = false;
                men.menu = true;
            }



            //������� �����
            for (int i = 0; i < 18; i++) {
                if (obj.ball.getGlobalBounds().intersects(obj.block[i].getGlobalBounds())) {
                    ky *= -1;
                    obj.ball.move(SpeedBall, 0.1 * ky);

                    //�������� ����� ���� ����
                    if (i < 6) {
                        //��� �������� �� �������
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
                        //���� � ������� ������
                        //(i % 2 == 0) <---- ��� ���� , ����� � ��������� ����� �� ������� ����.
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

            //�������� � �������� �����
            if (obj.moveGift) {
                obj.gift.move(0, SpeedBall);

                //���� ���� ����������� � �������
                if (obj.gift.getGlobalBounds().intersects(obj.player.getGlobalBounds())) {
                    obj.gift.setPosition(1800, 400);
                    obj.gift.move(0, 0);
                    score += 400;
                }
                //����� �� �������� � ���� ������ �� ����� , �� ������ ���
                Vector2f posGift = obj.gift.getPosition();
                if (posGift.y > 850) {
                    obj.gift.setPosition(1800, 400);
                    obj.gift.move(0, 0);
                }
            }

        }



        //�������� ������
        //�������� ������ �� ����� ���������� � ������
        ostringstream playerScoreString;
        playerScoreString << score;
        //����� � ����������� �����
        text.setString("���� ����:" + playerScoreString.str());





        window.draw(obj.fon);




        //���� ���� true , �� ����� ����
        if (men.menu) {
            window.draw(obj.game);
            window.draw(obj.exit);
        }
        //���� ������ ������ "������"  , �� ������
        if (men.game) {
            window.draw(obj.line);
            for (int i = 0; i < 18; i++) {
                window.draw(obj.block[i]);
            }
            window.draw(obj.ball);
            window.draw(obj.player);
            window.draw(text);
        }
        //���� ������ ������ "������" � ������ ���������� ��� � ����� , �� ����� ����
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