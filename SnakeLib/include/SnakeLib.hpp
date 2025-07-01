#pragma once

#include <vector>

enum CellStateIDX : unsigned char
{
	EMPTY = 0,
	FOOD = 1,
	SNAKE_BODY = 2,
	SNAKE_HEAD = 3
};

enum Direction : unsigned char
{
	UNDEFINED = 0,
	LEFT = 1,
	TOP = 2,
	RIGHT = 3,
	BOTTOM = 4
};

struct Dimensions
{
	unsigned int x_size = 0;
	unsigned int y_size = 0;

	Dimensions() = default;
	Dimensions(unsigned int x, unsigned y);
};

struct Cell
{
	CellStateIDX state = EMPTY;

	unsigned int x = 0;
	unsigned int y = 0;

	Cell* snake_next_to_tail = nullptr;
	Cell* snake_next_to_head = nullptr;

	//Cell() = default;
	Cell();
	Cell(const CellStateIDX& state) = delete;
	Cell(CellStateIDX&& state) = delete;
};


class SnakeGame
{
private:

	unsigned int score = 0;

	Cell* snake_head = nullptr;
	Cell* snake_tail = nullptr;
	Direction snake_direction = UNDEFINED;

	Cell* food = nullptr;

	Dimensions dimensions{1, 1};
	Cell** area = nullptr;
	std::vector<Cell*>* empty_area;

private:

	void init_area();
	void destroy_area();

	void place_food();
	void place_snake_head();

public:

	SnakeGame() = delete;
	SnakeGame(const SnakeGame& o) = delete;
	SnakeGame(const Dimensions& o);
	SnakeGame(Dimensions&& o);
	~SnakeGame();

	Dimensions get_dimensions() const;
	CellStateIDX get_cell_state_idx(unsigned int x, unsigned int y) const;
	unsigned int get_score() const;

	void set_snake_direction(Direction direction);

	int move_snake();
};