#include "Button.h"
#include<SFML/Audio.hpp>
#include<iostream>
void Button::DrawButton(RenderWindow& window){
	window.draw(body);
}

Button::Button(Texture*texture,Vector2f coord, Vector2f size, Color idle, Color hover, Color active){
	body.setPosition(coord);
	body.setSize(size);
	body.setOrigin(body.getSize() / 2.0f);
	idle_color = idle;
	hover_color = hover;
	active_color = active;
	body.setFillColor(idle_color);
	body.setTexture(texture);
	pressed = false;
	hovered = false;
}

void Button::StatusUpdate(const Vector2f mousePos){
	hovered = false;
	pressed = false;
	body.setFillColor(idle_color);
	if (body.getGlobalBounds().contains(mousePos)) {
		hovered = true;
		if (Mouse::isButtonPressed(Mouse::Left)) {
			pressed = true;
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::Enter)) {
			pressed = true;
		}
	}
	if (hovered == true) {
		body.setFillColor(hover_color);
	}
	if (pressed == true) {
		body.setFillColor(active_color);
	}
}

bool Button::ButtonClicked() {
	if (pressed == true) {
		return true;
	}
	return false;
}

bool Button::ButtonHovered()
{
	if (hovered == true) {
		return true;
	}
	return false;
}

void Button::setPosition(Vector2f coord)
{
	body.setPosition(coord);
}
