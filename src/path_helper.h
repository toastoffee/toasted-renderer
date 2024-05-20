/**
  ******************************************************************************
  * @file           : path_helper.h
  * @author         : toastoffee
  * @brief          : None
  * @attention      : None
  * @date           : 2024/5/12
  ******************************************************************************
  */


#ifndef TOASTED_RENDERER_PATH_HELPER_H
#define TOASTED_RENDERER_PATH_HELPER_H

#include <filesystem>
#include <iostream>

class PathHelper {

private:

public:
    std::filesystem::path static constructFilePath(const std::filesystem::path& path){
        std::filesystem::path ret = std::filesystem::current_path().parent_path();

        ret += '/';
        ret += path;
        return ret;
    }
};


#endif //TOASTED_RENDERER_PATH_HELPER_H
