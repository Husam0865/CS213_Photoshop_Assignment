#include <iostream>
#include <string>
#include <stdexcept>
#include "Image_Class.h"

using namespace std;

// filter 2
void filterBlackAndWhite(Image &image)
{
    int Half = 128;
    for (int i = 0; i < image.width; ++i)
    {
        for (int j = 0; j < image.height; ++j)
        {
            unsigned int avg = (image(i, j, 0) + image(i, j, 1) + image(i, j, 2)) / 3;
            if (avg > Half)
            {
                image(i, j, 0) = 255;
                image(i, j, 1) = 255;
                image(i, j, 2) = 255;
            }
            else
            {
                image(i, j, 0) = 0;
                image(i, j, 1) = 0;
                image(i, j, 2) = 0;
            }
        }
    }
}

// filter 5
void filterFlipImage(Image &image)
{
    for (int i = 0; i < image.height; i++)
    {
        for (int j = 0; j < image.width / 2; j++)
        {
            int ref = image.width - 1 - j;
            unsigned char r1 = image(j, i, 0);
            unsigned char g1 = image(j, i, 1);
            unsigned char b1 = image(j, i, 2);
            unsigned char r2 = image(ref, i, 0);
            unsigned char g2 = image(ref, i, 1);
            unsigned char b2 = image(ref, i, 2);
            image(j, i, 0) = r2;
            image(j, i, 1) = g2;
            image(j, i, 2) = b2;
            image(ref, i, 0) = r1;
            image(ref, i, 1) = g1;
            image(ref, i, 2) = b1;
        }
    }
}

// Filter 8
void filterCropImage(Image &image, int x, int y, int newWidth, int newHeight, Image &cropImage)
{
    for (int i = 0; i < newWidth; i++)
    {
        for (int j = 0; j < newHeight; j++)
        {
            int sourceX = x + i;
            int sourceY = y + j;
            if (sourceX >= 0 && sourceX < image.width && sourceY >= 0 && sourceY < image.height)
            {
                unsigned char r = image(sourceX, sourceY, 0);
                unsigned char g = image(sourceX, sourceY, 1);
                unsigned char b = image(sourceX, sourceY, 2);
                cropImage(i, j, 0) = r;
                cropImage(i, j, 1) = g;
                cropImage(i, j, 2) = b;
            }
        }
    }
}

// Filter 11
void filterResizingImage(Image &image, Image &newImage)
{
    int oldWidth = image.width;
    int oldHeight = image.height;
    int newWidth = newImage.width;
    int newHeight = newImage.height;
    float x_ratio = static_cast<float>(oldWidth) / newWidth;
    float y_ratio = static_cast<float>(oldHeight) / newHeight;
    for (int y = 0; y < newHeight; y++)
    {
        for (int x = 0; x < newWidth; x++)
        {
            int sourceX = static_cast<int>(x * x_ratio);
            int sourceY = static_cast<int>(y * y_ratio);
            newImage(x, y, 0) = image(sourceX, sourceY, 0);
            newImage(x, y, 1) = image(sourceX, sourceY, 1);
            newImage(x, y, 2) = image(sourceX, sourceY, 2);
        }
    }
}

// Filter 5: Infrared
void infraredFilter(Image &image)
{
    for (int i = 0; i < image.width; ++i)
    {
        for (int j = 0; j < image.height; ++j)
        {
            unsigned char r = image(i, j, 0);
            unsigned char g = image(i, j, 1);
            unsigned char b = image(i, j, 2);
            unsigned int avg = (r + g + b) / 3;
            image(i, j, 0) = 255;
            image(i, j, 1) = (unsigned char)(255 - avg);
            image(i, j, 2) = (unsigned char)(255 - avg);
        }
    }
}

int main()
{
    Image image;
    bool isLoaded = false;
    bool isModified = false;
    int choice;

    while (true)
    {
        cout << "\n====== Image Processing Menu ======\n";
        cout << "1. Load Image\n";
        cout << "2. Apply Black & White Filter\n";
        cout << "3. Apply Flip Filter\n";
        cout << "4. Apply Crop Filter\n";
        cout << "5. Apply Resizing Filter\n";
        cout << "6. Apply Infrared Filter\n";
        cout << "7. Save Image\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        string filename;

        switch (choice)
        {
        case 1:
            cout << "Enter the image filename: ";
            cin >> filename;
            if (image.loadNewImage(filename))
            {
                isLoaded = true;
                isModified = false;
                cout << "Image loaded successfully!\n";
            }
            else
            {
                cout << "Failed to load image.\n";
            }
            break;

        case 2:
            if (!isLoaded)
            {
                cout << "Please load an image first!\n";
            }
            else
            {
                filterBlackAndWhite(image);
                isModified = true;
                cout << "Black & White filter applied!\n";
            }
            break;

        case 3:
            if (!isLoaded)
            {
                cout << "Please load an image first!\n";
            }
            else
            {
                filterFlipImage(image);
                isModified = true;
                cout << "Flip filter applied!\n";
            }
            break;

        case 4:
            if (!isLoaded)
            {
                cout << "Please load an image first!\n";
            }
            else
            {
                int x, y, w, h;
                cout << "Enter crop details (X Y Width Height): ";
                cin >> x >> y >> w >> h;
                if (x < 0 || y < 0 || w <= 0 || h <= 0 || (x + w) > image.width || (y + h) > image.height)
                {
                    cout << "Invalid crop dimensions.\n";
                }
                else
                {
                    Image croppedImage(w, h);
                    filterCropImage(image, x, y, w, h, croppedImage);
                    image = croppedImage;
                    isModified = true;
                    cout << "Crop filter applied!\n";
                }
            }
            break;

        case 5:
            if (!isLoaded)
            {
                cout << "Please load an image first!\n";
            }
            else
            {
                int w, h;
                cout << "Enter new dimensions (Width Height): ";
                cin >> w >> h;
                if (w > 0 && h > 0)
                {
                    Image resizedImage(w, h);
                    filterResizingImage(image, resizedImage);
                    image = resizedImage;
                    isModified = true;
                    cout << "Resizing filter applied!\n";
                }
                else
                {
                    cout << "Invalid dimensions.\n";
                }
            }
            break;

        case 6:
            if (!isLoaded)
            {
                cout << "Please load an image first!\n";
            }
            else
            {
                infraredFilter(image);
                isModified = true;
                cout << "Infrared filter applied!\n";
            }
            break;

        case 7:
            if (!isLoaded)
            {
                cout << "Please load an image first!\n";
            }
            else if (!isModified)
            {
                cout << "No changes to save.\n";
            }
            else
            {
                cout << "Enter the filename to save: ";
                cin >> filename;
                if (image.saveImage(filename))
                {
                    isModified = false;
                    cout << "Image saved successfully!\n";
                }
                else
                {
                    cout << "Failed to save image.\n";
                }
            }
            break;

        case 8:
            if (isModified)
            {
                char confirm;
                cout << "You have unsaved changes. Are you sure you want to exit? (y/n): ";
                cin >> confirm;
                if (confirm == 'y' || confirm == 'Y')
                {
                    cout << "Exiting program. Goodbye!\n";
                    return 0;
                }
            }
            else
            {
                cout << "Exiting program. Goodbye!\n";
                return 0;
            }
            break;

        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    }

    return 0;
}