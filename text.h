#ifndef TEXT_H
#define TEXT_H
#include <iostream>
#include "viewer.h"

class text: public viewer {
  std::ostream &out;
  public:
  update(char[][]board) override;
};
#endif
