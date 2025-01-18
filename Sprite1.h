#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <utility> // For std::pair

using namespace sf;
using namespace std;
class pair
{
public:
	int x;
	int y;
};
class chip
{
public:
std::vector<std::pair<int, int>> chips; // A vector of pairs where each pair contains two integers
std::vector<std::pair<int, int>> index;
	string p;
	int s; 
	chip(int n)
	{
		if (n == 1)
		{
			s = n;
			p = "pics/chip_1.png";
		}
		else
		{
			s = n;
			p = "pics/chip_2.png";
		}
	}
	void add_sprite(int x,int y,int i,int j)
	{
		
		chips.push_back({x,y});
		index.push_back({ i,j });

	}
	void remove_sprite(int x,int y)
	{
		for (int i = 0; i < chips.size(); i++)
		{
			if (index[i].first == x && index[i].second == y)
			{

				index.erase(index.begin() + i );
				chips.erase(chips.begin() + i);
				cout << "removed" << endl;
				return;
			}

		}
	}
	void draw(RenderWindow& window,int grid[][10])
	{
		for (int i = 0; i < chips.size(); i++)
		{
			sf::Texture texture;
			string a;
			if (grid[index[i].first][index[i].second] == s+5)
			{
				if (s == 1)
				{
					a = "pics/chip_3.png";
				}
				else
					a = "pics/chip_4.png";
			}
			else
				a = p;
			if (!texture.loadFromFile(a)) {
				std::cerr << "Failed to load image!" << std::endl;
				return ;
			}

			// Create a sprite and set its texture
			sf::Sprite sprite;
			sprite.setTexture(texture);
			// Optional: Set the position of the sprite
			sprite.setPosition(chips[i].first,chips[i].second);
			window.draw(sprite);
		}
	}
};