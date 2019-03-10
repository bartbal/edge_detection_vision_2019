#ifndef STUDENT_GAUSSIAN_HPP
#define STUDENT_GAUSSIAN_HPP
#include <cmath>
#include <vector>

class GaussianFilter {
private:
	const double PI = 3.14159265359;
	double sigma;
	double factor;
	double bottom;
	int size;
	int k;

	double generateWeight(int i, int j);
public:
	GaussianFilter(double sigma, int maskSize) :
		sigma(sigma), size(maskSize)
	{
		factor = 1.0 / (2.0 * PI * sigma * sigma);
		k = (size - 1) / 2;
		bottom = 2.0 * sigma * sigma;
	}
	std::vector<std::vector<int>> getGaussianFilter(int maxGaussianValue);
};

#endif // STUDENT_GAUSSIAN_HPP