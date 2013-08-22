#ifndef GEOMETRY_H
#define GEOMETRY_H

//Cartesian point of type integer
struct PointCartInt {
    int x, y;
};

//Cartesian rectangle of type integer
//A is upper-left point, B is bottom-right
struct RectCartInt {
    struct PointCartInt A, B;
};

void init_rect(struct RectCartInt *rect);
int points_equal(struct PointCartInt A, struct PointCartInt B);
int point_in_rect(struct PointCartInt point, struct RectCartInt rect);
int rects_equal(struct RectCartInt R1, struct RectCartInt R2);
int rect_width(struct RectCartInt rect);
int rect_height(struct RectCartInt rect);
void print_rect(const struct RectCartInt rect, char buf[]);

#endif
