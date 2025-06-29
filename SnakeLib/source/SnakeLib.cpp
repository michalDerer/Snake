

















#include <iostream>
#include <stdexcept>
#include "snake.hpp"



Bodypart::Bodypart(int x, int y) : x(x), y(y)
{
#ifdef  _DEBUG
	std::cout << "Bodypart(int x, int y)" << std::endl;
#endif //  _DEBUG
}

GroundCell::GroundCell(GroundCellState state) : state(state)
{
#ifdef  _DEBUG
	std::cout << "GroundCell(GroundCellState state)" << std::endl;
#endif //  _DEBUG
}

SnakeGame::SnakeGame(const Dimensions& o)
{
#ifdef  _DEBUG
	std::cout << "SnakeGame(const Dimensions& o)" << std::endl;
#endif //  _DEBUG

	if (o.x_size == 0 || o.y_size == 0)
	{
		throw std::runtime_error("Invalid playground dimensions");
	}

	dimensions.x_size = o.x_size;
	dimensions.y_size = o.y_size;

	init();
}

SnakeGame::SnakeGame(Dimensions&& o) : dimensions(std::move(o))
{
#ifdef _DEBUG
	std::cout << "SnakeGame(Dimensions&& o)" << std::endl;
#endif // DEBUG

	if (dimensions.x_size == 0 || dimensions.y_size == 0)
	{
		throw std::runtime_error("Invalid playground dimensions");
	}

	init();
}

SnakeGame::~SnakeGame()
{
#ifdef _DEBUG
	std::cout << "~SnakeGame()" << std::endl;
#endif // DEBUG

	destroy();
}

void SnakeGame::create_ground()
{
	ground = new GroundCell * [dimensions.x_size] {};

	for (unsigned int i = 0; i < dimensions.x_size; ++i)
	{
		ground[i] = new GroundCell[dimensions.y_size]{};

		for (unsigned int j = 0; j < dimensions.y_size; ++j)
		{
			ground[i][j] = GroundCell(FOOD);
		}
	}
}

void SnakeGame::destroy_ground()
{
	for (unsigned int i = 0; i < dimensions.x_size; ++i)
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
}

void SnakeGame::init()
{
	std::srand(std::time({}));

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

int SnakeGame::random(int range)
{
	return std::rand() % range;
}




























//----------------------------------------------------------------------------


#include <iostream>
#include "SnakeLib.hpp"


#define out(s1) std::cout << s1 << "\n"

TestData::TestData()
{
	out("TestData()");
}

TestData::TestData(int x, int y) : x(x), y(y)
{
	std::cout << "TestData(int x, int y) " << x << " " << y << "\n";
}

TestData::~TestData()
{
	std::cout << "~TestData()" << "\n";
}

int TestData::get_x() const
{
	return x;
}

void TestData::set_x(int v)
{
	x = v;
}

int TestData::get_y() const
{
	return y;
}

void TestData::set_y(int v)
{
	y = v;
}

TestLib::TestLib()
{
	out("TestLib()");

	data = new TestData**[2]{};

	for (int i = 0; i < 2; i++)
	{
		data[i] = new TestData*[2]{};

		for (int j = 0; j < 2; j++)
		{
			data[i][j] = new TestData{i,j};
		}
	}
}

TestLib::~TestLib()
{
	out("~TestLib()");

	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
		{
			delete data[i][j];
			data[i][j] = nullptr;
		}

	for (int i = 0; i < 2; i++)
	{
		delete[] data[i];
		data[i] = nullptr;
	}

	delete[] data;
	data = nullptr;
}

const ITestDataPublic***& TestLib::get_data() const
{
	return (const ITestDataPublic***&)data;
}

//const ITestDataPublic& TestLib::get_data(int x, int y) const
//{
//	return data[x][y];
//}

void TestLib::message()
{
	std::cout << "Snake LIB." << "\n";
}
