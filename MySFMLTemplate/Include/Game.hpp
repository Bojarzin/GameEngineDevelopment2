#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <ResourceHolder.hpp>

namespace Textures
{
	enum ID
	{
		LANDSCAPE,
		AIRPLANE
	};
}

class Game : private sf::NonCopyable
{
	public:
		// Functions
		Game();
		void Run();
	
	private:
		// Functions
		void ProcessEvents();
		void Update(sf::Time _elapsedTime);
		void Render();
	
		void HandlePlayerInput(sf::Keyboard::Key _key, bool _isPressed);
		void UpdateStatistics(sf::Time _elapsedTime);
	
		// Variables
		sf::RenderWindow mWindow;
		sf::Sprite mPlayer;
		sf::Texture mBackgroundTexture;
		sf::Texture mPlayerTexture;
		sf::Sprite mBackground;
		sf::Image mIcon;
		sf::Font mFont;
		sf::Text mText;
		sf::Music mMusic;
		sf::Vector2f movementVector;
	
		bool mIsMovingUp = false;
		bool mIsMovingDown = false;
		bool mIsMovingRight = false;
		bool mIsMovingLeft = false;

		static const float playerSpeed;
		static const sf::Time timePerFrame;
		sf::Text mStatisticsText;
		sf::Time mStatisticsUpdateTime;
		std::size_t mStatisticsNumberOfFrames;

		ResourceHolder<sf::Texture, Textures::ID> textures;
};