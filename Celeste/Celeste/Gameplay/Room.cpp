#include "Room.h"

#include "../Engine/ResourceManager.h"
#include "../Engine/Graphics/SpriteRenderer.h"
#include "Celeste.h"
#include "RoomObjects/Platform.h"
#include "RoomObjects/PassablePlatform.h"
#include "RoomObjects/Spikes.h"
#include "RoomObjects/Gem.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>

Room::Room()
{
}

Room::~Room()
{
	for (auto object : roomObjects)
	{
		delete object;
		object = nullptr;
	}
}

void Room::Update(GLfloat _dt)
{
	for (auto object : roomObjects)
	{
		object->Update(_dt);
	}
}

void Room::Render(SpriteRenderer & _renderer)
{
	for (auto object : roomObjects)
	{
		object->Render(_renderer);
	}
}

void Room::DoCollisions(Celeste & _celeste)
{
	for (auto object : roomObjects)
	{
		object->DoCollision(_celeste);
	}
}

void Room::Init(std::string filePath)
{
	std::string line;
	std::ifstream infile;
	infile.open(filePath);

	//set id of room
	std::getline(infile, line);
	id = std::stoi(line);

	//set neighbors of room
	std::getline(infile, line);
	std::istringstream ss(line);
	std::istream_iterator<std::string> begin(ss), end;
	std::vector<std::string> neighborsString(begin, end);
	for (auto neighbor : neighborsString)
	{
		neighbors.push_back(std::stoi(neighbor));
	}

	//add room objects
	while (!infile.eof())
	{
		std::getline(infile, line);
		AddObject(line);
	}
	infile.close();
}

void Room::AddObject(std::string line)
{
	std::istringstream ss(line);
	std::istream_iterator<std::string> begin(ss), end;
	std::vector<std::string> tokens(begin, end);
	if (tokens[0] == "HGround" || tokens[0] == "VGround")
	{
		roomObjects.push_back(new Platform(glm::vec2(std::stof(tokens[1]), std::stof(tokens[2])),
			glm::vec2(std::stof(tokens[3]), std::stof(tokens[4])), std::stof(tokens[5]), ResourceManager::GetTexture(tokens[0])));
	}
	else if (tokens[0] == "PassablePlatform")
	{
		roomObjects.push_back(new PassablePlatform(glm::vec2(std::stof(tokens[1]), std::stof(tokens[2])),
			glm::vec2(std::stof(tokens[3]), std::stof(tokens[4])), ResourceManager::GetTexture(tokens[0])));
	}
	else if (tokens[0] == "Spikes")
	{
		roomObjects.push_back(new Spikes(glm::vec2(std::stof(tokens[1]), std::stof(tokens[2])),
			glm::vec2(std::stof(tokens[3]), std::stof(tokens[4])), std::stof(tokens[5]), ResourceManager::GetTexture(tokens[0])));
	}
	else if (tokens[0] == "Gem")
	{
		roomObjects.push_back(new Gem(glm::vec2(std::stof(tokens[1]), std::stof(tokens[2])),
			glm::vec2(std::stof(tokens[3]), std::stof(tokens[4])), ResourceManager::GetTexture(tokens[0])));
	}
	else
	{
		std::cout << "Invalid Line. Cannot add object." << std::endl;
	}
}

std::vector<GameObject*> Room::GetRoomObjects() const
{
	return roomObjects;
}
