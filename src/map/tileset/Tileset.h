//◦ EggEngine ◦
#pragma once
#include <string>
#include <memory>
#include <vector>
#include <map>

#include "engine/CoreSDL.h"
#include "engine/assets/texture/eAssetSprite.h"

namespace Game::Map
{

	//Спрайты тайлы для игровой карты
	class ATileset
	{
	public:
		using UPtr		= std::unique_ptr<ATileset>;
		using Ptr		= std::shared_ptr<ATileset>;
		using WeakPtr	= std::weak_ptr<ATileset>;

	public:
		ATileset();
		virtual ~ATileset();
		
	public:
		static ATileset::UPtr Create(const std::string& name,
									 const int firstgid,
									 const int tilewidth,
									 const int tileheight,
									 const int tilecount,
									 const int columns,
									 const Engine::Assets::EAssetSprite::Ptr &texture);
		
		void Destroy();
		
	public:
		int Tilewidth() const { return m_tilewidth; }
		int Tileheight() const { return m_tileheight; }
		
		bool Compare(const int tileId) const;
		SDL_Rect GetSource(const int tileId) const;
		Engine::Assets::EAssetSprite::Ptr GetTexture() const { return m_texture; }
		
		void AppendTile(const std::string &name, const int tileId);
		int FindTile(const std::string &name) const;
		
	private:
		int m_firstgid		= {};
		int m_tilewidth		= {};
		int m_tileheight	= {};
		int m_tilecount		= {};
		int m_columns		= {};
		std::string m_name;
		Engine::Assets::EAssetSprite::Ptr m_texture;

		std::map<std::string, int> m_tiles;
	};



	//---------------------------------------------------------

	class ATilesets : public std::vector<ATileset::UPtr>
	{
	public:
		using UPtr		= std::unique_ptr<ATilesets>;
		using Ptr		= std::shared_ptr<ATilesets>;
		using WeakPtr	= std::weak_ptr<ATilesets>;
		

		void Destroy() 
		{
			for (auto& tileset : *this) {
				tileset->Destroy();
			}
			clear();
		}

		int FindTile(const std::string &name) const {
			for (auto& tileset : *this) {
				const int tileId = tileset->FindTile(name);
				if (tileId > 0) return tileId;
			}
			return 0;
		}

		
	};

}




