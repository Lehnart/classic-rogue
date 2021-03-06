#ifndef DUNGEON_H
#define DUNGEON_H

#include <random>
#include <vector>

#include "block.h"
#include "goldpile.h"
#include "renderer.h"

class Room{
public:
    Room(int x, int y, int w, int h);
    Room(const Room& room);
    Room();

    int xc() const {return mX + (mWidth/2);}
    int yc() const {return mY + (mHeight/2);}

    int randomX(std::random_device& rand) const ;
    int randomY(std::random_device& rand) const ;

    bool isIn(unsigned int x, unsigned int y) const;

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
    void view(unsigned int povX, unsigned int povY);
    void getRandomRoomPosition(int& x, int& y);
    Block& block(int x, int y) const;

    std::vector<Room>& getRooms() {return mRooms;}

private:

    void initialize();
    void generateRandomDungeon();
    Room generateRoom();
    std::vector<Room> generateRooms();
    void connectRooms(std::vector<Room> rooms);
    bool connect2Rooms(const Room& room1, const Room& room2);

    void generateGold(const Room& room);

private:
    const int mWidth;
    const int mHeight;
    Block** mDungeonBlocks;
    std::vector<Room> mRooms;

    std::vector<GoldPile> mGoldPiles;

    std::random_device mRandomGenerator;
};


#endif // DUNGEON_H
