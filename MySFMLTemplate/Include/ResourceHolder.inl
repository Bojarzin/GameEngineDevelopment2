template<typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::Load(Identifier _id, const std::string _fileName)
{
	std::unique_ptr<Resource> resource;
	if (!resource->loadFromFile(_fileName)
	{
		throw std::runtime_error("Resource failed to load: " + _fileName);
	}

	//std::pair<Identifier _id, sf::Texture> mPair(_id, mTexture);
	mResourceMap.insert(std::make_pair(_id, std::move(resource));
}

template<typename Resource, typename Identifier>
Resource& ResourceHolder<Resource, Identifier>::Get(Identifier _id)
{
	std::map<Identifier, sf::Texture>::iterator it;
	it = mResourceMap.find(_id);

	assert(it != mTextureMap.end());

	return it->second;
}

template<typename Resource, typename Identifier>
const Resource& ResourceHolder<Resource, Identifier>::Get(Identifier _id) const
{
	std::map<Identifier, sf::Texture>::iterator it;
	it = mResourceMap.find(_id);

	assert(it != mResourceMap.end());

	return it->second;
}