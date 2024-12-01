#include <iostream>
#include <chrono>
#include <thread>

int main() {
    // Get current time
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
    std::tm now_tm = *std::localtime(&now_time_t);

    // Set target time to 2 PM
    now_tm.tm_hour = 14;  // 14:00 = 2 PM
    now_tm.tm_min = 0;
    now_tm.tm_sec = 0;

    // Convert back to std::chrono::system_clock::time_point
    std::chrono::system_clock::time_point target_time =
        std::chrono::system_clock::from_time_t(std::mktime(&now_tm));

    // Adjust if the time has already passed today
    if (target_time <= now) {
        target_time += std::chrono::hours(24);
    }

    // Sleep until the target time
    std::cout << "Sleeping until 2 PM..." << std::endl;
    std::this_thread::sleep_until(target_time);

    std::cout << "Awake at 2 PM!" << std::endl;
    return 0;
}
