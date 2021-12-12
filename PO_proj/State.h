#pragma once
#include <memory>
#include <SFML/Graphics.hpp>

class StateMachine;
class State : public sf::Drawable {
protected:
	StateMachine &parent_machine;
public:
	State(StateMachine& machine) : parent_machine(machine) {}
	virtual void update(sf::RenderWindow& window, float deltaTime) = 0;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
};