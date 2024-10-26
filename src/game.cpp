//
// Created by aziz on 10/25/24.
//
#include "game.h"

void Game::init(const std::pair<int, int>& cell) {
    m_initialized = true;

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution uid(0, 1);

    //initialize bombs for some
    for(std::size_t i = 0; i < m_grid.size(); i++) {
        for(std::size_t j = 0; j < m_grid[i].size(); j++) {
            Cell cell = {uid(mt) == 1, false, 0};
            m_grid[i][j] = cell;
        }
    }

    //initialize the number for neighbours who have bombs
    auto check_neighbour = [](int row, int column, auto& grid) {
        unsigned int sum = 0;

        int start_row {std::max(row - 1, 0)};
        int end_row {std::min( row + 1, static_cast<int>(grid.size()) - 1)};

        int start_column{ std::max(column - 1 , 0)};
        int end_column{ std::min(column + 1, static_cast<int>(grid[0].size()) - 1)};

        for(int i = start_row; i <= end_row; i++) {
            for(int j = start_column; j <= end_column; j++) {
                if(grid[i][j].is_bomb) {
                    sum++;
                }
            }
        }

        return sum;
    };
    for(std::size_t i = 0; i < m_grid.size(); i++) {
        for(std::size_t j = 0; j < m_grid[i].size(); j++) {
            m_grid[i][j].content = check_neighbour(i, j, m_grid);
        }
    }

    //make sure doesn't click straightaway on a bomb
    std::pair<int,int> start_index, stop_index;
    start_index.first = std::max(cell.first - 1, 0);
    start_index.second = std::max(cell.second - 1, 0 );

    stop_index.first = std::min(cell.first + 1, static_cast<int>(m_grid.size()) - 1);
    stop_index.second = std::min(cell.second + 1, static_cast<int>(m_grid[0].size()) - 1);

    for(int i = start_index.first; i <= stop_index.first; i++) {
        for(int j = start_index.first; j <= stop_index.second; j++) {
            m_grid[i][j] = {false, false, 0};
        }
    }
}
void Game::display() {
    if(!m_initialized) {
        for(std::size_t i = 0; i < m_grid.size(); i++) {
            for(std::size_t j = 0; j < m_grid[i].size(); j++) {
                std::cout << '*' << ' ';
            }
            std::cout << '\n';
        }
    }
    else {
        for(std::size_t i = 0; i < m_grid.size(); i++) {
            for(std::size_t j = 0; j < m_grid[i].size(); j++) {
                if(m_grid[i][j].is_picked) std::cout << m_grid[i][j].content << ' ';
                else std::cout << '*' << ' ';
            }
            std::cout << '\n';
        }
    }
}
void Game::choose(const std::pair<int, int> &cell) {
    auto& picked_cell = m_grid[cell.first][cell.second];
    if(picked_cell.is_bomb) {
        picked_cell.is_picked = true;
        m_running = false;
        std::cout << "you lost! \n";
        return;
    }
    picked_cell.is_picked = true;
    check();
}
void Game::check() {
    bool winning_cond {true};
    for(std::size_t i = 0; i < m_grid.size(); i++) {
        for(std::size_t j = 0; j < m_grid[i].size(); j++) {
            if(!m_grid[i][j].is_picked) winning_cond = false;
        }
    }

    if(winning_cond) {
        m_running = false;
        std::cout << "you won!!! \n";
    }
}


