// Lab04-Thresholding.cpp

// Thresholding is the simplest segmentation method
// Application example: Separate out regions of an image corresponding to objects which we want to analyze.
// This separation is based on the variation of intensity between the object pixels and the background pixels.
// If pixel value is greater than a threshold value, 
// it is assigned one value (may be white), else it is assigned another value (may be black)


#include "stdafx.h"
#include <opencv2\core.hpp>
#include <opencv2\imgcodecs.hpp>
#include <opencv2\highgui.hpp>
#include <opencv2\imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

/// Test 1: Binary threshold inverted (line 23-68)
/// Test 2: Detect the color from the different color space using Thresholding(line 70-168)

/*
/// Test 1: Binary threshold inverted
/// We expect that the pixels brighter than the thresh will turn dark, which is what actually happens

int threshold_value = 0;
int threshold_type = 3;
int const max_value = 255;
int const max_type = 4;
int const max_binary_value = 255;
Mat src, src_gray, dst;
const char* window_name = "Threshold Demo";

const char* trackbar_type = "Type: \n 0: Binary \n 1: Binary Inverted \n 2: Truncate \n 3: To Zero \n 4: To Zero Inverted";
const char* trackbar_value = "Value";

static void Threshold_Demo(int, void*)
{
	// 0: Binary 1: Binary Inverted 	 2: Threshold Truncated  	 3: Threshold to Zero  	 4: Threshold to Zero Inverted
	threshold(src_gray, dst, threshold_value, max_binary_value, threshold_type);
	imshow(window_name, dst);
}

int _tmain(int argc, char** argv)
{
	String imageName("D:\\opencv\\sources\\samples\\data\\stuff.jpg"); // by default
	src = imread(imageName, IMREAD_COLOR); // Load an image

	cvtColor(src, src_gray, COLOR_BGR2GRAY); // Convert the image to Gray

	namedWindow(window_name, WINDOW_AUTOSIZE); // Create a window to display results

	createTrackbar(trackbar_type,
		window_name, &threshold_type,
		max_type, Threshold_Demo); // Create Trackbar to choose type of Threshold

	createTrackbar(trackbar_value,
		window_name, &threshold_value,
		max_value, Threshold_Demo); // Create Trackbar to choose Threshold value

	
	Threshold_Demo(0, 0); // Call the function to initialize

	waitKey();
	return 0;
}
*/

/*
// Test 2: Detect the color from the different color space using Thresholding
int main(int argc, char* argv[])
{
	Mat HappyFish = imread("D:\\opencv\\sources\\samples\\data\\HappyFish.jpg");
	Mat HappyFishLAB;
	Mat HappyFishHSV;
	Mat HappyFishYCB;
	namedWindow("HappyFish");
	imshow("HappyFish", HappyFish);

	// Convert img into different color spaces and see what new information do the different channels of each color space provide us

	// 1: BRG to Lab
	// BRG is additive colorspace where colors are obtained by a linear combination of Red, Green, and Blue values.
	// Lab color space has three components: L(Lightness), a(ranging from Green to Magenta), and b(ranging from Blue to Yellow).
	cvtColor(HappyFish, HappyFishLAB, COLOR_BGR2Lab);
	namedWindow("HappyFishLAB");
	imshow("HappyFishLAB", HappyFishLAB);

	// 2: BRG to HSV
	// HSV color space has the following three components: 
	// H – Hue (Dominant Wavelength), S – Saturation (Purity/shades of the color), and V – Value (Intensity)
	cvtColor(HappyFish, HappyFishHSV, COLOR_BGR2HSV);
	namedWindow("HappyFishHSV");
	imshow("HappyFishHSV", HappyFishHSV);

	// 3: BRG to YCrCb
	// YCrCb color space is derived from the RGB color space and has the following three compoenents:
	// Y – Luminance or Luma component obtained from RGB after gamma correction.
	// Cr = R – Y ( how far is the red component from Luma ), and 
	// Cb = B – Y ( how far is the blue component from Luma ).
	cvtColor(HappyFish, HappyFishYCB, COLOR_BGR2YCrCb);
	namedWindow("HappyFishYCB");
	imshow("HappyFishYCB", HappyFishYCB);

	//// Now that we have got some idea about the different color spaces, 
	//// lets first try to use them to detect the Green color from the HappyFish

	//// Test 4: Color Segmentation
	//// Finding the mask of green pixels from several types of color
	//// Step 1: Get the color values for a particular color
	Vec3b bgrPixel(40, 158, 16); //Green Color

	// Create Mat object from vector since cvtColor accepts a Mat object
	Mat3b bgr(bgrPixel);

	//Convert pixel values to other color spaces.
	Mat3b hsv, ycb, lab;
	cvtColor(bgr, ycb, COLOR_BGR2YCrCb);
	cvtColor(bgr, hsv, COLOR_BGR2HSV);
	cvtColor(bgr, lab, COLOR_BGR2Lab);

	//Get back the vector from Mat
	Vec3b hsvPixel(hsv.at<Vec3b>(0, 0));
	Vec3b ycbPixel(ycb.at<Vec3b>(0, 0));
	Vec3b labPixel(lab.at<Vec3b>(0, 0));

	//// Step 2 : Applying threshold for segmentation
	int thresh = 50; // threshold value

	Scalar minBGR = Scalar(bgrPixel.val[0] - thresh, bgrPixel.val[1] - thresh, bgrPixel.val[2] - thresh);
	Scalar maxBGR = Scalar(bgrPixel.val[0] + thresh, bgrPixel.val[1] + thresh, bgrPixel.val[2] + thresh);

	Mat maskBGR, resultBGR;
	inRange(HappyFish, minBGR, maxBGR, maskBGR);
	bitwise_and(HappyFish, HappyFish, resultBGR, maskBGR);

	Scalar minHSV = Scalar(hsvPixel.val[0] - thresh, hsvPixel.val[1] - thresh, hsvPixel.val[2] - thresh);
	Scalar maxHSV = Scalar(hsvPixel.val[0] + thresh, hsvPixel.val[1] + thresh, hsvPixel.val[2] + thresh);

	Mat maskHSV, resultHSV;
	inRange(HappyFishHSV, minHSV, maxHSV, maskHSV);
	bitwise_and(HappyFishHSV, HappyFishHSV, resultHSV, maskHSV);

	Scalar minYCB = Scalar(ycbPixel.val[0] - thresh, ycbPixel.val[1] - thresh, ycbPixel.val[2] - thresh);
	Scalar maxYCB = Scalar(ycbPixel.val[0] + thresh, ycbPixel.val[1] + thresh, ycbPixel.val[2] + thresh);

	Mat maskYCB, resultYCB;
	inRange(HappyFishYCB, minYCB, maxYCB, maskYCB);
	bitwise_and(HappyFishYCB, HappyFishYCB, resultYCB, maskYCB);

	Scalar minLAB = Scalar(labPixel.val[0] - thresh, labPixel.val[1] - thresh, labPixel.val[2] - thresh);
	Scalar maxLAB = Scalar(labPixel.val[0] + thresh, labPixel.val[1] + thresh, labPixel.val[2] + thresh);

	Mat maskLAB, resultLAB;
	inRange(HappyFishLAB, minLAB, maxLAB, maskLAB);
	bitwise_and(HappyFishLAB, HappyFishLAB, resultLAB, maskLAB);

	// Result of green color masking using thredshold
	imshow("Result BGR", resultBGR);
	imshow("Result HSV", resultHSV);
	imshow("Result YCB", resultYCB);
	imshow("Output LAB", resultLAB);
	waitKey();

	return 0;
}
*/
