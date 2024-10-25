#include <iostream>
#include <algorithm>
#include <memory>

#include "game.h"

int main(int argc, char const *argv[])
{
    std::cout << "Welcome to Minesweeper! \n"
                 "Do you want to initialize the rows and columns?(Y/N) \n";

    //check if user wants to input his own rows or not
    char choice;
    do {
        std::cin >> choice;
    } while(std::toupper(choice) != 'Y' && std::toupper(choice) != 'N');

    int rows {0};
    int cols {0};
    if(choice == 'Y') {
        do {
            std::cout << "enter rows, then the columns \n";
            std::cin >> rows >> cols;
        }while(rows < 10 || cols < 10);
    }

    auto g{std::make_unique<Game>(rows, cols)};

    while(true) {
        while(g->running()) {
            int row;
            int col;

            g->display();
            do {
                std::cout << "Your input:(row) \n \n";
                std::cin >> row;

                std::cout << "Your input:(col) \n \n";
                std::cin >> col;
            }while

            auto cords = std::pair<int,int>(row, col);

            if(!g->initialized()) {
                g->init(cords);
            }

            g->choose(cords);
        }
        char choice;
        do {
            std::cout << "try again?(Y/N) \n";
            std::cin >> choice;
        } while(std::toupper(choice) == 'Y' || std::toupper(choice) == 'N' );
        if(choice == 'Y') break;
    }
    std::cout << "thank you for trying my game! \n";
}


//MAKE MATRIX NOT SQUARED, IT COULD BE OF DIMENSION 10 15/20 ETC, PREFERABLY COLUMNS MUST BE BIGGER THAN ROWS BY 10 COLUMNS AT LEAST
//MAKE GETTER FOR WIDTH
//USE WHAT I LEARNED FROM ALL THE TUTORIALS