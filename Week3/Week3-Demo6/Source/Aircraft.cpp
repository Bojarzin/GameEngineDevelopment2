#pragma region step 7

#include <Aircraft.hpp>
#include <ResourceHolder.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>


Textures::ID toTextureID(Aircraft::Type type)
{
	switch (type)
	{
	case Aircraft::Eagle:
		return Textures::Eagle;

	case Aircraft::Raptor:
		return Textures::Raptor;
	}
	return Textures::Eagle;
}

Aircraft::Aircraft(Type type, const TextureHolder& textures)
	: mType(type)
	, mSprite(textures.get(toTextureID(type)))
{
	sf::FloatRect bounds = mSprite.getLocalBounds();
	//by default, the origin of sprites is located in their upper-left corner
	mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void Aircraft::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}

#pragma endregion