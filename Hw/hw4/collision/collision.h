#include <eigen3/Eigen/Eigen>
#include <fstream>
#include <iostream>
#include <vector>

using Edge = std::pair<Eigen::Vector2d, Eigen::Vector2d>;

// returns true if the equation a*t^2+b*t+c=0 has a solution between 0 and 1 (inclusive)
// HINT: recall your solution to `quadratic` in HW1 
bool quadratic_has_valid_solution(double const a, double const b,  double const c) {
    // --- Your code here
    double x = b*b - 4*a*c;
	if(x < 0) return false;
	else if(x == 0){
        if(0 <= -b/(2*a) && -b/(2*a) <= 1 ){
            return true;
        }
        else return false;
    }
	else{
		double ans1 = std::min((-b+sqrt(x)) / (2*a), (-b-sqrt(x)) / (2*a));
		double ans2 = std::max((-b+sqrt(x)) / (2*a), (-b-sqrt(x)) / (2*a));
		if((0 <= ans1 && ans1 <= 1) || (0 <= ans2 && ans2 <= 1)) return true;
        else return false;
	}
    // ---
}

class Disc; // forward-declare the type Disc, otherwise we can't use it in the Obstacle base class

class Obstacle
{
public:
    // returns true if the robot is collides with the obstacle
    virtual bool check_collision(Disc const &robot) const = 0;

    // returns true if whether the point p is within this disc
    virtual bool contains(Eigen::Vector2d const &p) const = 0;
};

class Disc : public Obstacle
{
public:
    Disc(double x, double y, double radius) : pos_(x, y), radius_(radius) {}

    // override check_collision (HINT: use the `norm` function!)
    bool check_collision(Disc const &robot) const override
    {
        // --- Your code here
        Eigen::Vector2d delta = this->pos_ - robot.pos_;
        if(delta.norm() <= this->radius_ + robot.radius_){
            return true;
        }  
        else return false;
        // ---
    }

    // returns true if the point p is within this disc
    bool contains(Eigen::Vector2d const &p) const override
    {
        // --- Your code here
        Eigen::Vector2d delta = this->pos_ - p;
        if(delta.norm() <= this->radius_){
            return true;
        }  
        else return false;
        // ---
    }


    Eigen::Vector2d pos_;
    double radius_;
};
class Rectangle : public Obstacle
{
public:
    Rectangle(double x1, double y1, double x2, double y2) : bottom_left_(x1, y1), top_right_(x2, y2),
                                                            edges_{{{x1, y1}, {x2, y1}}, {{x2, y1}, {x2, y2}}, {{x2, y2}, {x1, y2}}, {{x1, y2}, {x1, y1}}},
                                                            corners_{{x1, y1}, {x2, y1}, {x2,y2}, {x1,y2}}
    {
    }

    // override check_collision
    // HINT: use the `Rectangle::check_intersection_with_edge`, `Rectangle::contains`, and `Disc::contains` functions
    // --- Your code here
    bool check_collision(Disc const &robot) const override
    {
        if(this->contains(robot.pos_)) return true;
        
        for(auto const& corner : this->corners_){
            if(robot.contains(corner)) return true;
        }

        for(auto const& e : this->edges_){
            if(check_intersection_with_edge(e, robot)) return true;
        }

        return false;
    }
    // ---

    // Override the `contains` function
    // --- Your code here
    bool contains(Eigen::Vector2d const &p) const override
    {
        double min_x = this->bottom_left_(0);
        double min_y = this->bottom_left_(1);
        double max_x = this->top_right_(0);
        double max_y = this->top_right_(1);

        if(min_x <= p(0) && p(0) <= max_x && min_y <= p(1) && p(1) <= max_y){
            return true;        
        }  
        else return false;
    }
    // ---

    // (HINT: use the `quadratic_has_valid_solution` function)
    bool check_intersection_with_edge(Edge const &e, Disc const& disc) const
    {
        // --- Your code here
        // Solve for d.dot(d) t^2 + (2f.dot(d) t + (f.dot(f) - r^2) = 0
        Eigen::Vector2d d = e.first - e.second;
        Eigen::Vector2d f = e.second - disc.pos_;

        double a = d.dot(d);
        double b = 2 * f.dot(d);
        double c = f.dot(f) - disc.radius_*disc.radius_;

        if(quadratic_has_valid_solution(a, b, c)){
            return true;
        }
        else return false;
        // ---
    }

    Eigen::Vector2d bottom_left_;
    Eigen::Vector2d top_right_;
    std::vector<Edge> edges_;
    std::vector<Eigen::Vector2d> corners_;
};

bool check_collisions(std::vector<Obstacle const *> const &obstacles, Disc const &robot)
{
    // --- Your code here
    for(auto const obstacle : obstacles){
        if(obstacle->check_collision(robot)) return true;
    }

    return false;
    // ---
}