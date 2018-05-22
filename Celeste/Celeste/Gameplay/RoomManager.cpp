#include "RoomManager.h"

#include "Room.h"

#include <string>

int RoomManager::currentRoom = 0;

RoomManager::RoomManager()
{
}

RoomManager::~RoomManager()
{
	for (auto room : rooms)
	{
		delete room;
		room = nullptr;
	}
}

void RoomManager::Init(int _numRooms)
{
	std::string folder = "Assets/Rooms/room";
	for (int i = 0; i < _numRooms; i++)
	{
		std::string filepath = folder + std::to_string(i) + ".txt";
		Room* room = new Room();
		room->Init(filepath);
		rooms.push_back(room);
	}
}

Room * RoomManager::GetCurrentRoom()
{
	return rooms[currentRoom];
}

void RoomManager::SetCurrentRoom(int _id)
{
	currentRoom = _id;
}
