#include "StudentPreProcessing.h"
#include <iostream>
#include "ImageIO.h"
#include "IntensityImagePrivate.h"
#include "Mask.h"



IntensityImage * StudentPreProcessing::stepToIntensityImage(const RGBImage &image) const {
	return nullptr;
}

IntensityImage * StudentPreProcessing::stepScaleImage(const IntensityImage &image) const {
	return nullptr;
}

IntensityImage * StudentPreProcessing::stepEdgeDetection(const IntensityImage &image) const {
	//std::vector<std::vector<int>> testMask = { {1,1,1},{1,2,1},{1,1,1} };
	ImageIO::isInDebugMode = true;
	//Mask guisianFilter({ {2,4,5, 4, 2},{4, 9,12, 9, 4},{5, 12, 15, 12, 5}, {4, 9, 12, 9, 4}, {2, 4, 5, 4, 2} }, 115);
	//Mask guisianFilter({ {1,1,1},{1,1,1},{1,1,1} }, 0);
	//Mask guisianFilter({ {0,0,0},{0,1,1},{0,0,0} }, 2);
	Mask guisianFilter({ {1,2,1},{2,4,2},{1,2,1} }, 16);
	Mask edgeDetection({ {0,1,0},{1,-4,1},{0,1,0} }, 9);
	//ImageIO::showImage(image);
	IntensityImagePrivate newImage = IntensityImagePrivate(image.getWidth(), image.getHeight());
	IntensityImagePrivate newImage2 = IntensityImagePrivate(image.getWidth(), image.getHeight());
	guisianFilter.apply(image, newImage);
	//edgeDetection.apply(image, newImage);
	edgeDetection.apply(newImage, newImage2);
	guisianFilter.apply(image, newImage);
	std::cout << "EdgeDetection\n";
	ImageIO::showImage(newImage);
	ImageIO::showImage(newImage2);
	return nullptr;
}


IntensityImage * StudentPreProcessing::stepThresholding(const IntensityImage &image) const {
	std::cout << "Thresholding\n";
	return nullptr;
}