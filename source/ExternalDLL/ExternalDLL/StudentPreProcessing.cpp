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
	//ImageIO::isInDebugMode = true;
	GaussianFilter filter(1.5, 9);
	Mask gaussianFilter(filter.getGaussianFilter(20));
	Mask edgeDetection({ {0,0,0,1,1,1,0,0,0},{0,0,0,1,1,1,0,0,0} ,{0,0,0,1,1,1,0,0,0} ,{1,1,1,-4,-4,-4,1,1,1},{1,1,1,-4,-4,-4,1,1,1},{1,1,1,-4,-4,-4,1,1,1},{0,0,0,1,1,1,0,0,0},{0,0,0,1,1,1,0,0,0},{0,0,0,1,1,1,0,0,0} }, 9);
	//Mask edgeDetection({ {1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1} ,{1,1,1,1,1,1,1,1,1} ,{1,1,1,-8,-8,-8,1,1,1},{1,1,1,-8,-8,-8,1,1,1},{1,1,1,-8,-8,-8,1,1,1},{1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1} }, 18);
	
	IntensityImage *newImage = ImageFactory::newIntensityImage(image.getWidth(), image.getHeight());
	IntensityImage *newImage2 = ImageFactory::newIntensityImage(image.getWidth(), image.getHeight());
	gaussianFilter.apply(image, *newImage);
	edgeDetection.apply(*newImage, *newImage2);

	return newImage2;
}


IntensityImage * StudentPreProcessing::stepThresholding(const IntensityImage &image) const {
	IntensityImage *newImage = ImageFactory::newIntensityImage(image.getWidth(), image.getHeight());
	float t = 90;
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