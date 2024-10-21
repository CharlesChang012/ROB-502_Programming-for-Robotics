#include <cmath>
#include <iomanip>
#include <iostream>
#include <fstream>

int main()
{
    double a, b, c;
    std::cout << "Type in a, b, and c. Press 'Enter' between each\n";
    std::cin >> a;
    std::cin >> b;
    std::cin >> c;
    std::cout << std::setprecision(4);
    // --- Your code here
    double x = b*b - 4*a*c;
	if(x < 0) std::cout << "None\n";
	else if(x == 0){
        if(b/(2*a) == 0) std::cout << 0 << "\n";
        else{
            std::cout << -b/(2*a) << "\n";
        }
    }
	else{
		double ans1 = std::min((-b+sqrt(x)) / (2*a), (-b-sqrt(x)) / (2*a));
		double ans2 = std::max((-b+sqrt(x)) / (2*a), (-b-sqrt(x)) / (2*a));
		std::cout << ans1 << "\n";
		std::cout << ans2 << "\n";
	}

    // ---
    return 0;
}
