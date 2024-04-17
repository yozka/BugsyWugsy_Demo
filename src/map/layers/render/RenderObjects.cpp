//◦ EggEngine ◦
#include "RenderObjects.h"
#include "engine/debug/eAssert.h"
#include "engine/common/eRect.h"
#include "components/ComponentRendering.h"


using namespace Game::Map;


ARenderObjects::ARenderObjects(const int width, const int height, const int tilewidth, const int tileheight)
:
	   m_width(width),
	   m_height(height),
	   m_tilewidth(tilewidth),
	   m_tileheight(tileheight)
{

}


ARenderObjects::~ARenderObjects()
{

}


void ARenderObjects::Render(const ALayerRenderObjects::Ptr &layer,
							const Engine::Render::ESpriteBatch::UPtr &context,
							const ACamera::Ptr &camera)
{
	const auto vision = camera->GetVisionObjects();
	
	//Сдесь максимально наивная реализация
	//смотрим весь список, и проверяем попадает ли объект в область видимости
	for (const auto& obj : layer->Objects()) {
		const auto& component = obj->GetComponent<Components::AComponentRendering>();
		if (component) {
			const Engine::FRect geometry = component->Geometry();
			if (geometry.IsIntersect(vision.viewRect)) {

				const Engine::FPoint objPos = geometry.Center();
				float x = objPos.x * vision.scale;
				float y = objPos.y * vision.scale;
				Engine::IPoint pt(vision.screenObjectStartX + x, vision.screenObjectStartY + y);
				component->Render(context, pt, vision.scale);
			}
		}
	}
}
