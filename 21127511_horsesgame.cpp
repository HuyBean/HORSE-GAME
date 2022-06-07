#include <iostream>
#include <time.h>
#include <conio.h>
#include <windows.h>
#pragma comment(lib, "winmm.lib")
const int MAX = 50;
void Print_horizontal_coordinates(int bsize) {
    std::cout << "  ";
    for (char i = 65; i < (65 + bsize); i++)
        std::cout << "    " << i << "      ";
    std::cout << "\n";
}
void Print_horizontal_line(int bsize) {
    std::cout << "  ";
    for (int i = 0; i < bsize; i++)
        std::cout << " --------- ";
    std::cout << "\n";
}
void Print_vertical_line(int bsize) {
    std::cout << "  ";
    for (int i = 0; i < bsize; i++)
        std::cout << "|         |";
    std::cout << "\n";
}
void print_Board(char board[][MAX], int bsize) {
    int k = 1;
    Print_horizontal_coordinates(bsize);
    for (int i = 0; i < bsize; i++) {
        Print_horizontal_line(bsize);
        Print_vertical_line(bsize);
        for (int j = 0; j < bsize; j++) {
            if (j == 0) {
                std::cout << k << " |    " << board[i][j] << "    |";
            }
            else {
                std::cout << "|    " << board[i][j] << "    |";
            }
        }
        std::cout << '\n';
        Print_vertical_line(bsize);
        Print_horizontal_line(bsize);
        k = k + 1;
    }
}
void init_Playername(char name[], int n) {
    for (int i = 0; i < n; i++) {
        std::cout << " Now please enter player " << i + 1 << " name ";
        std::cin >> name[i];
    }
}
void init_Board(char board[][MAX], int bsize) {
    for (int i = 0; i < bsize * bsize; i++) {
        for (int j = 0; j < bsize * bsize; j++) {
            board[i][j] = ' ';
        }
    }
}
void init_Posi(int pos[], int n) {
    for (int i = 0; i < n; i++) {
        pos[i] = 0;
    }
}
void roll_Dice(int rsize, int bsize, int pos[], char name[], int n, int cur) {
    int step = rand() % rsize + 1;
    std::cout << name[cur] << " roll " << step << "\n";
    if (step + pos[cur] > bsize * bsize) {
        std::cout << "Can not move forward\n";
    }
    else {
        pos[cur] = step + pos[cur];
        for (int i = 0; i < n; i++) {
            if ((pos[cur] == pos[i]) && (i != cur)) {
                pos[i] = 0;
                std::cout << name[i] << " is kicked to Start\n";
            }
        }
    }
}
void update_Board(char board[][MAX], int bsize, int pos[], char name[], int n) {
    init_Board(board, bsize);
    int row, col;
    for (int i = 0; i < n; i++) {
        row = pos[i] / bsize;
        col = pos[i] % bsize;
        board[row][col] = name[i];
    }
}
char play_Game(int rsize, int bsize, char board[][MAX], int pos[], char name[], int n, int limit_turns, int finish_point) {
    char winner = ' ';
    int cur_turn = 0;
    while (winner == ' ' && cur_turn < limit_turns) {

        roll_Dice(rsize, bsize, pos, name, n, cur_turn % n);
        update_Board(board, bsize, pos, name, n);
        print_Board(board, bsize);
        if (pos[cur_turn % n] == finish_point)
            winner = name[cur_turn % n];
        cur_turn += 1;
        system("pause");
    }
    return winner;
}
void count_Statistic(int count[], int n, char name[], int winner, int countmatch) {
    std::cout << " Number of match played : " << countmatch << "\n";
    for (int i = 0; i < n; i++) {
        if (name[i] == winner) {
            count[i]++;
        }
    }
    for (int i = 0; i < n; i++) {
        std::cout << " Number of match player " << i + 1 << " win: " << count[i] << "\n";
        std::cout << " Percentage the player " << i + 1 << " win:  " << (float)count[i] / countmatch * 100 << "%\n";
    }
}

int main() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 236);
    int stop, countmatch, sound;
    int count[MAX] = { 0 };
    stop = 1;
    countmatch = 0;
    while (stop == 1) {
        std::cout << "---------------------- WELCOME TO THE HORSE BOARD GAME ------------------\n";
        bool isPlay1 = PlaySound(L"mario.wav", NULL, SND_FILENAME);
        std::cout << " -----SETTING-----\n";
        int n, bsize, rsize, limit_turns, limit_turns_person;
        int pos[MAX];
        char name[MAX];
        char board[MAX][MAX];
        char winner = ' ';
        std::cout << " INPUT THE NUMBERS OF PLAYER = ";
        std::cin >> n;
        init_Playername(name, n);
        std::cout << " CHOOSE THE TABLE SIZE : \n";
        std::cout << " Press 0 for 3*3 \n";
        std::cout << " Press 1 for 4*4 \n";
        std::cout << " Press 2 for 5*5 \n";
        std::cout << " Press 3 for 6*6 \n";
        std::cout << " Press 4 for 7*7 \n";
        std::cout << " Press other number for customize \n";
        std::cout << " Your choice is : ";
        std::cin >> bsize;
        if (bsize == 0) { bsize = 3; }
        else if (bsize == 1) { bsize = 4; }
        else if (bsize == 2) { bsize = 5; }
        else if (bsize == 3) { bsize = 6; }
        else if (bsize == 4) { bsize = 7; }
        else {
            std::cout << "Please intput your number  ";
            std::cin >> bsize;
        }
        std::cout << " CHOOSE THE DICE RANGE : \n";
        std::cout << " Press 0 for 1-3 \n";
        std::cout << " Press 1 for 1-4 \n";
        std::cout << " Press 2 for 1-5 \n";
        std::cout << " Press 3 for 1-6 \n";
        std::cout << " Press other number for customize \n";
        std::cout << " Your choice is : ";
        std::cin >> rsize;
        if (rsize == 0) { rsize = 3; }
        else if (rsize == 1) { rsize = 4; }
        else if (rsize == 2) { rsize = 5; }
        else if (rsize == 3) { rsize = 6; }
        else {
            std::cout << "Please intput your number  ";
            std::cin >> rsize;
        }
        std::cout << "INPUT THE LIMIT TURN PER PLAYER (at least 10 ) = ";
        std::cin >> limit_turns_person;
        limit_turns = limit_turns_person * n;
        std::cout << "Do you want to turn on sound ?\n";
        std::cout << "Press 1 for Yes , press other numbers for No :  ";
        std::cin >> sound;
        std::cout << "ARE YOU READY ? !! LET'S GOOOOOO!!!!!!\n";
        if (sound == 1) { bool isPlay = PlaySound(L"mario.wav", NULL, SND_FILENAME); }
        system("pause");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 63);
        init_Board(board, bsize);
        srand(time(NULL));
        init_Posi(pos, n);
        update_Board(board, bsize, pos, name, n);
        print_Board(board, bsize);
        int finish_point = bsize * bsize - 1;
        winner = play_Game(rsize, bsize, board, pos, name, n, limit_turns, finish_point);
        if (winner == ' ')
            std::cout << "Tie game\n";
        else std::cout << winner << " is the winner\n";
        countmatch++;
        count_Statistic(count, n, name, winner, countmatch);
        if (sound == 1) { bool isPlay = PlaySound(L"mario.wav", NULL, SND_FILENAME); }
        std::cout << " DO YOU WANT TO REPLAY THE GAME ?\n";
        std::cout << " Press 1 to replay \n";
        std::cout << " Press 0 to stop the game\n";
        std::cout << " Your choice is : ";
        std::cin >> stop;
    }
    return 0;
}

