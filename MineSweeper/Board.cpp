#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include "Board.h"

using namespace std;
using namespace sf;

void Board::setColumn(int column, int input) {
    column = input / 32;

}

void Board::setRow(int row, int input) {
    row = input / 32;

}

void Board::mathForDigits(int a, int b, int c, int d)
{
    if (0 <= a and a <= 9)
    {
        b = 0;
        c = 0;
        d = a;

    }

    else if (10 <= a and a <= 99) {
        b = 0;
        c = a / 10;
        d = a % 10;
    }

    else if (100 <= a) {
        b = a / 100;
        c = (a / 10) % 10;
        d = a % 100;
    }
}


void Board::rawr(string filename, map<int, int> setMap)
{
    reset();
    map<int, int> setMap2 = readMinesIn(filename);
    placeMines(setMap2);
    surroundingMines();
}

void Board::SetDigits(int ones, int tens, int hundreds) {
    digit1->setTextureRect(IntRect(21 * ones, 0, 21, 32));
    digit1->setPosition(3 * 21, 512);

    digit2->setTextureRect(IntRect(21 * tens, 0, 21, 32));
    digit2->setPosition(2 * 21, 512);

    digit3->setTextureRect(IntRect(21 * hundreds, 0, 21, 32));
    digit3->setPosition(21, 512);
}

void Board::drawBoard(RenderWindow* window)
{


    for (auto& tile : blocks) {
        for (unsigned int j = 0; j < 16; j++)
        {
            tile[j]->drawTile(window, openSquare);
        }
    }


    mainReset->setPosition(368, 512);
    if (lost)
    {
        mainReset->setTexture(*sadFace);
    }
    else if (won)
    {

        mainReset->setTexture(*winFace);
    }
    else {
        mainReset->setTexture(*normalFace);
    }
    window->draw(*mainReset);


    dbgS->setTexture(*dbgT);
    dbgS->setPosition(496, 512);
    window->draw(*dbgS);


    tS1->setTexture(*tT1);
    tS1->setPosition(496+64, 512);
    window->draw(*tS1);

    tS2->setTexture(*tT2);
    tS2->setPosition(496+64+64, 512);
    window->draw(*tS2);

    tS3->setTexture(*tT3);
    tS3->setPosition(496+64+64+64, 512);
    window->draw(*tS3);


    int outputVal = totalMines - flagCounter;

    int hundredsDigit = 0, tensDigit = -1, thirdDigit = -1;

    mathForDigits(outputVal, hundredsDigit, tensDigit, thirdDigit);

    if (0 <= outputVal and outputVal <= 9)
    {
        hundredsDigit = 0;
        tensDigit = 0;
        thirdDigit = outputVal;

    }

    else if (10 <= outputVal and outputVal <= 99) {
        hundredsDigit = 0;
        tensDigit = outputVal / 10;
        thirdDigit = outputVal % 10;
    }

    else if (100 <= outputVal) {
        hundredsDigit = outputVal / 100;
        tensDigit = (outputVal / 10) % 10;
        thirdDigit = outputVal % 100;
    }

    if (flagCounter < 0)
    {


        if (0 <= outputVal and outputVal <= 9)
        {
            hundredsDigit = 0;
            tensDigit = 0;
            thirdDigit = outputVal;

        }

        else if (10 <= outputVal and outputVal <= 99) {
            hundredsDigit = 0;
            tensDigit = outputVal / 10;
            thirdDigit = outputVal % 10;
        }

        else if (100 <= outputVal) {
            hundredsDigit = outputVal / 100;
            tensDigit = (outputVal / 10) % 10;
            thirdDigit = outputVal % 100;
        }


        if (hundredsDigit >= vectorT.size()) {
            hundredsDigit = vectorT.size() - 1;
        }


        digit1->setTexture(*vectorT[hundredsDigit]);
        digit1->setPosition(21, 512);
        window->draw(*digit1);


        if (tensDigit != -1)
        {
            digit2->setTexture(*vectorT[tensDigit]);
            digit2->setPosition(42, 512);
            window->draw(*digit2);

        }


        if (thirdDigit != -1)
        {
            digit3->setTexture(*vectorT[thirdDigit]);
            digit3->setPosition(63, 512);
            window->draw(*digit3);
        }

    }


    if (hundredsDigit >= vectorT.size()) {
        hundredsDigit = vectorT.size() - 1;
    }


    digit1->setTexture(*vectorT[hundredsDigit]);
    digit1->setPosition(21, 512);
    window->draw(*digit1);


    if (tensDigit != -1)
    {
        digit2->setTexture(*vectorT[tensDigit]);
        digit2->setPosition(42, 512);
        window->draw(*digit2);

    }


    if (thirdDigit != -1)
    {
        digit3->setTexture(*vectorT[thirdDigit]);
        digit3->setPosition(63, 512);
        window->draw(*digit3);
    }


}

