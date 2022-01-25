#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <cassert>
#include <map>
#include <memory>
#include <stdexcept>

/*
enum class TextureID
{
	LANDSCAPE,
	AIRPLANE
};
*/



template<typename Resource, typename Identifier>
class ResourceHolder
{
	private:
		std::map<Identifier, Resource> mResourceMap;

	public:
		void Load(Identifier, const std::string _fileName);
		
		Resource& Get(Identifier _id);
		const Resource& Get(Identifier _id) const;
};


#include "ResourceHolder.inl"