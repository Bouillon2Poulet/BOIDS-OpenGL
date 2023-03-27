#ifndef __DISPLAYDEBUGUIPARAMETERS__HPP
#define __DISPLAYDEBUGUIPARAMETERS__HPP

class DebugUiParameters {
private:
    bool _displayProtectedRange = false;
    bool _displayVisibleRange   = false;
    bool _displayVelocityVector = false;
    bool _displayProximityNbr   = false;

public:
    void operator()(DebugUiParameters& toCopy);

    void  displayProtectedRange(bool input);
    bool  displayProtectedRange() const;
    bool* displayProtectedRangePtr();

    void  displayVisibleRange(bool input);
    bool  displayVisibleRange() const;
    bool* displayVisibleRangePtr();

    void  displayVelocityVector(bool input);
    bool  displayVelocityVector() const;
    bool* displayVelocityVectorPtr();

    void  displayProximityNbr(bool input);
    bool  displayProximityNbr() const;
    bool* displayProximityNbrPtr();
};

#endif