Tile* Board::getTile(int x, int y)
{
    return blocks[x][y];
}

void Board::click(int width, int height, bool leftClick)
{
    if (height < 512 and leftClick)
    {
        int column = 0;
        int row = 0;
        setColumn(column, width);
        setRow(row, height);
        inputBlock(column, row);
        winCheck();
    }
    else if (height < 512 and !leftClick) // RIGHT CLICK
    {
        int column = 0;
        int row = 0;
        setColumn(column, width);
        setRow(row, height);
        Tile* tile = blocks[column][row];
        if (tile->getClicked() or won or lost) {
            return; //exit the void function
        }
        tile->flag();
        if (tile->getFlagged()) {
            flagCounter++;
        }
        else {
            flagCounter--;
            totalMines--;
        }
        winCheck();
    }
    else if (width >= 368 and width <= 432 and height >= 512 and height <= 512+64 and left)
    {
        reset();
        map<int, int> setMap = randXD();
        placeMines(setMap);
        surroundingMines();
    }
    else if (width >= 496 and width <= 496+64 and height >= 512 and height <= 512+64 and left)
    {
        openSquare = !openSquare;
    }
    else if (width >= 496+64 and width <= 496+64+64 and height >= 512 & height < 512+64 and left) 
    {
        /*   reset();
           map<int, int> setMap = readMinesIn(".//boards//testboard1.brd");
           placeMines(setMap);
           surroundingMines();
           */
        map<int, int> setMap;

        rawr(".//boards//testboard1.brd", setMap);
    }
    else if (width >= 496+64+64 and width <= 496+64+64+64 and height >= 512 and height < 512+64 and left) 
    {

        map<int, int> setMap;

        /*    for (map<int,int>::iterator it = setMap.begin(); it != setMap.loser(); ++it)
            {
                cout << (*it).hundredsDigit << ": " << (*it).tensDigit << endl;
            }
            */


            //    cout << "1" << endl;

        //    cout << "2" << endl;

        //     cout << "3 " << endl;

        rawr(".//boards//testboard2.brd", setMap);
    }
    else if (width >= 496+64+64+64 and height >= 512 and height < 512+64 and left) 
    {

        map<int, int> setMap;


        rawr(".//boards//testboard3.brd", setMap);
    }
}

void Board::inputBlock(int column, int row)
{
    Tile* tile = blocks[column][row];

    if (tile->getClicked() or won or lost or tile->getFlagged())
    {
        return;
    }

    tile->click();
    clickedMines++;
    if (tile->getMine())
    {
        loser();
    }

    int nearbyMines = blocks[column][row]->getNumNearby();
    if (nearbyMines == 0) 
    {
        if (column > 0)
        {
            inputBlock(column - 1, row);
        }
        if (column < 24)
        {
            inputBlock(column + 1, row);
        }
        if (row > 0)
        {
            inputBlock(column, row - 1);
        }
        if (row < 15)
        {
            inputBlock(column, row + 1);
        }
        if (column > 0 and row > 0)
        {
            inputBlock(column - 1, row - 1);
        }
        if (column > 0 and row < 15)
        {
            inputBlock(column - 1, row + 1);
        }
        if (column < 24 and row > 0)
        {
            inputBlock(column + 1, row - 1);
        }
        if (column < 24 and row < 15)
        {
            inputBlock(column + 1, row + 1);
        }
    }
}

void Board::winCheck()
{
    if (flagCounter == totalMines and clickedMines + flagCounter == 400)
    {
        won = true;
    }
}

void Board::loser()
{
    lost = true;
}

