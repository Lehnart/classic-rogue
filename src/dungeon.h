#ifndef DUNGEON_H
#define DUNGEON_H

#include <vector>

#include "block.h"
#include "renderer.h"

class Room{
public:
    Room(int x, int y, int w, int h);
    Room(const Room& room);
    Room();

    int xc() const {return mX + (mWidth/2);}
    int yc() const {return mY + (mHeight/2);}

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
    Room generateRoom();
    std::vector<Room> generateRooms();
    void connectRooms(std::vector<Room> rooms);
    void connect2Rooms(const Room& room1, const Room& room2);

    Block block(int x, int y) const;

private:
    const int mWidth;
    const int mHeight;
    Block** mDungeonBlocks;
};


#endif // DUNGEON_H
