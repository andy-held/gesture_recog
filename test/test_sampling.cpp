// ========================================================================= //
// Filename      :  test_sampling.cpp
// Creation Date :  2016-6-21
// Created by    :  anfranek
// ========================================================================= //

#include <gtest/gtest.h>

#include <cmath>

#include <Eigen/Core>

#include "sampling.h"

TEST(equidistant_sampling, two_point_line)
{
    util::AlignedVecOfVec2d line = {{0, 0}, {4, 0}};

    util::AlignedVecOfVec2d expected = {{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}};
    auto sampled = util::sample_equidistant(line, 5);

    EXPECT_EQ(expected, sampled);
}

TEST(equidistant_sampling, three_point_line)
{
    util::AlignedVecOfVec2d line = {{0, 0}, {1, 1}, {2, 0}};

    util::AlignedVecOfVec2d expected = {{0, 0}, {2./3., 2./3.}, {4./3., 2./3.}, {2, 0}};
    auto sampled = util::sample_equidistant(line, 4);

    for(int i = 0; i < static_cast<int>(expected.size()); i++)
    {
        EXPECT_DOUBLE_EQ(expected[i][0], sampled[i][0]);
        EXPECT_DOUBLE_EQ(expected[i][1], sampled[i][1]);
    }
}
