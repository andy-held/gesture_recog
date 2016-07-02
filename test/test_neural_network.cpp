// ========================================================================= //
// Filename      :  test_neural_network.cpp
// Creation Date :  2016-6-14
// Created by    :  anfranek
// ========================================================================= //

#include <gtest/gtest.h>

#include <Eigen/Core>

#include <neural_network.h>

/**
 * @brief TEST neural_network, NAND
 *
 * NAND implemented as neural network containing one neuron.
 */
TEST(neural_network, NAND)
{
    NeuralNetwork<double, 2, 1> network;
    network.getLayer<0>().weights << -2, -2;
    network.getLayer<0>().biases << 3;

    EXPECT_GT(network.feedforward(Eigen::Vector2d(0, 0))[0], 0.5);
    EXPECT_GT(network.feedforward(Eigen::Vector2d(0, 1))[0], 0.5);
    EXPECT_GT(network.feedforward(Eigen::Vector2d(1, 0))[0], 0.5);
    EXPECT_LT(network.feedforward(Eigen::Vector2d(1, 1))[0], 0.5);
}

/**
 * @brief TEST neural_network, NAND_big_weights
 *
 * NAND implemented as neural network containing one neuron.
 * By using large weights and biases the results should be more distinct. I.e. 1 or 0.
 */
TEST(neural_network, NAND_big_weights)
{
    NeuralNetwork<double, 2, 1> network;
    network.getLayer<0>().weights << -2000, -2000;
    network.getLayer<0>().biases << 3000;

    EXPECT_DOUBLE_EQ(network.feedforward(Eigen::Vector2d(0, 0))[0], 1);
    EXPECT_DOUBLE_EQ(network.feedforward(Eigen::Vector2d(0, 1))[0], 1);
    EXPECT_DOUBLE_EQ(network.feedforward(Eigen::Vector2d(1, 0))[0], 1);
    EXPECT_DOUBLE_EQ(network.feedforward(Eigen::Vector2d(1, 1))[0], 0);
}

/**
 * @brief TEST neural_network, two_bit_adder
 *
 * Two bit adder implemented as neural network.
 * The network is rather complicated since only fully connected networks are possible as of yet.
 */
TEST(neural_network, two_bit_adder)
{
    NeuralNetwork<double, 2, 3, 3, 2> network;
    network.getLayer<0>().weights << 1000, 0, -2000, -2000, 0, 1000;
    network.getLayer<0>().biases << 0, 3000, 0;
    network.getLayer<1>().weights << -2000, -2000, 0, 0, -2000, -2000, 0, 1000, 0;
    network.getLayer<1>().biases << 3000, 3000, 0;
    network.getLayer<2>().weights << -2000, -2000, 0, 0, 0, -4000;
    network.getLayer<2>().biases << 3000, 3000;
    EXPECT_EQ(network.feedforward(Eigen::Vector2d(-0.01, -0.01)), Eigen::Vector2d(0, 0));
    EXPECT_EQ(network.feedforward(Eigen::Vector2d(-0.01, 1)), Eigen::Vector2d(1, 0));
    EXPECT_EQ(network.feedforward(Eigen::Vector2d(1, -0.01)), Eigen::Vector2d(1, 0));
    EXPECT_EQ(network.feedforward(Eigen::Vector2d(1, 1)), Eigen::Vector2d(0, 1));
}
