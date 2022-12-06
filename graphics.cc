#include "graphics.h"
#include <string>
#include <memory>

Graphics::Graphics(int rows, int cols): Viewer{rows, cols} {
	//make window
	xw = std::make_unique<Xwindow>(rows * tileSize, cols * tileSize);
	for (int a = 0; a < rows; ++a) {
		for (int b = 0; b < cols; ++b) {
            		if ((a + b) % 2 == 0) {
               		 xw->fillRectangle(b * tileSize, a * tileSize, tileSize, tileSize, Xwindow::Red);
					}
        	}
    	}

	//create board
    	for (int i = 0; i < rows; ++i) {
		    std::vector<char> board_row;
		    for (int j = 0; j < cols; ++j) {
			    board_row.emplace_back(' ');
		    }
		    curboard.emplace_back(board_row);
    	}
	
	//setting up for first time
   	for (size_t i = 0; i < curboard.size(); ++i) {
		for (size_t j = 0; j < curboard[i].size(); ++j) {
			std::string s(1, curboard[i][j]);
			xw->drawString(j * tileSize + tileSize/2 - 2, i * tileSize + tileSize/2 + 5, s);
		}
	}

	//initializing values
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
                        if (board[i][j] != curboard[i][j]) {//if tile has changed
				++changed_tile;
				curboard[i][j] = board[i][j];
                                std::string s (1, curboard[i][j]);

				//update tile color
				if ((i + j) % 2 == 0) {
					xw->fillRectangle(j * tileSize, i * tileSize, tileSize, tileSize, Xwindow::Red);
				} else {
					xw->fillRectangle(j * tileSize, i * tileSize, tileSize, tileSize, Xwindow::White);
				}

				//update change history
				if (start_changed) {
					end_x = j;
					end_y = i;
				} else {
					start_x = j;
					start_y = i;
					start_changed = true;
				}

				//draw charaacter
                                xw->drawString(j * tileSize + tileSize/2 - 2, i * tileSize + tileSize/2 + 5, s);
                        } else if ((i == last_y_start && j == last_x_start) || (i == last_y_end && j == last_x_end)) {//updating previously changed to normal colors
				std::string s (1, curboard[i][j]);
				if ((i + j) % 2 == 0) {
                                        xw->fillRectangle(j*tileSize,i*tileSize,tileSize,tileSize,Xwindow::Red);
                                } else {
                                        xw->fillRectangle(j*tileSize,i*tileSize,tileSize,tileSize,Xwindow::White);
                                }

				xw->drawString(j * tileSize + tileSize/2 - 2, i * tileSize + tileSize/2 + 5, s);
			}
                }
        }

	//updating values
	last_x_start = start_x;
	last_y_start = start_y;
	last_x_end = end_x;
	last_y_end = end_y;
	
	//making chanaged tiles blue
	if (changed_tile <= 2 && changed_tile > 0 && start_x >= 0 && start_y >= 0) {
		std::string s1(1, curboard[start_y][start_x]);
		xw->fillRectangle(start_x * tileSize, start_y * tileSize, tileSize, tileSize, Xwindow::Blue);
		xw->drawString(start_x * tileSize + tileSize/2 - 2, start_y * tileSize + tileSize/2 + 5, s1);

		if (changed_tile == 2 && end_x >= 0 && end_y >= 0) {
			std::string s2(1, curboard[end_y][end_x]);
			xw->fillRectangle(end_x * tileSize, end_y * tileSize, tileSize, tileSize, Xwindow::Blue);
			xw->drawString(end_x * tileSize + tileSize/2 - 2, end_y * tileSize + tileSize/2 + 5, s2);
		}
	}
}

Graphics::~Graphics() {}
