#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "Board.h"


using namespace std;

int main()
{

    int width = 0;
    int height = 0;

    ifstream file;
    file.open(".//boards//config.cfg");

    string line;
    getline(file, line);
    int numColumns = stoi(line);

    getline(file, line);
    int numRows = stoi(line);

    getline(file, line);
    int mineCount = stoi(line);

    width = numColumns * 32;
    height = (numRows * 32) + 88;



    RenderWindow* window = new RenderWindow(VideoMode(width, height), "Minesweeper");
    Board board;
    while (window->isOpen())
    {
        Event event;

        while (window->pollEvent(event))
        {

            if (event.type == Event::Closed)
                window->close();
            else if (event.type == Event::MouseButtonPressed)
            {
                bool leftClick = (event.mouseButton.button == Mouse::Left);
                board.click(event.mouseButton.x, event.mouseButton.y, leftClick);
            }

        }


        window->clear(Color::White);
        //     cout << "1" << endl;
        board.drawBoard(window);
        //      cout << "2" << endl;
        window->display();
        //     cout << "3" << endl;
    }
}