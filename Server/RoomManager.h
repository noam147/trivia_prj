#pragma once
#include <map>
#include "Room.h"
class RoomManager
{
public:
	Room createRoom(LoggedUser user, RoomData roomdata);

	void deleteRoom(int ID);
	bool isRoomExsist(int id);
	int getRoomState(int ID);
	std::vector<RoomData> getRooms();
	Room& getRoomByName(std::string name);
	Room& getRoom(int ID);
	int getIdOfRoom(Room room);
private:
	std::map<int, Room&> m_rooms;//roomID
	int _roomId = { 0 };
	static int counter;
};