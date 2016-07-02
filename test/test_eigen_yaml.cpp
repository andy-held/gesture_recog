// ========================================================================= //
// Filename      :  test_eigen_yaml.cpp
// Creation Date :  2016-6-21
// Created by    :  anfranek
// ========================================================================= //

#include <gtest/gtest.h>

#include <Eigen/Core>
#include <yaml-cpp/yaml.h>

#include "eigen_yaml.h"

/**
 * @brief TEST
 */
TEST(eigen_yaml, node)
{
    Eigen::Matrix2d mat;
    mat << 1, 2, 3, 6;

    YAML::Node node;
    node["mat"] = mat;
    Eigen::Matrix2d res;
    res = node["mat"].as<Eigen::Matrix2d>();

    EXPECT_EQ(mat, res);
}

TEST(eigen_yaml, emitter)
{
    Eigen::Matrix2d mat;
    mat << 1, 2, 3, 6;

    YAML::Node node;
    node["mat"] = mat;

    YAML::Emitter out;
    out << node;

    EXPECT_STREQ("mat:\n  rows: 2\n  cols: 2\n  data-type: double\n  data: [1, 2, 3, 6]", out.c_str());
}

TEST(eigen_yaml, load)
{
    YAML::Node node = YAML::Load("mat:\n  rows: 2\n  cols: 2\n  data-type: double\n  data: [1, 2, 3, 6]");

    Eigen::Matrix2d mat;
    mat << 1, 2, 3, 6;

    EXPECT_EQ(mat, node["mat"].as<Eigen::Matrix2d>());
}

TEST(eigen_yaml, MatrixXd)
{
    YAML::Node node = YAML::Load("mat:\n  rows: 2\n  cols: 2\n  data-type: double\n  data: [1, 2, 3, 6]");

    Eigen::MatrixXd mat(2,2);
    mat << 1, 2, 3, 6;

    EXPECT_EQ(mat, node["mat"].as<Eigen::MatrixXd>());
}

TEST(eigen_yaml, Matrix2Xd)
{
    YAML::Node node = YAML::Load("mat:\n  rows: 2\n  cols: 2\n  data-type: double\n  data: [1, 2, 3, 6]");

    Eigen::Matrix2Xd mat(2,2);
    mat << 1, 2, 3, 6;

    EXPECT_EQ(mat, node["mat"].as<Eigen::Matrix2Xd>());
}

TEST(eigen_yaml, MatrixX2d)
{
    YAML::Node node = YAML::Load("mat:\n  rows: 2\n  cols: 2\n  data-type: double\n  data: [1, 2, 3, 6]");

    Eigen::MatrixX2d mat(2,2);
    mat << 1, 2, 3, 6;

    EXPECT_EQ(mat, node["mat"].as<Eigen::MatrixX2d>());
}
