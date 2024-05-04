#include "pch.h"
#include "cEnemyAttributes.h"

cEnemyAttributes::cEnemyAttributes(std::string modelName, glm::vec3 position, glm::vec3 forward, float speed)
{
	enemyModelName = modelName;
	enemyPosition = position;
	enemyForward = forward;
	enemySpeed = speed;
}

// Function to make the enemy move towards the player
void cEnemyAttributes::Seek(cControlGameEngine& gameEngine, sPlayerAttributes& playerAttributes)
{
	glm::vec3 direction = glm::normalize(playerAttributes.playerPosition - enemyPosition);

	glm::vec3 orientationDirection = glm::normalize(glm::vec3(direction.x, 0.0f, direction.z));

	glm::quat rotationQuat = glm::rotation(enemyForward, orientationDirection);

	// Rotating model using quaternion
	gameEngine.RotateMeshModelUsingQuaternion(enemyModelName, rotationQuat);

	// Condition to check if the enemy model is not very close to the player
	if (glm::length(enemyPosition - playerAttributes.playerPosition) >= CLOSEST_DISTANCE)
	{
		enemyPosition += enemySpeed * orientationDirection * static_cast<float>(gameEngine.deltaTime);

		// Moving model towards player direction
		gameEngine.MoveModel(enemyModelName, enemyPosition.x, enemyPosition.y, enemyPosition.z);

		gameEngine.UseManualColors(enemyModelName, true);
		gameEngine.ChangeColor(enemyModelName, 0.85f, 0.f, 0.f); // Red
	}
	else
		gameEngine.UseManualColors(enemyModelName, false);
}

// Function to make the enemy move away from the player
void cEnemyAttributes::Flee(cControlGameEngine& gameEngine, sPlayerAttributes& playerAttributes)
{
	// Condition to check if the player is close enough for the enemy to flee
	if (glm::length(enemyPosition - playerAttributes.playerPosition) < MAINTAIN_DISTANCE)
	{
		glm::vec3 fleeDirection = glm::normalize(enemyPosition - playerAttributes.playerPosition);

		glm::vec3 orientationDirection = glm::normalize(glm::vec3(fleeDirection.x, 0.0f, fleeDirection.z));

		glm::quat rotationQuat = glm::rotation(enemyForward, orientationDirection);

		// Rotating model using quaternion
		gameEngine.RotateMeshModelUsingQuaternion(enemyModelName, rotationQuat);

		enemyPosition += enemySpeed * orientationDirection * static_cast<float>(gameEngine.deltaTime);

		// Moving the enemy away from the player
		gameEngine.MoveModel(enemyModelName, enemyPosition.x, enemyPosition.y, enemyPosition.z);

		gameEngine.UseManualColors(enemyModelName, true);
		gameEngine.ChangeColor(enemyModelName, 0.f, 0.f, 0.85f); // Blue
	}
	else
		gameEngine.UseManualColors(enemyModelName, false);
}

// Function to make the enemy move towards the player's future position
void cEnemyAttributes::Pursue(cControlGameEngine& gameEngine, sPlayerAttributes& playerAttributes)
{
	glm::vec3 futurePlayerPosition = playerAttributes.playerPosition + playerAttributes.playerVelocity * TIME_HORIZON;

	glm::vec3 pursueDirection = glm::normalize(futurePlayerPosition - enemyPosition); // Direction for movement

	glm::vec3 direction = glm::normalize(playerAttributes.playerPosition - enemyPosition); // Direction for orientation

	glm::vec3 orientationDirection = glm::normalize(glm::vec3(direction.x, 0.0f, direction.z));

	glm::quat rotationQuat = glm::rotation(enemyForward, orientationDirection);

	// Rotating model using quaternion
	gameEngine.RotateMeshModelUsingQuaternion(enemyModelName, rotationQuat);

	if (glm::length(enemyPosition - futurePlayerPosition) > 10.0f)
	{
		enemyPosition += enemySpeed * pursueDirection * static_cast<float>(gameEngine.deltaTime);

		// Moving model towards player direction
		gameEngine.MoveModel(enemyModelName, enemyPosition.x, enemyPosition.y, enemyPosition.z);

		gameEngine.UseManualColors(enemyModelName, true);
		gameEngine.ChangeColor(enemyModelName, 0.f, 0.85f, 0.f); // Green
	}
	else
		gameEngine.UseManualColors(enemyModelName, false);
}

