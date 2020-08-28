#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace std;
using namespace cv;

Mat img; Mat templ; Mat result;

int match_method = 0;

void MatchingMethod(int id, void*){

    String Fish_arr[3] = {"Eye", "Fin", "Tail"};
    String showText = Fish_arr[id];

    int result_cols = img.cols - templ.cols + 1;
    int result_rows = img.rows - templ.rows + 1;

    result.create(result_rows, result_cols, CV_32FC1);
    matchTemplate(img, templ, result, match_method);

    normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat());
    double minVal; double maxVal; Point minLoc; Point maxLoc;
    Point matchLoc;

    minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());
    matchLoc = minLoc;

    rectangle(img, matchLoc, Point(matchLoc.x + templ.cols, matchLoc.y + templ.rows), Scalar(0, 0, 0), 2, 8, 0);
    //rectangle(result, matchLoc, Point(matchLoc.x + templ.cols, matchLoc.y + templ.rows), Scalar(0, 255, 0), 2, 8, 0);

    putText(img, showText, Point(matchLoc.x + templ.cols - 40, matchLoc.y + templ.rows - 30), FONT_HERSHEY_PLAIN, 1.25, Scalar(0, 0, 255), 2.5);

    return;
}

int main()
{
    int i = 0;
    String Add_fish[3] = {"C:\\Users\\Ford\\Desktop\\Signal\\Template_Tracker\\Happy_eye.png",
                          "C:\\Users\\Ford\\Desktop\\Signal\\Template_Tracker\\Happy_back.png",
                          "C:\\Users\\Ford\\Desktop\\Signal\\Template_Tracker\\Happy_tail.png" };
    
    img = imread("C:\\opencv\\sources\\samples\\data\\HappyFish.jpg", IMREAD_COLOR);

    for (i = 0; i < 3; i++) {
        templ = imread(Add_fish[i], IMREAD_COLOR);
        MatchingMethod(i, 0);
    }

    namedWindow("Img", WINDOW_AUTOSIZE);
    //namedWindow("Result", WINDOW_AUTOSIZE);

    imshow("Img", img);
    
    waitKey(0);
    return EXIT_SUCCESS;
}
