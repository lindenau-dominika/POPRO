#include "NPC.h"
#include "entity.h"

NPC::NPC(sf::Texture  *texture, Animation animation, sf::FloatRect interaction_box, sf::Vector2f position) : Entity(texture, animation, 0, 1), bounding_box(interaction_box)
{
	GetBody()->setSize(sf::Vector2f(64.f, 65.f));
	GetBody()->setPosition(position);
	GetBody()->setTexture(texture);
	GetBody()->setOrigin(GetBody()->getSize().x /2, GetBody()->getSize().y/2);
}

void NPC::update(float deltaTime)
{
	GetAnimation().Update(deltaTime);
	GetBody()->setTextureRect(GetAnimation().GetUVRect());
}

const sf::FloatRect NPC::GetBounds() const
{
	return this->bounding_box;
}

