//
// Created by April on 8/25/2019.
//

#pragma once

struct Point {
    int x;
    int y;

    int idx(int width) const {
        return x + y * width;
    }
};

inline Point operator+(Point lhs, Point rhs) {
    return { lhs.x + rhs.x, lhs.y + rhs.y };
}

inline Point& operator+=(Point& lhs, Point rhs) {
    lhs = lhs + rhs;
    return lhs;
}

inline Point operator*(Point p, int scale) {
    return { p.x * scale, p.y * scale };
}

inline Point& operator*=(Point& p, int scale) {
    p = p * scale;
    return p;
}