<<--------------------------------------------------------------------------------Artificial_Intelligence_Project_01------------------------------------------------------------------------------------------>>

# Developers :
	- This project was done by Max Sherwin(1128059) and Keerthivasan Kalaivanan(1190826)

# About Project :
	- The project reads the scene contents( i.e the model properties, light properties, etc) from the json file located in "Artificial_Intelligence_Project_01->GameWorldConstruct->SceneDescription.json".

	- In the scene I have placed 5 Beholders and 1 controller character(Lego Spiderman). 
	
	- The Lego Spiderman can be controlled by the user using 'WASD' keys. The player can move around in 4 directions and the camera follows the player making it a 3rd person scene.
	
	- The 5 Beholders each will indicate different behaviours when moved closer to it or moved far away from it.
	
	- The Beholder will Seek the player(indicated with 'Red' color), Flee from the player(indicated with 'Blue' color), Pursue the player(indicated with 'Green' color), Evade from the player(indicated with 'Yellow' color) and Approach the player by maintaining a distance(indicated with 'Light Blue' color). 
	
	- The Behaviours can be changed in the main() function under the project 'GameWorldConstruct' inside the while loop( with a commented line on top saying 'Update Game Loop').  

	- The speed of the characters can also be changed above the main() function in the main.cpp file(with a commented line on top saying 'Game World Character Model Instances').

## How to build and run : 
	- The solution "Artificial_Intelligence_Project_01.sln" has to be built(either in debug or release platform mode) and then once succeeded(probably will!), make the "GameWorldConstruct" project as the startup project and now it'll be able to run for some visual treat.
	- When building the solution, the "MaxGameEngine" project should be run first since it is a static project without which the project with contents(GameWorldConstruct) cannot be run.
	
### Controls :
	- WASD keys = The buttons to control the character