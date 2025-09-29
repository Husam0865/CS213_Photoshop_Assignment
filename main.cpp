#include <iostream>
#include "Image_Class.h"
using namespace std;

// filter 3
Image applyInvert(Image image) {
    Image newImage(image.width, image.height);

    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            newImage(i, j, 0) = 255 - image(i, j, 0);
            newImage(i, j, 1) = 255 - image(i, j, 1);
            newImage(i, j, 2) = 255 - image(i, j, 2);
        }
    }

    return newImage;
}

// filter 12
Image applyBlur(Image image) {
    int BLUR = 20;
    Image tempImage(image.width, image.height);
    Image newImage(image.width, image.height);

    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            int sumR = 0, sumG = 0, sumB = 0;
            int count = 0;

            for (int i2 = -BLUR; i2 <= BLUR; i2++) {
                int x = i + i2;
                if (x >= 0 && x < image.width) {
                    sumR += image(x, j, 0);
                    sumG += image(x, j, 1);
                    sumB += image(x, j, 2);
                    count++;
                }
            }

            tempImage(i, j, 0) = sumR / count;
            tempImage(i, j, 1) = sumG / count;
            tempImage(i, j, 2) = sumB / count;
        }
    }

    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            int sumR = 0, sumG = 0, sumB = 0;
            int count = 0;

            for (int j2 = -BLUR; j2 <= BLUR; j2++) {
                int y = j + j2;
                if (y >= 0 && y < image.height) {
                    sumR += tempImage(i, y, 0);
                    sumG += tempImage(i, y, 1);
                    sumB += tempImage(i, y, 2);
                    count++;
                }
            }

            newImage(i, j, 0) = sumR / count;
            newImage(i, j, 1) = sumG / count;
            newImage(i, j, 2) = sumB / count;
        }
    }

    return newImage;
}

int main() {
    Image image;
    bool isLoaded = false;
    bool isModified = false;
    bool isSaved = false;

    int choice;
    do {
        cout << "\n====== Image Processing Menu ======\n";
        cout << "1. Load Image\n";
        cout << "2. Apply Invert Image (Filter 3)\n";
        cout << "3. Apply Blur (Filter 12)\n";
        cout << "8. Save Image\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        string filename;

        switch (choice) {
            case 1:
                cout << "Enter image filename: ";
                cin >> filename;
                image = Image(filename);
                isLoaded = true;
                isModified = false;
                isSaved = false;
                cout << "Image loaded successfully!\n";
                break;

            case 2:
                if (!isLoaded) {
                    cout << "Please load an image first (Option 1)!\n";
                    break;
                }
                image = applyInvert(image);
                isModified = true;
                isSaved = false;
                cout << "Invert filter applied!\n";
                break;

            case 3:
                if (!isLoaded) {
                    cout << "Please load an image first (Option 1)!\n";
                    break;
                }
                image = applyBlur(image);
                isModified = true;
                isSaved = false;
                cout << "Blur filter applied!\n";
                break;

            case 8:
                if (!isLoaded) {
                    cout << "Please load an image first (Option 1)!\n";
                    break;
                }
                cout << "Pls enter image name to store new image\n";
                cout << "and specify extension .jpg, .bmp, .png, .tga: ";
                cin >> filename;
                image.saveImage(filename);
                isSaved = true;
                cout << "Image saved!\n";
                system(filename.c_str());
                break;

            case 9:
                if (isModified && !isSaved) {
                    int exit;
                    cout << "You have unsaved changes! Choose an option:\n";
                    cout << "1. Save now\n2. Exit without saving\nAny other number: Cancel\n";
                    cout << "Enter your choice: ";
                    cin >> exit;

                    if (exit == 1) {
                        cout << "Pls enter image name to store new image\n";
                        cout << "and specify extension .jpg, .bmp, .png, .tga: ";
                        cin >> filename;
                        image.saveImage(filename);
                        cout << "Image saved!\n";
                        system(filename.c_str());
                        choice = 9;
                    } else if (exit == 2) {
                        cout << "Exiting without saving...\n";
                        choice = 9;
                    } else {
                        choice = 0;
                    }
                } else {
                    cout << "Exiting...\n";
                }
                break;

            default:
                cout << "Invalid choice! Try again.\n";
                break;
        }

    } while (choice != 9);

    return 0;
}
