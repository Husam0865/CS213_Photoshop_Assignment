#include <iostream>
#include "Image_Class.h"
using namespace std;

void lightenDarkenFilter(Image &image, bool lighten, int amount)
{
    for (int i = 0; i < image.width; ++i)
    {
        for (int j = 0; j < image.height; ++j)
        {
            for (int k = 0; k < 3; ++k)
            {
                int newValue;
                if (lighten == true)
                {
                    newValue = image(i, j, k) + amount;
                }
                else
                {
                    newValue = image(i, j, k) - amount;
                }

                if (newValue > 255)
                {
                    newValue = 255;
                }
                if (newValue < 0)
                {
                    newValue = 0;
                }

                image(i, j, k) = newValue;
            }
        }
    }
}

void filterEdgeDetection(Image &image)
{
    for (int i = 0; i < image.width; ++i)
    {
        for (int j = 0; j < image.height; ++j)
        {
            unsigned int avg = (image(i, j, 0) + image(i, j, 1) + image(i, j, 2)) / 3;
            image(i, j, 0) = avg;
            image(i, j, 1) = avg;
            image(i, j, 2) = avg;
        }
    }

    Image temp = image;

    for (int i = 0; i < image.width - 1; ++i)
    {
        for (int j = 0; j < image.height - 1; ++j)
        {
            int diffX = abs(temp(i, j, 0) - temp(i + 1, j, 0));
            int diffY = abs(temp(i, j, 0) - temp(i, j + 1, 0));
            int diff = diffX + diffY;

            if (diff > 30)
            {
                image(i, j, 0) = 0;
                image(i, j, 1) = 0;
                image(i, j, 2) = 0;
            }
            else
            {
                image(i, j, 0) = 255;
                image(i, j, 1) = 255;
                image(i, j, 2) = 255;
            }
        }
    }
}

void PurpleFilter(Image &image)
{
    for (int i = 0; i < image.width; ++i)
    {
        for (int j = 0; j < image.height; ++j)
        {
            int r = image(i, j, 0) + 70;
            int g = image(i, j, 1) - 50;
            int b = image(i, j, 2) + 80;

            if (r > 255)
            {
                r = 255;
            }
            if (g < 0)
            {
                g = 0;
            }
            if (b > 255)
            {
                b = 255;
            }

            image(i, j, 0) = r;
            image(i, j, 1) = g;
            image(i, j, 2) = b;
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
        cout << "2. Lighten / Darken Filter\n";
        cout << "3. Edge Detection Filter\n";
        cout << "4. Medium Purple Filter\n";
        cout << "5. Save Image\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        string filename;

        if (choice == 1)
        {
            cout << "Enter image file name: ";
            cin >> filename;
            image.loadNewImage(filename);
            isLoaded = true;
            cout << "Image loaded successfully!\n";
        }
        else if (choice == 2)
        {
            if (isLoaded == false)
            {
                cout << "Please load an image first!\n";
            }
            else
            {
                int subChoice;
                int amount;
                cout << "1. Lighten\n2. Darken\nEnter your choice: ";
                cin >> subChoice;
                cout << "Enter amount (50, 100): ";
                cin >> amount;

                if (subChoice == 1)
                {
                    lightenDarkenFilter(image, true, amount);
                }
                else
                {
                    lightenDarkenFilter(image, false, amount);
                }

                isModified = true;
                isSaved = false;
                cout << "Lighten/Darken filter applied!\n";
            }
        }
        else if (choice == 3)
        {
            if (isLoaded == false)
            {
                cout << "Please load an image first!\n";
            }
            else
            {
                filterEdgeDetection(image);
                isModified = true;
                isSaved = false;
                cout << "Edge Detection filter applied!\n";
            }
        }
        else if (choice == 4)
        {
            if (isLoaded == false)
            {
                cout << "Please load an image first!\n";
            }
            else
            {
                PurpleFilter(image);
                isModified = true;
                isSaved = false;
                cout << "Purple filter applied!\n";
            }
        }
        else if (choice == 5)
        {
            if (isModified == false)
            {
                cout << "No changes to save!\n";
            }
            else
            {
                cout << "Enter output file name: ";
                cin >> filename;
                image.saveImage(filename);
                isSaved = true;
                cout << "Image saved successfully!\n";
            }
        }
    } while (choice != 6);

    return 0;
}
