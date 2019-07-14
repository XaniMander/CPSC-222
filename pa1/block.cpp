#include <vector>
#include <iostream>
#include "cs221util/PNG.h"
#include "cs221util/HSLAPixel.h"
#include "block.h"

using namespace std;
using namespace cs221util;

void Block::build(PNG & im, int column, int width) {
  for (unsigned x = 0; x < im.width(); x++) {
    for (unsigned y = 0; y < im.height(); y++) {
      HSLAPixel* pixel = im.getPixel(x, y);
      data[x][y] = *pixel;
    }
  }
}

void Block::render(PNG & im, int column) const {
  for (unsigned x = 0; x < im.width(); x++) {
    for (unsigned y = 0; y < im.height(); y++) {
      HSLAPixel* pixel = im.getPixel(x,y);
      pixel->h = data[x][y].h;
      pixel->s = data[x][y].s;
      pixel->l = data[x][y].l;
      pixel->a = data[x][y].a;
    }
  }
}

void Block::greyscale() {
  for (int col = 0; col < width(); col++) {
    for (int row = 0; row < height(); row++) {
      HSLAPixel* pixel = &data[col][row];
      pixel->s = 0;
    }
  }
}

int Block::width() const {
  return Block::data.size();
}

int Block::height() const {
  return Block::data[0].size();
}
