#ifndef LEVELINFO_H_INCLUDED
#define LEVELINFO_H_INCLUDED

enum L_Type : int {
    L_Main = 0, L_Custom,
};

// информация об уровне (для записи в файл)
struct LevelInfo{
    char fileName[255];
    int movesCount;
    int pushBoxCount;
    int energy;
    int seconds;
    L_Type type;
    LevelInfo(){
        movesCount = pushBoxCount = energy = seconds = 0;
        type = L_Main;
        for (int i = 0; i < 255; i++)
            fileName[i] = '\0';
    }
    LevelInfo(char* _fileName, int _movesCount, int _pushBoxCount, int _energy, int _seconds, L_Type _type){
        for (int i = 0; i < 255; i++)
            fileName[i] = '\0';
        strcpy(fileName,_fileName);
        movesCount = _movesCount;
        pushBoxCount = _pushBoxCount;
        energy = _energy;
        seconds = _seconds;
        type = _type;
    }

    LevelInfo& operator=(const LevelInfo& right) {
        //проверка на самоприсваивание
        if (this == &right) {
            return *this;
        }
        movesCount = right.movesCount;
        pushBoxCount = right.pushBoxCount;
        energy = right.energy;
        seconds = right.seconds;
        type = right.type;
        strcpy(fileName, right.fileName);
        return *this;
    }
};

#endif // LEVELINFO_H_INCLUDED
