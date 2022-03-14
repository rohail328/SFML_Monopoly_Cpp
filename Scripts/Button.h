#pragma once
#include<SFML/Graphics.hpp>
using namespace sf;
class Button
{
private:
	RectangleShape body;
	Color idle_color;
	Color hover_color;
	Color active_color;
	bool pressed;
	bool hovered;
public:
	void DrawButton(RenderWindow& window);//draws the button onto the screen
	Button(Texture* text,Vector2f coord, Vector2f size, Color idle,Color hover,Color active);
	void StatusUpdate(const Vector2f mousePos);//updates the color of the button w.r.t the status and position of mouse
	bool ButtonClicked();//returns the status of button
	bool ButtonHovered();
	void setPosition(Vector2f coord);
	~Button() {};
};

