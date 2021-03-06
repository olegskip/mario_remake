#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <cmath>
#include <memory>


class GameObject
{
public:
	GameObject(sf::Vector2f pos, sf::Vector2f scale, const sf::Texture &_texture, bool _hasCollision = true);
	sf::Sprite getSpriteCopy();
	sf::Vector2f getPosition() const;
	sf::FloatRect getGlobalBounds() const;
	void setPosition(sf::Vector2f newPos);
	sf::Vector2f getOffset() const;
	void setOffset(sf::Vector2f newOffset);
	
	virtual void draw(sf::RenderWindow &window);
	/*
	 * This function decides, which animation should draw
	 * and control the animation direction
	 */
	virtual void animate(float /* deltaTime */) {};
	virtual void updateMovement(float deltaTime) = 0;

	bool isStandingOnAnyBlock = false;
	bool isNeedToRemove() const;
	void needToRemove();

	virtual void finalMove();

	const bool hasCollision;

protected:
	const sf::Texture &texture;
	sf::Sprite sprite;
	bool mIsNeedToRemove = false;

	sf::Vector2f offset = sf::Vector2f(0, 0);
};
