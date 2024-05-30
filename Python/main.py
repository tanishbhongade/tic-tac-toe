human_symbol = "O"
comp_symbol = "X"


def loc_to_move(loc):
    loc -= 1
    return [loc // 3, loc % 3]


def print_board(board):
    for i in range(3):
        print("|", end="")
        for j in range(3):
            print(board[i][j] + "|", end="")
        print()


def is_player_winning(board, player):
    # Check rows
    for i in range(3):
        if board[i][0] == player and board[i][1] == player and board[i][2] == player:
            return True

    # Check columns
    for i in range(3):
        if board[0][i] == player and board[1][i] == player and board[2][i] == player:
            return True

    # Check diagonals
    if board[0][0] == player and board[1][1] == player and board[2][2] == player:
        return True
    elif board[0][2] == player and board[1][1] == player and board[2][0] == player:
        return True

    return False


def no_of_empty_squares(board):
    count = 0
    for i in range(3):
        for j in range(3):
            if board[i][j] == " ":
                count += 1
    return count


def is_location_empty(board, i, j):
    if board[i][j] == " ":
        return True
    return False


def make_the_move(board, i, j, move):
    board[i][j] = move


def is_draw(board):
    if (
        no_of_empty_squares(board) == 0
        and is_player_winning(board, human_symbol) == False
        and is_player_winning(board, comp_symbol) == False
    ):
        return True
    else:
        return False


def best_move_ai(board):
    move = [-1, -1]
    best_score = float("-inf")
    score = float("-inf")

    for i in range(3):
        for j in range(3):
            if is_location_empty(board, i, j) == True:
                board[i][j] = comp_symbol
                score = minimax(board, 0, human_symbol)
                board[i][j] = " "
                if score > best_score:
                    best_score = score
                    move = [i, j]
    return move


def minimax(board, depth, player):
    if is_player_winning(board, human_symbol):
        return -1
    elif is_player_winning(board, comp_symbol):
        return 1
    elif is_draw(board):
        return 0

    if player == comp_symbol:
        best_score = float("-inf")
        for i in range(3):
            for j in range(3):
                if is_location_empty(board, i, j) == True:
                    board[i][j] = player
                    score = minimax(board, depth + 1, human_symbol)
                    board[i][j] = " "
                    best_score = max(best_score, score)
        return best_score

    elif player == human_symbol:
        best_score = float("inf")
        for i in range(3):
            for j in range(3):
                if is_location_empty(board, i, j) == True:
                    board[i][j] = player
                    score = minimax(board, depth + 1, comp_symbol)
                    board[i][j] = " "
                    best_score = min(best_score, score)
        return best_score


if __name__ == "__main__":
    loc = None
    human_move = []
    computer_move = []

    board = [[" ", " ", " "], [" ", " ", " "], [" ", " ", " "]]
    print_board(board)
    while True:
        # Human move
        loc = int(input("Player O, enter your move: "))
        if loc < 1 or loc > 9:
            print("Invalid input")
            continue

        human_move = loc_to_move(loc)
        if (
            board[human_move[0]][human_move[1]] == human_symbol
            or board[human_move[0]][human_move[1]] == comp_symbol
        ):
            print("Move already done")
            continue

        make_the_move(board, human_move[0], human_move[1], human_symbol)
        print_board(board)
        if is_player_winning(board, human_symbol) == True:
            print("You won!")
            break
        if (
            is_draw(board) == True
            and is_player_winning(board, comp_symbol) == False
            and is_player_winning(board, human_symbol) == False
        ):
            print("Draw!")
            break

        # Computer move
        computer_move = best_move_ai(board)
        if computer_move[0] == -1 and computer_move[1] == -1:
            break
        make_the_move(board, computer_move[0], computer_move[1], comp_symbol)
        print_board(board)
        if is_player_winning(board, comp_symbol) == True:
            print("Computer won!")
            break

        if (
            is_draw(board) == True
            and is_player_winning(board, comp_symbol) == False
            and is_player_winning(board, human_symbol) == False
        ):
            print("Draw!")
            break
