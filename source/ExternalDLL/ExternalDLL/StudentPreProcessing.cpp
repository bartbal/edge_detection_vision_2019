#include "StudentPreProcessing.h"
#include <iostream>
#include "ImageIO.h"
#include "IntensityImagePrivate.h"
#include "IntensityImage.h"
#include "gaussian.hpp"
#include "imageFactory.h"
#include "Mask.h"



IntensityImage * StudentPreProcessing::stepToIntensityImage(const RGBImage &image) const {
	return nullptr;
}

IntensityImage * StudentPreProcessing::stepScaleImage(const IntensityImage &image) const {
	return nullptr;
}

IntensityImage * StudentPreProcessing::stepEdgeDetection(const IntensityImage &image) const {
	ImageIO::isInDebugMode = true;
	GaussianFilter filter(1.5, 7);
	//Mask gaussianFilter(filter.getGaussianFilter(30));
	Mask gaussianFilter({ {2,4,5, 4, 2},{4, 9,12, 9, 4},{5, 12, 15, 12, 5}, {4, 9, 12, 9, 4}, {2, 4, 5, 4, 2} });
	//Mask gaussianFilter({ {0,0,0},{0,1,0},{0,0,0} });
	//Mask gaussianFilter({ {1,2,1},{2,4,2},{1,2,1} }, 16);
	//Mask edgeDetection({ {0,1,0},{1,-4,1},{0,1,0} }, 9);
	Mask edgeDetection({ {0,0,0,1,1,1,0,0,0},{0,0,0,1,1,1,0,0,0} ,{0,0,0,1,1,1,0,0,0} ,{1,1,1,-4,-4,-4,1,1,1},{1,1,1,-4,-4,-4,1,1,1},{1,1,1,-4,-4,-4,1,1,1},{0,0,0,1,1,1,0,0,0},{0,0,0,1,1,1,0,0,0},{0,0,0,1,1,1,0,0,0} }, 9);
	
	IntensityImage *newImage = ImageFactory::newIntensityImage(image.getWidth(), image.getHeight());
	IntensityImage *newImage2 = ImageFactory::newIntensityImage(image.getWidth(), image.getHeight());
	gaussianFilter.apply(image, *newImage);
	edgeDetection.apply(*newImage, *newImage2);
	//ImageIO::showImage(*newImage);
	//ImageIO::showImage(*newImage2);
	return newImage2;
}


IntensityImage * StudentPreProcessing::stepThresholding(const IntensityImage &image) const {
	IntensityImage *newImage = ImageFactory::newIntensityImage(image.getWidth(), image.getHeight());
	float t = 100;
	Intensity black = 255;
	Intensity white = 0;
	for (int i = 0; i < image.getHeight(); i++) {//for mask y
		for (int j = 0; j < image.getWidth(); j++) {//for mask x
			if (image.getPixel(j, i) <= t) {
				newImage->setPixel(j, i, white);
			}
			else {
				newImage->setPixel(j, i, black);
			}
		}
	}	
	return newImage;
}