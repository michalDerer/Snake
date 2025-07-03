#pragma once

#include <vector>


enum CellStateIDX : unsigned char
{
	EMPTY = 0,
	FOOD = 1,
	SNAKE_HEAD = 2,
	SNAKE_BODY = 3,
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
	~Dimensions();
};

struct CellPublic
{
	virtual const CellStateIDX get_state() const = 0;

	virtual const unsigned int get_x() const = 0;
	virtual const unsigned int get_y() const = 0;

	virtual const CellPublic& get_snake_next_to_head() const = 0;
	virtual const CellPublic& get_snake_next_to_tail() const = 0;
};

struct Cell : public CellPublic
{
	CellStateIDX state = EMPTY;

	unsigned int x = 0;
	unsigned int y = 0;

	Cell* snake_next_to_head = nullptr;
	Cell* snake_next_to_tail = nullptr;


	//Cell() = default;
	Cell();
	Cell(const CellStateIDX& state) = delete;
	Cell(CellStateIDX&& state) = delete;
	~Cell();

	const CellStateIDX get_state() const override;

	const unsigned int get_x() const override;
	const unsigned int get_y() const override;

	const CellPublic& get_snake_next_to_head() const override;
	const CellPublic& get_snake_next_to_tail() const override;
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

	const Dimensions get_area_dimensions() const;
	const CellStateIDX get_area_cell_state(unsigned int x, unsigned int y) const;
	const CellPublic& get_snake_head() const;
	const unsigned int get_score() const;

	void set_snake_direction(Direction direction);

	int snake_move();
};