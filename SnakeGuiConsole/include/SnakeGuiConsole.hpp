#pragma once

#include <iostream>
#include <winddi.h>
#include "SnakeLib.hpp"

// mal by byt source code subor ulozeny v UTF-8 kodovani, 
// ak chcem vypisovat do konzoly nastavenej v UTF-8

//nastavuje konzolu do prislusneho charakter setu
//SetConsoleOutputCP(65001);
//SetConsoleOutputCP(CP_UTF8);


const char* table[] = { "╔", "═", "╗", "║", "╚", "╝",
						" ", "Θ", "@", "X",
						" ", "Θ", "@", "─", "│", "┌", "┐", "└", "┘",
						"░", "▒", "▓", "°"};

/*
enum CellStateIDX : unsigned char
{
	EMPTY = 0,
	FOOD = 1,
	SNAKE_HEAD = 2,
	SNAKE_BODY = 3,
};
*/

//typedef unsigned int (*EvaluationFunction)(SnakeGame& game, unsigned int x, unsigned int y);
//c++11+
using EvaluationFunction = unsigned int (*)(SnakeGame& game, unsigned int x, unsigned int y);


bool is_area_cell_state_SNAKE(SnakeGame& game, unsigned int x, unsigned int y)
{
	return game.get_area_cell_state(x, y) >= SNAKE_HEAD;
}

unsigned int evaluate_simple(SnakeGame& game, unsigned int x, unsigned int y)
{
	return 6 + game.get_area_cell_state(x, y);
}

unsigned int evaluate_complex(SnakeGame& game, unsigned int x, unsigned int y)
{
	CellStateIDX state = game.get_area_cell_state(x, y);
	unsigned int state_translated = 0;

	switch (state)
	{
	case EMPTY:
	case FOOD:
	case SNAKE_HEAD:
		//netreba prelozit symbol
		state_translated = state;
		break;

	case SNAKE_BODY:
		//treba zistit symbol pre zadanu cast tela hada

		state_translated = state; //for now
		break;

	default:
		throw std::runtime_error("Unknow CellStateIDX enum value");
		break;
	}

	return 10 + state;
}

void draw_game_state(SnakeGame& game, Dimensions& dimensions, EvaluationFunction ef)
{
	//first line
	std::cout << table[0];
	for (int i = 0; i < dimensions.y_size; i++)
		std::cout << table[1];
	std::cout << table[2] << "\n";

	//game lines
	for (int i = 0; i < dimensions.x_size; i++)
	{
		std::cout << table[3];
		for (int j = 0; j < dimensions.y_size; j++)
			std::cout << table[ef(game, i, j)];
		std::cout << table[3] << "\n";
	}

	//last line
	std::cout << table[4];
	for (int i = 0; i < dimensions.y_size; i++)
		std::cout << table[1];
	std::cout << table[5] << "\n";
}