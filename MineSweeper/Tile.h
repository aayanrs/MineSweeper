#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;

class Tile
{
public:
    Tile();

    void drawTile(RenderWindow* window, bool debugMode);
    void click();

    void flag();

    // ==== SETTERS ====
    void setMine(bool val) {
        isItMine = val;
    }
    void setX(int x); // should also calculate xp
    void setY(int y); // should also calculate yp
    void setNumNearby(int num);

    // === GETTERS == 
    bool getClicked() { 
        return wasItClicked; 
    }

    bool getFlagged() { 
        return isItFlagged; 
    }
    bool getMine() { 
        return isItMine; 
    }
    int getX() { 
        return xcoord; 
    }
    int gety() { 
        return ycoord; 
    }

    float getXPixel() { 
        return xp; 
    }
    float getYPixel() {
        return yp; 
    }

    int getNumNearby() { 
        return numNearby; 
    }


private:
    int xcoord;
    int ycoord;

    float xp;
    float yp;

    bool isItMine = false;
    bool isItFlagged = false;
    bool wasItClicked = false;

    int numNearby;

    Texture* tileT;
    Sprite* tileS;

    Texture* mineT; // used for displaying mines and for displaying numbers after wasItClicked
    Sprite* mineS;

    Texture* flagT; // used only for flags
    Sprite* flagS;
};
