// ========================================================================= //
// Filename      :  eigen_yaml.h
// Creation Date :  2016-6-21
// Created by    :  anfranek
// ========================================================================= //

#pragma once

#include <Eigen/Core>
#include <yaml-cpp/yaml.h>

namespace util
{
template<typename ScalarT>
struct ScalarTypeTrait
{};

template<>
struct ScalarTypeTrait<float>
{
    static const char* id;
};

template<>
struct ScalarTypeTrait<double>
{
    static const char* id;
};

template<>
struct ScalarTypeTrait<int>
{
    static const char* id;
};

struct MatrixCheckerBase
{
protected:
    static void checktype(const std::string& a, const std::string& b)
    {
        if(a != b)
            throw std::runtime_error("YAML matrix serialization could not be read, type does not match.");
    }

    template<typename T>
    static void checkRows(T a, T b)
    {
        if(a != b)
            throw std::runtime_error("YAML matrix serialization could not be read, rows do not match.");
    }

    template<typename T>
    static void checkCols(T a, T b)
    {
        if(a != b)
            throw std::runtime_error("YAML matrix serialization could not be read, cols do not match.");
    }
};


template<typename Scalar, int Rows, int Cols, int Options, int MaxRows, int MaxCols>
struct MatrixChecker: public MatrixCheckerBase
{
    using MatrixT = Eigen::Matrix<Scalar, Rows, Cols, Options, MaxRows, MaxCols>;
    using IndexT = typename MatrixT::Index;

    static void check(const Eigen::Matrix<Scalar, Rows, Cols, Options, MaxRows, MaxCols>& mat, IndexT rows, IndexT cols, const std::string& type)
    {
        checkRows(mat.rows(), rows);
        checkCols(mat.cols(), cols);
        checktype(ScalarTypeTrait<Scalar>::id, type);
    }
};

template<typename Scalar, int Cols, int Options, int MaxRows, int MaxCols>
struct MatrixChecker<Scalar, Eigen::Dynamic, Cols, Options, MaxRows, MaxCols>: public MatrixCheckerBase
{
    using MatrixT = Eigen::Matrix<Scalar, Eigen::Dynamic, Cols, Options, MaxRows, MaxCols>;
    using IndexT = typename MatrixT::Index;

    static void check(MatrixT& mat, IndexT rows, IndexT cols, const std::string& type)
    {

        checkCols(mat.cols(), cols);
        mat.resize(rows, Eigen::NoChange);
        checktype(ScalarTypeTrait<Scalar>::id, type);
    }
};

template<typename Scalar, int Rows, int Options, int MaxRows, int MaxCols>
struct MatrixChecker<Scalar, Rows, Eigen::Dynamic, Options, MaxRows, MaxCols>: public MatrixCheckerBase
{
    using MatrixT = Eigen::Matrix<Scalar, Rows, Eigen::Dynamic, Options, MaxRows, MaxCols>;
    using IndexT = typename MatrixT::Index;

    static void check(MatrixT& mat, IndexT rows, IndexT cols, const std::string& type)
    {
        checkRows(mat.rows(), rows);
        mat.resize(Eigen::NoChange, cols);
        checktype(ScalarTypeTrait<Scalar>::id, type);
    }
};

template<typename Scalar, int Options, int MaxRows, int MaxCols>
struct MatrixChecker<Scalar, Eigen::Dynamic, Eigen::Dynamic, Options, MaxRows, MaxCols>: public MatrixCheckerBase
{
    using MatrixT = Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic, Options, MaxRows, MaxCols>;
    using IndexT = typename MatrixT::Index;

    static void check(MatrixT& mat, IndexT rows, IndexT cols, const std::string& type)
    {
        mat.resize(rows, cols);
        checktype(ScalarTypeTrait<Scalar>::id, type);
    }
};
}

namespace YAML
{
template<typename Scalar, int Rows, int Cols, int Options, int MaxRows, int MaxCols>
struct convert<Eigen::Matrix<Scalar, Rows, Cols, Options, MaxRows, MaxCols> >
{
    using MatrixT = Eigen::Matrix<Scalar, Rows, Cols, Options, MaxRows, MaxCols>;

    static Node encode(const MatrixT& rhs)
    {
        Node node;

        node["rows"] = rhs.rows();
        node["cols"] = rhs.cols();
        node["data-type"] = util::ScalarTypeTrait<Scalar>::id;

        using IndexT = typename MatrixT::Index;
        for(IndexT row = 0; row < rhs.rows(); row++)
        {
            for(IndexT col = 0; col < rhs.cols(); col++)
            {
                node["data"].push_back(rhs(row, col));
            }
        }
        node["data"].SetStyle(YAML::EmitterStyle::Flow);

        return node;
    }

    static bool decode(const Node& node, MatrixT& rhs)
    {
        using IndexT = typename MatrixT::Index;

        util::MatrixChecker<Scalar, Rows, Cols, Options, MaxRows, MaxCols>::check(rhs, node["rows"].as<IndexT>(), node["cols"].as<IndexT>(), node["data-type"].as<std::string>());

        int i = 0;
        for(IndexT row = 0; row < rhs.rows(); row++)
        {
            for(IndexT col = 0; col < rhs.cols(); col++)
            {
                rhs(row, col) = node["data"][i].as<Scalar>();
                i++;
            }
        }

        return true;
    }
};
}
