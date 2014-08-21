//
//  main.cpp
//  LinienErkennungRoboter
//
//  Created by Anna Lepak on 20.08.14.
//  Copyright (c) 2014 Anna. All rights reserved.
//

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv/cv.h"
#include <iostream>

using namespace cv;
using namespace std;



int main(int argc, char** argv)
{
    
    //Datei Laden
    Mat src = imread("/Users/Anna/Downloads/tor2.png", CV_LOAD_IMAGE_UNCHANGED);
    
    //prüfen ob Datei ein Bild ist
    if (src.empty())
    {
        cout << "can not open " << src << endl;
        return -2;
    }
    
    
    
    //Mit Gauss filter verschwimmen lassen
    Mat gauss, cgauss;
    GaussianBlur(src, gauss, Size(7, 7), 0, 0);
    cvtColor(gauss, cgauss, CV_RGB2GRAY);
    
    //Canny-Bild erzeugen
    Mat dst, cdst;
    Canny(gauss, dst, 50, 200, 3);
    cvtColor(dst, cdst, CV_GRAY2BGR);
 
    
    //Linien erkennen und erzeugen
#if 0
    vector<Vec2f> lines;
    HoughLines(dst, lines, 1, CV_PI / 180, 100, 0, 0);
    
    for (size_t i = 0; i < lines.size(); i++)
    {
        float rho = lines[i][0], theta = lines[i][1];
        Point pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a*rho, y0 = b*rho;
        pt1.x = cvRound(x0 + 1000 * (-b));
        pt1.y = cvRound(y0 + 1000 * (a));
        pt2.x = cvRound(x0 - 1000 * (-b));
        pt2.y = cvRound(y0 - 1000 * (a));
        line(cdst, pt1, pt2, Scalar(0, 0, 255), 3, CV_AA);
    }
#else
    //zweite methode linien zu erzeugen, prüfen wie die sich unterscheiden?
    vector<Vec4i> lines;
    HoughLinesP(dst, lines, 1, CV_PI / 180, 50, 50, 10);
    for (size_t i = 0; i < lines.size(); i++)
    {
        Vec4i l = lines[i];
        line(cdst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 3, CV_AA);
    }
    
#endif
    //bilder anzeigen
    imshow("original", src);
    imshow("gauss", cgauss);
    imshow("linienerkennung", cdst);
    
    waitKey(0);
    
    return -1;
}