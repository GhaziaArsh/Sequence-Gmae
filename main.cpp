#include <SFML/Graphics.hpp>
#include <ctime>
#include"button.h"
#include"board.h"
#include <iostream>
#include <vector>
#include"circle_button.h"
#include"sequencegame.h"
#include <algorithm> // For random_shuffle or shuffle
#include <random>    // For random number generator

using namespace sf;
using namespace std;



// Function to shuffle an array
void shuffleArray(std::vector<int>& arr) {
	// Seed with a real random value, if available
	std::random_device rd;
	std::mt19937 rng(rd()); // Mersenne Twister random generator

	// Shuffle using std::shuffle
	std::shuffle(arr.begin(), arr.end(), rng);
}

struct coordinats {
	int x;
	int y;
};

// Drawing the background
void createBack(RenderWindow& window) {
	Image map_image;
	if (!map_image.loadFromFile("pics/blue_bg.png")) {
		cerr << "Failed to load background image!" << endl;
	}
	Texture map;
	map.loadFromImage(map_image);
	Sprite s_map;
	s_map.setTexture(map);
	s_map.setPosition(0, 0);
	window.draw(s_map);
}
void game()
{
	if (1)
		return;
}
// Drawing the map
void createMap(RenderWindow& window) {
	Image map_image;
	if (!map_image.loadFromFile("pics/a1.png")) {
		cerr << "Failed to load map image!" << endl;
	}
	Texture map;
	map.loadFromImage(map_image);
	Sprite s_map;
	s_map.setTexture(map);
	s_map.setPosition(300, 90);
	window.draw(s_map);
}
void setupDeck(vector<Card>& deck) {
	// Define card ranks and suits
	std::vector<std::string> ranks = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A" };
	std::vector<std::string> suits = { "H", "D", "C", "S" }; // H: Hearts, D: Diamonds, C: Clubs, S: Spades

	// Create the deck by combining each rank with each suit
	for (const std::string& suit : suits) {
		for (const std::string& rank : ranks) {
			deck.push_back(Card(rank + suit));
		}
	}

	return;
}
void swap(Card& a, Card& b)
{
	Card temp = a;
	a = b;
	b = temp;
}
void shuffel_deck(vector<Card>& deck, int* arr)
{
	for (int i = 0; i < 52; i++)
	{
		swap(deck[i], deck[arr[i]]);
	}
}
void distribute_cards(player& p1, player& p2, vector<Card>deck)
{
	int index = 0;
	for (int i = 0; i < 7; i++)
	{
		p1.hand[i] = deck[index++];
		p2.hand[i] = deck[index++];
	}
}

