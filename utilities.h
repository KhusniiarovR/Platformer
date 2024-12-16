#ifndef UTILITIES_H
#define UTILITIES_H

#include <cstdlib>
#include <thread>
#include <chrono>
float rand_from_to(float from, float to) {
    return from + static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX) * (to - from); // NOLINT(*-msc50-cpp)
}

float rand_up_to(float to) {
    return rand_from_to(0.0f, to);
}

void destroy_fall_wall(Vector2 pos) {
    std::thread delayThread([=]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(400));
        get_collider(pos, FALL_WALL) = ' ';
    });
    delayThread.detach();
}
#endif // UTILITIES_H