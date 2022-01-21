#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

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
	
		// Variables
		sf::RenderWindow mWindow;
		sf::Sprite mPlayer;
		sf::Texture mTexture;
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
};