/**
 * @file customColorPicker.h
 * Definition of a custom color picker.
 *
 */
#ifndef CUSTOMCOLORPICKER_H
#define CUSTOMCOLORPICKER_H

#include "colorPicker.h"

/**
 * customColorPicker: a functor that determines the color that should be used
 * given an x and a y coordinate using a custom pattern.
 *
 */
class customColorPicker : public colorPicker
{
  public:
    /**
     * Constructs a new customColorPicker.
     *
     * @param fillColor Color for the border between cells of the grid.
     * @param gridSpacing Spacing between cells of the grid.
     */
    customColorPicker(HSLAPixel fillColor1, HSLAPixel fillColor2);

    /**
     * Picks the color for pixel (x, y). If the x or y coordinate is a
     * multiple of the spacing, it will be filled with the fillColor.
     * otherwise, it will be filled with white.
     *
     * @param x The x coordinate to pick a color for.
     * @param y The y coordinat to pick a color for.
     * @return The color chosen for (x, y).
     */
    virtual HSLAPixel operator()(int x, int y);

  private:
    HSLAPixel xColor;
    HSLAPixel yColor
};

#endif
