#ifndef BOOK_APPLICATION_HPP
#define BOOK_APPLICATION_HPP

#include <ResourceHolder.hpp>
#include <ResourceIdentifiers.hpp>
#include <Player.hpp>
#include <StateStack.hpp>
#include <MusicPlayer.hpp>
#pragma region step 6
#include <SoundPlayer.hpp>
#pragma endregion


#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>


class Application
{
	public:
								Application();
		void					run();
		

	private:
		void					processInput();
		void					update(sf::Time dt);
		void					render();

		void					updateStatistics(sf::Time dt);
		void					registerStates();


	private:
		static const sf::Time	TimePerFrame;

		sf::RenderWindow		mWindow;
		TextureHolder			mTextures;
	  	FontHolder				mFonts;
		Player					mPlayer;
		MusicPlayer				mMusic;
#pragma region step 7
		SoundPlayer				mSounds;
#pragma endregion


		StateStack				mStateStack;

		sf::Text				mStatisticsText;
		sf::Time				mStatisticsUpdateTime;
		std::size_t				mStatisticsNumFrames;
};

#endif // BOOK_APPLICATION_HPP
