#include <iostream>
using namespace std;

const int rows = 6, columns = 7;

class Game {
private:

    char** grid;
    int player;       //    1 : player 1         -1 : player 2
    char character;

public:

    Game();
    Game(char** grid, int player) { this->grid = grid; this->player = player; };
    Game(char** grid, int player, char character) { this->grid = grid; this->player = player; this->character = character; };
    

    void next_player() {
        player *= -1;
    }


    void update_character() {
        if (player == 1) {
            character = '#';
        }
        else {
            character = 'O';
        }
    }


    void fill_grid() {
        for (int i = 0; i < columns; i++) {
            for (int j = 0; j < rows; j++) {
                grid[i][j] = '.';
            }
        }
    }


    void display_grid() {

        // # : player 1
        // O : player 2
        cout << "\x1B[2J\x1B[H\n   1     2     3     4     5     6     7\n\n";

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                cout << "|  " << grid[j][i] << "  ";
            }
            cout << "|" << endl;
        }
        cout << endl;
    }

    void display_winner() {
        cout << "\aBravo! Le joueur " << player << " vient de gagner" << endl;
    }


    bool play_in_column(int col) {

        int y = 0;

        for (int i = 0; i < rows; i++) {

            if (grid[col][i] == '.') {
                if (y < rows - 1) { y++; }
            }
            else {
                if (y > 0) { y--; }
                break;
            }
        }

        update_character();
        grid[col][y] = character;

        return check_victory(col, y);
    }


    bool choose_column() {

        cout << "C'est au joueur " << player << " de jouer !\n\n";   // player's name
        int col = 0;
        bool done = false;

        do {
            cout << "Colonne : ";
            cin >> col;

            if (col > 0 && col <= columns) {
                if (grid[col - 1][0] == '.') {
                    done = true;
                    col--;
                }
            }

        } while (!done);

        return play_in_column(col);
    }


    bool check_col(int col) {

        int counter = 0;

        for (int row = 0; row < rows; row++) {
            if (grid[col][row] == character) {
                counter++;
                if (counter == 4) {
                    return true;
                }
            }
            else {
                counter = 0;
            }
        }
        return false;
    }


    bool check_row(int row) {

        int counter = 0;

        for (int col = 0; col < columns; col++) {
            if (grid[col][row] == character) {
                counter++;
                if (counter == 4) {
                    return true;
                }
            }
            else {
                counter = 0;
            }
        }
        return false;
    }


    bool check_diag(int col, int row) {
        
        int index = 1, counter = 1;

        while ((col+index) < columns && (row+index) < rows) {
            if (grid[col + index][row + index] == character) {
                counter++; index++;
            } else { break; }
        }

        index = 1;
        while ((col - index) >= 0 && (row - index) >= 0) {
            if (grid[col - index][row - index] == character) {
                counter++; index++;
            }
            else { break; }
        }

        if (counter >= 4) { return true; }
        else { counter = 1; }

        index = 1;
        while ((col + index) < columns && (row - index) >= 0) {
            if (grid[col + index][row - index] == character) {
                counter++; index++;
            }
            else { break; }
        }

        index = 1;
        while ((col - index) >= 0 && (row + index) < rows) {
            if (grid[col - index][row + index] == character) {
                counter++; index++;
            }
            else { break; }
        }

        if (counter >= 4) { return true; }
        else { return false; }
    }


    bool check_victory(int col, int row) {

        return check_col(col) || check_row(row) || check_diag(col, row);
    }

    bool play() {

        display_grid();
        if (choose_column()) {
            display_grid();
            display_winner();
            return true;
        }
        else {
            next_player();
            return false;
        }
    }
};


Game init_grid(int player) {

    char** grid = new char*[columns];
    for (int i = 0; i < columns; i++) {
        grid[i] = new char[rows];
    }

    Game game(grid, player);

    game.fill_grid();

    return game;
}


void start_game() {

    Game game = init_grid(1);   // parameter: num of the one who starts

    bool won = false; 

    while (!won) {

        if (game.play()) {
            won = true;
        };
    }
}

int main() {
    
    start_game();
}


/*

Updates:

Add structures to represent players

*/
