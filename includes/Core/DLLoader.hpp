/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-arcade-james.gbetchedji
** File description:
** prototyped
*/

#ifndef DLLOADER_HPP
#define DLLOADER_HPP
#include <string>
#include <iostream>
#include <dlfcn.h>

namespace arcade
{

    // Classe de base DLLoader by Nando
    class DLLoader
    {
    private:
        void *handle;
        void **fptr;

    public:
        DLLoader() : handle(nullptr) {}
        bool my_dlopen(const std::string &path);
        template <typename T>
        T my_dlsysm(const std::string &path_functions);
        void my_dl_error();
        void my_dlclose();
    };

    template <typename T>
    class DLLoaderImpl
    {
    private:
        void *_handle;
        T *_instance;

    public:
        DLLoaderImpl() : _handle(nullptr), _instance(nullptr) {}

        ~DLLoaderImpl()
        {
            unload();
        }

        bool load(const std::string &path, const std::string &createFuncName)
        {
            unload();

            _handle = dlopen(path.c_str(), RTLD_LAZY);
            if (!_handle) {
                std::cerr << "DLLoader error: " << dlerror() << std::endl;
                return false;
            }

            dlerror();

            typedef T *(*CreateFunc)();
            CreateFunc createFunc = reinterpret_cast<CreateFunc>(dlsym(_handle, createFuncName.c_str()));

            const char *dlsymError = dlerror();
            if (dlsymError) {
                std::cerr << "DLLoader error: " << dlsymError << std::endl;
                dlclose(_handle);
                _handle = nullptr;
                return false;
            }

            _instance = createFunc();
            return _instance != nullptr;
        }
        void unload()
        {
            if (_instance && _handle) {
                typedef void (*DestroyFunc)(T *);
                DestroyFunc destroyFunc = reinterpret_cast<DestroyFunc>(dlsym(_handle, "destroyDisplay"));

                if (destroyFunc)
                    destroyFunc(_instance);
                else
                    delete _instance;

                _instance = nullptr;
            }

            if (_handle){
                dlclose(_handle);
                _handle = nullptr;
            }
        }

        T *getInstance() const {
            return _instance;
        }
    };

}

#endif /* !DLLOADER_HPP */
