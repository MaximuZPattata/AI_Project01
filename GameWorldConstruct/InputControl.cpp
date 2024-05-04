#include "pch.h"

#include "cControlGameEngine.h"
#include "PlayerAttributes.h"

extern cControlGameEngine gameEngine;

const float POSITION_OFFSET = 0.0f;

extern sPlayerAttributes playerAttributes;

cMesh* controlMeshModel;

void resetCamAttributes()
{
    if (!gameEngine.mouseMoved)
        gameEngine.mouseMoved = true;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

    float ROTATION_DEGREES = 5.0f;

    const float CAMERA_SPEED = 300.0f;

    const float MODEL_MOVE_SPEED = 1.0f;

    float CAMERA_MOVEMENT = CAMERA_SPEED * gameEngine.deltaTime;

    glm::vec3 CAMERA_TARGET = gameEngine.GetCurrentCameraTarget();
    glm::vec3 CAMERA_UP = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 CAMERA_POSITION = gameEngine.GetCurrentCameraPosition();


    if (mods == 0)
    {
        //----------------------------Player Controls---------------------------------------------

        if (key == GLFW_KEY_W) // Player move forward
        {
            playerAttributes.playerVelocity.z = -playerAttributes.playerSpeed;

            playerAttributes.playerPosition += playerAttributes.playerVelocity;

            if (playerAttributes.playerDirection != ePlayerDirection::FRONT)
            {
                if (playerAttributes.playerDirection == ePlayerDirection::BACK)
                    gameEngine.RotateMeshModel(playerAttributes.playerModelName, 180.f, 0.f, 1.f, 0.f);
                else if(playerAttributes.playerDirection == ePlayerDirection::LEFT)
                    gameEngine.RotateMeshModel(playerAttributes.playerModelName, -90.f, 0.f, 1.f, 0.f);
                else if (playerAttributes.playerDirection == ePlayerDirection::RIGHT)
                    gameEngine.RotateMeshModel(playerAttributes.playerModelName, 90.f, 0.f, 1.f, 0.f);

                playerAttributes.playerDirection = ePlayerDirection::FRONT;
            }

            gameEngine.MoveModel(playerAttributes.playerModelName, playerAttributes.playerPosition.x, playerAttributes.playerPosition.y, playerAttributes.playerPosition.z);
        }

        else if (key == GLFW_KEY_S) // Player move backward
        {
            playerAttributes.playerVelocity.z = playerAttributes.playerSpeed;

            playerAttributes.playerPosition += playerAttributes.playerVelocity;

            if (playerAttributes.playerDirection != ePlayerDirection::BACK)
            {
                if (playerAttributes.playerDirection == ePlayerDirection::FRONT)
                    gameEngine.RotateMeshModel(playerAttributes.playerModelName, 180.f, 0.f, 1.f, 0.f);
                else if (playerAttributes.playerDirection == ePlayerDirection::LEFT)
                    gameEngine.RotateMeshModel(playerAttributes.playerModelName, 90.f, 0.f, 1.f, 0.f);
                else if (playerAttributes.playerDirection == ePlayerDirection::RIGHT)
                    gameEngine.RotateMeshModel(playerAttributes.playerModelName, -90.f, 0.f, 1.f, 0.f);

                playerAttributes.playerDirection = ePlayerDirection::BACK;
            }

            gameEngine.MoveModel(playerAttributes.playerModelName, playerAttributes.playerPosition.x, playerAttributes.playerPosition.y, playerAttributes.playerPosition.z);
        }

        else
            playerAttributes.playerVelocity.z = 0.0f;

        if (key == GLFW_KEY_A) // Player move left
        {
            playerAttributes.playerVelocity.x = -playerAttributes.playerSpeed;

            playerAttributes.playerPosition += playerAttributes.playerVelocity;

            if (playerAttributes.playerDirection != ePlayerDirection::LEFT)
            {
                if (playerAttributes.playerDirection == ePlayerDirection::FRONT)
                    gameEngine.RotateMeshModel(playerAttributes.playerModelName, 90.f, 0.f, 1.f, 0.f);
                else if (playerAttributes.playerDirection == ePlayerDirection::BACK)
                    gameEngine.RotateMeshModel(playerAttributes.playerModelName, -90.f, 0.f, 1.f, 0.f);
                else if (playerAttributes.playerDirection == ePlayerDirection::RIGHT)
                    gameEngine.RotateMeshModel(playerAttributes.playerModelName, 180.f, 0.f, 1.f, 0.f);

                playerAttributes.playerDirection = ePlayerDirection::LEFT;
            }

            gameEngine.MoveModel(playerAttributes.playerModelName, playerAttributes.playerPosition.x, playerAttributes.playerPosition.y, playerAttributes.playerPosition.z);
        }
        
        else if (key == GLFW_KEY_D) // Player move right
        {
            playerAttributes.playerVelocity.x = playerAttributes.playerSpeed;

            playerAttributes.playerPosition += playerAttributes.playerVelocity;

            if (playerAttributes.playerDirection != ePlayerDirection::RIGHT)
            {
                if (playerAttributes.playerDirection == ePlayerDirection::FRONT)
                    gameEngine.RotateMeshModel(playerAttributes.playerModelName, -90.f, 0.f, 1.f, 0.f);
                else if (playerAttributes.playerDirection == ePlayerDirection::BACK)
                    gameEngine.RotateMeshModel(playerAttributes.playerModelName, 90.f, 0.f, 1.f, 0.f);
                else if (playerAttributes.playerDirection == ePlayerDirection::LEFT)
                    gameEngine.RotateMeshModel(playerAttributes.playerModelName, -180.f, 0.f, 1.f, 0.f);

                playerAttributes.playerDirection = ePlayerDirection::RIGHT;
            }

            gameEngine.MoveModel(playerAttributes.playerModelName, playerAttributes.playerPosition.x, playerAttributes.playerPosition.y, playerAttributes.playerPosition.z);
        }

        else
            playerAttributes.playerVelocity.x = 0.0f;
    }

    return;
}

