#include "dungeon.h"

#include "block.h"
#include "renderer.h"

#include <vector>
#include <random>
#include <iostream>

#include <SDL2/SDL.h>

#define MIN_ROOM_SIZE  5
#define MAX_ROOM_SIZE  8
#define MIN_ROOM_COUNT 10
#define MAX_ROOM_COUNT 15

Room::Room(int x, int y, int width, int height):
    mX(x),
    mY(y),
    mWidth(width),
    mHeight(height){}


Room::Room(const Room& room):
    Room(room.mX, room.mY, room.mWidth, room.mHeight){
}

Room::Room():
    Room(0, 0, 1, 1){
}

int Room::randomX(std::random_device& rand) const {
    std::uniform_int_distribution<> roomXRand(mX+1, mX+mWidth-2);
    return roomXRand(rand);
}

int Room::randomY(std::random_device& rand) const {
    std::uniform_int_distribution<> roomYRand(mY+1, mY+mHeight-2);
    return roomYRand(rand);
}

Dungeon::Dungeon(int w, int h):
    mWidth(w),
    mHeight(h)
{
    generateRandomDungeon();
}

Dungeon::~Dungeon(){
    for(int j = 0; j < mHeight; j++){
        delete[] mDungeonBlocks[j];
    }
    delete[] mDungeonBlocks;
}

void Dungeon::draw(Renderer& renderer) const{
    for(int j = 0; j < mHeight; j++){
        for(int i = 0; i < mWidth; i++){
            block(i,j).draw(renderer);
        }
    }
}

void Dungeon::reset(){
    this->~Dungeon();
    generateRandomDungeon();
}

void Dungeon::generateRandomDungeon(){
    initialize();
    std::vector<Room> rooms = generateRooms();
    connectRooms(rooms);
}

void Dungeon::initialize(){
    mDungeonBlocks = new Block*[mHeight];
    for(int j = 0; j < mHeight; j++){
        mDungeonBlocks[j] = new Block[mWidth];
        for(int i = 0; i < mWidth; i++){
            mDungeonBlocks[j][i].setX(i*BLOCK_WIDTH);
            mDungeonBlocks[j][i].setY(j*BLOCK_HEIGHT);
            mDungeonBlocks[j][i].setType(BlockType::none);
        }
    }
}

std::vector<Room> Dungeon::generateRooms(){
    std::uniform_int_distribution<> roomSizeRand(MIN_ROOM_COUNT, MAX_ROOM_COUNT);

    int nRooms = roomSizeRand(mRandomGenerator);
    std::vector<Room> rooms;

    for(int i = 0 ; i < nRooms; i++){
        Room room = generateRoom();
        rooms.emplace_back(room);
    }
    return rooms;
}

Room Dungeon::generateRoom(){

    bool isEmpty = true;
    int yMin =0, xMin =0, width =0, height =0;
    do{
        isEmpty = true;
        std::uniform_int_distribution<> roomSizeRand(MIN_ROOM_SIZE, MAX_ROOM_SIZE);

        width = roomSizeRand(mRandomGenerator);
        height = roomSizeRand(mRandomGenerator);
        int xMax = static_cast<int>(mWidth) - width - 1;
        int yMax = static_cast<int>(mHeight) - height - 1;

        std::uniform_int_distribution<> topRand(1, yMax);
        std::uniform_int_distribution<> leftRand(1, xMax);
        yMin = topRand(mRandomGenerator);
        xMin = leftRand(mRandomGenerator);

        for(int j = yMin-1; j < yMin + height + 1; j++){
            for(int i=xMin-1; i < xMin + width + 1; i++){
                if(block(i,j).getType() != BlockType::none){
                    isEmpty = false;
                }
            }
        }
    } while( !isEmpty );

    for(int i = xMin+1; i < xMin + width-1; i++){
        for(int j=yMin+1; j < yMin + height-1; j++){
            mDungeonBlocks[j][i].setType(BlockType::ground);
        }
    }

    for(int i = xMin+1; i < xMin + width-1; i++){
        mDungeonBlocks[yMin][i].setType(BlockType::hwall);
        mDungeonBlocks[yMin + height-1][i].setType(BlockType::hwall);
    }
    for(int j=yMin+1; j < yMin + height-1; j++){
        mDungeonBlocks[j][xMin].setType(BlockType::vwall);
        mDungeonBlocks[j][xMin + width-1].setType(BlockType::vwall);
    }

    mDungeonBlocks[yMin][xMin].setType(BlockType::urwall);
    mDungeonBlocks[yMin][xMin + width-1].setType(BlockType::ulwall);
    mDungeonBlocks[yMin+height-1][xMin].setType(BlockType::drwall);
    mDungeonBlocks[yMin+height-1][xMin+width-1].setType(BlockType::dlwall);

    return Room(xMin, yMin, width, height);
}

