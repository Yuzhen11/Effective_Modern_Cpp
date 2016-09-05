#include <mutex>
#include <vector>
#include <atomic>

class Polynomial {
public:
    using RootsType = std::vector<double>;

    // Thread-safe problem
    RootsType root() const {
        if (!rootsAreValid) {
            // ... compute roots
            
            rootsAreValid = true;
        }
        return rootVals;
    }

private:
    // mutable for write variable in const function
    mutable bool rootsAreValid{ false };
    mutable RootsType rootVals{};
};

class Polynomial2 {
public:
    using RootsType = std::vector<double>;

    RootsType root() const {
        std::lock_guard<std::mutex> g(m);
        if (!rootsAreValid) {
            // ... compute roots
            
            rootsAreValid = true;
        }
        return rootVals;
    }

private:
    // mutable for write variable in const function
    mutable std::mutex m;  // locking and unlocking are non-const
    mutable bool rootsAreValid{ false };
    mutable RootsType rootVals{};
};

class Point {
public:
    double distanceFromOrigin() const {
        ++callCount;

        return 1.;
    }
private:
    mutable std::atomic<unsigned> callCount{0};
    double x,y;
};

int main() {
}
