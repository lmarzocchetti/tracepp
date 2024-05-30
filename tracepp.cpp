#include <iostream>
#include <format>

#include "modelio.h"

auto main() -> int {
#ifdef _WIN32
    auto ply{ trace::load_ply("../../../models/sphere_ascii.ply") };
#else
    auto ply{ trace::load_ply("../models/sphere_ascii.ply") };
#endif // _WIN32

    
    return 0;
}
