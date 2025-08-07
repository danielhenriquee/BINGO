# BINGO
BINGO - Project for Algorithms and Programming II - 2023/2

This is a terminal-based Bingo game developed in C++ as a programming assignment during the second semester of the Computer Engineering program. 
The game simulates a full Bingo match for up to 5 players, including randomized number drawing, real-time card updates, and automatic winner detection.

It was created to apply fundamental concepts of programming such as:
- Two-dimensional arrays
- Control structures (loops, conditionals, switch-case)
- Array manipulation and sorting (bubble sort)
- Random number generation using rand()
- Duplicate number checking and regeneration
- User input validation and name handling
- Function-based code modularization

Development Environment:
- Language: C++
- Compiler: g++
- Platform: replit.com – chosen for its collaborative coding features, real-time editing, and ease of access from both university and personal computers.
- Compatible with: Linux, macOS, Windows (UTF-8 support required)

Features:
- Automatic generation of up to 5 unique Bingo cards (5x5)
- Each card follows Bingo column number ranges (e.g., B: 1–15, I: 16–30, etc.)
- Duplicate prevention per row
- Player name input (up to 5 players)
- Random number draw with visual feedback and delay
- Last drawn number highlighted in red
- Matched numbers highlighted in green on each player card
- Real-time card checking for winner detection

NOTE: To properly display the game's interface, your terminal must support UTF-8 encoding. 
If you're on Windows, consider using a UTF-8–capable terminal or enabling UTF-8 with 'chcp 65001'.
Visual card rendering with box-drawing characters

Automatic return to the main menu after each match
