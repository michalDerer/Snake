















#include <iostream>
//#include "snake.hpp"


int main()
{
	try
	{
		/*Dimensions d1{ 1,1 };
		SnakeGame g1(d1);

		SnakeGame g2(Dimensions{2,2});

		auto dd1 = g1.get_dimensions();
		auto dd2 = g2.get_dimensions();

		std::cout << "x:" << dd1.x_size << " y:" << dd1.y_size << std::endl;
		std::cout << "x:" << dd2.x_size << " y:" << dd2.y_size << std::endl;*/

		;

		SnakeGame g1(Dimensions{ 2,2 });

		auto dd1 = g1.get_dimensions();

		std::cout << "x:" << dd1.x_size << " y:" << dd1.y_size << std::endl;


	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	return 0;
}





















//------------------------------------------------------------------------


#include <iostream>
#include "SnakeGuiConsole.hpp"
#include "SnakeLib.hpp"

using namespace std;

int main()
{ 
	cout << "Snake CONSOLE." << endl;

	TestLib lib{};

	cout << endl;
	lib.message();
	cout << endl;

	const ITestDataPublic***& data = lib.get_data();

	((TestData*)data[0][0])->x = 1;

	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
		{
			cout << "Data at i:" << i << " j:" << j << " = " 
				<< data[i][j]->get_x() 
				<< ", " 
				<< data[i][j]->get_y() 
				<< endl;

			//cout << "Data at i:" << i << " j:" << j << " = " 
			//	<< lib.get_data(i,j).get_x()
			//	<< ", " 
			//	<< lib.get_data(i, j).get_y()
			//	<< endl;
		}

	cout << endl;

	const int** start = lib.get_xarr();
	
	int x[2] = {2,2};
	start[0] = x;
	start[1] = x;

	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			cout << " " << start[i][j] << " ";


	cout << endl;
	return 0;
}
