#include "film.h"

/**
 * @brief Film::Film
 */

Film::Film(size_t width_, size_t height_)
{
    // Initialize the width and height of the image
    width  = width_;
    height = height_;

    // Allocate memory for the image matrix
    data = new Vector3D*[height];
    for( size_t i=0; i<height; i++)
    {
        data[i] = new Vector3D[width];
    }

    // Set all values to zero
    clearData();
}

Film::~Film()
{
    // Resease the dynamically-allocated memory for the image data
    for( size_t i=0; i<height; i++)
    {
        delete [] data[i];
    }
    delete [] data;
}

size_t Film::getWidth() const
{
    return width;
}

size_t Film::getHeight() const
{
    return height;
}

Vector3D Film::get3x3Average(size_t w, size_t h) const
{
	Vector3D sum;
	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			sum = sum + getPixelValue(w + i, h + j);
		}
	}

	return sum / 9;
}

Vector3D Film::getAverage(size_t w, size_t h, int size) const
{
	Vector3D sum;
	//as the division is within integers the result is floor of the
	//division that is what we want
	int delta = (size / 2);
	for (int i = -delta; i < delta; i++)
	{
		for (int j = -delta; j < delta; j++)
		{
			sum = sum + getPixelValue(w + i, h + j);
		}
	}

	return sum / (size * size);
}

void Film::applyAverageFilter(unsigned int iterations, int filterSize)
{
	Film auxFilm(width, height);
	Vector3D average;
	bool swap = true;
	int delta = (filterSize / 2);

	for (int iter = 0; iter < iterations; iter++)
	{
		for (int lin = delta; lin < width - delta; lin++)
		{
			for (int col = delta; col < height - delta; col++)
			{
				if (swap)
				{
					average = get3x3Average(col, lin);
					auxFilm.setPixelValue(col, lin, average);
				}
				else
				{
					average = auxFilm.get3x3Average(col, lin);
					setPixelValue(col, lin, average);
				}
			}
		}

		swap = !swap;
	}
}

Vector3D Film::getPixelValue(size_t w, size_t h) const
{
    return data[h][w];
}

void Film::setPixelValue(size_t w, size_t h, Vector3D &value)
{
    data[h][w] = value;
}

void Film::clearData()
{
    Vector3D zero;

    for(size_t h=0; h<height; h++)
    {
        for(size_t w=0; w<width; w++)
        {
            setPixelValue(w, h, zero);
        }
    }
}

int Film::save()
{
    return BitMap::save(data, width, height);
}

void Film::averageWith(const Film& f)
{
	for (size_t h = 0; h<height; h++)
	{
		for (size_t w = 0; w<width; w++)
		{
			Vector3D currentPixel = getPixelValue(w, h);
			Vector3D otherPixel = f.getPixelValue(w, h);
			setPixelValue(w, h, (currentPixel + otherPixel));
		}
	}
}

int Film::save(const std::string& s)
{
	return BitMap::save(data, width, height, s);
}
