#include <chrono>
#include <functional>

using Time = std::chrono::steady_clock::time_point;
enum class Sound {Beep, Siren, Whistle};
using Duration = std::chrono::steady_clock::duration;

void setAlarm(Time t, Sound s, Duration d) {
}

enum class Volume {Normal, Loud, LoudPlusPlus };
void setAlarm(Time t, Sound s, Duration d, Volume v) {
}

int main() {
    using namespace std::chrono;
    using namespace std::literals;  // c++14 only
    using namespace std::placeholders;

    using SetAlarm3ParamType = void(*)(Time t, Sound s, Duration d);
    // Problem: less likely to inline
    auto setSoundB2 = std::bind(static_cast<SetAlarm3ParamType>(setAlarm), 
                               std::bind(std::plus<>(),  // C++14
                                         std::bind(steady_clock::now),
                                         1h),
                               _1,
                               30s);
}
