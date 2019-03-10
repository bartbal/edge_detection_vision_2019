#include "gaussian.hpp"

//Generates and returns a weight value.
double GaussianFilter::generateWeight(int i, int j) {
	double top = std::pow((i - (k + 1)), 2) + std::pow((j - (k + 1)), 2);
	return factor * std::exp2(-(top) / (bottom));
}

//Returns a scaled Gaussian Kernal. maxGaussianValue is the top of the Gaussian.
std::vector<std::vector<int>> GaussianFilter::getGaussianFilter(int maxGaussianValue) {
	int midIndex = (size - 1) / 2;
	double midValue = generateWeight(midIndex + 1, midIndex + 1);
	double scale = maxGaussianValue / midValue;
	std::vector<std::vector<int>> tmp = {};
	for (int i = 1; i < size + 1; i++) {
		tmp.push_back(std::vector<int>{});
		for (int j = 1; j < size + 1; j++) {
			if (i == midIndex + 1 && j == midIndex + 1) {
				tmp[midIndex].push_back(static_cast<int>(midValue*scale));
			}
			else {
				tmp[i - 1].push_back(static_cast<int>(generateWeight(i, j)*scale));
			}
		}
	}
	return tmp;
}