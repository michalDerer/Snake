#pragma once

enum CellStateIDX : unsigned char
{
	EMPTY = 0,
	FOOD = 1,
	SNAKE_BODY = 2,
	SNAKE_HEAD = 3
};

enum Direction : char
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

	Dimensions(unsigned int x, unsigned y);
};

//struct Position
//{
//	unsigned int x = 0;
//	unsigned int y = 0;
//
//	Position(unsigned int x, unsigned y);
//};

//struct Bodypart
//{
//	unsigned int x;
//	unsigned int y;
//
//	Bodypart() = default;
//	Bodypart(unsigned int x, unsigned int y);
//};


//class ICellPublic
//{
//public:
//	virtual CellStateIDX get_state() const = 0;
//};

struct Cell //: public ICellPublic
{
	CellStateIDX state = EMPTY;

	unsigned int x = 0;
	unsigned int y = 0;

	Cell* snake_next_to_tail = NULL;
	Cell* snake_next_to_head = NULL;

	Cell() = default;
	Cell(const CellStateIDX& state);
	Cell(CellStateIDX&& state);

public:
	//CellStateIDX get_state() const override;
};



class SnakeGame
{
private:

	Dimensions dimensions{1, 1};
	unsigned int score = 0;

	Cell* snake_head = nullptr;
	Cell* snake_tail = nullptr;

	Direction snake_direction = UNDEFINED;

	Cell** area = nullptr;


private:

	void init_area();
	void destroy_area();


public:

	SnakeGame() = delete;
	SnakeGame(const SnakeGame& o) = delete;

	SnakeGame(const Dimensions& o);
	SnakeGame(Dimensions&& o);
	~SnakeGame();


	Dimensions get_dimensions() const;
	unsigned int get_score() const;

	void update();

	CellStateIDX get_cell_state_idx(unsigned int x, unsigned int y) const;

};