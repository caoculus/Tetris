#include "common.hpp"

class tetris
{
public:
    tetris();
    ~tetris();

    void tick();
private:
    struct piece
    {
        uint8_t orientation;
        square type;
        std::pair <int, int> pos {0, 3};

        static constexpr int lut[7][4][4][2] = {
        }
    };

    board board;
    uint32_t clock;
};