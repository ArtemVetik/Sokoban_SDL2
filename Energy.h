#ifndef ENERGY_H_INCLUDED
#define ENERGY_H_INCLUDED

#include "Timer.h"

// Информация о энергии игрока
struct Energy{
public:
    Energy(int maxEnergy){
        this->maxEnergy = curEnergy = maxEnergy;
    };

    int GetEnergy() { return curEnergy; }
    bool CanSpend(int val){ return val <= curEnergy; }

    void Spend(int val) {
        if (curEnergy == maxEnergy) recoveryTime.Start(); // если энергия полная, запускаем таймер
        curEnergy -= val;
    }

    void Update(){ // каждую секунду значение энергии увеличивается
        if (recoveryTime.GetMilliseconds() >= 1000) {
            curEnergy++;
            recoveryTime.Reset();
            if (curEnergy < maxEnergy) recoveryTime.Start();
        }
    }

    private:
        int curEnergy, maxEnergy;
        Timer recoveryTime;
};

#endif // ENERGY_H_INCLUDED
