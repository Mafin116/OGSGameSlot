#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>


using namespace std;

sf::RenderWindow window(sf::VideoMode(1000, 500), "SFML works!");


bool start = false;
int cellCount = 6;
bool roling = false;
sf::Clock timerSt;
sf::Clock timerRoll;
int timeToStop = 4;

float sizeFigure = 120;

vector<sf::Texture> textures(cellCount);
sf::Clock deltaClock;



void loadTexture()
{
    for (int i = 1; i <= textures.size(); i++)
    {
        string path = "texture/" + to_string(i) + ".png";
        textures[i-1].loadFromFile(path);
    
    }
}

void text()
{
    sf::Text text;
    sf::Font font;
    int fontSize = 25;
}

class Baraban
{
    vector<sf::RectangleShape> baraban;
    
    sf::Vector2f posB;
    bool rotateBool = false;
    bool next = false;

    void blind()
    {
        sf::RectangleShape up(sf::Vector2f(sizeFigure, sizeFigure * 0.7f));
        up.setFillColor(sf::Color::Black);
        up.setPosition(posB.x, 0);
        sf::RectangleShape down(sf::Vector2f(sizeFigure, sizeFigure * 0.7f));
        down.setFillColor(sf::Color::Black);
        down.setPosition(posB.x, window.getSize().y - sizeFigure *0.7f);
        window.draw(up);
        window.draw(down);
    }

