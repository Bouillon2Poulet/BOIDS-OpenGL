#ifndef __DEBUGUI__HPP
#define __DEBUGUI__HPP

#include <p6/p6.h>
#include "MovementVariables.h"
#include "behaviorVariables.h"
#include "displayDebugUiParameters.h"

class DebugUiVariables {
    glm::vec2&    _position;
    glm::vec2&    _velocity;
    float&        _protectedRange;
    float&        _visibleRange;
    unsigned int& _neighboringFishes;

public:
    DebugUiVariables(const DebugUiVariables& toCopy) = default;
    inline void operator()(const DebugUiVariables& toCopy)
    {
        _position          = toCopy._position;
        _velocity          = toCopy._velocity;
        _protectedRange    = toCopy._protectedRange;
        _visibleRange      = toCopy._visibleRange;
        _neighboringFishes = toCopy._neighboringFishes;
    }

    inline DebugUiVariables(MovementVariables& mvtToCopy, BehaviorVariables& bhvToCopy)
        : _position(*(mvtToCopy.positionPtr())), _velocity(*(mvtToCopy.velocityPtr())), _protectedRange(*(bhvToCopy.protectedRangePtr())), _visibleRange(*(bhvToCopy.visibleRangePtr())), _neighboringFishes(*(bhvToCopy.neighboringFishesPtr())){};

    inline glm::vec2 position() const
    {
        return _position;
    }

    inline glm::vec2 velocity() const
    {
        return _velocity;
    }
    inline float protectedRange() const
    {
        return _protectedRange;
    }
    inline float visibleRange() const
    {
        return _visibleRange;
    }
    inline unsigned int neighboringFishes() const
    {
        return _neighboringFishes;
    }
};

class DebugUi {
private:
    displayDebugUiParameters _parameters;
    DebugUiVariables         _variables;

public:
    DebugUi(MovementVariables& mvtToCopy, BehaviorVariables& bhvToCopy)
        : _variables(mvtToCopy, bhvToCopy){};

    DebugUi(const DebugUi& toCopy) = default;

    inline void copy(DebugUi& toCopy)
    {
        _parameters = toCopy._parameters;
        _variables(toCopy._variables);
    }
    inline displayDebugUiParameters parameters() const { return _parameters; };

    void drawProtectedCircle(p6::Context& ctx) const;
    void drawVisibleCircle(p6::Context& ctx) const;
    void drawVelocityVector(p6::Context& ctx) const;
    void drawProximityNbr(p6::Context& ctx) const;

    inline DebugUiVariables variables() { return _variables; };
    // DebugUi debugUi();
    // DebugUi* debugUiPtr();
};

#endif