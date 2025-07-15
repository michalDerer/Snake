#include <iostream>
#include "SnakeLib.hpp"


Dimensions::Dimensions(unsigned int x, unsigned y) : x_size(x), y_size(y)
{
#ifdef  _DEBUG
	std::cout << "Dimensions(unsigned int x, unsigned y) " << x << ", " << y << "\n";
#endif //  _DEBUG
}

Dimensions::~Dimensions()
{
#ifdef  _DEBUG
	std::cout << "~Dimensions() " << x_size << " " << y_size << "\n";
#endif //  _DEBUG
}

Cell::Cell()
{
#ifdef  _DEBUG
	std::cout << "Cell()" << "\n";
#endif //  _DEBUG
}

Cell::~Cell()
{
#ifdef  _DEBUG
	std::cout << "~Cell()" << "\n";
#endif //  _DEBUG
}

const CellStateIDX Cell::get_state() const
{
	return state;
}

const unsigned int Cell::get_x() const
{
	return x;
}
const unsigned int Cell::get_y() const
{
	return y;
}

const CellPublic* Cell::get_snake_next_to_head() const
{
	return snake_next_to_head;
}

const CellPublic* Cell::get_snake_next_to_tail() const
{
	return snake_next_to_tail;
}

SnakeGame::SnakeGame(const Dimensions& o)
{
#ifdef  _DEBUG
	std::cout << "SnakeGame(const Dimensions& o)" << "\n";
#endif //  _DEBUG

	if (o.x_size == 0 || o.y_size == 0)
	{
		throw std::runtime_error("Invalid dimensions");
	}

	dimensions.x_size = o.x_size;
	dimensions.y_size = o.y_size;
	
	std::srand(std::time(nullptr));
	init_area();
	place_food();
	place_snake_head();
}

SnakeGame::SnakeGame(Dimensions&& o) : dimensions(std::move(o))
{
#ifdef _DEBUG
	std::cout << "SnakeGame(Dimensions&& o)" << "\n";
#endif // DEBUG

	if (dimensions.x_size == 0 || dimensions.y_size == 0)
	{
		throw std::runtime_error("Invalid dimensions");
	}

	std::srand(std::time(nullptr));
	init_area();
	place_food();
	place_snake_head();
}

SnakeGame::~SnakeGame()
{
#ifdef _DEBUG
	std::cout << "~SnakeGame()" << "\n";
#endif // DEBUG

	snake_head = nullptr;
	snake_tail = nullptr;
	food = nullptr;
	destroy_area();
}

void SnakeGame::init_area()
{
	empty_area = new std::vector<Cell*>(/* dimensions.x_size * dimensions.y_size */);
	empty_area->reserve(dimensions.x_size * dimensions.y_size);

	area = new Cell * [dimensions.x_size] {};
	for (unsigned int i = 0; i < dimensions.x_size; i++)
	{
		area[i] = new Cell[dimensions.y_size]{};

		for (unsigned int j = 0; j < dimensions.y_size; j++)
		{
			area[i][j].x = i;
			area[i][j].y = j;
			empty_area->push_back(area[i] + j);
		}
	}
}

void SnakeGame::destroy_area()
{
	empty_area->clear();
	delete empty_area;
	empty_area = nullptr;

	for (unsigned int i = 0; i < dimensions.x_size; i++)
	{
		delete[] area[i];
		area[i] = nullptr;
	}

	delete[] area;
	area = nullptr;
}

void SnakeGame::place_food()
{
	if (food != nullptr)
	{
		food->state = EMPTY;
		empty_area->push_back(food);
		food = nullptr;
	}

	if (empty_area->empty())
	{
		return;
	}

	int idx = rand() % empty_area->size();
	food = (*empty_area)[idx];
	empty_area->erase(empty_area->begin() + idx);
	food->state = FOOD;
}

void SnakeGame::place_snake_head()
{
	int idx = rand() % empty_area->size();
	snake_head = empty_area->at(idx);
	snake_tail = snake_head;
	empty_area->erase(empty_area->begin() + idx);
	snake_head->state = SNAKE_HEAD;
}

