#include "CompleteLevelInfo.h"

LevelInfo* CompleteLevelInfo::arr = nullptr;
int CompleteLevelInfo::size = 0;

bool CompleteLevelInfo::loaded = false;

CompleteLevelInfo::CompleteLevelInfo()
{
    if (loaded) return;

    SDL_RWops *reader = SDL_RWFromFile(SaveLoad::LevelsInfo, "r+b");
    if (!reader)
    {
        SDL_RWFromFile(SaveLoad::LevelsInfo, "w+b");
        reader = SDL_RWFromFile(SaveLoad::LevelsInfo, "r+b");
    }
    size = SDL_RWsize(reader)/sizeof(LevelInfo);

    if (size){
        arr = new LevelInfo[size];
        SDL_RWread(reader,arr,size,sizeof(LevelInfo));
    }
    else arr = NULL;

    SDL_RWclose(reader);

    loaded = true;
}

void CompleteLevelInfo::DeleteRecord(char* levelName, L_Type type){
    if (!loaded) CompleteLevelInfo();

    int j = 0, s = -1;
    while (levelName[j] != '\0'){
        if (levelName[j] == '/') s = j;
        j++;
    }

    int deleteInd = size;
    for (int i = 0; i < size; i++){
        if (strcmp(arr[i].fileName, levelName + s + 1) == 0 && arr[i].type == type) {
            deleteInd = i;
            break;
        }
    }
    if (deleteInd == size) return;
    for (int i = deleteInd+1; i < size; i++){
        arr[i-1] = arr[i];
    }
    size--;
}

void CompleteLevelInfo::AddRecord(LevelInfo info){
    if (!loaded) CompleteLevelInfo();

    for (int i = 0; i < size; i++){ // если уроверь уже был пройден, обновляем рекорд
        if (strcmp(arr[i].fileName,info.fileName) == 0 && arr[i].type == info.type) {
            arr[i] = info;
            return;
        }
    }

    LevelInfo* tmp = new LevelInfo[size+1];
    for (int i = 0; i < size; i++){
        tmp[i] = arr[i];
    }
    tmp[size++] = info;
    if (arr) delete[]arr;
    arr = tmp;
}

LevelInfo CompleteLevelInfo::GetInfo(const char* levelName, L_Type type){
    if (!loaded) CompleteLevelInfo();

    for (int i = 0; i < size; i++){
        if (strcmp(arr[i].fileName, levelName) == 0 && arr[i].type == type) return arr[i];
    }
    return LevelInfo();
}

bool CompleteLevelInfo::HasLevelWithName(const char* levelName, L_Type type){
    if (!loaded) CompleteLevelInfo();

    for (int i = 0; i < size; i++){
        if (strcmp(arr[i].fileName, levelName) == 0 && arr[i].type == type) return true;
    }
    return false;
}

CompleteLevelInfo::~CompleteLevelInfo()
{
    if (!arr || !loaded) return;
    SDL_Log("CompleteLevelInfo dtor\t%x",this);

    SDL_RWops *writer = SDL_RWFromFile(SaveLoad::LevelsInfo, "w+b");
    SDL_RWwrite(writer, arr, size, sizeof(LevelInfo));
    SDL_RWclose(writer);

    loaded = false;
}
