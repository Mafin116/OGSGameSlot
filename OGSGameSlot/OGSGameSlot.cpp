#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>


using namespace std;

sf::RenderWindow window(sf::VideoMode(1000, 500), "SFML works!");



int cellCount = 6;
bool roling = false;
float sizeFigure = 120;

vector<sf::Texture> textures(cellCount);
sf::Clock deltaClock;
sf::Time dt;


void loadTexture()
{
    for (int i = 1; i <= textures.size(); i++)
    {
        string path = "texture/" + to_string(i) + ".png";
        textures[i].loadFromFile(path);
    
    }
}

class Baraban
{
    vector<sf::RectangleShape> baraban;
    
    sf::Vector2f posB;
    bool rotateBool = false;

    void blind()
    {
        sf::RectangleShape up(sf::Vector2f(sizeFigure, sizeFigure ));
        up.setFillColor(sf::Color::Green);
        up.setPosition(posB.x, 0);
        sf::RectangleShape down(sf::Vector2f(sizeFigure, sizeFigure ));
        down.setFillColor(sf::Color::Green);
        down.setPosition(posB.x, window.getSize().y - sizeFigure / 2);
        window.draw(up);
        window.draw(down);
    }

    void draw()
    {
        for (int i = 0; i < baraban.size(); i++)
        {
            baraban[i].setPosition(posB.x, posB.y + (sizeFigure * i + 3 * i));
            window.draw(baraban[i]);
        }
    }

    void rotateBar(float speed = 0.5f)
    {
        speed *= 10;
        for (int i = 0; i < baraban.size(); i++)
        {
            sf::Vector2f pos = baraban[i].getPosition();
            baraban[i].setPosition(posB.x, (pos.y + speed ));
            window.draw(baraban[i]);
            if (pos.y > posB.y + (sizeFigure + 3) * baraban.size())
            {
                baraban[i].setPosition(posB.x, baraban[i-1].getPosition().y - (sizeFigure + 3));
            }
        }

        blind();

    }
public:
    Baraban()
    {
        posB.x = 0;
        posB.y = 0;
        sf::RectangleShape rectangle(sf::Vector2f(sizeFigure, sizeFigure));
        rectangle.setFillColor(sf::Color::White);
        vector<sf::RectangleShape> bb(cellCount, rectangle);
        srand(time(0));
        baraban = bb;
        for (int i = 0; i < baraban.size(); i++)
        {
            baraban[i].setTexture(&textures[rand() % 6]);
        }
        draw();
    }

    Baraban(sf::Vector2f pos)
    {
        posB = pos;
        sf::RectangleShape rectangle(sf::Vector2f(sizeFigure, sizeFigure));
        rectangle.setFillColor(sf::Color::White);
        vector<sf::RectangleShape> bb(cellCount, rectangle);
        baraban = bb;
        for (int i = 0; i < baraban.size(); i++)
        {
            baraban[i].setTexture(&textures[rand() % 7]);
        }
        draw();
    }

    void rotate(bool rotateBool)
    {
        if (rotateBool) 
        {
            rotateBar(rand()%9*.1f);
        }
        else {
            bool next = true;
            for (int i = 0; i < baraban.size(); i++)
            {
                if (baraban[i].getPosition().y > window.getSize().y / 2 - 60 && baraban[i].getPosition().y < window.getSize().y / 2 - 58)
                {
                    rotateBar(0);
                    next = false;
                    break;
                }

            }
            if (next)
            {
                rotateBar(rand() % 9 * .1f);
            }
        }
        
    }

    void set_figure()
    {
    
    }

    void set_position(sf::Vector2f pos)
    {
        posB = pos;
    }
};

class Button
{
    sf::Vector2f size;
    sf::Vector2f position;
    string str = "Text";
    sf::RectangleShape button;

    sf::Text text;
    sf::Font font;
    int fontSize = 25;
    

public:
    Button(sf::Vector2f position, sf::Vector2f size, string strq = "Button")
    {

        button.setSize(size);
        button.setPosition(position);
        button.setFillColor(sf::Color::Green);
        str = strq;
        font.loadFromFile("font.ttf");
        text.setFont(font);
        text.setString(str);
        text.setCharacterSize(fontSize);
        text.setFillColor(sf::Color::White);
        text.setPosition(position.x+size.x/2-fontSize, position.y + size.y / 2-fontSize);
        //text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    }

    bool buttonPressed()
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

            if (button.getGlobalBounds().contains(mousePos.x,mousePos.y))
            {
                button.setFillColor(sf::Color::Blue);
                return true;
                cout << "Pressed" << endl;
            }

            return false;
    }   
    bool buttonReleased()
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);


            if (button.getGlobalBounds().contains(mousePos.x, mousePos.y))
            {
                button.setFillColor(sf::Color::Green);
                return true;
                cout << "Released" << endl;
            }

            return false;
    }

    void draw()
    {
        window.draw(button);
        window.draw(text);
    }

};

class Lines {
    int countLines = 3;
    vector<Baraban> line;

public:
    Lines(int cLine = 3)
    {
        countLines = cLine;
        line = vector<Baraban>(countLines);
        for (int i = 0; i < countLines; i++)
        {
            line[i] = Baraban (sf::Vector2f(30+i*(sizeFigure+20), -120));
        }
    }

    void setLines(int line)
    {
        countLines = line;
    }

    void draw()
    {
        for (int i = 0; i < countLines; i++)
        {
            line[i].rotate(roling);
        }
    }

};



int main()
{
    
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);




    
    loadTexture();

    Lines line(5);
    Button btnStart(sf::Vector2f(700, 150), sf::Vector2f(200, 80), "Start");
    Button btnStop(sf::Vector2f(700, 250), sf::Vector2f(200, 80), "Stop");
    

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();


            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.key.code == sf::Mouse::Left)
                {
                    roling = !btnStart.buttonPressed();
                    roling = !btnStop.buttonPressed();
                }
                
            }
            if (event.type == sf::Event::MouseButtonReleased)
            {
                if (event.key.code == sf::Mouse::Left)
                {
                    roling = !btnStart.buttonReleased();
                    roling = !btnStop.buttonReleased();
                }
            }

        }
        dt = deltaClock.restart();
        window.clear();


        btnStart.draw();
        btnStop.draw();
        line.draw();


        sf::RectangleShape line(sf::Vector2f(650.f, 5.f));
        line.setPosition(sf::Vector2f(0, window.getSize().y / 2 + 60));
        line.setFillColor(sf::Color::Blue);
        sf::RectangleShape line2(sf::Vector2f(650.f, 5.f));
        line2.setPosition(sf::Vector2f(0, window.getSize().y / 2 - 60));
        line2.setFillColor(sf::Color::Blue);
        window.draw(line);
        window.draw(line2);
        
        //window.draw(down);
        window.display();
    }

    return 0;
}
