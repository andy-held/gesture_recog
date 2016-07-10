// ========================================================================= //
// Filename      :  test_gesture_storage.cpp
// Creation Date :  2016-7-10
// Created by    :  anfranek
// ========================================================================= //

#include <gtest/gtest.h>

#include <Eigen/Core>

#include "gesture_storage.h"
#include "resource_path.h"

TEST(gesture_storage, save_n_load)
{
    Gestures::Storage expected;
    expected["test"]= {
    {{0, 2}, {5, 14}},
    {{1, 322}, {55, 4}, {345, 66}}
};
    auto filename = util::getResourcePath() + "test/test.yaml";

    Gestures::save(expected, filename);
    auto actual = Gestures::load(filename);

    EXPECT_EQ(expected, actual);
}

