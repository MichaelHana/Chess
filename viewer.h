#ifndef VIEWER_H
#define VIEWER_H
#include <vector>

class Viewer {
  protected:
        // need to somehow ensure this will always match the board size in main
        int rows=8;//static const int rows=8;
        int cols=8;//static const int cols=8;
  public:
        // must either ensure will always be getting 2d char array of proper size or put in protections
        virtual void update(std::vector<std::vector<char>> board)=0;//(char board[rows][cols])=0;
        // should add in a constructor for the case where we want to change the board dimensions
        virtual ~Viewer();
};
#endif
