#pragma once

#define SERIALIZE_START '{'
#define SERIALIZE_DELIMITER '_'
#define SERIALIZE_END '}'

enum lineDirection {
    undefined,
    north,
    north_east,
    east,
    south_east,
    south,
    south_west,
    west,
    north_west
};

struct /*class*/ positionABS {
    int X;
    int Y;
    void assign(const positionABS &pre) {
        X = pre.X;
        Y = pre.Y;
    }
    bool operator!=(const positionABS &pre) const { return ((X != pre.X) || (Y != pre.Y)) ? true : false; }
    positionABS operator+=(const lineDirection &pre) {
        if (pre == lineDirection::east) {
            X += 1;
        }
        if (pre == lineDirection::west && X > 1) {
            X -= 1;
        }
        if (pre == lineDirection::north) {
            Y += 1;
        }
        if (pre == lineDirection::south && Y > 1) {
            Y -= 1;
        }
        if (pre == lineDirection::north_east) {
            X += 1;
            Y += 1;
        }
        if (pre == lineDirection::south_west && X > 1 && Y > 1) {
            X -= 1;
            Y -= 1;
        }
        if (pre == lineDirection::south_east && Y > 1) {
            X += 1;
            Y -= 1;
        }
        if (pre == lineDirection::north_west && X > 1) {
            X -= 1;
            Y += 1;
        }
        return {X, Y};
    }
};

struct lineABS {
    positionABS line_start;
    positionABS line_end;
    lineDirection direction;
    // lineABS operator+=(const lineDirection &pre) { return {line_start, line_end, pre}; }
};
