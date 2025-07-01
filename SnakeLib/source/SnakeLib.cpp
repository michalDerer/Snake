#include <iostream>
//#include <stdexcept>
#include <random>
#include "SnakeLib.hpp"


Dimensions::Dimensions(unsigned int x, unsigned y) : x_size(x), y_size(y)
{
#ifdef  _DEBUG
	std::cout << "Dimensions(unsigned int x, unsigned y) " << x << ", " << y << "\n";
#endif //  _DEBUG
}

//Position::Position(unsigned int x, unsigned y) : x(x), y(y)
//{
//#ifdef  _DEBUG
//	std::cout << "Position(unsigned int x, unsigned y) " << x << ", " << y << "\n";
//#endif //  _DEBUG
//}

//Bodypart::Bodypart(unsigned int x, unsigned int y) : x(x), y(y)
//{
//#ifdef  _DEBUG
//	std::cout << "Bodypart(int x, int y) " << x << ", " << y << "\n";
//#endif //  _DEBUG
//}

Cell::Cell(const CellStateIDX& o) : state(o)
{
#ifdef  _DEBUG
	std::cout << "Cell(const CellStateIDX& o)" << "\n";
#endif //  _DEBUG
}

Cell::Cell(CellStateIDX&& o) : state(o)
{
#ifdef  _DEBUG
	std::cout << "Cell(CellStateIDX&& o)" << "\n";
#endif //  _DEBUG
}

//CellStateIDX Cell::get_state() const
//{
//	return state;
//}

SnakeGame::SnakeGame(const Dimensions& o)
{
#ifdef  _DEBUG
	std::cout << "SnakeGame(const Dimensions& o)" << "\n";
#endif //  _DEBUG

	if (o.x_size == 0 || o.y_size == 0)
	{
		throw std::runtime_error("Invalid ground dimensions");
	}

	dimensions.x_size = o.x_size;
	dimensions.y_size = o.y_size;

	init_area();
}

SnakeGame::SnakeGame(Dimensions&& o) : dimensions(std::move(o))
{
#ifdef _DEBUG
	std::cout << "SnakeGame(Dimensions&& o)" << "\n";
#endif // DEBUG

	if (dimensions.x_size == 0 || dimensions.y_size == 0)
	{
		throw std::runtime_error("Invalid ground dimensions");
	}

	init_area();
}

SnakeGame::~SnakeGame()
{
#ifdef _DEBUG
	std::cout << "~SnakeGame()" << "\n";
#endif // DEBUG

	destroy_area();
}

void SnakeGame::init_area()
{
	area = new Cell * [dimensions.x_size] {};

	for (unsigned int i = 0; i < dimensions.x_size; i++)
	{
		area[i] = new Cell[dimensions.y_size]{};

		for (unsigned int j = 0; j < dimensions.y_size; j++)
		{
			area[i][j].x = i;
			area[i][j].y = j;
		}
	}
}

void SnakeGame::destroy_area()
{
	for (unsigned int i = 0; i < dimensions.x_size; i++)
	{
		delete[] area[i];
		area[i] = nullptr;
	}

	delete[] area;
	area = nullptr;
}

Dimensions SnakeGame::get_dimensions() const
{
	return dimensions;
}

unsigned int SnakeGame::get_score() const
{
	return score;
}

void SnakeGame::update()
{
	Cell* next_cell = nullptr;

	switch (snake_direction)
	{
	case UNDEFINED:
		return;

	case LEFT:
		if (snake_head->x == 0)
		{
			next_cell = &area[dimensions.x_size - 1][snake_head->y];
		}
		else
		{
			next_cell = &area[snake_head->x - 1][snake_head->y];
		}
		break;

	case TOP:
		if (snake_head->y == 0)
		{
			next_cell = &area[snake_head->x][dimensions.y_size - 1];
		}
		else
		{
			next_cell = &area[snake_head->x][snake_head->y - 1];
		}
		break;

	case RIGHT:
		if (snake_head->x + 1 == dimensions.x_size)
		{
			next_cell = &area[0][snake_head->y];
		}
		else
		{
			next_cell = &area[snake_head->x + 1][snake_head->y];
		}
		break;

	case BOTTOM:
		if (snake_head->y + 1 == dimensions.y_size)
		{
			next_cell = &area[snake_head->x][0];
		}
		else
		{
			next_cell = &area[snake_head->x][snake_head->y + 1];
		}
		break;

	default:
		break;
	}
}

CellStateIDX SnakeGame::get_cell_state_idx(unsigned int x, unsigned int y) const
{
	return area[x][y].state;
}

