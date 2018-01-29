#include "Enemy.h"


Enemy::Enemy(sf::RenderWindow& window, const std::vector<sf::Vector2f>& path, EnemyType type, uint16_t waveNumber) :
	window(window),
	path(path),
	next_target_pos(path[0]),
	distance(0.0),
	speed(EnemyDataContainer::get(type).speed),
	hp(EnemyDataContainer::get(type).hp + waveNumber * 3),
	dmg(EnemyDataContainer::get(type).damage),
	gold(EnemyDataContainer::get(type).gold + waveNumber),
	body(EnemyDataContainer::get(type).body),
	slowed(false),
	original_speed(speed)
{
	body.setPosition(path[0]);
	body.setRotation(-90.f);
}

void Enemy::render() const
{
	window.draw(body);
}

const sf::Vector2f Enemy::getPosition() const
{
	return body.getPosition();
}

void Enemy::decreaseHp(int dmg)
{
	hp -= dmg;
	if (hp <= 0)
	{
		state = States::Dead;
	}
}

const int Enemy::getDmg() const
{
	return dmg;
}

const int Enemy::getGold() const
{
	return gold;
}

sf::FloatRect Enemy::getBounds() const
{
	return body.getGlobalBounds();
}

Enemy::~Enemy()
{
}

void Enemy::reduce_speed(float factor, sf::Time time) {
	speed = original_speed;
	speed *= factor;
	slow_duration = time;
	slow_timer.restart();
	slowed = true;
}


bool Enemy::is_slowed()
{
	return slowed;
}