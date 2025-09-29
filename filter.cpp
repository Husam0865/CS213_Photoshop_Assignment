#include <iostream>
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
void filterFlipImage(Image &Image)
{
    for (int i = 0; i < Image.height; i++)
    {
        for (int j = 0; j < Image.width / 2; j++)
        {
            int ref = Image.width - 1 - j;

            unsigned char r1 = Image(j, i, 0);
            unsigned char g1 = Image(j, i, 1);
            unsigned char b1 = Image(j, i, 2);

            unsigned char r2 = Image(ref, i, 0);
            unsigned char g2 = Image(ref, i, 1);
            unsigned char b2 = Image(ref, i, 2);

            Image(j, i, 0) = r2;
            Image(j, i, 1) = g2;
            Image(j, i, 2) = b2;

            Image(ref, i, 0) = r1;
            Image(ref, i, 1) = g1;
            Image(ref, i, 2) = b1;
        }
    }
}

int main()
{
    Image image;
    bool isLoaded = false;
    bool isModified = false;
    bool isSaved = false;

    int choice;
    do
    {
        cout << "\n====== Image Processing Menu ======\n";
        cout << "1. Load Image\n";
        cout << "2. Apply Black & White Image (Filter 2)\n";
        cout << "3. Apply Flip Image (Filter 5)\n";
        cout << "4. Save Image\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        string filename;

        switch (choice)
        {
        case 2:
            if (!isLoaded)
            {
                cout << "Please load an image first (Option 1)!\n";
                break;
            }
            filterBlackAndWhite(image);
            isModified = true;
            isSaved = false;
            cout << "Black & White filter applied!\n";
            break;

        case 3:
            if (!isLoaded)
            {
                cout << "Please load an image first (Option 1)!\n";
                break;
            }
            filterFlipImage(image);
            isModified = true;
            isSaved = false;
            cout << "Flip filter applied!\n";
            break;
        }
    } while (choice != 5);

    return 0;
}
