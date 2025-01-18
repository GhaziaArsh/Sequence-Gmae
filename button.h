#pragma once
#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<string>
using namespace sf;
using namespace std;
class Button
{
public:
	Text text;
	RectangleShape button;
	Button() {}

	Button(float length, float width, Color s, string t,int x,int y)
	{
		button.setSize({ length,width });
		/*text.setString(t);
		text.setFillColor(s);*/
		sf::Font font;
		if (!font.loadFromFile("fonts/Genflox.ttf")) { // Replace with the path to your .ttf font file
			return;
		}
		//Text a;
		//a.setString(t);
		//text = a;
		text.setFont(font);                    // Set the font
		//text.setString(t); 
		// Set the text content
		
		text.setCharacterSize(20);             // Set the font size
		text.setFillColor(sf::Color::Magenta);   // Set the text color
		text.setPosition(x+10, y+5);
		button.setFillColor(s);
		button.setPosition(x,y);
	}
	
	Button(sf::Text& t)
	{
		text = t;

		// Get the local bounds of the text
		sf::FloatRect textBounds = text.getLocalBounds();

		// Set the size of the button to match the text size (with some padding)
		float padding = 10.0f; // Add padding around the text
		button.setSize({ textBounds.width + 2 * padding, textBounds.height + 2 * padding });

		// Set the position of the button to align with the text
		button.setPosition({ text.getPosition().x - padding, text.getPosition().y - padding });

		// Optional: Adjust the origin of the text if needed for better alignment
		text.setOrigin(textBounds.left, textBounds.top);
	}

	void setbutton(Text& t)
	{
		text = t;
		button.setPosition({ text.getPosition().x,text.getPosition().y });
		button.setSize({ float(text.getString().getSize() * 22),40 });
		button.setFillColor(Color::Transparent);
	}
	bool mouseover(RenderWindow& window)
	{
		float buttonX = button.getPosition().x; // Get the x-coordinate of the button's position
		float buttonY = button.getPosition().y; // Get the y-coordinate of the button's position

		float mouseX = Mouse::getPosition(window).x; // Get the x-coordinate of the mouse cursor
		float mouseY = Mouse::getPosition(window).y; // Get the y-coordinate of the mouse cursor

		float buttonW = buttonX + button.getSize().x; // Calculate the right edge of the button
		float buttonH = buttonY + button.getSize().y; // Calculate the bottom edge of the button

		// Check if the mouse cursor is within the bounds of the button
		if (mouseX >= buttonX && mouseX <= buttonW && mouseY >= buttonY && mouseY <= buttonH)
		{
			return true; // Mouse is over the button
		}
		else
		{
			return false; // Mouse is not over the button
		}
	}

	void draw(RenderWindow& window)
	{
		window.draw(button);
		window.draw(text);
	}
};