    void rotateBar(float speed = 0.5f)
    {
        speed *= 10;
        for (int i = 0; i < baraban.size(); i++)
        {
            sf::Vector2f pos = baraban[i].getPosition();
            baraban[i].setPosition(posB.x, (pos.y + speed));
            window.draw(baraban[i]);
            if (pos.y > posB.y + (sizeFigure + 3) * baraban.size())
            {
                if (i + 1 == baraban.size())
                {
                    baraban[i].setPosition(posB.x, baraban[0].getPosition().y - (sizeFigure + 3));
                }
                else {
                    baraban[i].setPosition(posB.x, baraban[i + 1].getPosition().y - (sizeFigure + 3));
                }
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
            baraban[i].setTexture(&textures[rand() % 6]);
        }
        draw();
    }

    void draw()
    {
        for (int i = 0; i < baraban.size(); i++)
        {
            baraban[i].setPosition(posB.x, posB.y + (sizeFigure * i + 3 * i)+67);
            window.draw(baraban[i]);
        }
        blind();
    }

    void rotate(bool rotateBool)
    {
        float speed;
        
        if (timerSt.getElapsedTime().asSeconds() < 0.7f)
        {
            speed = timerSt.getElapsedTime().asSeconds() * 2.5 * (rand() % 9) * 0.1f;
        }
        else {
            speed = 0.5f * 3 * (rand() % 9) * 0.1f;
        }
        if (rotateBool) 
        {
            rotateBar(speed);

        }
        else {
            next = true;
            for (int i = 0; i < baraban.size(); i++)
            {
                if (baraban[i].getPosition().y > window.getSize().y / 2 - 61 && baraban[i].getPosition().y < window.getSize().y / 2 - 56)
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

    void setFigure()
    {
    
    }

    void setPosition(sf::Vector2f pos)
    {
        posB = pos;
    }

    int size()
    {
        return baraban.size();
    }

    sf::Vector2f getPosition(int i)
    {
        return baraban[i].getPosition();
    }

    sf::Texture getFigure(int i)
    {
        return *baraban[i].getTexture();
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
        button.setFillColor(sf::Color(200,200,200,230));
        str = strq;
        font.loadFromFile("font.ttf");
        text.setFont(font);
        text.setString(str);
        text.setCharacterSize(fontSize);
        text.setFillColor(sf::Color::Black);
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
                button.setFillColor(sf::Color(240, 240, 240, 230));
                return true;
                cout << "Released" << endl;
            }

            return false;
    }

    void setText(string txt)
    {
        text.setString(txt);
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
            line[i].draw();
        }
    }

    void roll()
    {
        for (int i = 0; i < countLines; i++)
        {
            
            line[i].rotate(roling);
        }
    }

    vector<int> getCombination()
    {
        vector<int> combine (line.size());
        for (int i = 0; i < line.size(); i++)
        {
            for (int j = 0; j < line[i].size(); j++)
            {
                if (line[i].getPosition(j).y > window.getSize().y / 2 - 63 && line[i].getPosition(j).y < window.getSize().y / 2 - 56)
                {
                    sf::Texture q = line[i].getFigure(j);
                    for (int obb = 0; textures.size() >= obb; obb++)
                    {
                        sf::Vector2u sz = (textures[obb].copyToImage().getSize());
                        
                        sf::Color w = textures[obb].copyToImage().getPixel(sz.x / 2, sz.y / 2);
                        sf::Color e = q.copyToImage().getPixel(sz.x / 2, sz.y / 2);

                        if (textures[obb].copyToImage().getPixel(sz.x/2,sz.y/2) == q.copyToImage().getPixel(sz.x / 2, sz.y / 2))
                        {
                            combine[i] = ++obb;
                            cout << obb;
                            break;
                        }
                    }
                    
                }
            }
        }
        cout << endl;
        return combine;
    }
    string winScore()
    {
        int max = 0;
        vector<int> comb = getCombination();
        for (int i = 0; i < countLines; i++)
        {
            int now = 0;
            for (int j = 0; j < countLines; j++)
            {
                if (comb[i] == comb[j])
                    now++;
            }
            if (now > max)
                max = now;
        }
        
        if (max < countLines)
        {
            return to_string(max) + " / " + to_string(countLines);
        }
        else {
            return "You Win";
        }
    }

};


void lineBar()
{
    sf::RectangleShape line1(sf::Vector2f(750.f, 7.f));
    line1.setPosition(sf::Vector2f(0, window.getSize().y / 2 + 60));
    line1.setFillColor(sf::Color::Black);
    sf::RectangleShape line2(sf::Vector2f(750.f, 7.f));
    line2.setPosition(sf::Vector2f(0, window.getSize().y / 2 - 67));
    line2.setFillColor(sf::Color::Black);
    window.draw(line1);
    window.draw(line2);
}

class TimeRoll
{
    sf::RectangleShape lineTimer;
public:
    TimeRoll()
    {
        lineTimer = sf::RectangleShape(sf::Vector2f(1000.f, 10.f));
        lineTimer.setPosition(sf::Vector2f(0, 20));
        lineTimer.setFillColor(sf::Color::Red);
        window.draw(lineTimer);
    }
    void print()
    {
        lineTimer.setSize(sf::Vector2f(1000, 10.f));
        lineTimer.setPosition(sf::Vector2f(0, 20));
        lineTimer.setFillColor(sf::Color(200, 45, 0, 0));
        window.draw(lineTimer);
    }
    void start()
    {
        lineTimer.setSize(sf::Vector2f(1000 - (1000 / timeToStop * timerRoll.getElapsedTime().asSeconds()), 10.f));
        lineTimer.setPosition(sf::Vector2f(0, 20));
        lineTimer.setFillColor(sf::Color(200,45,0,255/timeToStop * timerRoll.getElapsedTime().asSeconds()));
        window.draw(lineTimer);
    }

};



int main()
{
    sf::Time dt;
    sf::Clock timer;

    bool banner = true;
    bool visible = false;
    bool spamVisible = true;

    
    loadTexture();

    Lines line(4);
    Button btnStart(sf::Vector2f(750, 150), sf::Vector2f(200, 80), "Start");
    Button btnStop(sf::Vector2f(750, 250), sf::Vector2f(200, 80), "Stop");

    Button btnWin(sf::Vector2f(250, 150), sf::Vector2f(400, 200), "Win");

    TimeRoll timerr;
    

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
                    
                        
                    if (btnStart.buttonPressed())
                    {
                        if (!roling) {
                            timerSt.restart();
                            timerRoll.restart();
                        }
                        roling = true;
                        start = true;
                        visible = false;
                    }
                    if (btnStop.buttonPressed())
                    {
                        if (roling)
                        {
                            timer.restart();
                            roling = false;
                            visible = true;
                        }
                    }
                    if (btnWin.buttonPressed())
                    {
                        banner = true;
                        visible = false;
                    }
                    

                }
                    
                
            }
            if (event.type == sf::Event::MouseButtonReleased)
            {
                if (event.key.code == sf::Mouse::Left)
                {
                    btnStart.buttonReleased();
                    btnStop.buttonReleased();
                    btnWin.buttonReleased();
                }
            }

        }
        
        window.clear();


        btnStart.draw();
        btnStop.draw();
        if (start){ line.roll(); }
        else { line.draw(); }
        
        
        if (roling)
        {
            timerr.start();
        }
        else {
            timerr.print();
        }
        
        if(timerRoll.getElapsedTime().asSeconds() > timeToStop && roling == true)
        { 
            timer.restart();
            roling = false;
            visible = true;
        }

        lineBar();

        if (start && !roling && timer.getElapsedTime().asSeconds() >= 1 && visible)
        {
            if (banner)
            {
                btnWin.setText(line.winScore());
                banner = false;
            }
            btnWin.draw();
        }
        
        
        window.display();
    }

    return 0;
}
