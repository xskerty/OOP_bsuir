#pragma once
#include "IFigure.h"

namespace figures {

    class Circle :public IFigure
    {
    public:
        Circle(uint8_t x_pos, uint8_t y_pos, uint8_t radius);
        ~Circle() = default;
        inline std::vector<uint8_t> getStartValues() const { return startValues; }
        void transform(uint8_t, uint8_t) override;
    private:
        void refreshCoordinates() override;      
    };

    class Rectangle :public IFigure
    {
    public:
        Rectangle(uint8_t x_pos1, uint8_t y_pos1, uint8_t x_pos2, uint8_t y_pos2);
        ~Rectangle() = default;
        inline std::vector<uint8_t> getStartValues() const { return startValues; }
        void transform(uint8_t, uint8_t) override;
    private:
        void refreshCoordinates() override;
    };

    class Triangle :public IFigure
    {
    public:
        Triangle(uint8_t x_pos1, uint8_t y_pos1, uint8_t height);
        ~Triangle() = default;
        inline std::vector<uint8_t> getStartValues() const { return startValues; }
        void transform(uint8_t, uint8_t) override;
    private:
        void refreshCoordinates() override;
    };
}