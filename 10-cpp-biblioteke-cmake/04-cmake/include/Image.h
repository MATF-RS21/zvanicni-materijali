#ifndef IMAGE_H
#define IMAGE_H

#include <string>

class Image
{
public:
	Image();
	~Image();

	Image(const Image &other) = delete;
	Image &operator=(const Image &other) = delete;
	Image(Image &&other) = delete;
	Image &operator=(Image &&other) = delete;
	
	void LoadImageFromFile(const std::string &filename);
	void SaveBlackAndWhiteImageToFile(const std::string &outputFilename) const;

private:
	void DeInit() const;
	void CheckIfFilenameExists(const std::string &filename) const;

private:
	unsigned char* data_;
	int width_;
	int height_;
	int numOfChannels_;
};

#endif // IMAGE_H
