#include <iostream>
#include <algorithm>
#include <memory>

#include "game.h"
#include <SFML/Graphics.hpp>

int main(int argc, char const *argv[])
{
        std::cout << "Welcome to Minesweeper! \n"
                    "Do you want to initialize the rows?(Y/N) \n";
        //check if user wants to input his own rows or not
        char choice;
        do {
            std::cin >> choice;
        } while(std::toupper(choice) != 'Y' && std::toupper(choice) != 'N');

        int rows {0};
        int cols {0};
        if(choice == 'Y') {
            do {
                std::cout << "enter the number of rows\n";
                std::cin >> rows;
                cols = rows + 10;
            }while(rows < 5);
        }

        auto g{std::make_unique<Game>(rows, cols)};
        rows = g->rows();
        cols = g->cols();

        int row;
        int col;

        while(true) {
            while(g->running()) {
                g->display();
                do {
                    std::cout << "Your input:(row) \n \n";
                    std::cin >> row;

                    std::cout << "Your input:(col) \n \n";
                    std::cin >> col;
                }while(row >= rows || row < 0 || col >= cols || col < 0);

                auto cords = std::pair<int,int>(row, col);

                if(!g->initialized()) {
                    g->init(cords);
                }

                g->choose(cords);
            }
            do {
                std::cout << "try again?(Y/N) \n";
                std::cin >> choice;
            } while(std::toupper(choice) != 'Y' && std::toupper(choice) != 'N' );
            if(choice == 'N') break;
            g->run();
        }
        std::cout << "thank you for trying my game! \n";
}

