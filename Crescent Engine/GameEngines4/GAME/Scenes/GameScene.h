#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "../TesterClasses/ComponentA.h"
#include "../TesterClasses/ComponentB.h"
#include "../TesterClasses/AIComponent.h"
#include "../../Engine/Core/CoreEngine.h"
#include "../../Engine/Rendering/3D/ParticleEmitter.h"
#include "../../Engine//Math/IntDecision.h"
#include <glm/gtx/string_cast.hpp>

class GameScene : public Scene
{
public:
	GameScene();
	virtual ~GameScene();
	
	virtual bool OnCreate();
	virtual void Update(const float deltaTime_);
	virtual void Render();

private:
	LightSource* lightSource; 
	ParticleEmitter* particleEmitter; 
	IntDecision* intDecision; 

	std::string selectedObject;
	bool propertiesWindowOpen;
	bool hasObjects;
};
#endif

