#ifndef ROOM_MANAGER_H
#define ROOM_MANAGER_H

#include <vector>

class Room;

class RoomManager
{
public:
	RoomManager();
	~RoomManager();

	void Init(int _numRooms);
	Room* GetCurrentRoom();
	void SetCurrentRoom(int _id);
private:
	int currentRoom;
	std::vector<Room*> rooms;
};

#endif