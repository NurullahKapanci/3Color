#include <iostream>
#include <ctime>
#include "windows.h"
using namespace std;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
char lamps[10];

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
    show(1); cout << "     "; show(2); cout << "     "; show(4);cout << "\n";
    SetConsoleTextAttribute(hConsole, 8);
    cout << "\t      1     3\n\t   0     2     4\n\t";
    show(0); cout << "     "; show(8); cout << "     "; show(3); cout << "     "; show(5);
    SetConsoleTextAttribute(hConsole, 8);
    cout << "\n\t   9     7     5\n\t      8     6\n\t   ";
    show(9); cout << "     "; show(7); cout << "     "; show(6); cout << "\n\n";
}

bool gameover() {
    for (int i = 0; i < 10; i++) 
        if (lamps[i] != 'Y') return false;
    return true;
}

void change(int index) {
    if (lamps[index] == 'K') lamps[index] = 'S';
    else if (lamps[index] == 'S') lamps[index] = 'Y';
    else if (lamps[index] == 'Y') lamps[index] = 'K';
}

void press_button(int index) {
    change(index);
    change((index+1)%10);
    if (index < 3) change(8);
    else if (index == 3) change(2);
    else if ((3 < index)&&(index < 8)) change(3);
    else change (index-1);

}

void create() {
    srand(time(NULL));
    int loop_count = rand() % 13 + 5;
    for (int i = 0; i < 10; i++) 
        lamps[i] = 'Y';
    while (loop_count--)
        press_button(rand() % 10);
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