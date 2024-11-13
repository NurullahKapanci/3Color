#include <iostream>
#include <ctime>
#include "Windows.h"
using namespace std;
char lamps[12];
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void show(int index) {
    if (lamps[index] == 'Y')
        SetConsoleTextAttribute(hConsole, 2);
    else if (lamps[index] == 'S')
        SetConsoleTextAttribute(hConsole, 14);
    else if (lamps[index] == 'K')
        SetConsoleTextAttribute(hConsole, 4); 
    cout << "O   ";
    SetConsoleTextAttribute(hConsole, 8);
}

void display() {
    SetConsoleTextAttribute(hConsole, 8);
    system("cls");
    cout << "\n\n\t";
    show(0); show(1); show(2); show(3);
    cout << "\n\t  1   2   3\n\t";
    show(4); show(5); show(6); show(7);
    cout << "\n\t  4   5   6\n\t";
    show(8); show(9); show(10); show(11);
    cout << "\n\n";
}

bool gameover() {
    for (int i = 0; i < 12; i++) 
        if (lamps[i] != 'Y') return false;
    return true;
}

void change(int index) {
    if (lamps[index] == 'K') lamps[index] = 'S';
    else if (lamps[index] == 'S') lamps[index] = 'Y';
    else if (lamps[index] == 'Y') lamps[index] = 'K';
}

void press_button(int index) {
    if (index < 4) index--; 
    change(index);
    change(index+1);
    change(index+4);
    change(index+5);
}

void create() {
    srand(time(NULL));
    int loop_count = rand() % 13 + 5;
    for (int i = 0; i < 12; i++) 
        lamps[i] = 'Y';
    while (loop_count--)
        press_button(rand() % 6 + 1);
    if (gameover()) create();
}

int main() {
    create();
    display();
    int input;
    while (!gameover()) {
        cin >> input;
        press_button(input);
        display();
    }
    return 0;
}