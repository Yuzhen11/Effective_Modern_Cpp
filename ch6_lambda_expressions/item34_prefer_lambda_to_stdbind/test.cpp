#include <chrono>
#include <functional>

using Time = std::chrono::steady_clock::time_point;
enum class Sound {Beep, Siren, Whistle};
using Duration = std::chrono::steady_clock::duration;

void setAlarm(Time t, Sound s, Duration d) {
}

int main() {
    // setSoundL, L for lambda
    auto setSoundL = [](Sound s) {
        using namespace std::chrono;
        setAlarm(steady_clock::now()+hours(1),
                 s, 
                 seconds(30));
    };

    auto setSoundL2 = [](Sound s) {
        using namespace std::chrono;
        using namespace std::literals;  // c++14 only
        setAlarm(steady_clock::now()+1h,
                 s, 
                 30s);
    };

    using namespace std::chrono;
    using namespace std::literals;  // c++14 only
    using namespace std::placeholders;
    // B for bind
    auto setSoundB = std::bind(setAlarm, 
                               steady_clock::now()+1h,  // incorrect, will be evalued when std::bind is called
                               _1,
                               30s);

    // To make each call to setSoundB2 will create a new time
    auto setSoundB2 = std::bind(setAlarm, 
                               std::bind(std::plus<>(),  // C++14
                                         std::bind(steady_clock::now),
                                         1h),
                               _1,
                               30s);

}
