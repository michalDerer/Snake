#pragma once

#include <iostream>
#include <winddi.h>
#include "SnakeLib.hpp"

const char* table[] = { "╔","═","╗", "║", "╚", "╝",
						" ","Θ","@","X",
						"°", "@", "®", 
						"░", "▒", "▓", 
						"⌐", "─", "¬", "│", "┌", "┐", "└", "┘"};

//EMPTY = 0,
//FOOD = 1,
//SNAKE_HEAD = 2,
//SNAKE_BODY = 3,


void print(SnakeGame& game, Dimensions& dimensions)
{
	//SetConsoleOutputCP(437);
	//SetConsoleOutputCP(65001);
	//SetConsoleOutputCP(CP_UTF8);

	//std::cout << "╔═══╗\n";
	//std::cout << "║   ║\n";
	//std::cout << "╚═══╝\n";

	//first line
	std::cout << table[0];
	for (int i = 0; i < dimensions.y_size; i++)
		std::cout << table[1];
	std::cout << table[2] << "\n";

	for (int i = 0; i < dimensions.x_size; i++)
	{
		std::cout << table[3];
		for (int j = 0; j < dimensions.y_size; j++)
			std::cout << table[6 + game.get_area_cellstate_idx(i, j)];
		std::cout << table[3] << "\n";
	}

	//last line
	std::cout << table[4];
	for (int i = 0; i < dimensions.y_size; i++)
		std::cout << table[1];
	std::cout << table[5] << "\n";

}