// OpenRaw
// Command Line Raw Image Viewer
// Supports 16 bit, unsigned, single-channel images 16UC1
// Using OpenCV3
//
// By Shailendra Paliwal
// Februrary, 2018

#include "stdafx.h"
#include <opencv2/highgui/highgui.hpp> 
#include <opencv2/imgproc/imgproc.hpp>  
#include <opencv2/core/core.hpp>  
#include <iostream>

#define IMAGE_WIDTH	576
#define IMAGE_HEIGHT 768

using namespace cv;

int main(int argc, char* argv[])
{
	Mat img;
	FILE *stream = NULL;
	uint16_t *imagedata = NULL;
	int framesize = IMAGE_WIDTH * IMAGE_HEIGHT;

	// get filename from command-line arguments
	const char *filename;
	if (argc >= 2)
		filename = argv[1];
	else
	{
		std::cout << "usage: "<< argv[0] << " filepath\n";
		return 2;
	}

	// open raw binary image
	stream = fopen(filename, "rb");
	if (stream == NULL) {
		std::cout << "could not open file, exiting\n";
		return 1;
	}
	else std::cout << "file opened!\n";

	// memory allocation for binary image data buffer.
	imagedata = (uint16_t*)malloc(sizeof(uint16_t) * framesize);

	// read image data and store in buffer.
	fread(imagedata, sizeof(uint16_t), framesize, stream);

	// create Opencv mat structure for image dimension. For 16 bit bayer, type should be CV_16UC1.
	img.create(IMAGE_HEIGHT, IMAGE_WIDTH, CV_16UC1);

	// copy buffer data to Mat
	memcpy(img.data, imagedata, framesize);

	// clean up
	free(imagedata);
	fclose(stream);

	// show image
	namedWindow("image", CV_WINDOW_AUTOSIZE);
	imshow("image", img);
	waitKey(0);

    return 0;
}

