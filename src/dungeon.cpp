#include "dungeon.h"

#include "block.h"
#include "renderer.h"

#include <vector>
#include <random>

#include <SDL2/SDL.h>

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
            SDL_Rect rect;
            rect.x = i * BLOCK_WIDTH;
            rect.y = j * BLOCK_HEIGHT;
            rect.w = BLOCK_WIDTH;
            rect.h = BLOCK_HEIGHT;

            BlockType type = block(i,j);

            if(wall == type){
                renderer.fillRect(rect,BLACK);
            }
            if(ground == type){
                renderer.fillRect(rect,GREY);
            }
        }
    }
}


void Dungeon::generateRandomDungeon(){
    initialize();
    generateRooms();
}

void Dungeon::initialize(){
    mDungeonBlocks = new BlockType*[mHeight];
    for(int j = 0; j < mHeight; j++){
        mDungeonBlocks[j] = new BlockType[mWidth];
        for(int i = 0; i < mWidth; i++){
            mDungeonBlocks[j][i]=BlockType::wall;
        }
    }
}

void Dungeon::reset(){
    this->~Dungeon();
    generateRandomDungeon();
}

std::vector<Room> Dungeon::generateRooms(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> roomSizeRand(MIN_ROOM_COUNT, MAX_ROOM_COUNT);

    int nRooms = roomSizeRand(gen);
    std::vector<Room> rooms(static_cast<unsigned long>(nRooms));

    for(int i = 0 ; i < nRooms; i++){
        Room room = generateRoom();
        rooms.emplace_back(room);
    }
    return rooms;
}

Room Dungeon::generateRoom(){
    std::random_device rd;
    std::mt19937 gen(rd());

    bool isEmpty = true;
    int yMin =0, xMin =0, width =0, height =0;
    do{
        isEmpty = true;
        std::uniform_int_distribution<> roomSizeRand(MIN_ROOM_SIZE, MAX_ROOM_SIZE);

        width = roomSizeRand(gen);
        height = roomSizeRand(gen);
        int xMax = static_cast<int>(mWidth) - width - 1;
        int yMax = static_cast<int>(mHeight) - height - 1;

        std::uniform_int_distribution<> topRand(1, yMax);
        std::uniform_int_distribution<> leftRand(1, xMax);
        yMin = topRand(gen);
        xMin = leftRand(gen);

        for(int j = yMin-1; j < yMin + height + 1; j++){
            for(int i=xMin-1; i < xMin + width + 1; i++){
                if(block(i,j) == BlockType::ground){
                    isEmpty = false;
                }
            }
        }
    } while( !isEmpty );

    for(int i = xMin; i < xMin + width; i++){
        for(int j=yMin; j < yMin + height; j++){
            mDungeonBlocks[j][i] = BlockType::ground;
        }
    }

    return Room(xMin, yMin, width, height);
}

BlockType Dungeon::block(int x, int y) const{
    return mDungeonBlocks[y][x];
}