void Dungeon::connectRooms(std::vector<Room> rooms){
    std::vector<Room> connected_rooms;

    while(!rooms.empty()){
        Room room = rooms.back();

        if(connected_rooms.empty()){
            connected_rooms.push_back(room);
            continue;
        }

        std::uniform_int_distribution<> roomRand(0, connected_rooms.size()-1);
        int roomIndex = roomRand(mRandomGenerator);
        const Room& connected_room = connected_rooms[roomIndex];

        if(connect2Rooms(room, connected_room)){
            connected_rooms.push_back(room);
            rooms.pop_back();
        }
    }
}

bool Dungeon::connect2Rooms(const Room& room1, const Room& room2){
    int x1 = room1.randomX(mRandomGenerator);
    int x2 = room2.randomX(mRandomGenerator);
    int y1 = room1.randomY(mRandomGenerator);
    int y2 = room2.randomY(mRandomGenerator);

    int xmin = x1 > x2 ? x2 : x1;
    int xmax = x1 > x2 ? x1 : x2;
    int ymin = y1 > y2 ? y2 : y1;
    int ymax = y1 > y2 ? y1 : y2;


    for(int i=xmin; i<=xmax; i++){
        if (   mDungeonBlocks[y1][i].getType()!=BlockType::ground
            && mDungeonBlocks[y1][i].getType()!=BlockType::corridor
            && mDungeonBlocks[y1][i].getType()!=BlockType::vwall
            && mDungeonBlocks[y1][i].getType()!=BlockType::none)
        {
            return false;
        }
    }

    for(int j=ymin; j<=ymax; j++){
        if (   mDungeonBlocks[j][x2].getType()!=BlockType::ground
            && mDungeonBlocks[j][x2].getType()!=BlockType::corridor
            && mDungeonBlocks[j][x2].getType()!=BlockType::hwall
            && mDungeonBlocks[j][x2].getType()!=BlockType::none)
        {
            return false;
        }
    }

    for(int i=xmin; i<=xmax; i++){
        if (mDungeonBlocks[y1][i].getType()!=BlockType::ground){
            if (mDungeonBlocks[y1][i].getType()==BlockType::vwall){
                mDungeonBlocks[y1][i].setType(BlockType::hdoor);
            }
            else if (mDungeonBlocks[y1][i].getType()==BlockType::none){
                mDungeonBlocks[y1][i].setType(BlockType::corridor);
            }
        }
    }

    for(int j=ymin; j<=ymax; j++){
        if (mDungeonBlocks[j][x2].getType()!=BlockType::ground){
            if (mDungeonBlocks[j][x2].getType()==BlockType::hwall){
                mDungeonBlocks[j][x2].setType(BlockType::vdoor);
            }
            else if (mDungeonBlocks[j][x2].getType()==BlockType::none){
                mDungeonBlocks[j][x2].setType(BlockType::corridor);
            }
        }
    }
    return true;
}

Block Dungeon::block(int x, int y) const{
    return mDungeonBlocks[y][x];
}

