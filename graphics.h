#ifndef GRAPHICS_H
#define GRAPHICS_H
#include "viewer.h"
#include "window.h"
#include <memory>

class Graphics: public Viewer {
        std::unique_ptr<Xwindow> xw;
        std::vector<std::vector<char>> curboard;
	int last_x_start, last_y_start, last_x_end, last_y_end;
        const int tileSize = 20;
public:
	Graphics(int rows, int cols);
        void update(std::vector<std::vector<char>> board) override;
        ~Graphics() override;
};
#endif
