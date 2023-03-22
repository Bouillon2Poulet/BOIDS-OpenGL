#ifndef __DISPLAYDEBUGUIPARAMETERS__HPP
#define __DISPLAYDEBUGUIPARAMETERS__HPP

class displayDebugUiParameters {
private:
    bool _displayProtectedRange = true;
    bool _displayVisibleRange   = true;
    bool _displayVelocityVector = true;
    bool _displayProximityNbr   = false;

public:
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