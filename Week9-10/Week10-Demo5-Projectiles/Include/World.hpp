#pragma once

#include <ResourceHolder.hpp>
#include <ResourceIdentifiers.hpp>
#include <SceneNode.hpp>
#include <SpriteNode.hpp>
#include <Aircraft.hpp>
#include <CommandQueue.hpp>
#include <Command.hpp>

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <array>
#include <queue>


// Forward declaration
namespace sf
{
	class RenderWindow;
}

class World : private sf::NonCopyable
{
	public:
		explicit							World(sf::RenderWindow& window, FontHolder& fonts);
		void								update(sf::Time dt);
		void								draw();		
		CommandQueue&						getCommandQueue();

	private:
		void								loadTextures();
		void								buildScene();
		void								adaptPlayerPosition();
		void								adaptPlayerVelocity();


	private:
		enum Layer
		{
			Background,
			Air,
			LayerCount
		};

		struct SpawnPoint
		{
			SpawnPoint(Aircraft::Type type, float x, float y)
				: type(type)
				, x(x)
				, y(y)
			{
			}

			Aircraft::Type type;
			float x;
			float y;
		};

	private:
		sf::RenderWindow&					mWindow;
		sf::View							mWorldView;
		TextureHolder						mTextures;

		SceneNode							mSceneGraph;
		std::array<SceneNode*, LayerCount>	mSceneLayers;
		CommandQueue						mCommandQueue;

		sf::FloatRect						mWorldBounds;
		sf::Vector2f						mSpawnPosition;
		float								mScrollSpeed;
		Aircraft*							mPlayerAircraft;
		FontHolder&							mFonts;
		std::vector<SpawnPoint>				mEnemySpawnPoints;
		sf::FloatRect						getViewBounds() const;
		sf::FloatRect						getBattlefieldBounds() const;
		void								spawnEnemies();
		std::vector<Aircraft*>				mActiveEnemies;
		void								addEnemies();
		void								addEnemy(Aircraft::Type type, float relX, float relY);

};


