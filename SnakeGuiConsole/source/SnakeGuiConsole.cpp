//#include <stdio.h>
//#include <iostream>
//#include <string>
//#include <windows.h>
//
//#include <fcntl.h>
//#include <io.h>
//
//#include <SnakeLib.hpp>



//void ClearConsole()
//{
//    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//    if (hConsole == INVALID_HANDLE_VALUE) return;
//
//    CONSOLE_SCREEN_BUFFER_INFO csbi;
//    DWORD cellCount, count;
//    COORD homeCoords = { 0, 0 };
//
//    if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) return;
//
//    cellCount = csbi.dwSize.X * csbi.dwSize.Y;
//
//    // Fill the screen with blanks
//    FillConsoleOutputCharacter(hConsole, ' ', cellCount, homeCoords, &count);
//    FillConsoleOutputAttribute(hConsole, csbi.wAttributes, cellCount, homeCoords, &count);
//
//    // Move the cursor to the top-left corner
//    SetConsoleCursorPosition(hConsole, homeCoords);
//}


//int main() 
//{
//    
//    
//    SnakeGame game{Dimensions{2,2}};
//
//
//
//    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
//
//    if (hConsole == INVALID_HANDLE_VALUE) return -1;
//    if (hInput == INVALID_HANDLE_VALUE) return -2;
//
//    CONSOLE_SCREEN_BUFFER_INFO csbi;
//    DWORD cellCount, count;
//    COORD homeCoords = { 0, 0 };
//
//    DWORD events = 0;
//    INPUT_RECORD inputRecord;
//
//
//    //std::cout << "This will be cleared in 3 seconds..." << std::endl;
//    //Sleep(3000); // Pause for 3 seconds
//    //ClearConsole();
//    //std::cout << "Console cleared!" << std::endl;
//
//    //setup_console_utf8();
//    ClearConsole();
//    draw();
//
//    // Enable window input
//    SetConsoleMode(hInput, ENABLE_WINDOW_INPUT | ENABLE_PROCESSED_INPUT);
//    //std::cout << "Press ESC to quit...\n";
//
//    //int i = 0;
//    while (true) 
//    {
//        //ClearConsole();
//        //draw();
//        //Sleep(1000);
//
//        //std::cout << game.random(10) << "\n";
//
//        int x[10] = {};
//        for (int i = 0; i < 999; i++)
//        {
//            x[game.random(10)] += 1;
//        }
//
//        for (int i = 0; i < 10; i++)
//            std::cout << x[i] << "\n";
//
//    //    draw();
//    //    std::cout << "i:" << ++i << "\n";
//    //    Sleep(1000);
//
//
//        //ReadConsoleInput(hInput, &inputRecord, 1, &events);
//
//        //if (inputRecord.EventType == KEY_EVENT && inputRecord.Event.KeyEvent.bKeyDown) {
//        //    char ch = inputRecord.Event.KeyEvent.uChar.AsciiChar;
//        //    int vk = inputRecord.Event.KeyEvent.wVirtualKeyCode;
//
//        //    //std::cout << "Key pressed: " << ch << " (VK: " << vk << ")\n";
//
//        //    //if (ch == 'c') ClearConsole();
//
//        //    if (vk == VK_ESCAPE) break;
//        //}
//    }
//
//    return 0;
//}





#include <iostream>
#include <conio.h>
#include <windows.h>

//redraw

//void setCursorPosition(int x, int y) {
//    COORD coord = { (SHORT)x, (SHORT)y };
//    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
//}
//
//int main() {
//    int playerX = 5;
//    bool running = true;
//
//    // Hide the blinking cursor
//    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
//    CONSOLE_CURSOR_INFO cursorInfo;
//    GetConsoleCursorInfo(out, &cursorInfo);
//    cursorInfo.bVisible = false;
//    SetConsoleCursorInfo(out, &cursorInfo);
//
//    while (running) {
//        setCursorPosition(0, 0);  // Reset to top-left instead of clearing screen
//
//        // Draw scene
//        for (int i = 0; i < playerX; ++i) std::cout << ' ';
//        std::cout << "@       \n";  // Overdraw with padding
//        std::cout << "Use A/D to move. Press Q to quit.\n";
//
//        // Handle input
//        if (_kbhit()) {
//            char ch = _getch();
//            ch = tolower(ch);
//
//            if (ch == 'a' && playerX > 0) playerX--;
//            else if (ch == 'd') playerX++;
//            else if (ch == 'q') running = false;
//        }
//
//        Sleep(50);
//    }
//
//    // Restore cursor
//    cursorInfo.bVisible = true;
//    SetConsoleCursorInfo(out, &cursorInfo);
//
//    return 0;
//}


//input

int main() {
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(hInput, &mode);
    SetConsoleMode(hInput, mode & ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT)); // raw input mode

    INPUT_RECORD inputRecord;
    DWORD events;
    bool running = true;

    std::cout << "Press arrow keys or Q to quit.\n";

    while (running) {
        ReadConsoleInput(hInput, &inputRecord, 1, &events);

        if (inputRecord.EventType == KEY_EVENT && inputRecord.Event.KeyEvent.bKeyDown) {
            switch (inputRecord.Event.KeyEvent.wVirtualKeyCode) {
            case VK_LEFT:
                std::cout << "LEFT\n";
                break;
            case VK_RIGHT:
                std::cout << "RIGHT\n";
                break;
            case 'Q':
                running = false;
                break;
            }
        }
    }

    return 0;
}