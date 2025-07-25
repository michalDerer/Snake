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
//    INPUT_RECORD inputRecords;
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
//        //ReadConsoleInput(hInput, &inputRecords, 1, &events);
//
//        //if (inputRecords.EventType == KEY_EVENT && inputRecords.Event.KeyEvent.bKeyDown) {
//        //    char ch = inputRecords.Event.KeyEvent.uChar.AsciiChar;
//        //    int vk = inputRecords.Event.KeyEvent.wVirtualKeyCode;
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




//
//#include <iostream>
//#include <conio.h>
//#include <windows.h>

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



////---------------------------------------------------------------------------------------------
//#include <iostream>
//#include <windows.h>
//#include <array>
//
//int main() 
//{
//    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
//    DWORD mode;
//    GetConsoleMode(hInput, &mode);
//    SetConsoleMode(hInput, mode & ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT));
//
//    std::array<INPUT_RECORD, 1> inputRecords;
//    DWORD inputRecordsReaded;
//    bool isRunning = true;
//
//    std::cout << "Press arrow keys or Q to quit.\n";
//
//    while (isRunning) 
//    {
//        DWORD result = ReadConsoleInput(hInput, inputRecords.data(), inputRecords.size(), &inputRecordsReaded);
//
//        if (!result)
//        {
//            std::cout << "ERROR ReadConsoleInput\n";
//        }
//        else
//        {
//            std::cout << "Readed input records: " << inputRecordsReaded << "\n";
//
//            for (int i = 0; i < inputRecordsReaded; i++)
//            {
//                if (inputRecords[i].EventType == KEY_EVENT && inputRecords[i].Event.KeyEvent.bKeyDown)
//                {
//                    switch (inputRecords[i].Event.KeyEvent.wVirtualKeyCode)
//                    {
//                    case VK_LEFT:
//                        std::cout << "LEFT\n";
//                        break;
//                    case VK_RIGHT:
//                        std::cout << "RIGHT\n";
//                        break;
//                    case 'Q':
//                        isRunning = false;
//                        break;
//                    }
//                }
//            }
//        }
//    }
//
//    return 0;
//}
////---------------------------------------------------------------------------------------------



////---------------------------------------------------------------------------------------------
//#include <windows.h>
//#include "SnakeGuiConsole.hpp"
//
//int main()
//{
//    SetConsoleOutputCP(CP_UTF8);
//
//    try
//    {
//        //ocekovat konstruktory
//        //Dimensions{}
//        //Cell
//
//        Dimensions dimensions(2, 2);
//        SnakeGame game(dimensions);
//
//        draw_game_state(game, dimensions, evaluate_complex);
//        game.set_snake_direction(TOP);
//        std::cout << game.snake_move() << " " << game.get_score() <<  "\n";
//
//        draw_game_state(game, dimensions, evaluate_complex);
//        game.set_snake_direction(RIGHT);
//        std::cout << game.snake_move() << " " << game.get_score() << "\n";
//
//        draw_game_state(game, dimensions, evaluate_complex);
//        game.set_snake_direction(TOP);
//        std::cout << game.snake_move() << " " << game.get_score() << "\n";
//
//    }
//    catch (std::exception e)
//    {
//        std::cout << e.what() << "\n";
//    }
//}
////---------------------------------------------------------------------------------------------

//#include <chrono>
#include <thread>
#include <windows.h>
#include "SnakeGuiConsole.hpp"

int main()
{
    SetConsoleOutputCP(CP_UTF8);

    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(hInput, &mode);
    SetConsoleMode(hInput, mode & ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT));

    INPUT_RECORD inputRecord;
    DWORD inputRecordsReaded;
    bool isRunning = true;
    
    //Dimensions dimensions(2, 2);
    //SnakeGame game(dimensions);



    std::cout << "Press arrow keys or Q to quit.\n";
    //draw_game_state(game, dimensions, evaluate_simple);



    while (isRunning)
    {
        std::cout << "SLEEP\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));


        /*try 
        {*/
            DWORD result = ReadConsoleInput(hInput, &inputRecord, 1, &inputRecordsReaded);
        
            if (!result)
            {
                std::cout << "ERROR ReadConsoleInput\n";
            }
            else
            {
                if (inputRecord.EventType == KEY_EVENT && inputRecord.Event.KeyEvent.bKeyDown)
                {
                    //std::cout << "CODE: " << inputRecord.Event.KeyEvent.wVirtualKeyCode << "\n";

                    switch (inputRecord.Event.KeyEvent.wVirtualKeyCode)
                    {
                    case 'W':
                        std::cout << "W\n";
                        //game.set_snake_direction(TOP);
                        break;

                    case 'A':
                        std::cout << "A\n";
                        //game.set_snake_direction(LEFT);
                        break;

                    case 'S':
                        std::cout << "S\n";
                        //game.set_snake_direction(BOTTOM);
                        break;

                    case 'D':
                        std::cout << "D\n";
                        //game.set_snake_direction(RIGHT);
                        break;

                    case 'Q':
                        isRunning = false;
                        break;

                    default:
                        std::cout << "UNDEFINED\n";
                        break;
                    }
                }

            //    std::cout << game.snake_move() << " " << game.get_score() << "\n";
            //    draw_game_state(game, dimensions, evaluate_simple);

            }
        /*}
        catch (std::exception e)
        {
            std::cout << e.what() << "\n";
        }*/
    }




}