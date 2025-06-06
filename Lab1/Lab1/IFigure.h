#pragma once
#include <vector>
class IFigure
{
public:
    IFigure();
    void fill();    
    inline std::vector<std::pair<int, int>> getCoordinates() const { return coordinates; }
    inline std::vector<int> getStartValues() const { return startValues; };
    inline bool getIsFilled() const{ return isFilled; };
    virtual void transform(int, int) = 0;
protected:
    std::vector<std::pair<int, int>> coordinates;
    bool isFilled;
    std::vector<int> startValues;
private:
    virtual void refreshCoordinates() = 0;
};