// Daniel Henrique da Silva, Lucas dos Santos Luckow, Samuel Alfonso Werner Stuhlert, Victor Menezes Ferreira.

#include <iostream>
#include <locale.h>
#include <time.h>
#include <unistd.h>
using namespace std;
#define TAM 5

#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

void delay(unsigned long t) {
    sleep(t);
} // Controls delay time between each drawn number, t in seconds

void returnToMenu(int &menu) {
    menu = 0;
    cout << "\nPress any key to return to the menu\n";
    cin.ignore();
    cin.get();
    system(CLEAR);
} // Returns to the main menu

void printMenu() {
    cout << endl;
    cout << "██████  ██ ███    ██  ██████   ██████  ██\n"
            "██   ██ ██ ████   ██ ██       ██    ██ ██\n"
            "██████  ██ ██ ██  ██ ██   ███ ██    ██ ██\n"
            "██   ██ ██ ██  ██ ██ ██    ██ ██    ██   \n"
            "██████  ██ ██   ████  ██████   ██████  ██\n\n\n";
  
    cout << "1.  PLAY\n\n\n"
            "2.  ABOUT\n\n\n"
            "3.  EXIT\n\n\n\n";
} // Print main menu

void about() {
    cout << "\nDevelopers:    Daniel Henrique da Silva\n"
            "               Lucas dos Santos Luckow\n"
            "               Samuel Alfonso Werner Stuhlert\n"
            "               Victor Menezes Ferreira\n\n"
            "Professor:     Prof. Rafael Ballotin Martins\n"
            "Course:        Algorithms and Programming II\n"
            "August/2023\n\n";
} // Print "about"

void print(int card[SIZE][SIZE], string players[SIZE], int p, int numbers[75]) {
    cout << "0" << p << " - " << players[p - 1] << endl; // Print card number and its owner
    cout << "╔═══════════════╗\n"; // Print this edge before the loop that prints the card
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (j == 0) { // Print this edge before first column
                cout << "║";
            }
      
            if (card[i][j] < 10 and j != 8) { // If the value is a single digit, print 0 before and add space
                if (numbers[card[i][j] - 1] != 0) { // Check if the number has already been drawn
                    cout << "\033[32m0" << card[i][j] << " \033[0m"; // Change color to green then reset
                } else {
                    cout << "0" << card[i][j] << " ";
                }
              
            } else if (card[i][j] > 0 and j == 8) { // If it's a single digit in the last column, print 0 without space
                if (numbers[card[i][j] - 1] != 0) {
                    cout << "\033[32m0" << card[i][j] << "\033[0m";
                } else {
                    cout << "0" << card[i][j];
                }
              
            } else if (card[i][j] != 0 and j < 8) { // If the value has two digits, print with space
                if (numbers[card[i][j] - 1] != 0) {
                    cout << "\033[32m" << card[i][j] << " \033[0m";
                } else {
                    cout << card[i][j] << " ";
                }
              
            } else { // Print value without space (last column)
                if (numbers[card[i][j] - 1] != 0) {
                    cout << "\033[32m" << card[i][j] << "\033[0m";
                } else {
                    cout << card[i][j];
                }
            }
        }      
        cout << "║ " << endl; // After each row, print border and newline
    }    
    cout << "╚═══════════════╝\n\n"; //After the card is printed, print this bottom border
} // // Prints the cards

void generate(int card[SIZE][SIZE]) {
    int num = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            card[i][j] = rand() % 15 + 1 + num; // 15+1 generate values from 1 to 15, num starts at 0
        }
        num += 15; // After the 'j' loop, before i++, add 15 to num, since the min and max values of the next line are 15 more than the previous one
    }
} // Generate random card

void check(int card[SIZE][SIZE]) {
    int num = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int verify  = 0; verify  < 2; verify ++) { // Re-check after changing a number, in case it's still a duplicate
            for (int k = 0; k < SIZE; k++) {
                for (int j = 0; j < SIZE; j++) {
                    if (k != j) {
                        if (card[i][k] == card[i][j]) { // Checks all columns to see if the value is repeated
                            card[i][k] = rand() % 15 + 1 + num; // If a duplicate is found, replace it with a new number
                        }
                    }
                }
            }
        }
        num += 15; // Increases the range offset for the next column
    }
} // Checks if there are repeated numbers in the card and replaces them

void bubblesort(int card[SIZE][SIZE]) {
    int i, j, cond, temp, row;
    for (row = 0; row < SIZE; row++) { // Loop to go through all rows of the matrix, sorting each one
        cond = 1;
        for (i = SIZE - 1; (i >= 1) && (cond == 1); i--) {
            cond = 0;
            for (j = 0; j < i; j++) {
                if (card[row][j + 1] < card[row][j]) {
                    temp = card[row][j];
                    card[row][j] = card[row][j + 1];
                    card[row][j + 1] = temp;
                    cond = 1;
                }
            }
        }
    }
} // Bubble sort adjusted to sort each row of the matrix

void names(string players[SIZE]) {
    cin.ignore();
    for (int i = 0; i < SIZE; i++) {
        cout << endl << "Type player's name of card 0" << i + 1 << ": ";
        getline(cin, players[i]);
    }
} // Get players names

void draw(int numbers[75], int &num) {
    int i = 0; // Set i=0 to start the loop
    while (i != 1) {
        num = rand() % 75 + 1;       // Draw a number from 1 to 75
        if (numbers[num - 1] == 0) { // Check if the number was already drawn
            numbers[num - 1] = num;  // If not, store the number in the array
            i = 1; // Set i=1 to exit the loop
        } else {
            i = 0; // If already drawn, continue looping
        }
    }
} // Draw a number

