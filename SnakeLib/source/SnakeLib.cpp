#include <iostream>
//#include <stdexcept>
#include <random>
#include "SnakeLib.hpp"


Bodypart::Bodypart(unsigned int x, unsigned int y) : x(x), y(y)
{
#ifdef  _DEBUG
	std::cout << "Bodypart(int x, int y) " << x << ", " << y << "\n";
#endif //  _DEBUG
}

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

CellStateIDX Cell::get_state() const
{
	return state;
}

Dimensions::Dimensions(unsigned int x, unsigned y) : x_size(x), y_size(y)
{
#ifdef  _DEBUG
	std::cout << "Dimensions(unsigned int x, unsigned y) " << x << ", " << y << "\n";
#endif //  _DEBUG
}

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

	init();
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

	init();
}

SnakeGame::~SnakeGame()
{
#ifdef _DEBUG
	std::cout << "~SnakeGame()" << "\n";
#endif // DEBUG

	destroy();
}

void SnakeGame::create_ground()
{
	ground = new Cell*[dimensions.x_size]{};

	for (unsigned int i = 0; i < dimensions.x_size; i++)
	{
		ground[i] = new Cell[dimensions.y_size]{};
	}
}

void SnakeGame::destroy_ground()
{
	for (unsigned int i = 0; i < dimensions.x_size; i++)
	{
		delete[] ground[i];
		ground[i] = nullptr;
	}

	delete[] ground;
	ground = nullptr;
}

void SnakeGame::create_snake()
{
	snake.emplace_front(Bodypart{ random(dimensions.x_size), random(dimensions.y_size) });
}

void SnakeGame::destroy_snake()
{
	snake.clear();
}

void SnakeGame::init()
{
	std::srand(std::time({}));

	gen = std::mt19937(rd());											// Create a random number engine
	//dist = std::uniform_int_distribution<unsigned int>(0, UINT32_MAX);	// Define the distribution range
	dist = std::uniform_int_distribution<unsigned int>(0, 10);

	create_ground();
	create_snake();
}

void SnakeGame::destroy()
{
	destroy_snake();
	destroy_ground();
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

}

unsigned int SnakeGame::random(unsigned int range)
{
	//return std::rand() % range;
	return dist(gen);
}