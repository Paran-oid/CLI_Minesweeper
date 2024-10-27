//
// Created by aziz on 10/25/24.
//
#include "game.h"

void Game::init(const std::pair<int, int>& cell_cords) {
    m_initialized = true;

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution uid(0, 1);

    //initialize bombs for some
    for(std::size_t i = 0; i < m_grid.size(); i++) {
        for(std::size_t j = 0; j < m_grid[i].size(); j++) {
            Cell cell = {uid(mt) == 1, false, "0"};
            m_grid[i][j] = cell;
        }
    }

    //initialize the number for neighbours who have bombs
    auto check_neighbour = [](int row, int column, auto& grid) {
        int sum = 0;

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

        return std::to_string(sum);
    };

    //make sure doesn't click straightaway on a bomb
    std::pair<int,int> start_index, stop_index;
    start_index.first = std::max(cell_cords.first - 1, 0);
    start_index.second = std::max(cell_cords.second - 1, 0 );

    stop_index.first = std::min(cell_cords.first + 1, static_cast<int>(m_grid.size()) - 1);
    stop_index.second = std::min(cell_cords.second + 1, static_cast<int>(m_grid[0].size()) - 1);

    for(int i = start_index.first; i <= stop_index.first; i++) {
        for(int j = start_index.first; j <= stop_index.second; j++) {
            m_grid[i][j] = {false, false, "0", {i, j}};
        }
    }


    for(std::size_t i = 0; i < m_grid.size(); i++) {
        for(std::size_t j = 0; j < m_grid[i].size(); j++) {
            if(!m_grid[i][j].is_bomb)
                m_grid[i][j].content = check_neighbour(i, j, m_grid);
            else {
                m_grid[i][j].content = 'X';
            }
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
                if(m_grid[i][j].is_picked)std::cout << m_grid[i][j].content << ' ';
                else std::cout << '*' << ' ';
            }
            std::cout << '\n';
        }
    }
}
void Game::choose(const std::pair<int, int> &cell_cords) {
    auto& picked_cell = m_grid[cell_cords.first][cell_cords.second];
    if(picked_cell.is_bomb) {
        picked_cell.is_picked = true;
        m_running = false;
        std::cout << "you lost! \n";
        return;
    }
    dfs(m_grid, cell_cords.first, cell_cords.second,  m_grid.size(), m_grid[0].size());
    check();
}
void Game::dfs(std::vector<std::vector<Cell>>& m_grid, int x, int y, int rows, int cols){
    if(
        x < 0 || x >= rows ||
        y < 0 || y >= cols
        )
        return;

    else if(m_grid[x][y].is_bomb || m_grid[x][y].is_picked) return;

    m_grid[x][y].is_picked = true;
    dfs(m_grid, x - 1, y, rows, cols);
    dfs(m_grid, x + 1, y, rows, cols);
    dfs(m_grid, x, y - 1, rows, cols);
    dfs(m_grid, x, y + 1, rows, cols);
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


