#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

//����� ��� ��������
class Object {
public:
    Sprite fon, game, exit , block[18] , player , ball;

    RectangleShape line;
};

//Menu
class Menu {
public:
    bool menu = true;
    bool game = false;
 };



int main()
{
    double kx = 0;
    double ky = 0;
    double SpeedBoard = 0.2;
    double SpeedBall = 0.09;

    int eventGameStart = 0;

    //�������� ���� ���������
    RenderWindow window(VideoMode(1200, 800), "Arcanoid");

    Object obj;
    Menu men;

    //���
    Texture t1, t2, t3, t4, t5, t6;
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
            obj.block[j * 6 + i].setTextureRect(IntRect(0, 0, 140, 26));
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
                        if (eventGameStart == 0 ) {
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
                //���� ����� ����
                if (BallInGame.y > 800) {
                    obj.player.setPosition(400, 750);
                    obj.ball.setPosition(510, 660);
                    eventGameStart = 0;
                }


                
                for (int i = 0; i < 18; i++) {
                    if (obj.ball.getGlobalBounds().intersects(obj.block[i].getGlobalBounds())) {
                        ky *= -1;
                        obj.ball.move(SpeedBall, 0.1 * ky);

                        obj.block[i].setPosition(1300, 0);
                    }
                }
            }
        






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
        }

        window.display();

    }
 
  

    return 0;
}