int main() {
	int n = 0;
	int index = 14;
	bool selected = false;
	Card selected_card;
	RenderWindow window(VideoMode(1350, 760), "Sequence Board Game ");
	Board board;
	board.setupBoard();
	Font font;
	int win_p = 0;
	bool win = false;
	bool drawn = false;
	if (!font.loadFromFile("C:/Users/Shah Salman/Downloads/perfect-dark-brk/pdark.ttf")) {
		cerr << "Failed to load font!" << endl;
	}
	vector<int>arr;
	int turn = 1;
	string t = "Draw";
	sf::Text text;
	Font f;
	if (!f.loadFromFile("fonts/Genflox.ttf")) {
		cerr << "Failed to load font!" << endl;
	}
	text.setFont(f);                    // Set the font
	text.setString(t);        // Set the text content
	text.setCharacterSize(25);             // Set the font size
	text.setFillColor(sf::Color::Black);   // Set the text color
	text.setPosition(615, 630);
	circle_Button Draw(text);
	Draw.c.setFillColor(Color::Red);
	Draw.c.setOutlineThickness(5.f); // Set outline thickness (5 pixels)
	Draw.c.setOutlineColor(sf::Color::Black);
	Draw.c.setRadius(40.f);
	for (int i = 0; i < 52; i++)
	{
		arr.push_back(i);
	}
	shuffleArray(arr);
	vector<Card> deck;
	setupDeck(deck);
	sf::Text t1;
	t1.setFont(f);                    // Set the font
	t1.setString("Cards Left");        // Set the text content
	t1.setCharacterSize(25);             // Set the font size
	t1.setFillColor(sf::Color::Black);   // Set the text color
	t1.setPosition(615, 20);
	Button cards_left(t1);
	cards_left.button.setFillColor(Color::Red);
	cards_left.button.setOutlineThickness(5.f); // Set outline thickness (5 pixels)
	cards_left.button.setOutlineColor(sf::Color::Black);
	cards_left.button.setSize({ 180,40 });
	t1.setCharacterSize(40);
	t1.setPosition(670, 50);
	t1.setFillColor(sf::Color::Green);   // Set the text color
	t1.setString(to_string(deck.size()));
	board.setupBoard();
	// Set game icon
	Image icon;
	player Player1(1, 20, 80);
	Player1.turn = 1;
	player Player2(2, 1140, 80);
	Player1.set_name(1);
	Player2.set_name(2);
	distribute_cards(Player1, Player2, deck);
	//Player1.hand[0].value = "10S";
	Player1.print_hand();
	Player2.print_hand();
	if (!icon.loadFromFile("pics/icon.png")) {
		cerr << "Failed to load icon!" << endl;
		return 1;
	}
	window.setIcon(32, 32, icon.getPixelsPtr());


	const int ROWS = 5;
	const int COLS = 9;

	bool FIELD_GAME_STATUS[ROWS][COLS];

	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			FIELD_GAME_STATUS[i][j] = true;
		}
	}

	Clock timeMoney;
	Clock clock;
	bool stack_empty = false;
	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		float moneyTime = timeMoney.getElapsedTime().asSeconds();
		clock.restart();
		time = time / 800;
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
			{
				window.close();
			}
			t1.setString(to_string(deck.size() - index));
			// Handle mouse click event
			if (deck.size() - index == 2)
			{
				drawn = true;
				stack_empty = true;
			}
			if (event.type == Event::MouseButtonPressed)
			{
				//if clicked on draw button

				if (Draw.mouseover(window))
				{

					if (drawn == false)
					{
						if (event.mouseButton.button == Mouse::Left) {
							if (Player1.turn)
							{
								Player1.hand[Player1.cards++] = deck[index++];
								cout << deck[index - 1].value << endl;
								drawn = true;
							}
							else
							{
								Player2.hand[Player2.cards++] = deck[index++];
								cout << deck[index - 1].value << endl;
								drawn = true;
							}
						}
					}
				}
				//if I clicked on player's cards
				else if (drawn && (Player1.mouseover(window) || (Player2.mouseover(window))))
				{
					if (event.mouseButton.button == Mouse::Left)
					{

						if (Player1.turn && Player1.mouseover(window))
						{
							for (int i = 0; i < 8; i++)
							{
								if (Player1.hand_grid[i].mouseover(window))
								{
									cout << "selected = " << Player1.hand[i].value << endl;
									selected = true;
									selected_card = Player1.hand[i];
									break;
								}
							}
						}
						else if (Player2.turn && Player2.mouseover(window))
						{
							for (int i = 0; i < 8; i++)
							{
								if (Player2.hand_grid[i].mouseover(window))
								{
									selected_card = Player2.hand[i];
									selected = true;
									int s = 0;
								}
							}
						}
					}

				}

				else if (board.mouseover(window) && selected)
				{
					int n = 0;
					if (Player1.turn)
						n = 1;
					else if (Player2.turn)
						n = 2;

					for (int i = 0; i < 10; i++)
					{
						for (int j = 0; j < 10; j++)
						{
							if (board.grid[i][j].mouseover(window))
							{
								//normal cards other that jacks
								if ((board.board[i][j]->value == selected_card.value) && (board.flag[i][j] == 0))
								{
									board.flag[i][j] = n;
									if (n == 1)
									{
										Player1.chips.add_sprite(board.grid[i][j].button.getPosition().x + 5, board.grid[i][j].button.getPosition().y, i, j);
										cout << "chip added" << endl;
										board.grid[i][j].button.setOutlineThickness(2.5); // Set outline thickness (5 pixels)
										board.grid[i][j].button.setOutlineColor(sf::Color::Black); // Set outline color
										selected = false;
										drawn = false;
										Player1.turn = false;
										Player2.turn = true;
										Player1.remove_card(selected_card);
										board.checkForSequences(n, Player1.count);
										if (Player1.count == 2)
											win = true;
									}
									else if (n == 2)
									{
										Player2.chips.add_sprite(board.grid[i][j].button.getPosition().x + 5, board.grid[i][j].button.getPosition().y, i, j);
										cout << "chip added" << endl;
										selected = false;
										drawn = false;
										Player1.turn = true;
										Player2.turn = false;
										Player2.remove_card(selected_card);
										board.checkForSequences(n, Player2.count);
										if (Player2.count == 2)
											win = true;
									}
									if (win)
									{
										win_p = n;
										cout << "_______________win ___________________" << endl;

									}

								}


								//conditions for jack
								else if ((selected_card.value == "JC") || (selected_card.value == "JH") ||(selected_card.value == "JD") || (selected_card.value == "JS"))
								{
									//one eye jacked condition
									if (selected_card.value != "JS")
									{
										if (n == 1)
										{
											if (board.flag[i][j] == 2)
											{
												board.flag[i][j] = 1;
												Player2.chips.remove_sprite(i, j);
												Player1.chips.add_sprite(board.grid[i][j].button.getPosition().x + 5, board.grid[i][j].button.getPosition().y, i, j);
												board.grid[i][j].button.setOutlineThickness(2.5); // Set outline thickness (5 pixels)
												board.grid[i][j].button.setOutlineColor(sf::Color::Black); // Set outline color
												selected = false;
												drawn = false;
												Player1.turn = false;
												Player2.turn = true;
												window.clear();
												Player1.remove_card(selected_card);
												board.checkForSequences(n, Player1.count);
												if (Player1.count == 2)
													win = true;
											}
											if (win)
											{
												win_p = n;
												cout << "_______________win ___________________" << endl;

											}
										}
										else if (n == 2)
										{
											if (board.flag[i][j] == 1)
											{
												board.flag[i][j] = 2;
												Player1.chips.remove_sprite(i, j);
												Player2.chips.add_sprite(board.grid[i][j].button.getPosition().x + 5, board.grid[i][j].button.getPosition().y, i, j);
												cout << "chip added" << endl;
												selected = false;
												drawn = false;
												Player1.turn = true;
												Player2.turn = false;
												Player2.remove_card(selected_card);
												board.checkForSequences(n, Player2.count);
												if (Player2.count == 2)
													win = true;
											}
											if (win)
											{
												win_p = n;
												cout << "_______________win ___________________" << endl;

											}
										}
									}
									//two eye jacked
									else
									{
										if (n == 1)
										{
											if (board.flag[i][j] != 1 && board.flag[i][j] != n+5)
											{
												board.flag[i][j] = 1;
												Player2.chips.remove_sprite(i, j);
												Player1.chips.add_sprite(board.grid[i][j].button.getPosition().x + 5,
													board.grid[i][j].button.getPosition().y, i, j);
												cout << "chip added" << endl;
												board.grid[i][j].button.setOutlineThickness(2.5); // Set outline thickness (5 pixels)
												board.grid[i][j].button.setOutlineColor(sf::Color::Black); // Set outline color
												selected = false;
												drawn = false;
												Player1.turn = false;
												Player2.turn = true;
												Player2.remove_card(selected_card);
												board.checkForSequences(n, Player1.count);
												if (Player1.count == 2)
													win = true;
											}
										}
										else if (n == 2)
										{
											if (board.flag[i][j] != 2 && board.flag[i][j] != n+5)
											{
												board.flag[i][j] = 2;
												Player1.chips.remove_sprite(i, j);
												Player2.chips.add_sprite(board.grid[i][j].button.getPosition().x + 5,
													board.grid[i][j].button.getPosition().y, i, j);
												cout << "chip added" << endl;
												board.grid[i][j].button.setOutlineThickness(2.5); // Set outline thickness (5 pixels)
												board.grid[i][j].button.setOutlineColor(sf::Color::Black); // Set outline color
												selected = false;
												drawn = false;
												Player2.turn = false;
												Player1.turn = true;
												Player2.remove_card(selected_card);
												board.checkForSequences(n, Player2.count);
												if (Player2.count == 2)
													win = true;
											}
										}
										if (win)
										{
											win_p = n;
											cout << "_______________win ___________________" << endl;

										}
									}
								}
							}
							board.grid[i][j].button.setOutlineThickness(2.5); // Set outline thickness (5 pixels)
							board.grid[i][j].button.setOutlineColor(sf::Color::Black); // Set outline color
						}
					}
				}
			}
		}

		//change grid color
		if (selected)
		{
			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 10; j++)
				{
					if (board.board[i][j]->value == selected_card.value && board.flag[i][j] == 0)
					{
						board.grid[i][j].button.setOutlineThickness(2.5); // Set outline thickness (5 pixels)
						board.grid[i][j].button.setOutlineColor(sf::Color::Green); // Set outline color
					}
					else if ((selected_card.value == "JC") || (selected_card.value == "JH") ||
						(selected_card.value == "JD") || (selected_card.value == "JS"))
					{
						int a = 0;
						int b = 0;
						if (Player1.turn)
						{
							a = 1;
							b = 2;
						}
						else
						{
							a = 2;
							b = 1;
						}
						if (selected_card.value != "JS")
						{
							if (board.flag[i][j] != a && (board.flag[i][j] == b))
							{
								board.grid[i][j].button.setOutlineThickness(2.5); // Set outline thickness (5 pixels)
								board.grid[i][j].button.setOutlineColor(sf::Color::Green); // Set outline color
							}
							else
							{
								board.grid[i][j].button.setOutlineThickness(2.5);
								board.grid[i][j].button.setOutlineColor(sf::Color::Black);
							}
						}
						else
						{
							if (board.flag[i][j] != a && board.flag[i][j] != b)
							{
								board.grid[i][j].button.setOutlineThickness(2.5); // Set outline thickness (5 pixels)
								board.grid[i][j].button.setOutlineColor(sf::Color::Green); // Set outline color
							}
							else
							{
								board.grid[i][j].button.setOutlineThickness(2.5);
								board.grid[i][j].button.setOutlineColor(sf::Color::Black);
							}
						}
					}
					else if (board.grid[i][j].button.getOutlineColor() == sf::Color::Green)
					{
						board.grid[i][j].button.setOutlineThickness(2.5);
						board.grid[i][j].button.setOutlineColor(sf::Color::Black);
					}
					else
					{
						board.grid[i][j].button.setOutlineThickness(2.5);
						board.grid[i][j].button.setOutlineColor(sf::Color::Black); // Set outline color
					}
				}
			}
		}
		//blinking
		if (!drawn)
		{
			if (n <= 1)
			{
				Draw.c.setOutlineColor(sf::Color::Black); // Set outline color
				n++;
			}
			else
			{
				Draw.c.setOutlineColor(sf::Color::Green); // Set outline color
				n = 0;
			}
		}
		else
			Draw.c.setOutlineColor(sf::Color::Black); // Set outline color


		window.clear();

		createBack(window);
		createMap(window);
		board.draw(window);
		Player1.draw(window, board.flag);
		Player2.draw(window, board.flag);
		cards_left.draw(window);
		window.draw(t1);
		Draw.draw(window);
		if (win || stack_empty)
		{
			sf::Texture texture;
			string path;
			if (win)
			{
				path = "pics/winning_screen.png";
			}
			else
			{
				path = "pics/draw_screen.png";


			}
			if (!texture.loadFromFile(path)) {
				std::cerr << "Failed to load image!" << std::endl;

			}

			// Create a sprite and set its texture
			sf::Sprite sprite;
			sprite.setTexture(texture);


			// Optional: Set the position of the sprite
			sprite.setPosition(10, 10);
			window.draw(sprite);
			if (win_p == 1)
			{
				text.setFont(f);                    // Set the font
				text.setString("Player 1 ");        // Set the text content
				text.setCharacterSize(30);             // Set the font size
				text.setFillColor(sf::Color::Black);   // Set the text color
				text.setPosition(590, 210);
				Button b(text);
				b.button.setSize({ 150,50 });
				b.button.setFillColor(Color::White);
				b.draw(window);
			}
			else if (win_p == 2)
			{
				text.setFont(f);                    // Set the font
				text.setString("Player 2 ");        // Set the text content
				text.setCharacterSize(30);             // Set the font size
				text.setFillColor(sf::Color::White);   // Set the text color
				text.setPosition(590, 210);
				Button b(text);

				b.button.setFillColor(Color::Black);
				b.button.setSize({ 150,50 });

				b.draw(window);
			}
			else
			{
				text.setFont(f);                    // Set the font
				text.setString("Draw ");        // Set the text content
				text.setCharacterSize(100);             // Set the font size
				text.setFillColor(sf::Color::Blue);   // Set the text color
				text.setPosition(480, 300);
				Button b(text);
				b.button.setSize({ 300,100 });
				b.button.setFillColor(Color::Transparent);
				b.draw(window);
			}
		}
		window.setSize(sf::Vector2u(1350, 760));
		window.display();
	}

	return 0;
}
