//
// Created by Brad on 8/25/2019.
//

#pragma once

struct Point {
    int x;
    int y;

    int idx(int width) const {
        return x + y * width;
    }

    Point operator+(Point rhs) const {
        return { x + rhs.x, y + rhs.y };
    }

    Point operator*(int scale) const {
        return { x * scale, y * scale };
    }
};