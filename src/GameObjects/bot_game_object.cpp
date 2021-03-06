#include "bot_game_object.h"

BotGameObject::BotGameObject(sf::Vector2f pos, sf::Vector2f scale, sf::Texture &texture, Direction spawnDirection): 
	GameObject(pos, scale, texture)
{
	runAnimation = std::make_shared<AnimationController>(0, 18, 10, sf::Vector2f(60, 72), 32, true);
	dieAnimation = std::make_shared<AnimationController>(1, 1, 0, sf::Vector2f(60, 72), 32, true);
	currentAnimation = runAnimation;
	sprite.setTextureRect(currentAnimation->getSpriteRect(direction));
	direction = spawnDirection;
}

void BotGameObject::updateMovement(float deltaTime) // override
{
	mIsChangedDirection = false;
	const int dx = getDX(direction);
	if(mIsAlive) {
		if(isStandingOnAnyBlock) {
			offset.x += config::goomba::RUN_ACCELERATION * dx * deltaTime * 60;
			if(std::abs(offset.x) > config::goomba::RUN_MAX_SPEED)
				offset.x = config::goomba::RUN_MAX_SPEED * dx;
		}
		else {
			if(offset.x > 0) {
				offset.x -= config::goomba::DECELERATION_IN_JUMP;
				if(offset.x < 0)
					offset.x = 0;
			}
			else if(offset.x < 0) {
				offset.x += config::goomba::DECELERATION_IN_JUMP * deltaTime * 60;
				if(offset.x > 0)
					offset.x = 0;
			}
		}
	}
	else 
		offset.x = 0;

	offset.y += config::GRAVITY;
	if(offset.y > config::MAX_FALLING_SPEED)
		offset.y = config::MAX_FALLING_SPEED;

	if(!mIsAlive && dieStopwatch.getElapsedTime().asSeconds() > config::goomba::DEATH_TIME)
		mIsNeedToRemove = true;
}

void BotGameObject::animate(float deltaTime) // override
{
	currentAnimation->setCurrentFrame(currentAnimation->getCurrentFrame() + deltaTime * std::abs(offset.x) * currentAnimation->animationSpeed);
	sprite.setTextureRect(currentAnimation->getSpriteRect(direction));
}

void BotGameObject::changeDirection()
{
	if(!mIsAlive || mIsChangedDirection) return;
	mIsChangedDirection = true;
	if(direction == Direction::LEFT)
		direction = Direction::RIGHT;
	else
		direction = Direction::LEFT;
}

bool BotGameObject::isChangedDirection() const
{
	return mIsChangedDirection;
}

bool BotGameObject::isAlive() const
{
	return mIsAlive;
}

void BotGameObject::die()
{
	mIsAlive = false;
	currentAnimation = dieAnimation;
	dieStopwatch.restart();
}
