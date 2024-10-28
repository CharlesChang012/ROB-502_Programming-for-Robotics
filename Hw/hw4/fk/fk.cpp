#include <fstream>
#include <iomanip>
#include <iostream>
#include <eigen3/Eigen/Eigen>

Eigen::Matrix3d transform_mat(double q, double l)
{
    // --- Your code here
    Eigen::Matrix3d T;
    T << cos(q), -sin(q), l * cos(q),
         sin(q),  cos(q), l * sin(q),
              0,       0,          1;

    return T;
    // ---
}

int main(int argc, char* argv[])
{
    // by defult, use the file joint_angles.txt, but if you supply a command line argument, use that instead
    std::string input_filename{"joint_angles.txt"};
    if (argc >= 2) {
        input_filename = argv[1];
    }
    std::ifstream ifs(input_filename);

    if (!ifs.good()) {
        std::cerr << "Failed to open file " << input_filename << std::endl;
        return 0;
    }

    double l1{1.0};
    double l2{0.5};
    double l3{0.25};

    while (ifs.peek() != -1)
    {
        double q1, q2, q3;
        ifs >> q1 >> q2 >> q3;

        // --- Your code here
        Eigen::Matrix3d T_total = transform_mat(q1, l1) * transform_mat(q2, l2) * transform_mat(q3, l3);

        std::cout << std::setprecision(3) << T_total.row(0).col(2) << std::endl;
        std::cout << std::setprecision(3) << T_total.row(1).col(2) << std::endl;
        // ---
    }
}