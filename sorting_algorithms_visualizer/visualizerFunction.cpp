#include "visualizerFunction.h"
#include <fstream>

extern int sleep_time;
extern unsigned int nr_compares;
extern unsigned int nr_assigns;

static void init_array(ArrayElement* arr, int n)
{
	int nr = 1;
	for (ArrayElement* p = arr; p < arr + n; p++)
		p->initialize(nr++);

	// shuffle the array
	while (nr != 0)
	{
		int x, y;
		x = rand() % n;
		y = rand() % n;
		if (x != y)
		{
			std::swap(arr[x], arr[y]);
			nr--;
		}
	}
}

extern int sleep_time;
void visualizer(visualizerArg* arg)
{
	sf::RenderWindow view(arg->view);
	view.setFramerateLimit(MAXIMUM_FRAME_LIMIT);

	sf::Font font;
	if (!font.loadFromFile("font/asd.ttf"))
	{
		std::ofstream log("log.txt");
		log << "Failed to load the font from file";
		log.close();
	}

	sf::Text text, textStatus,ta;
	text.setFont(font);
	textStatus.setFont(font);
	ta.setFont(font);
	text.setCharacterSize(18);
	textStatus.setCharacterSize(18);
	ta.setCharacterSize(18);
	text.setFillColor(sf::Color::White);
	ta.setFillColor(sf::Color::White);
	text.setPosition(15, 5);
	ta.setPosition(740, 5);
	textStatus.setPosition(805, 5);
	ta.setString("Status:");
	char buff[100];
	

	sf::RectangleShape shape;
	shape.setOutlineColor(sf::Color(50, 50, 100));
	shape.setOutlineThickness(2);

	srand((unsigned int)time((time_t*)0));

	ArrayElement arr[301];

	int& n = arg->n;
	init_array(arr, n);
	Status status = Status::UNSORTED;

	sortFunctionThreadArg threadArg;
	threadArg.arr = arr;
	threadArg.method = arg->sortingMethod;

	SF_Thread t(&sort, &threadArg);
	threadArg.runningInstance = t.getRunningInstance();
	threadArg.status = &status;
	threadArg.n = n;

	while (arg->appIsOpen)
	{
		sleep_time = 100 - arg->sortingSpeed;
		if (arg->shouldRun) {
			if (!t.isRunning()) {
				threadArg.n = n;
				threadArg.method = arg->sortingMethod;
				t.start();
			}
			else
				t.terminate();

			arg->shouldRun = false;
		}

		if (arg->shouldShuffle) {
			t.terminate();
			init_array(arr, n);
			status = Status::UNSORTED;
			arg->shouldShuffle = false;
		}

		// drawing
		view.clear();
		sf::Vector2f vec;
		vec.x = 900 / n - 2; // 20 - ticknes outline number = 2
		for (int i = 0; i < n; i++)
		{
			shape.setFillColor(arr[i].color);

			vec.y = -arr[i].value * 540 / n;
			shape.setSize(vec);
			shape.setPosition(i * 900 / n, 570);
			view.draw(shape);
		}

		sprintf_s(buff, "Nr of assigns: %d \t\t Nr of compares: %d", nr_assigns, nr_compares);
		text.setString(buff);
		view.draw(text);

		view.draw(ta);
		switch (status)
		{
		case Status::UNSORTED:
			sprintf_s(buff, "Unsorted");
			textStatus.setFillColor(sf::Color::White);
			break;
		case Status::SORTING:
			sprintf_s(buff, "Sorting");
			textStatus.setFillColor(sf::Color::Red);
			break;
		case Status::SORTED:
			sprintf_s(buff, "Sorted");
			textStatus.setFillColor(sf::Color::Green);
			break;
		default:
			break;
		}
		textStatus.setString(buff);
		view.draw(textStatus);

		view.display();
	}

	t.terminate();
	view.close();
}