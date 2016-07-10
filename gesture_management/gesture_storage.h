// ========================================================================= //
// Filename      :  gesture_storage.h
// Creation Date :  2016-7-9
// Created by    :  anfranek
// ========================================================================= //
#pragma once

#include <map>
#include <string>
#include <vector>

#include <Eigen/Core>

namespace Gestures
{
typedef std::map<std::string, std::vector<std::vector<Eigen::Vector2i>>> Storage;

Storage load(const std::string& filename);

void save(const Storage& store, const std::__cxx11::string &filename);
}
