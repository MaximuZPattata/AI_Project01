#pragma once
#include "pch.h"

#include "PlayerAttributes.h"
#include <cControlGameEngine.h>

class cEnemyAttributes
{
public:
	glm::vec3 enemyPosition;
	glm::vec3 enemyForward;

	std::string enemyModelName;
	
	float enemySpeed;

	cEnemyAttributes(std::string modelName, glm::vec3 position, glm::vec3 forward, float speed);

	void Seek(cControlGameEngine& gameEngine, sPlayerAttributes& playerAttributes);
	void Flee(cControlGameEngine& gameEngine, sPlayerAttributes& playerAttributes);
	void Pursue(cControlGameEngine& gameEngine, sPlayerAttributes& playerAttributes);
	void Evade(cControlGameEngine& gameEngine, sPlayerAttributes& playerAttributes);
	void Approach(cControlGameEngine& gameEngine, sPlayerAttributes& playerAttributes);

private:

	float CLOSEST_DISTANCE = 25.f; // The closest the enemy can get to the player is 25 units(SEEK)
	float MAINTAIN_DISTANCE = 75.f; // Length of distance the enemy has to maintain from the player before fleeing(FLEE and APPROACH)
	float TIME_HORIZON = 15.0f; // How much further the AI should look into the player's position(PURSUE and EVADE)
};

