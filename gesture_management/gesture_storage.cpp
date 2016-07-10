// ========================================================================= //
// Filename      :  gesture_storage.cpp
// Creation Date :  2016-7-9
// Created by    :  anfranek
// ========================================================================= //
#include "gesture_storage.h"

#include <fstream>

#include <yaml-cpp/yaml.h>

#include "eigen_yaml.h"

Gestures::Storage Gestures::load(const std::string& filename)
{
    YAML::Node node = YAML::LoadFile(filename);
    return node.as<Storage>();
}

void Gestures::save(const Gestures::Storage &store, const std::string& filename)
{
    YAML::Node node;
    node = store;

    YAML::Emitter emitter;
    emitter << node;

    std::ofstream file(filename);
    file << emitter.c_str();
}
