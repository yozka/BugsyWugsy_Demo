//◦ EggEngine ◦
#pragma once
#include <string>
#include <memory>


namespace Engine::Assets
{

	class EAsset
	{
	public:
		using Ptr = std::shared_ptr<EAsset>;
		using UPtr = std::unique_ptr<EAsset>;
		
	public:
		EAsset() = default;
		virtual ~EAsset() = default;
		
	public:
		virtual std::string Name() const = 0;
		virtual std::string Group() const = 0; //Группа ассета
		
	};

}
