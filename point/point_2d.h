//
// Created by guy on 10/21/18.
//

#ifndef INC_3D_PAINT_POINT_2D_H
#define INC_3D_PAINT_POINT_2D_H


class point_2d {
public:
    int x;
    int y;
    point_2d(int new_x,int new_y){x=new_x;y=new_y;}
    point_2d& operator =(const point_2d a)
    {
        x=a.x;
        y=a.y;
        return *this;
    }
};


#endif //INC_3D_PAINT_POINT_2D_H
