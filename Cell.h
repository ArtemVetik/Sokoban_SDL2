#ifndef CELL_H
#define CELL_H


class Cell
{
    public:
        Cell();
        Cell(int x, int y);
        ~Cell();

        int X(){return x;}
        int Y(){return y;}

        Cell Left(int offcet = 1){ return Cell(x-offcet,y);}
        Cell Right(int offcet = 1){ return Cell(x+offcet,y);}
        Cell Up(int offcet = 1){ return Cell(x,y-offcet);}
        Cell Down(int offcet = 1){ return Cell(x,y+offcet);}

        Cell& operator =(const Cell& obj){
            this->x = obj.x;
            this->y = obj.y;
        }

    private:
        int x,y;
};

#endif // CELL_H
