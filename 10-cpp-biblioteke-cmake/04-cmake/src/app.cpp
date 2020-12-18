#include <iostream>

#include "Image.h"
#include "FileNotFoundException.h"

int main()
{
	using namespace std;

	string input;

	cout << "Enter the input image file path: ";
	cin >> input;

	Image img;
	try {
		img.LoadImageFromFile(input);
		const auto output = input + "_BW.jpg";
		img.SaveBlackAndWhiteImageToFile(output);
	}
	catch (const FileNotFoundException& e) {
		cout << e.what() << endl;
		exit(EXIT_FAILURE);
	}

	return 0;
}
