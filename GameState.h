#ifndef GAMESTATE_H
#define GAMESTATE_H

// состояния игры
class GameState{
    public:

        enum States{
            MainMenuStatus, // главное меню
            ChoiseLevelStatus, // выбор уровня
            ChoiseCustomLevels, // выбор кастомного уровня
            PlayState, // игра
            RepeatState, // повторение текущей игры
            InfoStatus, // окно информации
            LevelCompleteState, // окончание уровня (окно статистики)
            PrevMoveState,// отмена хода
            NextLevelState, // переход на следующий уровень
            ExceptionState, // окно ошибки
            MapCreatorState, // создание карты
            ExitStatus, // выход
        };

        static States curState; // текущее состояние
};

#endif // GAMESTATE_H
