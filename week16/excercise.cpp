#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <fstream>

struct Board {
    std::vector<bool> cells;
    std::size_t width;
    std::size_t height;
};

void print_board(const Board& board) {
    
        for(size_t i = 0; i < board.height; i++){

            for(size_t x = 0; x < board.width; x++){

                if(board.cells[i * board.width + x] == true){
                    std::cout << "*";
                }
                else{
                    std::cout << " ";
                }

            }

            std::cout << std::endl;
        } 
        
    }

bool get_alive(const Board& board, int x, int y){
    if (x < 0 || y < 0 || x >= static_cast<int>(board.width) || y >= static_cast<int>(board.height))
        return false;

    return board.cells[x + y * board.width];
}

int neighbour_count(const Board& board, std::size_t x, std::size_t y) {
    int count = 0;
    count += get_alive(board, x - 1, y - 1);
    count += get_alive(board, x, y - 1);
    count += get_alive(board, x + 1, y - 1);
    count += get_alive(board, x - 1, y);
    count += get_alive(board, x + 1, y);
    count += get_alive(board, x - 1, y + 1);
    count += get_alive(board, x, y + 1);
    count += get_alive(board, x + 1, y + 1);
    return count;
}

Board game_step(const Board& board) {
    Board newboard;
    newboard.width = board.width;
    newboard.height = board.height;
    newboard.cells.resize(board.cells.size());
    for(size_t y = 0; y < board.height; y++){

        for(size_t x = 0; x < board.width; x++){

            newboard.cells[x + y * board.width] = (board.cells[x + y * board.width] && neighbour_count(board, x, y) == 2) || neighbour_count(board, x, y) ==3;

        }
    }
    return newboard;
}

void clear_screen() {
    std::cout << "\033[2J\033[1;1H";
}

Board parse_board(const std::string& path);
Board default_board();

int main(int argc, const char** argv) {
    using namespace std::chrono_literals;
    Board board;
    if (argc > 1) {
        board = parse_board(argv[1]);
    } else {
        board = default_board();
    }

    while (true) {
        board = game_step(board);
        clear_screen();
        print_board(board);
        std::this_thread::sleep_for(50ms);
    }
    
    return 0;
}

Board parse_board(const std::string& path) {
    Board board;
    // If a filename is provided, load board from file.
    std::ifstream infile(path);
    if (!infile) {
        std::cerr << "Error: Cannot open file " << path << std::endl;
        abort();
    }
    
    // Read board dimensions from the first two lines.
    infile >> board.width >> board.height;
    // Discard the rest of the line after reading numbers.
    std::string line;
    std::getline(infile, line);
    
    // Skip potential empty lines before board pattern.
    while (std::getline(infile, line) && line.empty()) {
        // continue skipping
    }
    
    // Allocate board cells (initialize to dead).
    board.cells.assign(board.width * board.height, false);
    
    // Process the first non-empty board line that was already read.
    std::size_t row = 0;
    if (!line.empty() && row < board.height) {
        for (std::size_t col = 0; col < line.size() && col < board.width; ++col) {
            if (line[col] == '#')
                board.cells[row * board.width + col] = true;
        }
        ++row;
    }
    
    // Continue reading remaining lines.
    while (row < board.height && std::getline(infile, line)) {
        if (line.empty())
            continue;
        for (std::size_t col = 0; col < line.size() && col < board.width; ++col) {
            if (line[col] == '#')
                board.cells[row * board.width + col] = true;
        }
        ++row;
    }
    return board;
}

Board default_board() {
    Board board;
    board.width = 200;
    board.height = 54;
    board.cells.assign(board.width * board.height, false);
    
    // Default board pattern as provided.
    std::vector<std::string> defaultPattern = {
        "                                      #",
        "                                    # #",
        "                          ##      ##            ##",
        "                         #   #    ##            ##",
        "              ##        #     #   ##",
        "              ##        #   # ##    # #",
        "                        #     #       #",
        "                         #   #    ",
        "                          ##      "
    };
    
    // Place the default pattern into the top rows of the board.
    for (std::size_t row = 0; row < defaultPattern.size() && row < board.height; ++row) {
        const std::string &line = defaultPattern[row];
        for (std::size_t col = 0; col < line.size() && col < board.width; ++col) {
            if (line[col] == '#')
                board.cells[row * board.width + col] = true;
        }
    }

    return board;
}
