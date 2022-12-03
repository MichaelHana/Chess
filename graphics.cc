#include "graphics.h"
#include "symbols.h"
#include <string>
#include <iostream>

Graphics::Graphics() {
    xw = new Xwindow(rows * 100, cols * 100);
    for (int a = 0; a < rows; ++a) {
        for (int b = 0; b < cols; ++b) {
            if ((a + b) % 2) {
                //std::cout << a << b <<std::endl;
                xw->fillRectangle(b * 100, a * 100, 100, 100, Xwindow::Red);
            }
        }
    }
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::string s(1, curboard[i][j]);
            std::cout << s << std::endl;
            xw->drawString(j * 100 + 50, i * 100 + 50, s);
            //xw->drawString(j*100+40,i*100+40,convertpiece(curboard[i][j]));
        }
    }
}

void Graphics::update(char **board) {//(char board[rows][cols]) {
        for (int i=0; i< rows; ++i) {
                for (int j=0; j< cols; ++j) {
                        if (board[i][j] != curboard[i][j]) {
                                std::string s(1, board[i][j]);
                                if ((i+j)%2){
                                        xw->fillRectangle(j*100,i*100,100,100,Xwindow::Red);
                                } else {
                                        xw->fillRectangle(j*100,i*100,100,100,Xwindow::White);
                                }
                                xw->drawString(j*100+50,i*100+50,s);
                        }
                }
        }
}

Graphics::~Graphics() {
        delete xw;
}
