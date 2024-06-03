#include "RoomManager.h"
#include "RequestError.hpp"
int RoomManager::counter = 0;
Room RoomManager::createRoom(LoggedUser user, RoomData roomdata)
{
    int curr = counter;
    roomdata.id = curr;//set the id to the counterId
    Room r(roomdata,user);
    this->m_rooms.insert(std::make_pair(curr,std::ref(r)));
    counter++;
    return r;
}

void RoomManager::deleteRoom(int ID)
{
    for (auto it = this->m_rooms.begin(); it != this->m_rooms.end(); it++)
    {
        if (it->second.getRoomData().id == ID)
        {
            m_rooms.erase(it);
            return;
        }
    }
}

bool RoomManager::isRoomExsist(int id)
{
    for (auto it = this->m_rooms.begin(); it != this->m_rooms.end(); it++)
    {
        if (it->second.getRoomData().id == id)
        {
            return true;
        }
    }
    return false;
}

int RoomManager::getRoomState(int ID)
{
    return this->getRoom(ID).getRoomData().isActive;
}

std::vector<RoomData> RoomManager::getRooms()
{
    std::vector<RoomData> rooms;
    for (auto it = this->m_rooms.begin(); it != this->m_rooms.end(); it++)
    {
        rooms.push_back(it->second.getRoomData());
    }
    return rooms;
}

Room& RoomManager::getRoomByName(std::string name)
{
    for (auto it = this->m_rooms.begin(); it != this->m_rooms.end(); it++)
    {
        if (it->second.getRoomData().name == name)
        {
            return it->second;
        }
    }
    throw RequestError();
}

Room& RoomManager::getRoom(int ID)
{
    for (auto it = this->m_rooms.begin(); it != this->m_rooms.end(); it++)
    {
        if (it->first == ID)
        {
            return it->second;
        }
    }
}

int RoomManager::getIdOfRoom(Room room)
{
    for (auto it = this->m_rooms.begin(); it != this->m_rooms.end(); it++)
    {
        if (it->second.getRoomData().name == room.getRoomData().name)
        {
            return it->first;
        }
    }
    return -1;
}


