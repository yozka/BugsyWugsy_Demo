//◦ EggEngine ◦
#pragma once
#include <string>
#include <memory>
#include <unordered_map>
#include <typeinfo>
#include <typeindex>

#include "eAsset.h"
#include "engine/debug/eAssert.h"

namespace Engine::Assets
{

	class EAssetResources
	{
	public:
		using Ptr		= std::shared_ptr<EAssetResources>;
		using UPtr		= std::unique_ptr<EAssetResources>;
		using WeakPtr	= std::weak_ptr<EAssetResources>;
		
	public:
		EAssetResources() = default;
		virtual ~EAssetResources() = default;
		
	public:
		
		template<typename T>
		std::shared_ptr<T> Add(std::shared_ptr<T> asset)
		{
			const std::string name = asset->Name();
			auto &collect = m_collects[std::type_index(typeid(T))];
			collect[name] = asset;
			return asset;
		}
		
		template<typename T>
		std::shared_ptr<T> Find(const std::string &name) const
		{
			const auto collect = m_collects.find(std::type_index(typeid(T)));
			if (collect != m_collects.cend()) {
				const auto asset = collect->second.find(name);
				if (asset != collect->second.cend()) {
					return std::static_pointer_cast<T>(asset->second);
				}
			}
			sassert(false);
			return {};
		}

		bool Contains(const std::string& name) const
		{
			for (const auto& collect : m_collects) {
				const auto asset = collect.second.find(name);
				if (asset != collect.second.cend()) {
					return true;
				}
			}
			return false;
		}
		
		template<typename T>
		bool Contains(const std::string& name) const
		{
			const auto collect = m_collects.find(std::type_index(typeid(T)));
			if (collect != m_collects.cend()) {
				const auto asset = collect->second.find(name);
				if (asset != collect->second.cend()) {
					return true;
				}
			}
			return false;
		}
		
		void RemoveGroup(const std::string& group)
		{
			for (auto& collect : m_collects) {
				auto& map = collect.second;
				for (auto it = std::begin(map); it != std::end(map);) {
					if (it->second->Group() == group) {
						it = map.erase(it);
					} else ++it;
				}
			}
		}
		
		template<typename T>
		void RemoveGroup(const std::string& group)
		{
			auto collect = m_collects.find(std::type_index(typeid(T)));
			if (collect == m_collects.end()) return;
			auto& map = collect->second;
			for (auto it = std::begin(map); it != std::end(map);) {
				if (it->second->Group() == group) {
					it = map.erase(it);
				} else ++it;
			}
		}


	private:
		using TCollects = std::unordered_map<std::string, EAsset::Ptr>;
		std::unordered_map<std::type_index, TCollects> m_collects;
		
	};

}
