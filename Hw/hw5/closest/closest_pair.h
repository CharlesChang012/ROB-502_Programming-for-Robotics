#include <vector>
#include <math.h>
#include <algorithm>

struct Point {
    int id;
    double x, y;
};

double dist(const Point& p1, const Point& p2) {
    auto dx = p1.x - p2.x;
    auto dy = p1.y - p2.y;
    return std::sqrt(dx*dx + dy*dy);
}


// --- Your code here
std::pair<Point, Point> closest_pair_recursion(const std::vector<Point>& points, int l, int r){

    // base case
    if(r - l <= 3){
        double min_dist = std::numeric_limits<double>::max();
        std::pair<Point, Point> min_pair;

        for(int i = l; i < r; i++){
            for(int j = i+1; j < r; j++){
                double distance = dist(points[i], points[j]);

                if(distance < min_dist){
                    min_dist = distance;
                    if(points[i].id < points[j].id) min_pair = std::make_pair(points[i], points[j]);
                    else min_pair = std::make_pair(points[j], points[i]);
                }
            }
        }
        return min_pair;
    }
    

    int mid = l + (r-l)/2; 
    Point mid_p = points[mid];

    std::pair<Point, Point> l_pair = closest_pair_recursion(points, l, mid);
    std::pair<Point, Point> r_pair = closest_pair_recursion(points, mid, r);

    double l_dist = dist(l_pair.first, l_pair.second);
    double r_dist = dist(r_pair.first, r_pair.second);

    std::pair<Point, Point> min_pair = (l_dist < r_dist) ? l_pair : r_pair;

    double min_dist = std::min(l_dist, r_dist);

    std::vector<Point> mid_close;
    for(int i = l; i < r; i++){
        if(std::abs(points[i].x - mid_p.x) < min_dist) mid_close.push_back(points[i]);
    }

    std::sort(mid_close.begin(), mid_close.end(), [](const Point& p1, const Point& p2){return p1.y < p2.y;});

    for(int i = 0; i < mid_close.size(); i++){
        for(int j = i+1; j < mid_close.size() && (mid_close[j].y - mid_close[i].y) < min_dist; j++){
            double distance = dist(mid_close[i], mid_close[j]);
            if(distance < min_dist){
                min_dist = distance;
                if(mid_close[i].id < mid_close[j].id) min_pair = std::make_pair(mid_close[i], mid_close[j]);
                else min_pair = std::make_pair(mid_close[j], mid_close[i]);
            }
        }
    }

    return min_pair;
}


// ---

std::pair<Point, Point> closest_pair(const std::vector<Point>& points) {
    // --- Your code here
    std::vector<Point> sorted_points = points;

    sort(sorted_points.begin(), sorted_points.end(), [](const Point& p1, const Point& p2){return p1.x < p2.x;});


    return closest_pair_recursion(sorted_points, 0, points.size());
    // ---
}