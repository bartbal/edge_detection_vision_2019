#pragma once
#include "IntensityImage.h"
#include <vector>

class Mask{
private:
	std::vector<std::vector<int>> m_mask;
	int m_devider;

public:
	Mask(std::vector<std::vector<int>> mask, int devider = 0);
	~Mask();

	Intensity getPixel(const IntensityImage &originalImage, int x, int y, int orgHeight, int orgWidth);

	Intensity maskPixel(const IntensityImage &originalImage, int x, int y, int orgHeight, int orgWidth);

	void apply(const IntensityImage &originalImage, IntensityImage &newImage);

	int getHeight();

	int getWidth();

	int Mask::getSum();
}; 