Board::Board()
{
    normalFace = new Texture;
    sadFace = new Texture;
    winFace = new Texture;
    mainReset = new Sprite;

    normalFace->loadFromFile("images\\face_happy.png");
    sadFace->loadFromFile("images\\face_lose.png");
    winFace->loadFromFile("images\\face_win.png");



    dbgT = new Texture;
    dbgS = new Sprite;
    dbgT->loadFromFile("images\\debug.png");

    tT1 = new Texture;
    tS1 = new Sprite;
    tT1->loadFromFile("images\\test_1.png");

    tT2 = new Texture;
    tS2 = new Sprite;
    tT2->loadFromFile("images\\test_2.png");

    tT3 = new Texture;
    tS3 = new Sprite;
    tT3->loadFromFile("images\\test_3.png");


    digit1 = new Sprite;
    digit2 = new Sprite;
    digit3 = new Sprite;
    sb0 = new Texture;
    sb0->loadFromFile("images\\digits.png", Rect<int>(0, 0, 21, 32));
    sb1 = new Texture;
    sb1->loadFromFile("images\\digits.png", Rect<int>(21, 0, 21, 32));
    sb2 = new Texture;
    sb2->loadFromFile("images\\digits.png", Rect<int>(42, 0, 21, 32));
    sb3 = new Texture;
    sb3->loadFromFile("images\\digits.png", Rect<int>(63, 0, 21, 32));
    sb4 = new Texture;
    sb4->loadFromFile("images\\digits.png", Rect<int>(84, 0, 21, 32));
    sb5 = new Texture;
    sb5->loadFromFile("images\\digits.png", Rect<int>(105, 0, 21, 32));
    sb6 = new Texture;
    sb6->loadFromFile("images\\digits.png", Rect<int>(126, 0, 21, 32));
    sb7 = new Texture;
    sb7->loadFromFile("images\\digits.png", Rect<int>(147, 0, 21, 32));
    sb8 = new Texture;
    sb8->loadFromFile("images\\digits.png", Rect<int>(168, 0, 21, 32));
    sb9 = new Texture;
    sb9->loadFromFile("images\\digits.png", Rect<int>(189, 0, 21, 32));
    vectorT.push_back(sb0);
    vectorT.push_back(sb1);
    vectorT.push_back(sb2);
    vectorT.push_back(sb3);
    vectorT.push_back(sb4);
    vectorT.push_back(sb5);
    vectorT.push_back(sb6);
    vectorT.push_back(sb7);
    vectorT.push_back(sb8);
    vectorT.push_back(sb9);
    unsigned int x=0;
    
    for (x; x < 25; x++)
    {
        for (unsigned int y =0; y < 16; y++) // program breaks for some reason when unsigned int y is taken out, doesnt really matter
        {
            blocks[x][y] = new Tile;
            blocks[x][y]->setX(x);
            blocks[x][y]->setY(y);
        }
    }


    map<int, int> setMap = randXD();
    placeMines(setMap);

    surroundingMines();
}

void Board::reset()
{
    totalMines = 0;
    clickedMines = 0;
    flagCounter = 0;
    lost = false;
    won = false;

    // delete them to clear
    for (auto& tile : blocks) {
        for (auto& j : tile) {
            delete j;
        }
    }
    unsigned int x = 0;
    
    for (x; x < 25; x++)
    {
        for (unsigned int y = 0; y < 16; y++)
        {
            blocks[x][y] = new Tile;
            blocks[x][y]->setX(x);
            blocks[x][y]->setY(y);
        }
    }
}

map<int, int> Board::randXD()
{
    map<int, int> returnMap;

    unsigned int i = 0;
    for (i; i < 400; i++)
    {
        returnMap[i] = 0;
    }
    int temp = 0;
    while (temp < 50)
    {
        int temp2 = rand() % 400;
        if (returnMap[temp2] == 0)
        {
            temp++;
            returnMap[temp2] = 1;
        }
    }

    return returnMap;
}

map<int, int> Board::readMinesIn(string filepath)
{
    map<int, int> returnMap;
    ifstream file(filepath);
    string line;

    int index = 0;
    for (unsigned int i = 0; i < 16; i++)
    {
        getline(file, line);
        for (unsigned int j = 0; j < 25; j++)
        {
            int mineInFile = stoi(line.substr(j, 1));
            returnMap[index] = mineInFile;
            index++;
        }
    }
    return returnMap;
}

void Board::placeMines(map<int, int> setMap)
{
    // set up mines
    for (unsigned int column = 0; column < 25; column++)
    {
        for (unsigned int row = 0; row < 16; row++)
        {
            Tile* tile = blocks[column][row];
            int mine = row * 25 + column;
            tile->setMine(setMap[mine] != 0);
            if (setMap[mine] == 1) totalMines++;
        }
    }
}

void Board::minesToFlags(map<int, int>setMap)
{
    // make this
}

void Board::surroundingMines()
{
    for (unsigned int column = 0; column < 25; column++)
    {
        for (unsigned int row = 0; row < 16; row++)
        {
            // calculate the number of blocks around this one
            int nearbyMine = 0;
            if (column > 0)
            {
                if (blocks[column - 1][row]->getMine()) nearbyMine++;
            }
            if (column < 24)
            {
                if (blocks[column + 1][row]->getMine()) nearbyMine++;
            }
            if (row > 0)
            {
                if (blocks[column][row - 1]->getMine()) nearbyMine++;
            }
            if (row < 15)
            {
                if (blocks[column][row + 1]->getMine()) nearbyMine++;
            }
            if (column > 0 and row > 0)
            {
                if (blocks[column - 1][row - 1]->getMine()) nearbyMine++;
            }
            if (column > 0 and row < 15)
            {
                if (blocks[column - 1][row + 1]->getMine()) nearbyMine++;
            }
            if (column < 24 and row > 0)
            {
                if (blocks[column + 1][row - 1]->getMine()) nearbyMine++;
            }
            if (column < 24 and row < 15)
            {
                if (blocks[column + 1][row + 1]->getMine()) nearbyMine++;
            }
            blocks[column][row]->setNumNearby(nearbyMine);
        }
    }
}