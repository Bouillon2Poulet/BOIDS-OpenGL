#pragma once

class BehaviorVariables {
private:
    float _protectedRange  = 0.1f;
    float _visibleRange    = 0.2f;
    float _avoidFactor     = 0.4f;
    float _matchingFactor  = 0.01f;
    float _centeringFactor = 0.001f;
    float _turnFactor      = 0.05f;
    // unsigned int _neighboringFishes = 0;
    float _maxSpeed = 0.3f;
    float _minSpeed = 0.1f;

public:
    BehaviorVariables()                                = default;
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
