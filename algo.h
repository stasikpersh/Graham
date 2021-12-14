#pragma once
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <stack>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include<fstream>
#include<sstream>


struct Point {
    int x;
    int y;
public:

    Point() {
        x = 0;
        y = 0;
    }

    Point(int x, int y) {
        this->x = x;
        this->y = y;
    }

    int GetX() {
        return x;
    }

    int GetY() {
        return y;
    }

    void SetPoint(Point& pt) {
        x = pt.GetX();
        y = pt.GetY();
    }
};

Point current;

Point NextToTop(std::stack<Point>& S) {
    Point point = S.top();
    S.pop();
    Point next = S.top();
    S.push(point);
    return next;
}

int Angle(Point current, Point p1, Point p2) {
    int ang = (p1.y - current.y) * (p2.x - p1.x) - (p1.x - current.x) * (p2.y - p1.y);
    if (ang == 0) { return 0; }
    else if (ang > 0) return 1;
    else return -1;
}

void Tr(Point& p1, Point& p2) {
    Point p_time = p1;
    p1 = p2;
    p2 = p_time;
}

int Dist(Point p1, Point p2) {
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

bool Compare(const Point& p1, const Point& p2) {

    if (Angle(current, p1, p2) == 0) {
        return (Dist(current, p1) < Dist(current, p2));
    }

    return (Angle(current, p1, p2) == -1);
}

struct Graham {
public:
    void BuildVector(std::vector<Point> list) {
        data = list;
        count = list.size();
    }

    void AddPoint(int x, int y) {
        data.push_back(Point(x, y));
        count++;
    }

    void QuickHull() {

        if (count < 3) {
            throw - 1;
        }

        int current_index = FindCurrent();
        Tr(data[0], data[current_index]);
        current = data[0];
        sort(data.begin() + 1, data.end(), Compare);
        int iter = 1;

        for (int i = 1; i < count; i++) {
            while (i < count - 1 && Angle(current, data[i], data[i + 1]) == 0) {
                i++;
            }
            data[iter] = data[i];
            iter++;
        }

        if (iter < 3) {
            throw - 1;
        }

        S.push(data[0]);
        S.push(data[1]);
        S.push(data[2]);

        for (int i = S.size(); i < iter; i++) {

            while (S.size() > 1 && Angle(NextToTop(S), S.top(), data[i]) != -1) {
                S.pop();
            }

            S.push(data[i]);
        }

        std::vector<Point> result;

        while (S.size() > 0) {
            result.push_back(S.top());
            S.pop();
        }

        for (int i = 0; i < result.size() / 2; i++) {
            auto index_t = result[i];
            result[i] = result[result.size() - 1 - i];
            result[result.size() - 1 - i] = index_t;
        }

        for (int i = result.size() - 1; i >= 0; i--) {
            S.push(result[i]);
        }
    }

    void HeapHull() {

        if (count < 3) {
            throw - 1;
        }

        int current_index = FindCurrent();
        Tr(data[0], data[current_index]);
        current = data[0];
        HeapSort(data);

        int iter = 1;
        for (int i = 1; i < count; i++) {
            while (i < count - 1 && Angle(current, data[i], data[i + 1]) == 0) {
                i++;
            }
            data[iter] = data[i];
            iter++;
        }

        if (iter < 3) {
            throw - 1;
        }

        S.push(data[0]);
        S.push(data[1]);
        S.push(data[2]);

        for (int i = S.size(); i < iter; i++) {
            while (S.size() > 1 && Angle(NextToTop(S), S.top(), data[i]) != -1) {
                S.pop();
            }

            S.push(data[i]);
        }

        std::vector<Point> result;
        while (S.size() > 0) {
            result.push_back(S.top());
            S.pop();
        }

        for (int i = 0; i < result.size() / 2; i++) {
            auto index_t = result[i];
            result[i] = result[result.size() - 1 - i];
            result[result.size() - 1 - i] = index_t;
        }

        for (int i = result.size() - 1; i >=0; i--) {
            S.push(result[i]);
        }
    }

    void HeapHullPrint() {
        HeapHull();
        PrintStack();
    }
    void QuickHullPrint() {
        QuickHull();
        PrintStack();
    }

    void PrintStack() {
        while (!S.empty()) {
            Point p = S.top();
            std::cout << "(" << p.x << ", " << p.y << ")" << std::endl;
            S.pop();
        }
    }

private:
    int count = 0;
    std::vector<Point> data;
    std::stack<Point> S;
    int FindCurrent() {
        int index = 0;
        int min_x = data[0].x;
        int min_y = data[0].y;
        for (int i = 1; i < count; i++) {
            if ((data[i].y < min_y) || (min_y == data[i].y && data[i].x < min_x)) {
                min_x = data[i].x;
                min_y = data[i].y;
                index = i;
            }
        }
        return index;
    }

    void HeapSort(std::vector<Point>& data_sort) {
        for (int i = data_sort.size() / 3 - 1; i >= 0; i--) {
            Up(data_sort, data_sort.size(), i);
        }

        for (int i = data_sort.size() - 1; i >= 0; i--) {
            Tr(data_sort[0], data_sort[i]);
            Up(data_sort, i, 0);
        }

        int size = data_sort.size();

        for (int i = 0; i < size / 2; ++i) {
            Tr(data_sort[i], data_sort[size - i - 1]);
        }
    }

    void Up(std::vector<Point>& data_sort, int size, int i) {
        int parent = i;
        int first_child = i * 3 + 1;
        int last_child = std::min((i + 1) * 3, size - 1);

        for (int j = first_child; j <= last_child; j++) {
            if (Compare(data_sort[j], data_sort[parent])) {
                parent = j;
            }
        }

        if (i != parent) {
            Tr(data_sort[i], data_sort[parent]);
            Up(data_sort, size, parent);
        }
    }
};

