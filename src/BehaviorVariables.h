#pragma once

#include <stdlib.h>
#include <iostream>
#include <string>
class BehaviorVariables {
private:
    float _protectedRange;
    float _visibleRange;
    float _avoidFactor;
    float _matchingFactor;
    float _centeringFactor;
    float _turnFactor;
    // unsigned int _neighboringFishes = 0;
    float _maxSpeed;
    float _minSpeed;

public:
    inline BehaviorVariables() = default;
    inline BehaviorVariables(int type)
    {
        std::cout << "!!1.15 : 1\n";
        if (type == 0)
        {
            _protectedRange  = 0.03f;
            _visibleRange    = 0.2f;
            _avoidFactor     = 0.1f;
            _matchingFactor  = 0.05;
            _centeringFactor = 0.001;
            _turnFactor      = 0.05;

            _maxSpeed = 0.1;
            _minSpeed = 0.05;
        }
        else if (type == 1)
        {
            std::cout << "!!1.16\n";
            _protectedRange  = 0.1f;
            _visibleRange    = 0.2f;
            _avoidFactor     = 0.2f;
            _matchingFactor  = 0.001;
            _centeringFactor = 0.001;
            _turnFactor      = 0.05;

            _maxSpeed = 0.05;
            _minSpeed = 0.01;
        }
        else
        {
            std::cout << "!!1.17\n";
            // std::abort();
        };
    };
    BehaviorVariables(const BehaviorVariables& toCopy) = default;

    inline void copy(const BehaviorVariables& toCopy)
    {
        _protectedRange = toCopy._protectedRange;
        _visibleRange   = toCopy._visibleRange;
        _avoidFactor    = toCopy._avoidFactor;
        _matchingFactor = toCopy._matchingFactor, _centeringFactor = toCopy._centeringFactor;
        _turnFactor = toCopy._turnFactor;
        //_neighboringFishes = toCopy._neighboringFishes;
        _maxSpeed = toCopy._maxSpeed;
        _minSpeed = toCopy._minSpeed;
    }

    void   protectedRange(float input);
    float  protectedRange() const;
    float* protectedRangePtr();

    void   visibleRange(float input);
    float  visibleRange() const;
    float* visibleRangePtr();

    void   avoidFactor(float input);
    float  avoidFactor() const;
    float* avoidFactorPtr();

    void   matchingFactor(float input);
    float  matchingFactor() const;
    float* matchingFactorPtr();

    void   centeringFactor(float input);
    float  centeringFactor() const;
    float* centeringFactorPtr();

    void   turnFactor(float input);
    float  turnFactor() const;
    float* turnFactorPtr();

    void   maxSpeed(float input);
    float  maxSpeed() const;
    float* maxSpeedPtr();

    void   minSpeed(float input);
    float  minSpeed() const;
    float* minSpeedPtr();
};
