#include "customColorPicker.h"

customColorPicker::customColorPicker(HSLAPixel fillColor1, HSLAPixel fillColor2) {
    xColor = fillColor1;
    yColor = fillColor2;
}

HSLAPixel customColorPicker::operator()(int x, int y) {
    double h = xColor.dist(yColor)%360;
    double s;
    double l;
    if (h%2==0) {
      s = cos(x);
      l = sin(y);
    } else {
      s = 1 - cos(x);
      l = 1 - sin(y);
    }
    return new HSLAPixel(h,s,l);
}
