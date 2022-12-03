#ifndef TEXT_H
#define TEXT_H
#include <iostream>
#include "viewer.h"

class Text: public Viewer {
  std::ostream &out;
  public:
  void update(std::vector<std::vector<char>> board) override;//(char board[rows][cols]) override;
  Text(std::ostream &out);
};
#endif
