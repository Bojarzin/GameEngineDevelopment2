#include "Game.hpp"


Game::Game()
	: mWindow(sf::VideoMode(800, 600), "SFML Application", sf::Style::Close)
	, mTexture()
	, mBackground()
	, mAirplaneTexture()
	, mPlayer()
	, mMusic()
	, mFont()
	, mIcon()
	, mIsMovingUp(false)
	, mIsMovingDown(false)
	, mIsMovingRight(false)
	, mIsMovingLeft(false)

{

	if (!mAirplaneTexture.loadFromFile("Media/Textures/Eagle.png"))
	{
		// Handle loading error
	}

	mPlayer.setTexture(mAirplaneTexture);
	mPlayer.setPosition(100.f, 100.f);
	mPlayer.setOrigin(20.f, 20.f);

	//mIcon.loadFromFile("Media/Textures/icon.png");
	//You could also create your own image
	mIcon.create(20, 20, sf::Color::Red);
	sf::Color color = mIcon.getPixel(0, 0);
	//color.a = 0; //make the top-left pixel transparent
	color.r = 0;   //set the r = 0 (rgb) from the color
	mIcon.setPixel(0, 0, color);

	mWindow.setIcon(mIcon.getSize().x, mIcon.getSize().y, mIcon.getPixelsPtr());

	//Load a sprite to display
	if (!mTexture.loadFromFile("Media/Textures/cute_image.jpg"))
		return;
	mBackground.setTexture(mTexture);

	if (!mFont.loadFromFile("Media/Sansation.ttf"))
		return;


	mText.setString("Hello SFML");
	mText.setFont(mFont);
	mText.setPosition(5.f, 5.f);
	mText.setCharacterSize(50);
	mText.setFillColor(sf::Color::Black);


	mMusic.openFromFile("Media/Sound/nice_music.ogg");

	//change some parameters
	mMusic.setPosition(0, 0, 0); //change its 3D position - the default position is (0,0,0)
	mMusic.setPitch(2); //increase the pitch - pitch represents the perceived fundamental frequency of a sound such as modifying the playing speed of the sound
	mMusic.setVolume(50); //reduce the volume
	mMusic.setAttenuation(100); //an attenuation value of 100 will make the sound fade out very quicky as it gets further from the listener - default value is 1
	mMusic.setLoop(true); //make it loop
	//Play the music
	//mMusic.play();



}

void Game::run()
{

	while (mWindow.isOpen())
	{
		processEvents();
		update();
		render();
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			handlePlayerInput(event.key.code, true);
			break;

		case sf::Event::KeyReleased:
			handlePlayerInput(event.key.code, false);
			break;

		case sf::Event::Closed:
			mWindow.close();
			break;
		}
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		sf::Vector2i mousePosition = sf::Mouse::getPosition(mWindow);
		mPlayer.setPosition((float)mousePosition.x, (float)mousePosition.y);
	}
}

void Game::update()
{
	sf::Vector2f movement(0.f, 0.f);
	if (mIsMovingUp)
		movement.y -= 1.f;
	if (mIsMovingDown)
		movement.y += 1.f;
	if (mIsMovingLeft)
		movement.x -= 1.f;
	if (mIsMovingRight)
		movement.x += 1.f;

	mPlayer.move(movement);

}

void Game::render()
{
	//Question: What do you think will it happen if you comment out the following two lines
	mWindow.clear();
	mWindow.draw(mBackground);
	mWindow.draw(mPlayer);
	mWindow.draw(mText);

	//Update the window
	mWindow.display();
}


void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::W)
		mIsMovingUp = isPressed;
	else if (key == sf::Keyboard::S)
		mIsMovingDown = isPressed;
	else if (key == sf::Keyboard::A)
		mIsMovingLeft = isPressed;
	else if (key == sf::Keyboard::D)
		mIsMovingRight = isPressed;

}
