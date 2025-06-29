#pragma once












#include <forward_list>

struct Bodypart
{
	unsigned int x;
	unsigned int y;

	Bodypart() = default;
	Bodypart(int x, int y);
};

enum GroundCellState
{
	EMPTY = 0x0,
	FOOD = 0x1,
	SNAKE_BODY = 0x2,
	SNAKE_HEAD = 0x3
};

struct GroundCell
{
	GroundCellState state = EMPTY;

	GroundCell() = default;
	GroundCell(GroundCellState state);
};

struct Dimensions
{
	unsigned int x_size = 0;
	unsigned int y_size = 0;
};

class SnakeGame
{
private:

	Dimensions dimensions{};
	unsigned int score = 0;

	GroundCell** ground = nullptr;
	std::forward_list<Bodypart> snake{};


private:

	void create_ground();
	void destroy_ground();

	void create_snake();
	void destroy_snake();

	void init();
	void destroy();

	//int random(int range);

public:

	SnakeGame() = delete;
	SnakeGame(const SnakeGame& o) = delete;

	SnakeGame(const Dimensions& o);
	SnakeGame(Dimensions&& o);
	~SnakeGame();


	Dimensions get_dimensions() const;
	unsigned int get_score() const;

	void update();

	int random(int range);
};



















//--------------------------------------------------------

class ITestDataPublic
{
public:
	virtual int get_x() const = 0;

	virtual int get_y() const = 0;
};

class TestData : public ITestDataPublic
{
	int y = 0;

public:
	int x = 0;
	TestData();
	TestData(int x, int y);
	~TestData();

	int get_x() const override;
	void set_x(int v);

	int get_y() const override;
	void set_y(int v);
};

class TestLib
{
	TestData*** data = nullptr;


public:
	TestLib();
	~TestLib();

	const ITestDataPublic***& get_data() const;
	//const ITestDataPublic& get_data(int x, int y) const;

	const int** get_xarr() 
	{ 
		int** s = new int*[2] {};
		
		for (int i = 0; i < 2; i++)
		{
			s[i] = new int[2] {};
			for (int j = 0; j < 2; j++)
				s[i][j] = j;
		}

		return (const int**)s; 
	};

	void message();

};