/**
 * @file filler.cpp
 * Implementation of functions in the filler namespace.
 *
 */
#include "filler.h"

animation filler::fillSolidDFS(PNG& img, int x, int y, HSLAPixel fillColor,
                                 double tolerance, int frameFreq)
{
    /**
     * @todo Your code here! You should replace the following line with a
     * correct call to fill with the correct colorPicker parameter.
     */
     solidColorPicker a(fillColor);
     return fill<Stack>(img, x, y, a, tolerance, frameFreq);
}

animation filler::fillGridDFS(PNG& img, int x, int y, HSLAPixel gridColor,
                                int gridSpacing, double tolerance, int frameFreq)
{
    /**
     * @todo Your code here! You should replace the following line with a
     * correct call to fill with the correct colorPicker parameter.
     */
     gridColorPicker a(gridColor, gridSpacing);
     return fill<Stack>(img, x, y, a, tolerance, frameFreq);
}

animation filler::fillGradientDFS(PNG& img, int x, int y,
                                    HSLAPixel fadeColor1, HSLAPixel fadeColor2,
                                    int radius, double tolerance, int frameFreq)
{
    /**
     * @todo Your code here! You should replace the following line with a
     * correct call to fill with the correct colorPicker parameter.
     */
     gradientColorPicker a(fadeColor1, fadeColor2, radius, x, y);
     return fill<Stack>(img, x, y, a, tolerance, frameFreq);
}

animation filler::fillSolidBFS(PNG& img, int x, int y, HSLAPixel fillColor,
                                 double tolerance, int frameFreq)
{
    /**
     * @todo Your code here! You should replace the following line with a
     * correct call to fill with the correct colorPicker parameter.
     */
     solidColorPicker a(fillColor);
     return fill<Queue>(img, x, y, a, tolerance, frameFreq);
}

animation filler::fillGridBFS(PNG& img, int x, int y, HSLAPixel gridColor,
                                int gridSpacing, double tolerance, int frameFreq)
{
    /**
     * @todo Your code here! You should replace the following line with a
     * correct call to fill with the correct colorPicker parameter.
     */
     gridColorPicker a(gridColor, gridSpacing);
     return fill<Queue>(img, x, y, a, tolerance, frameFreq);
}

animation filler::fillGradientBFS(PNG& img, int x, int y,
                                    HSLAPixel fadeColor1, HSLAPixel fadeColor2,
                                    int radius, double tolerance, int frameFreq)
{
    /**
     * @todo Your code here! You should replace the following line with a
     * correct call to fill with the correct colorPicker parameter.
     */
     gradientColorPicker a(fadeColor1, fadeColor2, radius, x, y);
     return fill<Queue>(img, x, y, a, tolerance, frameFreq);
}

struct XYPixel {
    int x;
    int y;
    XYPixel(int newX,int newY) {
      x = newX;
      y = newY;
    }
};

int process(vector<vector<bool>>& visited, int k, PNG& img, XYPixel currXY, HSLAPixel start,
            double tolerance, OrderingStructure<XYPixel>& os, colorPicker& fillColor, animation& gif, int frameFreq) {
    if (!visited[currXY.y][currXY.x]) {
      visited[currXY.y][currXY.x] = true;
      HSLAPixel* currHSLA = (img.getPixel(currXY.x, currXY.y));
      if (start.dist(*currHSLA) <= tolerance) {
          os.add(currXY);
          *currHSLA = fillColor(currXY.x, currXY.y);
          k++;
          if (k%frameFreq==0) {
              gif.addFrame(img);
          }
      }
    }
    return k;
}

template <template <class T> class OrderingStructure>
animation filler::fill(PNG& img, int x, int y, colorPicker& fillColor,
                       double tolerance, int frameFreq)
{
    HSLAPixel start = *(img.getPixel(x, y));
    animation gif;
    int k = 0;
    OrderingStructure<XYPixel> os;
    vector<vector<bool>> visited;
    for (int i = 0; i< img.height(); i++) {
      vector<bool> temp;
      for (int j = 0; j< img.width(); j++){
        temp.push_back(false);
      }
      visited.push_back(temp);
    }
    k = process(visited, k, img, XYPixel(x,y), start, tolerance, os, fillColor, gif, frameFreq);
    int x_dir[4] = {1,0,-1,0};
    int y_dir[4] = {0,1,0,-1};
    while (!os.isEmpty()) {
        XYPixel currXY = os.remove();
        for (int i=0; i<4;i++) {
          int nX = currXY.x+x_dir[i];
          int nY = currXY.y+y_dir[i];
          if ((nX>=0 && nX<img.width()) && (nY>=0 && nY<img.height())){
            k = process(visited, k, img, XYPixel(nX, nY), start, tolerance, os, fillColor, gif, frameFreq);
          }
        }
    }
    gif.addFrame(img);
    return gif;

    /**
     * @todo You need to implement this function!
     *
     * This is the basic description of a flood-fill algorithm: Every fill
     * algorithm requires an ordering structure, which is passed to this
     * function via its template parameter. For a breadth-first-search
     * fill, that structure is a Queue, for a depth-first-search, that
     * structure is a Stack. To begin the algorithm, you simply place the
     * given point in the ordering structure, marking it processed
     * (the way you mark it is a design decision you'll make yourself).
     * We have a choice to either change the color, if appropriate, when we
     * add the point to the OS, or when we take it off. In our test cases,
     * we have assumed that you will change the color when a point is added
     * to the structure.
     * Until the structure is empty, you do the following:
     *
     * 1.     Remove a point from the ordering structure, and then...
     *
     *        1.    add its unprocessed neighbors whose color values are
     *              within (or equal to) tolerance distance from the center,
     *              to the ordering structure, and
     *              mark them as processed.
     *        2.    if it is an appropriate frame, send the current PNG to the
     *              animation (as described below).
     * 2.     When implementing your breadth-first-search and
     *        depth-first-search fills, you will need to explore neighboring
     *        pixels in some order.
     *
     *        While the order in which you examine neighbors does not matter
     *        for a proper fill, you must use the same order as we do for
     *        your animations to come out like ours! The order you should put
     *        neighboring pixels **ONTO** the queue or stack is as follows:
     *        **RIGHT(+x), DOWN(+y), LEFT(-x), UP(-y). IMPORTANT NOTE: *UP*
     *        here means towards the top of the image, so since an image has
     *        smaller y coordinates at the top, this is in the *negative y*
     *        direction. Similarly, *DOWN* means in the *positive y*
     *        direction.** To reiterate, when you are exploring (filling out)
     *        from a given pixel, you must first try to fill the pixel to
     *        it's RIGHT, then the one DOWN from it, then to the LEFT and
     *        finally UP. If you do them in a different order, your fill may
     *        still work correctly, but your animations will be different
     *        from the grading scripts!
     * 3.     For every k pixels filled, **starting at the kth pixel**, you
     *        must add a frame to the animation, where k = frameFreq.
     *
     *        For example, if frameFreq is 4, then after the 4th pixel has
     *        been filled you should add a frame to the animation, then again
     *        after the 8th pixel, etc.  You must only add frames for the
     *        number of pixels that have been filled, not the number that
     *        have been checked. So if frameFreq is set to 1, a pixel should
     *        be filled every frame.
     * 4.     Finally, as you leave the function, send one last frame to the
     *        animation. This frame will be the final result of the fill, and
     *        it will be the one we test against.
     */

}
