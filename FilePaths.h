#ifndef FILEPATHS_H_INCLUDED
#define FILEPATHS_H_INCLUDED

// ----------------------- Игровые объекты ---------------
namespace GameObjectsPath{
    char* const WallImage = "Images/brick.bmp";
    char* const TargetImage = "Images/target.bmp";
    char* const Box1Image = "Images/box1.bmp";
    char* const Box2Image = "Images/box2.bmp";
    char* const Box3Image = "Images/box3.bmp";
    char* const StoneGroundImage = "Images/stoneGround.bmp";
    char* const SandGroundImage = "Images/sandGround.bmp";
    char* const PlayerImage = "Images/playerImage.bmp";
};

// ----------------------- Полотна анимации ---------------
namespace SpriteSheetPaths{
    namespace Player{
        char* const RightSide = "Images/playerRight.bmp";
        char* const LeftSide = "Images/playerLeft.bmp";
        char* const FaceSide = "Images/playerFace.bmp";
        char* const BackSide = "Images/playerBack.bmp";
    };
    char* const Clock = "Images/clockSheet.bmp";
};

// ----------------------- Шрифты -----------------
namespace FontsPath{
    char* const ClearSansThinFont = "Fonts/ClearSansThin.ttf";
    char* const FreeMonoFont = "Fonts/FreeMono.ttf";
    char* const SerifGothicBold = "Fonts/SerigGothicBold.ttf";
};

// ---------------------- UI --------------------
namespace UIPaths{
    namespace StatusBar{
        char* const Back = "Images/backStatusBar.bmp";
        char* const Filled = "Images/filledStatusBar.bmp";
        char* const LightingImage = "Images/lightning.bmp";
    };
    namespace Scrollbar{
        char* const Back = "Images/fullbar.bmp";
        char* const Slider = "Images/slider.bmp";
    }
    namespace Background{
        char* const SandBackground = "Images/sandBackground.bmp";
        char* const MainBackgound = "Images/mainBackgound.bmp";
    };
    namespace Buttons{
        namespace Round{
            char* const Normal = "Images/normalRoundButton.bmp";
            char* const Pressed = "Images/pressedRoundButton.bmp";
            char* const Highlited = "Images/highlitedRoundButton.bmp";
        };
        namespace Square{
            char* const Normal = "Images/normalSquareButton.bmp";
            char* const Pressed = "Images/pressedSquareButton.bmp";
            char* const Highlited = "Images/highlitedSquareButton.bmp";
        };
        namespace SquareDialog{
            char* const Normal = "Images/backDialogButtonNormal.bmp";
            char* const Pressed = "Images/backDialogButtonPressed.bmp";
            //char* const Highlited = "Images/highlitedDialogButtonNormal.bmp";
        };
        namespace Home{
            char* const Normal = "Images/homeNormal.bmp";
            char* const Pressed = "Images/homePressed.bmp";
            char* const Highlited = "Images/homeHighlited.bmp";
        };
        namespace Back{
            char* const Normal = "Images/backNormal.bmp";
            char* const Pressed = "Images/backPressed.bmp";
            char* const Highlited = "Images/backHighlited.bmp";
        };
        namespace Prev{
            char* const Normal = "Images/prevRoundNormal.bmp";
            char* const Pressed = "Images/prevRoundPressed.bmp";
            char* const Highlited = "Images/prevRoundHighlited.bmp";
        };
        namespace Repeat{
            char* const Normal = "Images/repeatlNormal.bmp";
            char* const Pressed = "Images/repeatlPressed.bmp";
            char* const Highlited = "Images/repeatHighlited.bmp";
        };
        namespace Next{
            char* const Normal = "Images/nextNormal.bmp";
            char* const Pressed = "Images/nextPressed.bmp";
            char* const Highlited = "Images/nextHighlited.bmp";
        };
        namespace NextRound{
            char* const Normal = "Images/nextRoundNormal.bmp";
            char* const Pressed = "Images/nextRoundPressed.bmp";
            char* const Highlited = "Images/nextRoundHighlited.bmp";
        }
        namespace Save{
            char* const Normal = "Images/saveNormal.bmp";
            char* const Pressed = "Images/savePressed.bmp";
            char* const Highlited = "Images/saveHighlited.bmp";
            char* const Icon = "Images/saveIcon.bmp";
        };
    };
    namespace Panel{
        char* const InfoPanel = "Images/infoTable.bmp";
        char* const ResultPanel = "Images/resPanel.bmp";
        char* const ToolsPanel = "Images/toolsPanel.bmp";
    };
    namespace Images{
        char* const SquareFrame = "Images/squareFrame.bmp";
        char* const GarbageImage = "Images/garbageImage.bmp";
    }
};

namespace SaveLoad{
    char* const LevelsInfo = "Config/levelsInfo.bin";
};

#endif // FILEPATHS_H_INCLUDED
