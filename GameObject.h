#ifndef GAMEOBJECT_H_INCLUDED
#define GAMEOBJECT_H_INCLUDED

#include <iostream>

enum GameObject : char{
    EmptyCh = ' ', // пустая клетка
    WallCh = '*', // стена
    BoxCh1 = '1', // ящик с весом 1
    BoxCh2 = '2', // ящик с весом 2
    BoxCh3 = '3', // ящик с весом 3
    PlayerCh = 'p', // игрок
    TargetCh = 'x', // место для ящика
    Box1OnTarget = 'a', // ящик с весом 1, стоящий на месте для ящика
    Box2OnTarget = 'b', // ящик с весом 2, стоящий на месте для ящика
    Box3OnTarget = 'c', // ящик с весом 3, стоящий на месте для ящика
    PlayerOnTarget = 'P', // игрок на месте для ящика
};

// класс-помощник для перечисления GameObject
class GOHelper{
    public:
        // Проверка на то, что символ является ящикои
        static bool IsBox(char sym){
            return sym >= BoxCh1 && sym <= BoxCh3 || sym >= Box1OnTarget && sym <= Box3OnTarget;
        }
        // Проверка на то, что символ является игроком
        static bool IsPlayer(GameObject sym){
            return sym == PlayerCh || sym == PlayerOnTarget;
        }
        // Проверка на то, что на текущем объекте можно стоять
        static bool CanStay(GameObject sym){
            return sym == EmptyCh || sym == TargetCh;
        }
        // Проверка на то, что символ является метом для ящиков
        static bool IsTarget(GameObject sym){
            return sym == TargetCh || sym >= Box1OnTarget && sym <= Box3OnTarget || sym == PlayerOnTarget;
        }

        // (очень помог)
        // перестановка игровых объектов по правилам (при движении игрока и\или смещении ящиков)
        static void Displace(GameObject *first, GameObject *second, GameObject *third){
            if (!IsPlayer(*first)) return;

            if (IsBox(*second)){
                if (IsTarget(*third) && IsTarget(*second)) { *third = *second; *second = TargetCh; }
                else if (IsTarget(*third) && !IsTarget(*second)) { *third = (GameObject)(Box1OnTarget + *second - BoxCh1); *second = EmptyCh; }
                else if (!IsTarget(*third) && IsTarget(*second)) { *third = (GameObject)(BoxCh1 + *second - Box1OnTarget); *second = TargetCh; }
                else if (!IsTarget(*third) && !IsTarget(*second)) { *third = *second; *second = EmptyCh; }
            }
            if (CanStay(*second)){
                if (IsTarget(*second) && IsTarget(*first)) { *second = *first; *first = TargetCh; }
                else if (IsTarget(*second) && !IsTarget(*first)) { *second = PlayerOnTarget; *first = EmptyCh; }
                else if (!IsTarget(*second) && IsTarget(*first)) { *second = PlayerCh; *first = TargetCh; }
                else if (!IsTarget(*second) && !IsTarget(*first)) {*second = *first; *first = EmptyCh;}
            }
        }

        // получение веса ящика
        static int GetBoxWeight(GameObject sym){
            if (sym == BoxCh1 || sym == Box1OnTarget) return 1;
            if (sym == BoxCh2 || sym == Box2OnTarget) return 2;
            if (sym == BoxCh3 || sym == Box3OnTarget) return 3;
            return 0;
        }
};

#endif // GAMEOBJECT_H_INCLUDED
