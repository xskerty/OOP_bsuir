#pragma once
#include <vector>
class IFigure
{
public:
    IFigure();
    void fill();    
    inline std::vector<std::pair<int, int>> getCoordinates() const { return coordinates; }
    inline std::vector<uint8_t> getStartValues() const { return startValues; };
    inline bool getIsFilled() const{ return isFilled; };
    virtual void transform(uint8_t, uint8_t) = 0;
protected:
    std::vector<std::pair<int, int>> coordinates;
    bool isFilled;
    std::vector<uint8_t> startValues;
private:
    virtual void refreshCoordinates() = 0;
};