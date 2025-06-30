#pragma once

#include <forward_list>
#include <random>
#include <stdint.h>

enum CellStateIDX : unsigned char
{
	EMPTY = 0,
	FOOD = 1,
	SNAKE_BODY = 2,
	SNAKE_HEAD = 3
};

enum Direction : unsigned char
{
	LEFT = 0,
	TOP = 1,
	RIGHT = 2,
	BOTTOM = 3
};

struct Bodypart
{
	unsigned int x;
	unsigned int y;

	Bodypart() = default;
	Bodypart(unsigned int x, unsigned int y);
};


class ICellPublic
{
public:
	virtual CellStateIDX get_state() const = 0;
};

struct Cell : public ICellPublic
{
	CellStateIDX state = EMPTY;

	Cell() = default;
	Cell(const CellStateIDX& state);
	Cell(CellStateIDX&& state);

public:
	CellStateIDX get_state() const override;
};

struct Dimensions
{
	unsigned int x_size = 0;
	unsigned int y_size = 0;

	Dimensions(unsigned int x, unsigned y);
};

class SnakeGame
{
private:

	std::random_device rd;								// Seed
	std::mt19937 gen;									// Mersenne Twister engine
	std::uniform_int_distribution<unsigned int> dist;	// Define the distribution range

	Dimensions dimensions{1, 1};
	unsigned int score = 0;

	Cell** ground = nullptr;
	std::forward_list<Bodypart> snake{};


private:

	void create_ground();
	void destroy_ground();

	void create_snake();
	void destroy_snake();

	void init();
	void destroy();


public:

	SnakeGame() = delete;
	SnakeGame(const SnakeGame& o) = delete;

	SnakeGame(const Dimensions& o);
	SnakeGame(Dimensions&& o);
	~SnakeGame();


	Dimensions get_dimensions() const;
	unsigned int get_score() const;

	void update();

	unsigned int random(unsigned int range);
};