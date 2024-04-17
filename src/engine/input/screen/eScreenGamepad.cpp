//◦ EggEngine ◦
#include "eScreenGamepad.h"
#include "engine/debug/eAssert.h"


using namespace Engine::Input;


EScreenGamepad::EScreenGamepad()
{
	//CreateKeys();
}


void EScreenGamepad::CreateKeys()
{

	auto keyUp = std::make_shared<EScreenKey>("KEY_UP");
	keyUp->SetRect({ 70, 300, 120, 350 });
	keyUp->SetColor({ 100,0,0,20 });
	keyUp->SetColorPush({ 255,255,255,255 });
	m_keys.push_back(keyUp);

	auto keyDown = std::make_shared<EScreenKey>("KEY_DOWN");
	keyDown->SetRect({ 70, 420, 120, 470 });
	keyDown->SetColor({ 100,0,0,20 });
	keyDown->SetColorPush({ 255,255,255,255 });
	m_keys.push_back(keyDown);

	auto keyLeft = std::make_shared<EScreenKey>("KEY_LEFT");
	keyLeft->SetRect({ 10, 360, 60, 410 });
	keyLeft->SetColor({ 100,0,0,20 });
	keyLeft->SetColorPush({ 255,255,255,255 });
	m_keys.push_back(keyLeft);

	auto keyRight = std::make_shared<EScreenKey>("KEY_RIGHT");
	keyRight->SetRect({ 130, 360, 180, 410 });
	keyRight->SetColor({ 100,0,0,20 });
	keyRight->SetColorPush({ 255,255,255,255 });
	m_keys.push_back(keyRight);

	auto keyJump = std::make_shared<EScreenKey>("KEY_JUMP");
	keyJump->SetRect({ 1150, 580, 1300, 750 });
	keyJump->SetColor({ 0,100,100,20 });
	keyJump->SetColorPush({ 255,255,255,255 });
	m_keys.push_back(keyJump);

	auto keyAction = std::make_shared<EScreenKey>("KEY_ACTION");
	keyAction->SetRect({1150, 10, 1300, 160});
	keyAction->SetColor({0,0,100,20});
	keyAction->SetColorPush({ 255,255,255,255 });
	m_keys.push_back(keyAction);

	auto keyMenu = std::make_shared<EScreenKey>("KEY_MENU");
	keyMenu->SetRect({ 10, 10, 60, 60 });
	keyMenu->SetColor({ 0,100,0,20 });
	keyMenu->SetColorPush({ 255,255,255,255 });
	m_keys.push_back(keyMenu);
}




void EScreenGamepad::EventInput(SDL_Event& event)
{
	SYSTouch data;
	if (m_touchScreen.EventInputDown(event, data)) {
		//Нажатие на экран
		m_activeEvent = true;
		m_touchEvent.pressed = true;
		m_touchPos = data.pos;
		m_touchId = data.id;
		
		bool down = false;
		for (const auto& key : m_keys) {
			down |= key->InputDown(data);
		}
		//return down;
	}

	if (m_touchScreen.EventInputMove(event, data)) {
		if (data.id == m_touchId) {
			m_activeEvent = true;
			m_touchEvent.moving = true;
			m_touchPos = data.pos;
		}
		
		bool move = false;
		for (const auto& key : m_keys) {
			move |= key->InputMove(data);
		}
		//return move;
	}
	
	if (m_touchScreen.EventInputUp(event, data)) {
		m_activeEvent = true;
		m_touchEvent.released = true;
		m_touchId = -1;
		
		bool up = false;
		for (const auto& key : m_keys) {
			up |= key->InputUp(data);
		}
		//return up;
	}

	//return false;
}


void EScreenGamepad::Update(const float dt)
{
	m_active = m_activeEvent;
	if (m_active) {
		m_touch = m_touchEvent;
		m_touchEvent = {};
		m_activeEvent = false;
	}
}


bool EScreenGamepad::HasControls(TControls &controls) const
{
	if (!m_active) return false;
	
	controls.touch.pos = m_touchPos;
	if (m_touch.pressed) 	controls.touch.pressed = true;
	if (m_touch.released) 	controls.touch.released = true;
	if (m_touch.moving) 	controls.touch.moving = true;
	return true;
}


void EScreenGamepad::Render(const Engine::Render::ERenderContext::UPtr& context)
{
	m_touchScreen.Init(context->RenderWidth(), context->RenderHeight());

	for (const auto& key : m_keys) {
		key->Render(context);
	}
}


EScreenKey::Ptr EScreenGamepad::FindKey(const std::string& name) const
{
	const auto item = std::find_if(m_keys.cbegin(), m_keys.cend(), [name](const auto &obj) { return obj->GetName() == name; });
	if (item != m_keys.cend()) {
		return *item;
	}
	//sassert(false);
	return {};
}
