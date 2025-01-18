#pragma once
#include"board.h"
#include"Sprite1.h"
class player
{
public:
	string name;
	Card* hand;
	bool turn;
	chip chips;
	int n;
	int count;
	Button* hand_grid;
	int cards;
	// l=150
	// w=100
	player(int d,int x,int y):chips(d)
	{
		n = d;
		hand = new Card[8];
		turn = false;
		cards = 7;
		count = 0;
		hand_grid = new Button[8];
		for (int i = 0; i < 8; i++)
		{
			hand_grid[i].button.setOutlineThickness(5.f); // Set outline thickness (5 pixels)
			hand_grid[i].button.setOutlineColor(sf::Color::Green); // Set outline color
			hand_grid[i].button.setFillColor(sf::Color::Transparent);
			if (i < 4)
			{
				if (i == 0)
				{
					//int x=20
					//int y=80
					hand_grid[i].button.setPosition(x, y);
					hand_grid[i].button.setSize({95, 145});
				}
				else
				{
					hand_grid[i].button.setPosition(hand_grid[i-1].button.getPosition().x,   hand_grid[i-1].button.getPosition().y + hand_grid[i-1].button.getSize().y + 5 );
					hand_grid[i].button.setSize({95, 145});

				}
			}
			else
			{
				if (i == 4)
				{
					hand_grid[i].button.setPosition(hand_grid[0].button.getPosition().x + hand_grid[0].button.getSize().x + 5, hand_grid[0].button.getPosition().y);
					hand_grid[i].button.setSize({ 95, 145 });
				}
				else
				{
					hand_grid[i].button.setPosition(hand_grid[i - 1].button.getPosition().x, hand_grid[i - 1].button.getPosition().y + hand_grid[i - 1].button.getSize().y + 5);
					hand_grid[i].button.setSize({ 95, 145 });
				}
			}
		}
	}
	void remove_card(Card& c)
	{
		for (int i = 0; i < cards; i++)
		{
			if (hand[i].value == c.value)
			{
				for (int j = i; j < cards-1; j++)
				{
					hand[j] = hand[j + 1];
					
				}
				cards--;
				return;
			}
		}
	}
	void set_name(int num)
	{
		name = "Player " + to_string(num);

	}
	bool mouseover(RenderWindow& window)
	{
		for (int i = 0; i < cards; i++)
		{
			if (hand_grid[i].mouseover(window))
				return true;
		}
		return false;
	}
	void draw(RenderWindow&window,int grid[][10])
	{
		sf::Font font;
		chips.draw(window,grid);
		if (!font.loadFromFile("fonts/Genflox.ttf")) { // Replace with the path to your .ttf font file
			std::cerr << "Error loading font\n";
			return ;
		}

		// Create a text object
		sf::Text text;
		text.setFont(font);                    // Set the font
		text.setString(name);        // Set the text content
		text.setCharacterSize(30);             // Set the font size
		text.setFillColor(sf::Color::Black);   // Set the text color
		text.setPosition(hand_grid[0].button.getPosition().x + 10 , hand_grid[0].button.getPosition().y -60);
		Button b(text);
		b.button.setOutlineThickness(5.f); // Set outline thickness (5 pixels)
		b.button.setOutlineColor(sf::Color::Black); // Set outline color
		b.button.setFillColor(sf::Color::Red);
		b.draw(window);
		for (int i = 0; i < 8; i++)
		{
			if (turn)
			hand_grid[i].draw(window);
			if (cards == i)
			{
				return;
			}
			sf::Texture texture;
			string path;
			if (turn)
				path = hand[i].return_path();
			else
				path = "cards/card_cover.png";
			if (!texture.loadFromFile(path)) {
				cout << "-----------"<<hand[i].value << "--------" << endl;
				return ;
			}
			// Create a sprite and set the texture
			sf::Sprite sprite;
			sprite.setTexture(texture);

			// Set the position of the sprite (optional)
			sprite.setPosition(hand_grid[i].button.getPosition().x, hand_grid[i].button.getPosition().y);
			window.draw(sprite);
		}
	}
	/*
	2H   4H   6H   8H   10H   QH   AH

3H   5H   7H   9H   JH   KH   2D
	*/
	void print_hand()
	{
		for (int i = 0; i < 7; i++)
		{
			cout << hand[i].value << "   ";
		}
		cout << endl << endl;
	}
};
