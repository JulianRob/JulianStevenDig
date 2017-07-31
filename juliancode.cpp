#include "SFML/Graphics.hpp"
#include <iostream>
#include <string>
#include "player.h"
#include "ground.h"
//#include "ResourcePath.hpp"

#include <windows.h>
using namespace std;

int tile1 = 14; //if tile1 = 0, then 1 tile will be created. If tile1 = 1, then 2 tiles will be created. Every 5 tiles a new row is created.
int counting = 0;

void doBoundariesStuff();
void doAnimationStuff(int);
player steven;
ground layer1[15]; //must be plus 1 of tile1


std::string getexepath()
{
  char result[ MAX_PATH ];
  return std::string( result, GetModuleFileName( NULL, result, MAX_PATH ) );
}


int main()
{
string imagePath = getexepath();
    imagePath = imagePath.substr(0,imagePath.find_last_of("\\"));
    imagePath = imagePath.substr(0,imagePath.find_last_of("\\"));
    imagePath = imagePath.substr(0,imagePath.find_last_of("\\"));
    imagePath = imagePath + "\\images\\";

    steven.loadTexture(imagePath + "SurfaceSpriteSheet1.png");
    steven.updateTexture(10000);
    steven.sprite.setScale(8,8);

    for(int x = 0; x <= tile1; x++)
    {
        layer1[x].loadTexture(imagePath + "ground.png");
    }

    for(int x = 0; x <=tile1; x++)
    {
        layer1[x].sprite.setScale(8,8);
    }

	sf::RenderWindow window(sf::VideoMode(600, 600), "Surface");
	window.setFramerateLimit(60);

	sf::Clock clock;

	while (window.isOpen())
	{
    	sf::Event event;

    	while (window.pollEvent(event))
    	{
        	if (event.type == sf::Event::Closed)
            	window.close();
    	}

    	sf::Time time = clock.getElapsedTime();

    	steven.lx = steven.x;
    	steven.ly = steven.y;

    	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    	{
        	steven.sprite.move(sf::Vector2f(-1*steven.base_speed * time.asMilliseconds(), 0));
        	steven.setFacing(true);
    	}

    	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    	{
        	steven.sprite.move(sf::Vector2f(0, -1*steven.base_speed * time.asMilliseconds()));
    	}

    	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    	{
        	steven.sprite.move(sf::Vector2f(0, steven.base_speed * time.asMilliseconds()));
    	}

    	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    	{
        	steven.sprite.move(sf::Vector2f(steven.base_speed * time.asMilliseconds(), 0));
        	steven.setFacing(false);
    	}

    	//update his position variables
    	steven.x = steven.sprite.getPosition().x;
    	steven.y = steven.sprite.getPosition().y;

    	doBoundariesStuff();
    	doAnimationStuff(time.asMilliseconds());

    	clock.restart().asMilliseconds();

    	window.clear();

        for(int x = 0; x <= tile1; x++)
        {
            window.draw(layer1[x].sprite);
        }

    	window.draw(steven.sprite);

        for(int y = 300; y <=(300+(3*128)); y+=128) //3 is the # of rows
        {
            for(int x = 64; x <= (5) * 128; x+=128) //5 is the # of tiles per row
            {
                layer1[counting].sprite.setPosition(x,y);
                counting+=1;
            }
        }
        counting = 0;

    	window.display();

	}
}

void doBoundariesStuff() {
float width = steven.texture.getSize().x; //170?
float height = steven.texture.getSize().y; //289 pixels tall? Did you scale the sprite up by 4? 56 pixels works

std::cout << width << endl;

//player
if (steven.x < steven.width*4) steven.setPosition(steven.width*4,steven.y);
if (steven.x > 600 - steven.width*4) steven.setPosition(600 - steven.width*4,steven.y);
if (steven.y < steven.height*4) steven.setPosition(steven.x,steven.height*4);
if (steven.y > 600 - steven.height*4) steven.setPosition(steven.x,600 - steven.height*4);



}

void doAnimationStuff(int elapsed) {
steven.updateTexture(elapsed);

}


