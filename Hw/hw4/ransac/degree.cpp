#include <iostream>
#include <cmath>
#include <eigen3/Eigen/Eigen>

double calculateAngleBetweenPlanes(const Eigen::Vector4d& plane1, const Eigen::Vector4d& plane2) {
    // Extracting the normal vectors from the plane parameters
    Eigen::Vector3d normal1(plane1(0), plane1(1), plane1(2));
    Eigen::Vector3d normal2(plane2(0), plane2(1), plane2(2));
    
    // Calculate the dot product
    double dotProduct = normal1.dot(normal2);
    
    // Calculate magnitudes
    double magnitude1 = normal1.norm();
    double magnitude2 = normal2.norm();
    
    // Calculate cosine of the angle
    double cosTheta = dotProduct / (magnitude1 * magnitude2);
    
    // Clamp the value to avoid numerical issues
    cosTheta = std::max(-1.0, std::min(1.0, cosTheta));
    
    // Calculate the angle in radians
    double angleRadians = std::acos(cosTheta);
    
    // Convert to degrees
    double angleDegrees = angleRadians * (180.0 / M_PI);
    
    return angleDegrees;
}

int main() {
    // Define two planes as Ax + By + Cz + D = 0
    // For testing pointcloud1
    //Eigen::Vector4d plane1(1, -1, -0.4, 1.0); 
    //Eigen::Vector4d plane2(0.454, -0.436, -0.23, -2.35);
    // For testing pointcloud2
    Eigen::Vector4d plane1(-0.4, 1.0, -0.4, 1.0); 
    Eigen::Vector4d plane2(-0.626, 2.18, -1, -2.35);

    // Calculate the angle between the two planes
    double angle = calculateAngleBetweenPlanes(plane1, plane2);

    // Output the angle
    std::cout << "Angle between the two planes: " << angle << " degrees" << std::endl;

    return 0;
}
