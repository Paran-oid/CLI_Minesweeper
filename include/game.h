//
// Created by aziz on 10/25/24.
//

#ifndef GAME_H
#define GAME_H

#include <vector>
#include <random>
#include <iostream>

struct Cell {
    bool is_bomb;
    bool is_picked;
    unsigned int content;
};

class Game {
public:
    //constructors
    Game(int rows = 0, int columns = 0)
        :m_initialized(false), m_running(true)
    {
        if(rows == 0 || columns == 0) {
            std::random_device rd;
            std::mt19937 mt(rd());
            std::uniform_int_distribution uid(10, 50);

            int rows = uid(mt);
            int columns = uid(mt);

            m_grid.resize(rows);
            for(int i = 0; i < m_grid.size(); i++) {
                m_grid[i].resize(columns);
            }
        }
        else {
            m_grid.resize(rows);
            for(int i = 0; i < m_grid.size(); i++) {
                m_grid[i].resize(columns);
            }
        }
    }

    //methods
    void display();
    void init(const std::pair<int, int>& cell);
    void choose(const std::pair<int,int>& cell);
    void check();

    //getters and setters
    bool initialized() const{ return m_initialized;}
    bool running() const {return m_running;}

private:
    std::vector<std::vector<Cell>> m_grid;
    bool m_initialized;
    bool m_running;
};

#endif //GAME_H
