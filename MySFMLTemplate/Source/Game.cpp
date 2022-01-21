#include <Game.hpp>

const float Game::playerSpeed = 100.0f;
const sf::Time Game::timePerFrame = sf::seconds(1.0f / 60.f);

Game::Game()
	:mWindow(sf::VideoMode(800, 600), "My First SFML", sf::Style::Close),
	mPlayer(),
	mTexture(),
	mPlayerTexture(),
	mBackground(),
	mIcon(),
	mFont(),
	mText(),
	mMusic(),
	movementVector(0.0f, 0.0f)
{
	mIcon.loadFromFile("Media/Textures/Icon.png");
	mWindow.setIcon(mIcon.getSize().x, mIcon.getSize().y, mIcon.getPixelsPtr());

	if (!mPlayerTexture.loadFromFile("Media/Textures/Eagle.png"))
	{
		std::cout << "Could not load texture Eagle.png";
		return;
	}

	mPlayer.setTexture(mPlayerTexture);
	mPlayer.setPosition(100.0f, 100.0f);

	if (!mTexture.loadFromFile("Media/Textures/cute_image.jpg"))
	{
		std::cout << "Could not load background file cute_image.jpg";
		return;
	}
	
	mBackground.setTexture(mTexture);

	if (!mFont.loadFromFile("Media/Sansation.ttf"))
	{
		std::cout << "Could not load font file Sansation.ttf";
		return;
	}

	mText.setFont(mFont);
	mText.setCharacterSize(20);
	mText.setPosition(mWindow.getSize().x / 2 - mText.getCharacterSize()*2, 50);
	mText.setFillColor(sf::Color::White);
	mText.setOutlineColor(sf::Color::Black);
	mText.setOutlineThickness(2.0f);
	mText.setString("Welcome to my game!");

	if (!mMusic.openFromFile("Media/Sound/nice_music.ogg"))
	{
		std::cout << "Could not load music file nice_music.ogg";
		return;
	}
	mMusic.setVolume(25.0f);
	mMusic.play();
}

void Game::Run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (mWindow.isOpen())
	{
		sf::Time elapsedTime = clock.restart();


		ProcessEvents();
		Update(elapsedTime);
		Render();
	}
}

void Game::ProcessEvents()
{
	sf::Event event;

	while (mWindow.pollEvent(event))
	{
		switch (event.type)
		{
			case (sf::Event::Closed):
				mWindow.close();
				break;

			case (sf::Event::KeyPressed):
				HandlePlayerInput(event.key.code, true);
				break;

			case (sf::Event::KeyReleased):
				HandlePlayerInput(event.key.code, false);
				break;

			default:
				break;
		}

		if (event.type == sf::Event::Closed)
		{
			mWindow.close();
		}
	}
	
}

void Game::HandlePlayerInput(sf::Keyboard::Key _key, bool _isPressed)
{
	if (_key == sf::Keyboard::W)
	{
		mIsMovingUp = _isPressed;
	}
	if (_key == sf::Keyboard::S)
	{
		mIsMovingDown = _isPressed;
	}
	if (_key == sf::Keyboard::A)
	{
		mIsMovingLeft = _isPressed;
	}
	if (_key == sf::Keyboard::D)
	{
		mIsMovingRight = _isPressed;
	}
}

void Game::Update(sf::Time _elapsedTime)
{
	movementVector = sf::Vector2f(0.0f, 0.0f);

	if (mIsMovingUp)
	{
		movementVector.y -= playerSpeed;
	}
	if (mIsMovingDown)
	{
		movementVector.y += playerSpeed;
	}
	if (mIsMovingLeft)
	{
		movementVector.x -= playerSpeed;
	}
	if (mIsMovingRight)
	{
		movementVector.x += playerSpeed;
	}

	mPlayer.move(movementVector * _elapsedTime.asSeconds());
}

void Game::Render()
{
	mWindow.clear();
	mWindow.draw(mBackground);
	mWindow.draw(mPlayer);
	mWindow.draw(mText);
	mWindow.display();
}