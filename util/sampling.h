// ========================================================================= //
// Filename      :  sampling.h
// Creation Date :  2016-6-21
// Created by    :  anfranek
// ========================================================================= //

#pragma once

#include <vector>

#include <Eigen/Core>

namespace util
{
template<typename T>
T lerp(const T& a, const T& b, double alpha)
{
    return a + alpha*(b-a);
}

template<typename MatT>
using AlignedStdVec = std::vector<MatT, Eigen::aligned_allocator<MatT> >;
using AlignedVecOfVec2d = AlignedStdVec<Eigen::Vector2d>;

AlignedVecOfVec2d sample_equidistant(const AlignedVecOfVec2d& line, size_t samples);
}
