#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#include <string.h>
#include <vector>
using namespace std;


string get_random_char(){
    string s;
    s.push_back(rand() % 96);
    return s;
}

int main()
{       
    sf::RenderWindow window(sf::VideoMode(1400, 800), "Matrix");

    int lowest[70] = {0};
    int lifetime = 33;
    string particles[70][40] = {{" "}};
    int particleLifeTime [70][40];
    memset(particleLifeTime, lifetime, sizeof(particleLifeTime));

    sf::Text text;
    sf::Font font;
    font.loadFromFile("font.ttf");
    text.setFont(font);
    text.setCharacterSize(20);


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        for(int i = 0; i < 70; ++i){
            if(lowest[i] != 0){ 
                //if there is already a character on this line,
                for(int a = 0; a < 40; ++a){
                    text.setPosition(sf::Vector2f(20*i, 20*a));
                    text.setStyle(sf::Text::Regular);
                    text.setFillColor(sf::Color::Green);

                    if (particleLifeTime[i][a] <= 8){
                        int alpha = max(0, particleLifeTime[i][a] * 25);
                        text.setFillColor(sf::Color(0, 255, 0, alpha));
                        if(particleLifeTime[i][a] == 0 && a >= 38){
                            lowest[i] = 0;  //free the column for drawing
                            particles[i][a] = "";
                        }
                    }
                    text.setString(particles[i][a]);
                    window.draw(text);
                    particleLifeTime[i][a]--;
                }
                if(rand() % 3 < 2 && lowest[i] < 40 && i < 69){     
                    //create new particle at the bottom of the line 
                    text.setPosition(sf::Vector2f(20*i, lowest[i] * 20));
                    text.setFillColor(sf::Color::White);
                    text.setStyle(sf::Text::Bold);
                    string outp = get_random_char(); 
                    text.setString(outp);
                    particles[i][lowest[i]] = outp;
                    window.draw(text);
                    lowest[i]++;
                    particleLifeTime[i][lowest[i]] = lifetime;
                }
            }
            else{   
                //create new particle at the top of an empty line
                if(rand() % 68 <= 1){
                    text.setPosition(sf::Vector2f(i*30, 0));
                    text.setFillColor(sf::Color::White);
                    text.setStyle(sf::Text::Bold);
                    string outp = get_random_char(); 
                    text.setString(outp);
                    particles[i][0] = outp;
                    lowest[i] = 1;
                    particleLifeTime[i][0] = lifetime;
                }
            }
        }

        sf::sleep(sf::milliseconds(32));

        window.display();
        window.clear();
    }
    return 0;
}