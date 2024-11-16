#include <iostream>
#include <ctime>
#include "Windows.h"
using namespace std;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
char lamps[12];
int max_size = 12;
string game_type;

void set_game_type() {
    system("cls");
    cout << "Enter game type(1/2/3): ";
    int input; cin >> input;
    if (input == 1) game_type = "quad";
    else if (input == 2) game_type = "hexagon";
    else if (input == 3) game_type = "double_hexagon";
    else set_game_type();
}

void show(int index) {
    if (lamps[index] == 'G')
        SetConsoleTextAttribute(hConsole, 2);
    else if (lamps[index] == 'Y')
        SetConsoleTextAttribute(hConsole, 14);
    else if (lamps[index] == 'R')
        SetConsoleTextAttribute(hConsole, 4); 
    cout << "O   ";
    SetConsoleTextAttribute(hConsole, 8);
}

void display() {
    SetConsoleTextAttribute(hConsole, 8);
    system("cls");
    cout << "\n\n\t";

    if (game_type == "quad") {
        show(0); show(1); show(2); show(3);
        cout << "\n\t  1   2   3\n\t";
        show(4); show(5); show(6); show(7);
        cout << "\n\t  4   5   6\n\t";
        show(8); show(9); show(10); show(11);
        cout << "\n\n";
    }

    else if (game_type == "hexagon") {
        cout << "   "; show(2); cout << "  "; show(3); cout << "\n";
        cout << "\t      2\n\t   1     3\n\t";
        show(1); cout << "  "; show(6); cout << "  "; show(4);
        cout << "\n\t   6     4\n\t      5\n\t   ";
        show(0); cout << "  "; show(5); cout << "\n\n";
    }
    
    else if (game_type == "double_hexagon") {
        cout << "   "; show(1); cout << "  "; show(2); cout << "  "; show(4);cout << "\n";
        cout << "\t      1     3\n\t   0     2     4\n\t";
        show(0); cout << "  "; show(8); cout << "  "; show(3); cout << "  "; show(5);
        cout << "\n\t   9     7     5\n\t      8     6\n\t   ";
        show(9); cout << "  "; show(7); cout << "  "; show(6); cout << "\n\n";
    }
    
}

bool gameover() {
    for (int i = 0; i < max_size; i++) 
        if (lamps[i] != 'G') return false;
    return true;
}

void change(int index) {
    if (lamps[index] == 'R') lamps[index] = 'Y';
    else if (lamps[index] == 'Y') lamps[index] = 'G';
    else if (lamps[index] == 'G') lamps[index] = 'R';
}

void press_button(int index) {
    if (game_type == "quad") {
        if (index < 4) index--; 
        change(index);
        change(index+1);
        change(index+4);
        change(index+5);
    }

    else if (game_type == "hexagon") {
        change(6);
        change(index%6);
        change(++index%6);
    }

    else if (game_type == "double_hexagon") {
        change(index);
        change((index+1)%10);
        if (index < 3) change(8);
        else if (index == 3) change(2);
        else if ((3 < index)&&(index < 8)) change(3);
        else change (index-1);
    }
}

void create() {
    srand(time(0));
    int loop_count = (game_type == "hexagon") ? rand() % 4 + 2 : rand() % 13 + 5;
    for (int i = 0; i < max_size; i++) lamps[i] = 'G';
    while (loop_count--) press_button((game_type == "double_hexagon") ? rand() % 10 : rand() % 6 + 1);
    if (gameover()) create();
}

void start() {
    int input, min, max;
    if (game_type == "double_hexagon") {
        min = 0; max = 9;
    } else {
        min = 1; max = 6;
    }
    while (!gameover()) {
        display();
        cin >> input;
        if ((min <= input) && (input <= max))
            press_button(input);
        display();
    }
    display();
}

int main() {
    set_game_type();
    create();
    start();
    return main();
}