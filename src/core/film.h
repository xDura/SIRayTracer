#ifndef FILM_H
#define FILM_H

#include "vector3d.h"
#include "bitmap.h"

#include <iostream>


/**
 * @brief The Film class
 */
class Film
{
public:
    // Constructor(s)
    Film(size_t width_, size_t height_);
    Film() = delete;

    // Destructor
    ~Film();

    // Getters
    size_t getWidth() const;
    size_t getHeight() const;
    Vector3D getPixelValue(size_t w, size_t h) const;
	Vector3D get3x3Average(size_t w, size_t h) const;
	Vector3D getAverage(size_t w, size_t h, int size) const;
	void applyAverageFilter(unsigned int iterations, int filterSize);
	void averageWith(const Film& f);

    // Setters
    void setPixelValue(size_t w, size_t h, Vector3D &value);

    // Other functions
    int save();
	int save(const std::string& s);
    void clearData();

private:
    // Image size
    size_t width;
    size_t height;

    // Pointer to image data
    Vector3D **data;
};

#endif // FILM_H
