#include "graphics.h"
#include "symbols.h"
#include <string>
#include <iostream>
#include <memory>

Graphics::Graphics() {
    xw = std::make_unique<Xwindow>(rows * 100, cols * 100);
    for (int a = 0; a < rows; ++a) {
        for (int b = 0; b < cols; ++b) {
            if ((a + b) % 2) {
                //std::cout << a << b <<std::endl;
                xw->fillRectangle(b * 100, a * 100, 100, 100, Xwindow::Red);
            }
        }
    }

    // create board
    for (int i = 0; i < rows; ++i) {
	    std::vector<char> board_row;
	    for (int j = 0; j < cols; ++j) {
		    board_row.emplace_back(' ');
	    }
	    curboard.emplace_back(board_row);
    }

    for (size_t i = 0; i < curboard.size(); ++i) {
        for (size_t j = 0; j < curboard[i].size(); ++j) {
            std::string s(1, curboard[i][j]);
            xw->drawString(j * 100 + 50, i * 100 + 50, s);
            //xw->drawString(j*100+40,i*100+40,convertpiece(curboard[i][j]));
        }
    }

    last_x_start = last_y_start = last_x_end = last_y_end = -1;
}

void Graphics::update(std::vector<std::vector<char>> board) {//(char board[rows][cols]) {
        bool start_changed = false;
	int changed_tile = 0;
	int start_x, start_y, end_x, end_y;
	start_x = start_y = end_x = end_y = 0;
	int curboard_size = static_cast<int>(curboard.size());
	for (int i = 0; i < curboard_size; ++i) {
		int curboard_i_size = static_cast<int>(curboard[i].size());
                for (int j = 0; j < curboard_i_size; ++j) {
                        if (board[i][j] != curboard[i][j]) {
				++changed_tile;
				curboard[i][j] = board[i][j];
                                std::string s (1, curboard[i][j]);

				if ((i + j) % 2) {
					xw->fillRectangle(j * 100, i * 100, 100, 100, Xwindow::Red);
				} else {
					xw->fillRectangle(j * 100, i * 100, 100, 100, Xwindow::White);
				}

				if (start_changed) {
					end_x = j;
					end_y = i;
				} else {
					start_x = j;
					start_y = i;
					start_changed = true;
				}

                                xw->drawString(j * 100 + 50, i * 100 + 50, s);
                        } else if ((i == last_y_start && j == last_x_start) || (i == last_y_end && j == last_x_end)) {
				std::string s (1, curboard[i][j]);
				if ((i + j) % 2) {
                                        xw->fillRectangle(j*100,i*100,100,100,Xwindow::Red);
                                } else {
                                        xw->fillRectangle(j*100,i*100,100,100,Xwindow::White);
                                }

				xw->drawString(j * 100 + 50, i * 100 + 50, s);
			}
                }
        }

	last_x_start = start_x;
	last_y_start = start_y;
	last_x_end = end_x;
	last_y_end = end_y;
	
	if (changed_tile <= 2 && changed_tile > 0 && start_x >= 0 && start_y >= 0) {
		std::string s1(1, curboard[start_y][start_x]);
		xw->fillRectangle(start_x * 100, start_y * 100, 100, 100, Xwindow::Blue);
		xw->drawString(start_x * 100 + 50, start_y * 100 + 50, s1);

		if (changed_tile == 2 && end_x >= 0 && end_y >= 0) {
			std::string s2(1, curboard[end_y][end_y]);
			xw->fillRectangle(end_x * 100, end_y * 100, 100, 100, Xwindow::Blue);
			xw->drawString(end_y * 100 + 50, end_y * 100 + 50, s2);
		}
	}
}

Graphics::~Graphics() {}
