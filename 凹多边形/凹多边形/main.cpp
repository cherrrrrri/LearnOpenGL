#include <iostream>
#include <vector>
using namespace std;

struct Point {
    double x;
    double y;
};

// 计算向量叉积
double crossProduct(const Point& A, const Point& B, const Point& C) {
    double ABx = B.x - A.x;
    double ABy = B.y - A.y;
    double BCx = C.x - B.x;
    double BCy = C.y - B.y;
    return ABx * BCy - ABy * BCx;
}

bool isConvexPolygon(const vector<Point>& vertices) {
    int n = vertices.size();
    if (n < 3) {
        return false;  // 一个多边形至少有三个顶点才能是凸多边形
    }

    double prevCrossProduct = 0;
    for (int i = 0; i < n; i++) {
        const Point& A = vertices[i];
        const Point& B = vertices[(i + 1) % n];  // 循环到第一个顶点，形成闭合多边形
        const Point& C = vertices[(i + 2) % n];

        double currentCrossProduct = crossProduct(A, B, C);

        if (i == 0) {
            prevCrossProduct = currentCrossProduct;
        }
        else {
            if (prevCrossProduct * currentCrossProduct < 0) {
                return false;  // 叉积方向不一致，不是凸多边形
            }
        }
    }

    return true;
}

int main() {
    // 例子1：凸多边形
    vector<Point> polygon1 = { {0, 0}, {1, 1}, {2, 0}, {1, -1} };
    bool isConvex1 = isConvexPolygon(polygon1);
    cout << "Polygon 1 is convex: " << (isConvex1 ? "true" : "false") << endl;

    // 例子2：非凸多边形
    vector<Point> polygon2 = { {0, 0}, {1, 1}, {2, 0}, {1, -1}, {0.5, 0.5} };
    bool isConvex2 = isConvexPolygon(polygon2);
    cout << "Polygon 2 is convex: " << (isConvex2 ? "true" : "false") << std::endl;

    return 0;
}
