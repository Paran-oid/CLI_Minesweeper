//
// Created by aziz on 10/25/24.
//

#ifndef GAME_H
#define GAME_H

#include <vector>
#include <random>
#include <iostream>

struct Cell {
    std::pair<int,int> cords;
    char content;
    bool is_bomb;
    bool is_picked;
};
class Game {
public:
    //constructors
    explicit Game(int rows = 0, int columns = 0)
        :m_initialized(false), m_running(true)
    {
        if(rows == 0 || columns == 0) {
            std::random_device rd;
            std::mt19937 mt(rd());
            std::uniform_int_distribution uid(5, 50);

            int rows = uid(mt);
            int columns = rows + 10;

            m_grid.resize(rows);
            for(int i = 0; i < m_grid.size(); i++) {
                m_grid[i].resize(columns);
            }
        }
        else {
            m_grid.resize(rows);
            for(auto& row: m_grid) {
                row.resize(columns);
            }
        }
    }

    //methods
    void init(const std::pair<int, int>& cell_cords);
    void choose(const std::pair<int,int>& cell_cords);

    static void dfs(std::vector<std::vector<Cell>>& m_grid, int x, int y, std::size_t rows, std::size_t cols);
    void check();
    void display() const;


    //getters
    [[nodiscard]] bool initialized() const{ return m_initialized;}
    [[nodiscard]] bool running() const {return m_running;}
    [[nodiscard]] int rows() const{return m_grid.size();}
    [[nodiscard]] int cols() const{return m_grid[0].size();}

    //setters
    void run(){m_running = true;}

private:
    std::vector<std::vector<Cell>> m_grid;
    bool m_initialized;
    bool m_running;
};

#endif //GAME_H
