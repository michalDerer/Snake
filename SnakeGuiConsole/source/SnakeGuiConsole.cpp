#include <stdio.h>
#include <iostream>
#include <string>
#include <windows.h>


#include <fcntl.h>
#include <io.h>


#include <SnakeLib.hpp>



void setup_console_utf8() 
{
    // Set the console to UTF-8
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // Optional: set output mode for wide text if using std::wcout
    //_setmode(_fileno(stdout), _O_U8TEXT);
}

void ClearConsole()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) return;

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD cellCount, count;
    COORD homeCoords = { 0, 0 };

    if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) return;

    cellCount = csbi.dwSize.X * csbi.dwSize.Y;

    // Fill the screen with blanks
    FillConsoleOutputCharacter(hConsole, ' ', cellCount, homeCoords, &count);
    FillConsoleOutputAttribute(hConsole, csbi.wAttributes, cellCount, homeCoords, &count);

    // Move the cursor to the top-left corner
    SetConsoleCursorPosition(hConsole, homeCoords);
}


std::string make_line()
{
    int l = 5;
    int symbol = std::rand() % l;
    std::string s{};

    s.append("|");
    for (int i = 0; i < l; i++)
    {
        s.append((i == symbol ? "A" : "0"));
    }
    s.append("|");
    return s;
}

void draw()
{
    //std::string s = make_table();

    /*std::u8string s = u8"╔═╗";
    std::string s_utf8(s.begin(), s.end());

    std::cout << s_utf8 << std::endl;*/

    std::cout << make_line() << "\n";
}




int main() 
{
    
    
    SnakeGame game{Dimensions{2,2}};



    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);

    if (hConsole == INVALID_HANDLE_VALUE) return -1;
    if (hInput == INVALID_HANDLE_VALUE) return -2;

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD cellCount, count;
    COORD homeCoords = { 0, 0 };

    DWORD events = 0;
    INPUT_RECORD inputRecord;


    //std::cout << "This will be cleared in 3 seconds..." << std::endl;
    //Sleep(3000); // Pause for 3 seconds
    //ClearConsole();
    //std::cout << "Console cleared!" << std::endl;

    //setup_console_utf8();
    ClearConsole();
    draw();

    // Enable window input
    SetConsoleMode(hInput, ENABLE_WINDOW_INPUT | ENABLE_PROCESSED_INPUT);
    //std::cout << "Press ESC to quit...\n";

    //int i = 0;
    while (true) 
    {
        //ClearConsole();
        //draw();
        //Sleep(1000);

        //std::cout << game.random(10) << "\n";

        int x[10] = {};
        for (int i = 0; i < 999; i++)
        {
            x[game.random(10)] += 1;
        }

        for (int i = 0; i < 10; i++)
            std::cout << x[i] << "\n";

    //    draw();
    //    std::cout << "i:" << ++i << "\n";
    //    Sleep(1000);


        //ReadConsoleInput(hInput, &inputRecord, 1, &events);

        //if (inputRecord.EventType == KEY_EVENT && inputRecord.Event.KeyEvent.bKeyDown) {
        //    char ch = inputRecord.Event.KeyEvent.uChar.AsciiChar;
        //    int vk = inputRecord.Event.KeyEvent.wVirtualKeyCode;

        //    //std::cout << "Key pressed: " << ch << " (VK: " << vk << ")\n";

        //    //if (ch == 'c') ClearConsole();

        //    if (vk == VK_ESCAPE) break;
        //}
    }

    return 0;
}















//#include <iostream>
////#include "snake.hpp"
//
//
//int main()
//{
//	try
//	{
//		/*Dimensions d1{ 1,1 };
//		SnakeGame g1(d1);
//
//		SnakeGame g2(Dimensions{2,2});
//
//		auto dd1 = g1.get_dimensions();
//		auto dd2 = g2.get_dimensions();
//
//		std::cout << "x:" << dd1.x_size << " y:" << dd1.y_size << std::endl;
//		std::cout << "x:" << dd2.x_size << " y:" << dd2.y_size << std::endl;*/
//
//		;
//
//		SnakeGame g1(Dimensions{ 2,2 });
//
//		auto dd1 = g1.get_dimensions();
//
//		std::cout << "x:" << dd1.x_size << " y:" << dd1.y_size << std::endl;
//
//
//	}
//	catch (const std::exception& e)
//	{
//		std::cout << e.what() << std::endl;
//	}
//
//	return 0;
//}





















//------------------------------------------------------------------------


//#include <iostream>
//#include "SnakeGuiConsole.hpp"
//#include "SnakeLib.hpp"
//
//using namespace std;
//
//int main()
//{ 
//	cout << "Snake CONSOLE." << endl;
//
//	TestLib lib{};
//
//	cout << endl;
//	lib.message();
//	cout << endl;
//
//	const ITestDataPublic***& data = lib.get_data();
//
//	((TestData*)data[0][0])->x = 1;
//
//	for (int i = 0; i < 2; i++)
//		for (int j = 0; j < 2; j++)
//		{
//			cout << "Data at i:" << i << " j:" << j << " = " 
//				<< data[i][j]->get_x() 
//				<< ", " 
//				<< data[i][j]->get_y() 
//				<< endl;
//
//			//cout << "Data at i:" << i << " j:" << j << " = " 
//			//	<< lib.get_data(i,j).get_x()
//			//	<< ", " 
//			//	<< lib.get_data(i, j).get_y()
//			//	<< endl;
//		}
//
//	cout << endl;
//
//	const int** start = lib.get_xarr();
//	
//	int x[2] = {2,2};
//	start[0] = x;
//	start[1] = x;
//
//	for (int i = 0; i < 2; i++)
//		for (int j = 0; j < 2; j++)
//			cout << " " << start[i][j] << " ";
//
//
//	cout << endl;
//	return 0;
//}
