#ifndef COMPLETELEVELINFO_H
#define COMPLETELEVELINFO_H

#include <SDL2/SDL.h>
#include "FilePaths.h"
#include "LevelInfo.h"

class CompleteLevelInfo
{
    public:
        CompleteLevelInfo();
        ~CompleteLevelInfo();

        static void AddRecord(LevelInfo info);
        static void DeleteRecord(char* levelPath, L_Type type);
        static bool HasLevelWithName (const char* levelName, L_Type type);
        static LevelInfo GetInfo(const char* levelName, L_Type type);
    private:
        static LevelInfo* arr;
        static int size;

        static bool loaded;
};

#endif // COMPLETELEVELINFO_H
