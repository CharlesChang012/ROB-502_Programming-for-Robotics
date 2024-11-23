#include <cmath>
#include <fstream>
#include <initializer_list>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

// iterative version of binary search; you should handle the case when the
// element is not in the sequence
template <typename T>
int iterativeBinarySearch(const std::vector<T>& vals, T key,
                          int& numTimesCalled) {
    // --- Your code here

    int l = 0;
    int r = vals.size() - 1;

    while(l <= r){
        numTimesCalled++;

        int mid = l + (r-l)/2;

        if(vals[mid] < key) l = mid + 1;
        else if(vals[mid] > key) r = mid - 1;
        else return mid;
    }

    return -1;  // key not found
    // ---
}

template <typename T>
int recursiveBinarySearch(const std::vector<T>& vals, T key, int l, int r,
                          int& numTimesCalled) {
    // --- Your code here
    numTimesCalled++;

    if(r < l) return -1;    // not found

    int mid = l + (r-l)/2;

    if(vals[mid] < key) return recursiveBinarySearch(vals, key, mid+1, r, numTimesCalled);
    else if(vals[mid] > key) return recursiveBinarySearch(vals, key, l, mid-1, numTimesCalled);
    else return mid;
    // ---
}

int main() {
    std::ifstream input{"input.txt"};
    std::ofstream output{"output.txt"};

    std::string line;

    int num;
    while (input.peek() != EOF) {
        std::vector<int> nums;
        int num;
        while ((input.peek() != '\n') && (input >> num)) {
            nums.push_back(num);
        }
        if (input.peek() == '\n') {
            input.get();
        }
        int lookup;
        input >> lookup;
        if (input.peek() == '\n') {
            input.get();
        }

        int numIterativeCalled = 0;
        int numRecursiveCalled = 0;

        int indexIterative =
            iterativeBinarySearch(nums, lookup, numIterativeCalled);

        int indexRecursive = recursiveBinarySearch(
            nums, lookup, 0, nums.size() - 1, numRecursiveCalled);

        if (indexIterative != indexRecursive) {
            output << "inconsistent indices found via iterative and recursive binary search\n";
        }

        if (indexIterative == -1) {
            output << "ERROR" << std::endl;
        } else {
            output << indexIterative << ' ' << numIterativeCalled << ' '
                << numRecursiveCalled << std::endl;
        }
    }
}