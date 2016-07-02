// ========================================================================= //
// Filename      :  neural_network.h
// Creation Date :  2016-6-13
// Created by    :  anfranek
// ========================================================================= //

#pragma once

#include <type_traits>

#include <Eigen/Core>

 // TODO: check whether it would be an advantage to not force Eigen to evaluate for the return
template<typename Derived>
Eigen::Matrix<typename Eigen::MatrixBase<Derived>::Scalar, Eigen::MatrixBase<Derived>::RowsAtCompileTime, Eigen::MatrixBase<Derived>::ColsAtCompileTime> sigmoid(const Eigen::MatrixBase<Derived>& z)
{
    return ((z.array() * -1).exp()+1).inverse().matrix();
}

template <typename ScalarT, size_t InputDim, size_t ActivationDim, size_t... LayerDims>
struct Layers
{
    using NextLayerT = Layers<ScalarT, ActivationDim, LayerDims...>;
    using OutputVecT = typename NextLayerT::OutputVecT;
    using WeightsMatT = Eigen::Matrix<ScalarT, ActivationDim, InputDim>;
    using BiasVecT = Eigen::Matrix<ScalarT, ActivationDim, 1>;
    using ActivationVecT = Eigen::Matrix<ScalarT, ActivationDim, 1>;

    NextLayerT next_layer;
    WeightsMatT weights;
    BiasVecT biases;

    template <typename Derived>
    OutputVecT feedforward(const Eigen::MatrixBase<Derived>& input)
    {
        return next_layer.feedforward(sigmoid(weights*input+biases));
    }
};

template <typename ScalarT, size_t InputDim, size_t OutputDim>
struct Layers<ScalarT, InputDim, OutputDim>
{
    using WeightsMatT = Eigen::Matrix<ScalarT, OutputDim, InputDim>;
    using BiasVecT = Eigen::Matrix<ScalarT, OutputDim, 1>;
    using OutputVecT = Eigen::Matrix<ScalarT, OutputDim, 1>;

    WeightsMatT weights;
    BiasVecT biases;

    template <typename Derived>
    OutputVecT feedforward(const Eigen::MatrixBase<Derived>& input)
    {
        return sigmoid(weights*input+biases);
    }
};

template <size_t Index, typename LayerT>
struct LayerGetter
{
    static auto get(LayerT& layer) -> decltype(LayerGetter<Index-1, typename LayerT::NextLayerT>::get(layer.next_layer))
    {
        return LayerGetter<Index-1, typename LayerT::NextLayerT>::get(layer.next_layer);
    }
};

template <typename LayerT>
struct LayerGetter<0, LayerT>
{
    static LayerT& get(LayerT& layer)
    {
        return layer;
    }
};

template <typename ScalarT, int InputDim, int... LayerDims>
struct NeuralNetwork
{
    using LayerT = Layers<ScalarT, InputDim, LayerDims...>;
    using OutputVecT = typename LayerT::OutputVecT;

    LayerT layers;

    NeuralNetwork()
    {}

    template <size_t Index>
    auto getLayer() -> decltype(LayerGetter<Index, LayerT>::get(layers))
    {
        return LayerGetter<Index, LayerT>::get(layers);
    }

    template <typename Derived>
    OutputVecT feedforward(const Eigen::MatrixBase<Derived>& input)
    {
        EIGEN_STATIC_ASSERT((std::is_same<ScalarT, typename Eigen::internal::traits<Derived>::Scalar>::value),
            YOU_MIXED_DIFFERENT_NUMERIC_TYPES__YOU_NEED_TO_USE_THE_CAST_METHOD_OF_MATRIXBASE_TO_CAST_NUMERIC_TYPES_EXPLICITLY);
        eigen_assert(input.rows() == InputDim);
        eigen_assert(input.cols() == 1); // TODO: extend the function to accept matrices with several columns, passing each column to feedforward

        return layers.feedforward(input);
    }
};