void drawn(int numbers[75], int num) {
    system(CLEAR);
    cout << endl << "Drawn numbers: " << endl;
    for (int i = 0; i < 75; i++) {
        if (numbers[i] != 0) {
            cout << "\033[32m" << numbers[i] << "\033[0m" << "\t";
        }
    }
    cout << endl << "Last drawn number: " << "\033[31m" << num << "\033[0m" << endl << endl;
} // Print drawn numbers

int won(int card1[SIZE][SIZE], int card2[SIZE][SIZE], int card3[SIZE][SIZE], int card4[SIZE][SIZE], int card5[SIZE][SIZE], int numbers[75]) {
    int winner1 = 0, winner2 = 0, winner3 = 0, winner4 = 0, winner5 = 0; // Reset counters
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (card1[i][j] == numbers[card1[i][j] - 1]) { // Check if number was already drawn
                winner1++; // If true, add 1 to counter
                if (winner1 == 25)
                    return (winner1);
            }
            if (card2[i][j] == numbers[card2[i][j] - 1]) {
                winner2++;
                if (winner2 == 25)
                    return (winner2);
            }
            if (card3[i][j] == numbers[card3[i][j] - 1]) {
                winner3++;
                if (winner3 == 25)
                    return (winner3);
            }
            if (card4[i][j] == numbers[card4[i][j] - 1]) {
                winner4++;
                if (winner4 == 25)
                    return (winner4);
            }
            if (card5[i][j] == numbers[card5[i][j] - 1]) {
                winner5++;
                if (winner5 == 25)
                    return (winner5);
            }
        }
    }
    return 0;
} // Check if a player already won

void winnerScreen(int card1[SIZE][SIZE], int card2[SIZE][SIZE], int card3[SIZE][SIZE], int card4[SIZE][SIZE], int card5[SIZE][SIZE], int numbers[75], string players[SIZE]) {
    cout << "██████  ██ ███    ██  ██████   ██████  ██\n"
            "██   ██ ██ ████   ██ ██       ██    ██ ██\n"
            "██████  ██ ██ ██  ██ ██   ███ ██    ██ ██\n"
            "██   ██ ██ ██  ██ ██ ██    ██ ██    ██   \n"
            "██████  ██ ██   ████  ██████   ██████  ██\n\n\n";
                                                   
    int winner1 = 0, winner2 = 0, winner3 = 0, winner4 = 0, winner5 = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (card1[i][j] == numbers[card1[i][j] - 1]) {
                winner1++;
                if (winner1 == 25)
                    cout << "Congratulations " << players[0] << " of card 01, you won!\n";
            }
            if (card2[i][j] == numbers[card2[i][j] - 1]) {
                winner2++;
                if (winner2 == 25)
                    cout << "Congratulations " << players[1] << " of card 02, you won!\n";
            }
            if (card3[i][j] == numbers[card3[i][j] - 1]) {
                winner3++;
                if (winner3 == 25)
                    cout << "Congratulations " << players[2] << " of card 03, you won!\n";
            }
            if (card4[i][j] == numbers[card4[i][j] - 1]) {
                winner4++;
                if (winner4 == 25)
                    cout << "Congratulations " << players[3] << " of card 04, you won!\n";
            }
            if (card5[i][j] == numbers[card5[i][j] - 1]) {
                winner5++;
                if (winner5 == 25)
                    cout << "Congratulations " << players[4] << " of card 05, you won!\n";
            }
        }
    }
    cout << endl << endl;
} // Print winner(s) player(s)
  
int main() {
    #ifdef _WIN32
        system("chcp 65001 > nul"); // To support accents in Windows terminal
    #endif
    setlocale(LC_ALL, "pt_BR.UTF-8");
    srand(time(NULL));
    int menu;

    do {
        string(players[SIZE]);
        int numbers[75] = {0}, num;
        
        printMenu();
        cin >> menu;
  
        switch (menu) {
        case 1: // Play
            system(CLEAR);
      
            int card01[SIZE][SIZE];
            int card02[SIZE][SIZE];
            int card03[SIZE][SIZE];
            int card04[SIZE][SIZE];
            int card05[SIZE][SIZE];
      
            generate(card01);
            check(card01);
            bubblesort(card01);
      
            generate(card02);
            check(card02);
            bubblesort(card02);
      
            generate(card03);
            check(card03);
            bubblesort(card03);
      
            generate(card04);
            check(card04);
            bubblesort(card04);
      
            generate(card05);
            check(card05);
            bubblesort(card05);
      
            names(players);
      
            do {
                draw(numbers, num);
                drawn(numbers, num);
                print(card01, players, 1, numbers);
                print(card02, players, 2, numbers);
                print(card03, players, 3, numbers);
                print(card04, players, 4, numbers);
                print(card05, players, 5, numbers);
                delay (1);
            } while (won(card01, card02, card03, card04, card05, numbers) != 25);
            delay (3);
            winnerScreen(card01, card02, card03, card04, card05, numbers, players);
            returnToMenu(menu);
            break;
    
        case 2: // About
            system(CLEAR);
            about();
            returnToMenu(menu);
            break;
    
        case 3: // Exit
            break;
        }
      
        system(CLEAR);
    } while (menu != 3);
    return 0;
}
