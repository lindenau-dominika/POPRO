#include "StateMachine.h"

void StateMachine::update(sf::RenderWindow& window, float deltaTime)
{
	if (!states.empty()) {
		states.back()->update(window, deltaTime);
	}
}

void StateMachine::draw(sf::RenderWindow& window)
{
	if (!states.empty()) {
		window.draw(*states.back());
	}
}
