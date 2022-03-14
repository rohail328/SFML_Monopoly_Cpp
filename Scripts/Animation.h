#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
using namespace std;
using namespace sf;
class Animation
{
public:
	Animation(Vector2f pos, Texture*texture,Vector2u imC,float sT,Color color);
	~Animation();
	void Update(float deltaTime);//switches between different frames of an animation
	IntRect uvRect;//defines a rectangle
	Vector2f size;
	void DrawAnimation(RenderWindow& window);
private:
	Vector2u imagecount;
	Vector2u currentImage;
	RectangleShape body;
	Vector2f cood;
	float totalTime;
	float switchTime;
};


Animation::Animation(Vector2f pos,Texture* texture, Vector2u imC, float sT,Color color) {
	imagecount = imC;//row and column wise frame count 
	switchTime = sT;//Frame per second
	totalTime = 0.0f;
	currentImage.x = 0;
	currentImage.y = 0;
	//size of each frame 
	size.x = texture->getSize().x / float(imagecount.x);
	size.y = texture->getSize().y / float(imagecount.y);
	uvRect.width = texture->getSize().x / float(imagecount.x);
	uvRect.height = texture->getSize().y / float(imagecount.y);
	//creates a rectangle on which the animation is displayed
	body.setSize(size);
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(pos);
	body.setTexture(texture);
	body.setFillColor(color);
}

Animation::~Animation() {

}

void Animation::Update(float deltaTime) {
	//currentImage.y = 0;
	totalTime += deltaTime;
	if (totalTime >= switchTime) {
		totalTime -= switchTime;
		currentImage.x++;
		if (currentImage.x >= imagecount.x) {
			currentImage.x = 0;
			currentImage.y++;
			if (currentImage.y >= imagecount.y) {
				currentImage.y = 0;
			}
		}
	}
	uvRect.top = currentImage.y * uvRect.height;
	body.setTextureRect(uvRect);
}

void Animation::DrawAnimation(RenderWindow& window) {
	window.draw(body);
}