#pragma once
#include "IFigure.h"

namespace figures {

    class Circle :public IFigure
    {
    public:
        Circle(int x_pos, int y_pos, int radius);
        ~Circle() = default;
        inline std::vector<int> getStartValues() const { return startValues; }
        void transform(int, int) override;
    private:
        void refreshCoordinates() override;      
    };

    class Rectangle :public IFigure
    {
    public:
        Rectangle(int x_pos1, int y_pos1, int x_pos2, int y_pos2);
        ~Rectangle() = default;
        inline std::vector<int> getStartValues() const { return startValues; }
        void transform(int, int) override;
    private:
        void refreshCoordinates() override;
    };

    class Triangle :public IFigure
    {
    public:
        Triangle(int x_pos1, int y_pos1,int side1, int side2, int side3);
        ~Triangle() = default;
        inline std::vector<int> getStartValues() const { return startValues; }
        void transform(int, int) override;
    private:
        void refreshCoordinates() override;
    };
}