void mouse_callback(GLFWwindow* window, double xPos, double yPos)
{
    if (gameEngine.enableMouseMovement)
    {
        glm::vec3 CAMERA_UP = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::vec3 CAMERA_POSITION = gameEngine.GetCurrentCameraPosition();

        int screenWidth, screenHeight;
        glfwGetWindowSize(window, &screenWidth, &screenHeight);

        float mouseSensitivity = 0.05f;

        float xOffset = 0.0f;
        float yOffset = 0.0f;

        if (xPos >= screenWidth - 1 || xPos <= 0) // Rotate Cam when mouse moves to the edge of the screen(left or right)
        {
            xOffset = 0.0f;

            if (xPos <= 0)
                xOffset = -10.0f;
            else if (xPos >= screenWidth - 1)
                xOffset = 10.0f;

            gameEngine.yaw += mouseSensitivity * xOffset;
        }

        if (yPos >= screenHeight - 1 || yPos <= 20) // Rotate Cam when mouse moves to the edge of the screen(up or down)
        {
            yOffset = 0.0f;

            if (yPos <= 20)
                yOffset = 10.0f;
            else if (yPos >= screenHeight - 1)
                yOffset = -10.0f;

            gameEngine.pitch += mouseSensitivity * yOffset;
        }

        if (gameEngine.mouseMoved)
        {
            gameEngine.previousX = xPos;
            gameEngine.previousY = yPos;
            gameEngine.mouseMoved = false;
        }

        xOffset = xPos - gameEngine.previousX;
        yOffset = gameEngine.previousY - yPos; //Reversed Y

        xOffset *= mouseSensitivity;
        yOffset *= mouseSensitivity;

        gameEngine.yaw += xOffset;
        gameEngine.pitch += yOffset;

        if (gameEngine.pitch > 90.0f)
            gameEngine.pitch = 90.0f;

        if (gameEngine.pitch < -90.0f)
            gameEngine.pitch = -90.0f;

        glm::vec3 front;

        front.x = cos(glm::radians(gameEngine.yaw)) * cos(glm::radians(gameEngine.pitch));
        front.y = sin(glm::radians(gameEngine.pitch));
        front.z = sin(glm::radians(gameEngine.yaw)) * cos(glm::radians(gameEngine.pitch));

        glm::vec3 cameraFront = glm::normalize(front);

        gameEngine.MoveCameraTarget(cameraFront.x, cameraFront.y, cameraFront.z);

        gameEngine.previousX = xPos;
        gameEngine.previousY = yPos;
    }
}