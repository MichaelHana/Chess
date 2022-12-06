#ifndef VIEWER_H
#define VIEWER_H
#include <vector>

class Viewer {
  protected:
        int rows;
        int cols;
  public:
	Viewer(int rows, int cols);
        virtual void update(std::vector<std::vector<char>> board)=0;
        virtual ~Viewer();
};
#endif
