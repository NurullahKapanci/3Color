#include <iostream>
#include <ctime>
#include "windows.h"
using namespace std;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
char lamps[7];

void show(int index) {
    if (lamps[index] == 'Y')
        SetConsoleTextAttribute(hConsole, 2);
    else if (lamps[index] == 'S')
        SetConsoleTextAttribute(hConsole, 14);
    else if (lamps[index] == 'K')
        SetConsoleTextAttribute(hConsole, 4); 
    cout << "O";
    SetConsoleTextAttribute(hConsole, 7);
}

void display() {
    system("cls");
    cout << "\n\n\t   ";
    show(2); cout << "     "; show(3); cout << "\n";
    SetConsoleTextAttribute(hConsole, 8);
    cout << "\t      2\n\t   1     3\n\t";
    show(1); cout << "     "; show(6); cout << "     "; show(4);
    SetConsoleTextAttribute(hConsole, 8);
    cout << "\n\t   6     4\n\t      5\n\t   ";
    show(0); cout << "     "; show(5); cout << "\n\n";
}

bool gameover() {
    for (int i = 0; i < 7; i++) 
        if (lamps[i] != 'Y') return false;
    return true;
}

void change(int index) {
    if (lamps[index] == 'K') lamps[index] = 'S';
    else if (lamps[index] == 'S') lamps[index] = 'Y';
    else if (lamps[index] == 'Y') lamps[index] = 'K';
}

void press_button(int index) {
    change(6);
    change(index%6);
    change(++index%6);
}

void create() {
    srand(time(NULL));
    int loop_count = rand() % 4 + 2;
    for (int i = 0; i < 7; i++) 
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