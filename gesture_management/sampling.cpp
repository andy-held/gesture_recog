// ========================================================================= //
// Filename      :  sampling.cpp
// Creation Date :  2016-6-21
// Created by    :  anfranek
// ========================================================================= //

#include "sampling.h"

util::AlignedVecOfVec2d util::sample_equidistant(const AlignedVecOfVec2d& line, size_t samples)
{
    if(samples == 0)
        throw std::runtime_error("Invalid sampling size.");
    AlignedVecOfVec2d sampled_line;
    sampled_line.reserve(samples);

    std::vector<double> cum_lengths(line.size());
    cum_lengths[0] = 0.;
    for(int i = 1; i < static_cast<int>(line.size()); i++)
    {
        cum_lengths[i] = (line[i] - line[i-1]).norm() + cum_lengths[i-1];
    }

    double step_len = cum_lengths.back()/static_cast<double>(samples - 1);
    sampled_line.push_back(line.front());
    size_t cum_index = 1;
    for(int i = 1; i < static_cast<int>(samples)-1; i++)
    {
        double sample = i * step_len;
        while(cum_lengths[cum_index] < sample)
            cum_index++;
        double alpha = (sample - cum_lengths[cum_index-1])/(cum_lengths[cum_index] - cum_lengths[cum_index-1]);
        sampled_line.push_back(lerp(line[cum_index-1], line[cum_index], alpha));
    }
    sampled_line.push_back(line.back());

    return sampled_line;
}
