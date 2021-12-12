#pragma once
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "State.h"

class StateMachine {
private:
	std::vector<std::unique_ptr<State>> states;
public:
	void push_state(std::unique_ptr<State> state) {
		states.push_back(std::move(state));
	}

	void pop_state() {
		states.pop_back();
	}

	void update(sf::RenderWindow& window, float deltaTime);
	void draw(sf::RenderWindow& window);
};	