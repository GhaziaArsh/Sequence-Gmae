#pragma once
#pragma once
#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<string>
using namespace sf;
using namespace std;
class circle_Button
{
public:
	Text text;
	RectangleShape button;
	CircleShape c;

	circle_Button() {}
	circle_Button(Text& t)
	{
		text = t;
		button.setPosition({ text.getPosition().x - 2,text.getPosition().y - 23 });
		button.setSize({ 80,80 });

		button.setFillColor(Color::Green);
		c.setPosition({ button.getPosition().x,button.getPosition().y	});
	}
	void setbutton(Text& t)
	{
		text = t;
		button.setPosition({ text.getPosition().x,text.getPosition().y });
		c.setPosition({ button.getPosition().x,button.getPosition().y });
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
		window.draw(c);
		window.draw(text);
	}
};