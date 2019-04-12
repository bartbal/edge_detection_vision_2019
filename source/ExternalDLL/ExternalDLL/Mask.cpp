#include "Mask.h"



Mask::Mask(std::vector<std::vector<int>> mask, int devider) :
	m_mask(mask),
	m_devider(devider)
{}



Mask::~Mask()
{
}

/// \brief   
/// Get the height of the mask
/// \details
/// Returns the height of the mask
int Mask::getHeight() {
	return m_mask.size();
}

/// \brief   
/// Get the with of the mask
/// \details
/// Returns the with of the mask
int Mask::getWidth() {
	if (getHeight() != 0) {
		return m_mask[0].size();
	}
	return 0;
}

/// \brief   
/// Get the intesnity of a pixel
/// \details
/// This function returns the intensity of a pixel, 
/// if the given coordinat is not on the images it returns NULL
Intensity Mask::getPixel(const IntensityImage &originalImage, int x, int y, int orgHeight, int orgWidth) {
	if(
		x < 0 
		|| 
		y < 0
		||
		x > orgWidth
		||
		y > orgHeight
	) {
		return NULL;
	}

	return originalImage.getPixel(x, y);
}

/// \brief   
/// Get the sum of the mask
/// \details
/// Calculate the sum of the mask
int Mask::getSum() {
	int sum = 0;
	for (int i = 0; i < getHeight(); i++) {//for mask y
		for (int j = 0; j < getWidth(); j++) {//for mask x
			sum += m_mask[j][i];
		}
	}
	return sum;
}

/// \brief   
/// Apply mask on a pixel
/// \details
/// This function calculates the intensity of a given pixel with the mask
Intensity Mask::maskPixel(const IntensityImage &originalImage, int x, int y, int orgHeight, int orgWidth) {
	int start_y = y - ((getHeight() - 1) / 2);
	int start_x = x - ((getWidth() - 1) / 2);
	int sum = getSum();
	int newPixel = 0;

	for (int i = 0; i < getHeight(); i++) {//for mask y
		for (int j = 0; j < getWidth(); j++) {//for mask x
			Intensity orgPxl = getPixel(originalImage, start_x + j, start_y + i, orgHeight, orgWidth);
			if (orgPxl == NULL) {
				continue;
			}
			if (m_devider != 0) {
				newPixel += (orgPxl*m_mask[j][i])/ m_devider;
				//if (newPixel < 0) {
				//	newPixel *= -1;
				//}
			} else if (sum <= 1) {
				newPixel += orgPxl * m_mask[j][i];
			}
			else {
				newPixel += (orgPxl*m_mask[j][i]) / sum;
			}
			if (newPixel > 255) {
				newPixel = 255;
			}
			else if (newPixel < 0) {
				newPixel = 0;
			}
		}
	}
	return newPixel;
}

/// \brief   
/// Apply the mask to a new image
/// \details
/// This function gets the mask from the originalImage and saves it in the newImage
void Mask::apply(const IntensityImage &originalImage, IntensityImage &newImage) {
	int orgHeight = originalImage.getHeight();
	int orgWidth = originalImage.getWidth();
	for (int i = 0; i < orgHeight; i++) {
		for (int j = 0; j < orgWidth; j++) {
			newImage.setPixel(j, i, maskPixel(originalImage, j, i, orgHeight, orgWidth));
		}
	}
}