#include <iostream>
#include "viewer.h"
#ifndef TEXT_H
#define TEXT_H

class text: public viewer {
  std::ostream &out;
  public:
  update(char[][]board) override;
};
#endif
