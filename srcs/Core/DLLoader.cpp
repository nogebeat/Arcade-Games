/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-arcade-james.gbetchedji [WSL: Ubuntu]
** File description:
** DLLoader
*/

#include "../../includes/Core/DLLoader.hpp"
#include <iostream>

namespace arcade {

bool DLLoader::my_dlopen(const std::string &path) {
    handle = dlopen(path.c_str(), RTLD_LAZY);
    return handle != nullptr;
}

template<typename T>
T DLLoader::my_dlsysm(const std::string &path_functions) {
    return reinterpret_cast<T>(dlsym(handle, path_functions.c_str()));
}

void DLLoader::my_dl_error() {
    std::cerr << "DLLoader error: " << dlerror() << std::endl;
}

void DLLoader::my_dlclose() {
    if (handle) {
        dlclose(handle);
        handle = nullptr;
    }
}
}
