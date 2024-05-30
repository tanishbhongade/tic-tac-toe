#include <iostream>
#include <vector>
#include <iterator>
#include <limits.h>
using namespace std;
typedef vector<vector<char>> matrix;
typedef long long int lli;
typedef pair<int, int> pint;

constexpr char human_symbol = 'O';
constexpr char computer_symbol = 'X';

pair<int, int> convert_location_to_move(int loc)
{
    loc--;
    return {loc / 3, loc % 3};
}

void print_board(const matrix board)
{
    // Printing the tic tac toe board
    for (int i = 0; i < 3; i++)
    {
        cout << "|";
        for (int j = 0; j < 3; j++)
        {
            cout << board[i][j] << "|";
        }
        cout << endl;
    }
}

bool is_player_winning(const matrix board, const char player_symbol)
{
    // Check rows
    if (board[0][0] == player_symbol && board[0][1] == player_symbol && board[0][2] == player_symbol)
    {
        // 1
        return 1;
    }
    else if (board[1][0] == player_symbol && board[1][1] == player_symbol && board[1][2] == player_symbol)
    {
        // 2
        return 1;
    }
    else if (board[2][0] == player_symbol && board[2][1] == player_symbol && board[2][2] == player_symbol)
    {
        // 3
        return 1;
    }
    // Check columns
    else if (board[0][0] == player_symbol && board[1][0] == player_symbol && board[2][0] == player_symbol)
    {
        // 4
        return 1;
    }
    else if (board[0][1] == player_symbol && board[1][1] == player_symbol && board[2][1] == player_symbol)
    {
        // 5
        return 1;
    }
    else if (board[0][2] == player_symbol && board[1][2] == player_symbol && board[2][2] == player_symbol)
    {
        // 6
        return 1;
    }
    // Check diagonals
    else if (board[0][0] == player_symbol && board[1][1] == player_symbol && board[2][2] == player_symbol)
    {
        // 7
        return 1;
    }
    else if (board[2][0] == player_symbol && board[1][1] == player_symbol && board[0][2] == player_symbol)
    {
        // 8
        return 1;
    }
    return false;
}

bool is_game_draw(const matrix board)
{
    bool all_full = true;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] != 'O' && board[i][j] != 'X')
            {
                all_full = false;
            }
        }
    }
    if (all_full == true)
    {
        if (is_player_winning(board, 'O') == false && is_player_winning(board, 'X') == false)
        {
            return true;
        }
    }
    return false;
}

void make_the_move(matrix &board, int row, int col, char move)
{
    board[row][col] = move;
}

int no_empty_squares(const matrix board)
{
    int count = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == ' ')
            {
                count++;
            }
        }
    }
    return count;
}

bool is_location_empty(const matrix board, int i, int j)
{
    if (board[i][j] == ' ')
        return true;
    return false;
}

int minimax(matrix board, int depth, char player)
{
    int result = is_player_winning(board, player);
    if (result == true && player == human_symbol)
    {
        return -1;
    }
    else if (result == true && player == computer_symbol)
    {
        return 1;
    }
    else if (is_game_draw(board) == true)
    {
        return 0;
    }

    if (player == computer_symbol)
    {
        lli best_score = INT_MIN;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (is_location_empty(board, i, j) == true)
                {
                    board[i][j] = player;
                    lli score = minimax(board, depth + 1, human_symbol);
                    board[i][j] = ' ';
                    best_score = max(score, best_score);
                }
            }
        }
        return best_score;
    }
    else
    {
        lli best_score = INT_MAX;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (is_location_empty(board, i, j) == true)
                {
                    board[i][j] = player;
                    lli score = minimax(board, depth + 1, computer_symbol);
                    board[i][j] = ' ';
                    best_score = min(score, best_score);
                }
            }
        }
        return best_score;
    }
}

pint best_move_ai(matrix board)
{
    lli best_score = INT_MIN;
    lli score;
    pint move = {-1, -1};

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (is_location_empty(board, i, j) == true)
            {
                board[i][j] = computer_symbol;
                score = minimax(board, 0, human_symbol);
                board[i][j] = ' ';
                if (score > best_score)
                {
                    best_score = score;
                    move = {i, j};
                }
            }
        }
    }
    return move;
}

int main()
{
    int loc;
    pair<int, int> player_move;
    pair<int, int> comp_move;

    matrix board = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}};

    print_board(board);
    while (is_player_winning(board, computer_symbol) == false && is_player_winning(board, human_symbol) == false && no_empty_squares(board) != 0)
    {
        // Player moves
        cout << "Player O, enter your move: ";
        cin >> loc;

        if (loc < 1)
        {
            cout << "Invalid input" << endl
                 << endl;
            continue;
        }
        player_move = convert_location_to_move(loc);
        if (board[player_move.first][player_move.second] == human_symbol || board[player_move.first][player_move.second] == computer_symbol)
        {
            cout << "Move already done" << endl;
            continue;
        }

        make_the_move(board, player_move.first, player_move.second, human_symbol);
        print_board(board);

        // Computer moves
        comp_move = best_move_ai(board);
        if (comp_move.first == -1 || comp_move.second == -1)
        {
            break;
        }

        make_the_move(board, comp_move.first, comp_move.second, computer_symbol);

        print_board(board);
    }

    if (is_player_winning(board, human_symbol) == true)
    {
        cout << "You won!" << endl;
    }
    else if (is_player_winning(board, computer_symbol) == true)
    {
        cout << "Computer won!" << endl;
    }
    else
    {
        cout << "Draw!" << endl;
    }

    return 0;
}