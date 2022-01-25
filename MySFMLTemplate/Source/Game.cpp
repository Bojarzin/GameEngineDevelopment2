#include <Game.hpp>

const float Game::playerSpeed = 100.0f;
const sf::Time Game::timePerFrame = sf::seconds(1.0f / 60.f);

Game::Game()
	:mWindow(sf::VideoMode(800, 600), "My First SFML", sf::Style::Close),
	mPlayer(),
	mBackgroundTexture(),
	mPlayerTexture(),
	mBackground(),
	mIcon(),
	mFont(),
	mText(),
	mMusic(),
	movementVector(0.0f, 0.0f),
	mStatisticsText(),
	mStatisticsUpdateTime(),
	mStatisticsNumberOfFrames(0)
{
	mIcon.loadFromFile("Media/Textures/Icon.png");
	mWindow.setIcon(mIcon.getSize().x, mIcon.getSize().y, mIcon.getPixelsPtr());

	try
	{
		textures.Load(Textures::AIRPLANE, "Media/Textures/Eagle.png");
		textures.Load(Textures::LANDSCAPE, "Media/Textures/cute_image.jpg");
	}
	catch (std::runtime_error& e)
	{
		std::cout << "Excepetion " << e.what() << std::endl;
	}


	mPlayerTexture = textures.Get(Textures::AIRPLANE);

	mPlayer.setTexture(mPlayerTexture);
	mPlayer.setPosition(100.0f, 100.0f);

	mBackgroundTexture = textures.Get(Textures::LANDSCAPE);
	mBackground.setTexture(mBackgroundTexture);

	if (!mFont.loadFromFile("Media/Sansation.ttf"))
	{
		std::cout << "Could not load font file Sansation.ttf";
		return;
	}

	mStatisticsText.setFont(mFont);
	mStatisticsText.setCharacterSize(20);
	mStatisticsText.setPosition(mWindow.getSize().x / 2 - mText.getCharacterSize()*2, 50);
	mStatisticsText.setFillColor(sf::Color::White);
	mStatisticsText.setOutlineColor(sf::Color::Black);
	mStatisticsText.setOutlineThickness(2.0f);
	//mStatisticsText.setString("Welcome to my game!");

	if (!mMusic.openFromFile("Media/Sound/nice_music.ogg"))
	{
		std::cout << "Could not load music file nice_music.ogg";
		return;
	}
	mMusic.setVolume(1.0f);
	mMusic.play();
}

void Game::Run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (mWindow.isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;

		while (timeSinceLastUpdate > timePerFrame)
		{
			ProcessEvents();
			Update(elapsedTime);

			timeSinceLastUpdate -= timePerFrame;
		}
		UpdateStatistics(elapsedTime);

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
	
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2i mousePosition = sf::Mouse::getPosition(mWindow);
		mPlayer.setPosition(mousePosition.x, mousePosition.y);
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

void Game::UpdateStatistics(sf::Time _elapsedTime)
{
	mStatisticsUpdateTime += _elapsedTime;
	mStatisticsNumberOfFrames += 1;

	if (mStatisticsUpdateTime >= sf::seconds(1.0f))
	{
		mStatisticsText.setString
		(
		"Frame/Second " + std::to_string(mStatisticsNumberOfFrames) + "\n" +
		"Time/Update " + std::to_string(mStatisticsUpdateTime.asMicroseconds() / mStatisticsNumberOfFrames)
		);

		mStatisticsUpdateTime -= sf::seconds(1.0f);
		mStatisticsNumberOfFrames = 0;
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
	mWindow.draw(mStatisticsText);
	mWindow.display();
}