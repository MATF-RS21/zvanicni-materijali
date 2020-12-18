#include <filesystem>

namespace fs = std::filesystem;

#include <stb_image.h>
#include <stb_image_write.h>

#include "Image.h"
#include "FileNotFoundException.h"

Image::Image()
	: data_(nullptr)
	, width_(0)
	, height_(0)
	, numOfChannels_(0)
{}

Image::~Image()
{
	DeInit();
}

void Image::LoadImageFromFile(const std::string &filename) {
	DeInit();
	CheckIfFilenameExists(filename);
	data_ = stbi_load(filename.c_str(), &width_, &height_, &numOfChannels_, 1);
}

void Image::SaveBlackAndWhiteImageToFile(const std::string &outputFilename) const {
	if (!data_) {
		return;
	}
	stbi_write_jpg(outputFilename.c_str(), width_, height_, 1, data_, 100);
}

void Image::DeInit() const
{
	if (data_) {
		free(data_);
	}
}

void Image::CheckIfFilenameExists(const std::string &filename) const
{
	if (!fs::exists(filename))
	{
		throw FileNotFoundException("The file you entered does not exist");
	}
}