const Dimensions SnakeGame::get_area_dimensions() const
{
	return dimensions;
}

const unsigned int SnakeGame::get_score() const
{
	return score;
}

const CellStateIDX SnakeGame::get_area_cell_state(unsigned int x, unsigned int y) const
{
	return area[x][y].state;
}

const CellPublic* SnakeGame::get_snake_head() const
{
	return snake_head;
}

void SnakeGame::set_snake_direction(Direction direction)
{
	snake_direction = direction;
}

/// <summary>
/// Update game state by one step.
/// </summary>
/// <returns> 
///		0 - game continues,
///		1 - undefined snake direction,
///		2 - game stopped GAME OVER 
/// </returns>
int SnakeGame::snake_move()
{
	Cell* next_cell = nullptr;

	switch (snake_direction)
	{
	case UNDEFINED:
		//undefined directiona
		return 1;

	case LEFT:
		if (snake_head->y == 0)
		{
			next_cell = &area[snake_head->x][dimensions.y_size - 1];
		}
		else
		{
			next_cell = &area[snake_head->x][snake_head->y - 1];
		}
		break;

	case TOP:
		if (snake_head->x == 0)
		{
			next_cell = &area[dimensions.x_size - 1][snake_head->y];
		}
		else
		{
			next_cell = &area[snake_head->x - 1][snake_head->y];
		}
		break;

	case RIGHT:
		if (snake_head->y + 1 == dimensions.y_size)
		{
			next_cell = &area[snake_head->x][0];
		}
		else
		{
			next_cell = &area[snake_head->x][snake_head->y + 1];
		}
		break;

	case BOTTOM:
		if (snake_head->x + 1 == dimensions.x_size)
		{
			next_cell = &area[0][snake_head->y];
		}
		else
		{
			next_cell = &area[snake_head->x + 1][snake_head->y];
		}
		break;

	default:
		throw std::runtime_error("Unknown Direction enum value");
		break;
	}

	switch (next_cell->state)
	{
	case EMPTY:
		if (snake_head->snake_next_to_tail == nullptr)
		{
			//snake head bez tela, len posun hlavu, update empty area

			next_cell->state = SNAKE_HEAD;
			snake_head->state = EMPTY;

			auto found = std::find_if(empty_area->begin(), empty_area->end(), [&next_cell](Cell* c)
				{
					return c->x == next_cell->x && c->y == next_cell->y;
				});
			//ak nenastane zhoda vrati iterator na posledny prvok
			if (found != empty_area->end())
			{
				empty_area->erase(found);
			}
			else
			{
				//vratilo iterator na posledny prvok, treba overit ci je zhoda
				if ((*found)->x == next_cell->x && (*found)->y == next_cell->y)
				{
					empty_area->erase(found);
				}
			}
			empty_area->push_back(snake_head);

			snake_head = next_cell;
			snake_tail = next_cell;
		}
		else
		{
			//snake head s telom, posun hlavy, chvostu a update empty area

			next_cell->state = SNAKE_HEAD;
			snake_head->state = SNAKE_BODY;
			next_cell->snake_next_to_tail = snake_head;
			snake_head->snake_next_to_head = next_cell;
			snake_head = next_cell;

			snake_tail->state = EMPTY;
			snake_tail = snake_tail->snake_next_to_head;
			snake_tail->snake_next_to_tail->snake_next_to_head = nullptr;
			snake_tail->snake_next_to_tail = nullptr;
		}
		break;
		
	case FOOD:
		//netreba update empty area, food je odobraty z empty are, food sa zmeni na snake head
		food = nullptr;
		score++;

		next_cell->state = SNAKE_HEAD;
		snake_head->state = SNAKE_BODY;
		next_cell->snake_next_to_tail = snake_head;
		snake_head->snake_next_to_head = next_cell;
		snake_head = next_cell;

		place_food();
		break;
			
	case SNAKE_BODY:
	case SNAKE_HEAD:
		//game over
		return 2;

	default:
		throw std::runtime_error("Unknown CellStateIDX enum value");
		break;
	}

	//game continues
	return 0;
}

