// ========================================================================= //
// Filename      :  resource_path.cpp
// Creation Date :  2016-6-12
// Created by    :  anfranek
// ========================================================================= //

#include "resource_path.h"

#include <iostream>

#include <SDL.h>

std::string util::getResourcePath(const std::string &subDir)
{
    const char PATH_SEP = '/';

    //This will hold the base resource path: Lessons/res/
    //We give it static lifetime so that we'll only need to call
    //SDL_GetBasePath once to get the executable path
    static std::string baseRes;
    if (baseRes.empty())
    {
        //SDL_GetBasePath will return NULL if something went wrong in retrieving the path
        char *basePath = SDL_GetBasePath();
        if (basePath)
        {
            baseRes = basePath;
            SDL_free(basePath);
        }
        else
        {
            std::cerr << "Error getting resource path: " << SDL_GetError() << std::endl;
            return "";
        }
//        //We replace the last bin/ with res/ to get the the resource path
        size_t pos = baseRes.rfind("build");
        baseRes = baseRes.substr(0, pos) + "data" + PATH_SEP;
    }
    //If we want a specific subdirectory path in the resource directory
    //append it to the base path. This would be something like Lessons/res/Lesson0
//    return subDir.empty() ? baseRes : baseRes + subDir + PATH_SEP;
    return baseRes + subDir + PATH_SEP;
}
