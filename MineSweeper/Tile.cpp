#include <SFML/Graphics.hpp>
#include <iostream>
#include "Tile.h"

using namespace std;
using namespace sf;

Tile::Tile()
{
    tileT = new Texture;
    if (!tileT->loadFromFile("images\\tile_hidden.png"))
    {
        cout << "hidden tile didnt load.";
    }
    tileS = new Sprite;

    flagT = new Texture;
    flagT->loadFromFile("images\\flag.png");
    flagS = new Sprite;
    flagS->setTexture(*flagT);
}

void Tile::drawTile(RenderWindow* window, bool debugMode)
{
    tileS->setTexture(*tileT);
    tileS->setPosition(xp, yp);
    window->draw(*tileS);

    // Display flags?
    if (isItFlagged)
    {
        flagS->setPosition(xp, yp);
        window->draw(*flagS);
    }

    // Display mines?
    if ((debugMode && isItMine) or (wasItClicked && isItMine))
    {
        mineS->setTexture(*mineT);
        mineS->setPosition(xp, yp);
        window->draw(*mineS);
    }

    // Display number?
    else if (wasItClicked && mineT && numNearby > 0)
    {
        mineS->setTexture(*mineT);
        mineS->setPosition(xp, yp);
        window->draw(*mineS);
    }
}

void Tile::setX(int x)
{
    xcoord = x;
    xp = 32 * x;
}

void Tile::setY(int y)
{
    ycoord = y;
    yp = 32 * y;
}

void Tile::click()
{
    if (isItFlagged or wasItClicked)
    {
        return;
    }

    wasItClicked = true;

    if (isItMine)
    {
        // todo update texture
        return;
    }

    tileT->loadFromFile("images\\tile_revealed.png");
}

void Tile::setNumNearby(int num)
{
    numNearby = num;
    if (isItMine) // load isItMine texture
    {
        mineT = new Texture;
        mineT->loadFromFile("images\\mine.png");
        mineS = new Sprite;
    }
    else if (numNearby > 0)
    {
        mineT = new Texture;
        mineT->loadFromFile(string("images\\number_") + to_string(num) + ".png");
        mineS = new Sprite;
    }
}

void Tile::flag()
{
    if (wasItClicked)
    {
        return;
    }
    isItFlagged = !isItFlagged;
}