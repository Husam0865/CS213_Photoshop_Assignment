#include <iostream>
#include "Image_Class.h"

using namespace std;

int main() {
    string filename;

    cout << "Enter the image name (e.g., my_photo.jpg): ";
    cin >> filename;

    Image image(filename);

    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            
            int total_color = 0;

            total_color += image(i, j, 0);
            total_color += image(i, j, 1);
            total_color += image(i, j, 2);
            
            int average_gray = total_color / 3;

            image(i, j, 0) = average_gray;
            image(i, j, 1) = average_gray;
            image(i, j, 2) = average_gray;
        }
    }

    cout << "Enter a new name to save the grayscale image: ";
    cin >> filename;

    image.saveImage(filename);

    cout << "Image saved successfully!" << endl;

    return 0;
}