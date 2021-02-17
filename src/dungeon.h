#ifndef DUNGEON_H
#define DUNGEON_H

#include <vector>

#include "renderer.h"

enum BlockType{
    none = 0,
    ground = 1,
    wall = 2
};

const int MIN_ROOM_SIZE = 3;
const int MAX_ROOM_SIZE = 6;
const int MIN_ROOM_COUNT = 10;
const int MAX_ROOM_COUNT = 20;

class Room{
public:
    Room(int x, int y, int w, int h);
    Room(const Room& room);
    Room();

private:
    unsigned int mX;
    unsigned int mY;
    unsigned int mWidth;
    unsigned int mHeight;
};

class Dungeon
{
public:
    Dungeon(int w, int h);
    ~Dungeon();

    void reset();
    void draw(Renderer& renderer) const;

private:

    void initialize();
    void generateRandomDungeon();
    std::vector<Room> generateRooms();
    Room generateRoom();

    BlockType block(int x, int y) const;

private:
    const int mWidth;
    const int mHeight;
    BlockType** mDungeonBlocks;
};


#endif // DUNGEON_H
