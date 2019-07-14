#include "stats.h"

stats::stats(PNG & im){
  for (int j = 0; j < im.height(); j++) {
    vector<double> tempXrow;
    vector<double> tempYrow;
    vector<double> tempSrow;
    vector<double> tempLrow;
    for (int i = 0; i < im.width(); i++) {
      tempXrow.push_back(sumCalc(sumHueX, tempXrow, cos((im.getPixel(i,j)->h)*(PI/180)), i));
      tempYrow.push_back(sumCalc(sumHueY, tempYrow, sin((im.getPixel(i,j)->h)*(PI/180)), i));
      tempSrow.push_back(sumCalc(sumSat, tempSrow, im.getPixel(i,j)->s, i));
      tempLrow.push_back(sumCalc(sumLum, tempLrow, im.getPixel(i,j)->l, i));
    }
    sumHueX.push_back(tempXrow);
    sumHueY.push_back(tempYrow);
    sumSat.push_back(tempSrow);
    sumLum.push_back(tempLrow);
  }
}

double stats::sumCalc(vector<vector<double>>& sumTable, vector<double>& tempRow, double currCell, int i) {
  if (!tempRow.empty())
    currCell += tempRow.back();
  if (!sumTable.empty())
    currCell += sumTable.back().at(i);
  if (!tempRow.empty() && !sumTable.empty())
    currCell -= sumTable.back().at(i-1);
  return currCell;
}

long stats::rectArea(pair<int,int> ul, pair<int,int> lr){
  return (get<1>(lr)-get<1>(ul)+1)*(get<0>(lr)-get<0>(ul)+1);
}

HSLAPixel stats::getAvg(pair<int,int> ul, pair<int,int> lr){
  double x = (avgCalc(sumHueX,ul,lr));//*(180/PI);
  double y = (avgCalc(sumHueY,ul,lr));//*(180/PI);
  double h = atan2(y,x)*(180/PI);
  if (h < 0)
    h += 360;
  double s = avgCalc(sumSat,ul,lr);
  double l = avgCalc(sumLum,ul,lr);
  return *(new HSLAPixel(h,s,l));
}

double stats::avgCalc(vector<vector<double>>& sumTable, pair<int,int>& ul, pair<int,int>& lr) {
  double LRSum = sumTable.at(get<1>(lr)).at(get<0>(lr));
  double URSum = 0;
  if (get<1>(ul)!=0)
    URSum = sumHueX.at(get<1>(ul)-1).at(get<0>(lr));
  double LLSum  = 0;
  if (get<0>(ul)!=0)
    LLSum = sumHueX.at(get<1>(lr)).at(get<0>(ul)-1);
  double ULSum = 0;
  if (get<1>(ul)!=0 && get<0>(ul)!=0)
    ULSum = sumHueX.at(get<1>(ul)-1).at(get<0>(ul)-1);
  return (LRSum - LLSum - URSum + ULSum)/rectArea(ul,lr);
}

double stats::entropy(pair<int,int> ul, pair<int,int> lr){

    vector<int> distn;

    /* using private member hist, assemble the distribution over the
    *  given rectangle defined by points ul, and lr into variable distn.
    *  You will use distn to compute the entropy over the rectangle.
    *  if any bin in the distn has frequency 0, then do not add that
    *  term to the entropy total. see .h file for more details.
    */

    /* my code includes the following lines:
        if (distn[i] > 0 )
            entropy += ((double) distn[i]/(double) area)
                                    * log2((double) distn[i]/(double) area);
    */

    return  -1;
}
