#include <random>
#include <iomanip>
#include <iostream>
#include <eigen3/Eigen/Eigen>
#include <vector>

struct Plane
{
    double a;
    double b;
    double c;
    double d;
};

struct FitResult
{
    Plane plane;
    int n_inliers = -1;
};

void pretty_print(std::string const &input_filename, Plane const &plane)
{
    std::cout << std::setprecision(3) << "--infile " << input_filename << " -a " << plane.a << " -b " << plane.b << " -c " << plane.c << " -d " << plane.d << '\n';
}

std::ostream &operator<<(std::ostream &os, Plane const &plane)
{
    os << std::setprecision(3) << plane.a << " " << plane.b << " " << plane.c << " " << plane.d;
    return os;
}

Plane compute_plane_from_points(Eigen::Vector3d const &p0,Eigen::Vector3d const &p1,Eigen::Vector3d const &p2)
{
    // 1. given p0, p1, and p2 form two vectors v1 and v2 which lie on the plane
    // 2. use v1 and v2 to find the normal vector of the plane `n`
    // 3. set a,b,c from the normal vector `n`
    // 4. set `d = -n.dot(p0)`
    // --- Your code here
	Eigen::Vector3d v1 = p1 - p0;
	Eigen::Vector3d v2 = p2 - p0;
	
	Eigen::Vector3d n = {
        v1[1] * v2[2] - v1[2] * v2[1],
        v1[2] * v2[0] - v1[0] * v2[2],
        v1[0] * v2[1] - v1[1] * v2[0]
    };

    Plane p;
    p.a = n[0];
    p.b = n[1];
    p.c = n[2];
    p.d = -n.dot(p0);

    return p;
    // ---
}

class BaseFitter
{
public:
    BaseFitter(int num_points) : mt(rd()), dist(0, num_points - 1)
    {
        mt.seed(0);
    }

    /**
     * Given all of the data `points`, select a random subset and fit a plane to that subset.
     * the parameter points is all of the points
     * the return value is the FitResult which contains the parameters of the plane (a,b,c,d) and the number of inliers
     */
    virtual FitResult fit(Eigen::MatrixXd const &points) = 0;

    int get_random_point_idx()
    {
        return dist(mt);
    };

    double const inlier_threshold_{0.025};   // default: 0.02

private:
    // These are for generating random indices, you don't need to know how they work.
    // Just use `get_random_point_idx()` and `points.row(rand_idx)`
    std::random_device rd;
    std::mt19937 mt;
    std::uniform_int_distribution<int> dist;
};

class AnalyticFitter : public BaseFitter
{
public:
    AnalyticFitter(int num_points) : BaseFitter(num_points) {}

    // by writing `override`, the compiler will check that this function actually overrides something 
    // in the base class. Always use this to prevent mistakes in the function signature!
    FitResult fit(Eigen::MatrixXd const &points) override
    {
        // 1. select 3 points from `points` randomly 
        // 2. compute the equation of the plane (HINT: use compute_plane_from_points)
        // 3. compute the `n_inliers` given that plane equation
        // (HINT: multiply the points matrix by the normal vector)
        // --- Your code here
        // 1. Select 3 random points
        std::vector<int> randNums;
        Eigen::MatrixXd randPoints(3, 3);

        // Randomly select unique numbers
        while (randNums.size() < 3) {
            int randNum = get_random_point_idx();
            if(find(randNums.begin(), randNums.end(), randNum) == randNums.end()){
                randNums.push_back(randNum);
            }           
        }

        // Get corresponding random points
        for(size_t i = 0; i < randNums.size(); i++){
            randPoints.row(i) = points.row(randNums[i]);
        }

        // 2. Compute equation of the plane
        Plane analytic_plane = compute_plane_from_points(randPoints.row(0), randPoints.row(1), randPoints.row(2));

        // 3. Compute 'n_inliers' given that plane
        Eigen::Vector3d normal = {analytic_plane.a, analytic_plane.b, analytic_plane.c};
        Eigen::VectorXd numerator = (points * normal).array() + analytic_plane.d;
        Eigen::VectorXd distances = (numerator.array().abs() / normal.norm()).matrix();

        int n_inliers = (distances.array() < inlier_threshold_).count();
        // ---

        return {analytic_plane, n_inliers};
    }
};

class LeastSquaresFitter : public BaseFitter
{
public:
    LeastSquaresFitter(int num_points, int n_sample_points) : BaseFitter(num_points), n_sample_points_(n_sample_points) {}

    // You should override the `fit` method here
    // --- Your code here
    FitResult fit(Eigen::MatrixXd const &points) override{
        // 1. Select 10 random points
        std::vector<int> randNums;
        Eigen::MatrixXd randPoints(n_sample_points_, 3);

        // Randomly select unique numbers and Get corresponding random points
        for (int i = 0; i < n_sample_points_; i++) {
            int randNum = get_random_point_idx();
            randPoints.row(i) = points.row(randNum);       
        }

        // 2. Compute equation of the plane
        // Solve for ax + by - z + d = 0
        // that is ax + by + d = z

        // create the A matrix from points
        Eigen::MatrixXd A(n_sample_points_, 3);
        A = randPoints.block(0, 0, n_sample_points_, 2).rowwise().homogeneous();

        // create the b matrix from points
        Eigen::VectorXd b = randPoints.col(2);

        // solve for x
        Eigen::VectorXd x = A.colPivHouseholderQr().solve(b);
        Plane analytic_plane = {x(0), x(1), -1, x(2)};

        // 3. Compute 'n_inliers' given that plane
        Eigen::Vector3d normal = {analytic_plane.a, analytic_plane.b, analytic_plane.c};
        Eigen::VectorXd numerator = (points * normal).array() + analytic_plane.d;
        Eigen::VectorXd distances = (numerator.array().abs() / normal.norm()).matrix();

        int n_inliers = (distances.array() < inlier_threshold_).count();

        return {analytic_plane, n_inliers};
    }


    // ---

    int const n_sample_points_;
};

Plane ransac(BaseFitter &fitter, Eigen::MatrixXd const &points)
{
    // --- Your code here
    FitResult best_result;

    for(size_t i = 0; i < 150; i++){
        FitResult fitRes = fitter.fit(points);
        if(fitRes.n_inliers > best_result.n_inliers) best_result = fitRes;
    }
    // ---

    // HINT: the number of inliers should be between 20 and 80 if you did everything correctly
    std::cout << best_result.n_inliers << std::endl;
    return best_result.plane;
}
