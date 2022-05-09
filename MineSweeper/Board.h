#pragma once

#include <SFML/Graphics.hpp>
#include "Tile.h"

using namespace std;
using namespace sf;

class Board
{
public:
    Board();
    void setColumn(int column, int input);
    void setRow(int row, int input);
    void click(int positionx, int positiony, bool leftClick);
    void inputBlock(int positionx, int positiony);

    Tile* getTile(int positionx, int positiony);

    void drawBoard(RenderWindow* window);

    void mathForDigits(int a, int b, int c, int d);

    void rawr(string filename, map<int, int> setMap);

private:
    map<int, int> randXD();
    map<int, int> readMinesIn(string filepath);
    void placeMines(map<int, int> setMap);
    void surroundingMines();

    void winCheck();

    int num3;
    int num4;

    Tile* blocks[25][16];

    int totalMines = 0;
    int clickedMines = 0;
    int flagCounter = 0;

    bool lost = false;
    bool won = false;
    void loser();
    void reset();

    void minesToFlags(map<int, int> setMap);

    void SetDigits(int ones, int tens, int hundreds);

    bool openSquare = false;

    // sprites
    Texture* normalFace;
    Texture* sadFace;
    Texture* winFace;
    Sprite* mainReset;

    Texture* dbgT;
    Sprite* dbgS;

    Texture* tT1;
    Sprite* tS1;

    Texture* tT2;
    Sprite* tS2;

    Texture* tT3;
    Sprite* tS3;

    Texture* sb0;
    Texture* sb1;
    Texture* sb2;
    Texture* sb3;
    Texture* sb4;
    Texture* sb5;
    Texture* sb6;
    Texture* sb7;
    Texture* sb8;
    Texture* sb9;

    Sprite* digit1;
    Sprite* digit2;
    Sprite* digit3;
    Sprite* digitNeg;

    vector<Texture*> vectorT;
};