// Function to make the enemy move away from the player's future position
void cEnemyAttributes::Evade(cControlGameEngine& gameEngine, sPlayerAttributes& playerAttributes)
{
	glm::vec3 futurePlayerPosition = playerAttributes.playerPosition + playerAttributes.playerVelocity * TIME_HORIZON;

	if (glm::length(enemyPosition - futurePlayerPosition) < MAINTAIN_DISTANCE)
	{
		glm::vec3 fleeDirection = glm::normalize(enemyPosition - futurePlayerPosition);

		glm::vec3 orientationDirection = glm::normalize(glm::vec3(fleeDirection.x, 0.0f, fleeDirection.z));

		glm::quat rotationQuat = glm::rotation(enemyForward, orientationDirection);

		// Rotating model using quaternion
		gameEngine.RotateMeshModelUsingQuaternion(enemyModelName, rotationQuat);

		enemyPosition += enemySpeed * orientationDirection * static_cast<float>(gameEngine.deltaTime);

		// Moving the enemy away from the player
		gameEngine.MoveModel(enemyModelName, enemyPosition.x, enemyPosition.y, enemyPosition.z);

		gameEngine.UseManualColors(enemyModelName, true);
		gameEngine.ChangeColor(enemyModelName, 0.85f, 0.85f, 0.f); // Yellow
	}
	else
		gameEngine.UseManualColors(enemyModelName, false);
}

// Function to make the enemy maintain distance from the player
void cEnemyAttributes::Approach(cControlGameEngine& gameEngine, sPlayerAttributes& playerAttributes)
{
	float offset = 10.f;

	if (glm::length(enemyPosition - playerAttributes.playerPosition) > MAINTAIN_DISTANCE + offset)
	{
		glm::vec3 direction = glm::normalize(playerAttributes.playerPosition - enemyPosition);

		glm::vec3 orientationDirection = glm::normalize(glm::vec3(direction.x, 0.0f, direction.z));

		glm::quat rotationQuat = glm::rotation(enemyForward, orientationDirection);

		// Rotating model using quaternion
		gameEngine.RotateMeshModelUsingQuaternion(enemyModelName, rotationQuat);

		// Condition to check if the enemy model is not very close to the player
		if (glm::length(enemyPosition - playerAttributes.playerPosition) > MAINTAIN_DISTANCE + offset)
		{
			enemyPosition += enemySpeed * orientationDirection * static_cast<float>(gameEngine.deltaTime);

			// Moving model towards player direction
			gameEngine.MoveModel(enemyModelName, enemyPosition.x, enemyPosition.y, enemyPosition.z);

			gameEngine.UseManualColors(enemyModelName, true);
			gameEngine.ChangeColor(enemyModelName, 0.f, 0.85f, 0.85f); // Light Blue
		}
		else
			gameEngine.UseManualColors(enemyModelName, false);
	}

	else if (glm::length(enemyPosition - playerAttributes.playerPosition) < MAINTAIN_DISTANCE)
	{
		glm::vec3 fleeDirection = glm::normalize(enemyPosition - playerAttributes.playerPosition);

		glm::vec3 orientationDirection = glm::normalize(glm::vec3(fleeDirection.x, 0.0f, fleeDirection.z));

		glm::quat rotationQuat = glm::rotation(enemyForward, orientationDirection);

		// Rotating model using quaternion
		gameEngine.RotateMeshModelUsingQuaternion(enemyModelName, rotationQuat);

		enemyPosition += enemySpeed * orientationDirection * static_cast<float>(gameEngine.deltaTime);

		// Moving the enemy away from the player
		gameEngine.MoveModel(enemyModelName, enemyPosition.x, enemyPosition.y, enemyPosition.z);

		gameEngine.UseManualColors(enemyModelName, true);
		gameEngine.ChangeColor(enemyModelName, 0.f, 0.85f, 0.85f); // Light Blue
	}
	else
		gameEngine.UseManualColors(enemyModelName, false);
}
