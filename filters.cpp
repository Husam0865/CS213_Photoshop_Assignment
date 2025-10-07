#include <iostream>
#include "Image_Class.h"
using namespace std;

// filter 1
void GrayscaleFilter(Image &image)
{
    for (int i = 0; i < image.width; ++i)
    {
        for (int j = 0; j < image.height; ++j)
        {
            int total_color = image(i, j, 0) + image(i, j, 1) + image(i, j, 2);
            int average_gray = total_color / 3;
            image(i, j, 0) = image(i, j, 1) = image(i, j, 2) = average_gray;
        }
    }
}

// filter 4
void mergeImages(const Image &image1, const Image &image2, Image &result_image, int method)
{
    if (method == 1)
    {
        int biggest_w = max(image1.width, image2.width);
        int biggest_h = max(image1.height, image2.height);

        Image new_image1(biggest_w, biggest_h);
        Image new_image2(biggest_w, biggest_h);

        for (int i = 0; i < biggest_w; ++i)
        {
            for (int j = 0; j < biggest_h; ++j)
            {
                int old_i1 = i * (double)image1.width / biggest_w;
                int old_j1 = j * (double)image1.height / biggest_h;
                int old_i2 = i * (double)image2.width / biggest_w;
                int old_j2 = j * (double)image2.height / biggest_h;

                for (int c = 0; c < 3; ++c)
                {
                    new_image1(i, j, c) = image1(old_i1, old_j1, c);
                    new_image2(i, j, c) = image2(old_i2, old_j2, c);
                }
            }
        }

        result_image = Image(biggest_w, biggest_h);
        for (int i = 0; i < biggest_w; ++i)
        {
            for (int j = 0; j < biggest_h; ++j)
            {
                for (int c = 0; c < 3; ++c)
                {
                    result_image(i, j, c) = (new_image1(i, j, c) + new_image2(i, j, c)) / 2;
                }
            }
        }
    }
    else if (method == 2)
    {
        int smallest_w = min(image1.width, image2.width);
        int smallest_h = min(image1.height, image2.height);

        result_image = Image(smallest_w, smallest_h);
        for (int i = 0; i < smallest_w; ++i)
        {
            for (int j = 0; j < smallest_h; ++j)
            {
                for (int c = 0; c < 3; ++c)
                {
                    result_image(i, j, c) = (image1(i, j, c) + image2(i, j, c)) / 2;
                }
            }
        }
    }
}

// filter 7
void lightenDarkenFilter(Image &image, bool lighten, int amount)
{
    for (int i = 0; i < image.width; ++i)
    {
        for (int j = 0; j < image.height; ++j)
        {
            for (int k = 0; k < 3; ++k)
            {
                int newValue = lighten ? image(i, j, k) + amount : image(i, j, k) - amount;
                if (newValue > 255) newValue = 255;
                if (newValue < 0) newValue = 0;
                image(i, j, k) = newValue;
            }
        }
    }
}

// filter 10
void filterEdgeDetection(Image &image)
{
    for (int i = 0; i < image.width; ++i)
    {
        for (int j = 0; j < image.height; ++j)
        {
            unsigned int avg = (image(i, j, 0) + image(i, j, 1) + image(i, j, 2)) / 3;
            image(i, j, 0) = image(i, j, 1) = image(i, j, 2) = avg;
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
                image(i, j, 0) = image(i, j, 1) = image(i, j, 2) = 0;
            else
                image(i, j, 0) = image(i, j, 1) = image(i, j, 2) = 255;
        }
    }
}

// filter 16
void PurpleFilter(Image &image)
{
    for (int i = 0; i < image.width; ++i)
    {
        for (int j = 0; j < image.height; ++j)
        {
            int r = image(i, j, 0) + 70;
            int g = image(i, j, 1) - 50;
            int b = image(i, j, 2) + 80;
            if (r > 255) r = 255;
            if (g < 0) g = 0;
            if (b > 255) b = 255;
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
        cout << "1. Grayscale Filter\n";
        cout << "2. Merge Images\n";
        cout << "3. Lighten / Darken Filter\n";
        cout << "4. Edge Detection Filter\n";
        cout << "5. Medium Purple Filter\n";
        cout << "6. Save Image\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        string filename;

        if (choice == 1)
        {
            if (!isLoaded) cout << "Please load an image first!\n";
            else
            {
                GrayscaleFilter(image);
                isModified = true;
                isSaved = false;
                cout << "Grayscale filter applied!\n";
            }
        }
        else if (choice == 2)
        {
            if (!isLoaded) cout << "Please load an image first!\n";
            else
            {
                string file2, outFile;
                cout << "Enter the second image name: ";
                cin >> file2;
                Image image2(file2);

                int method;
                cout << "Merge method (1 = resize & merge, 2 = merge common part): ";
                cin >> method;

                Image result_image;
                mergeImages(image, image2, result_image, method);

                cout << "Enter output file name: ";
                cin >> outFile;
                result_image.saveImage(outFile);
                cout << "Images merged successfully!\n";
            }
        }
        else if (choice == 3)
        {
            if (!isLoaded) cout << "Please load an image first!\n";
            else
            {
                int subChoice, amount;
                cout << "1. Lighten\n2. Darken\nEnter your choice: ";
                cin >> subChoice;
                cout << "Enter amount (50, 100): ";
                cin >> amount;
                lightenDarkenFilter(image, subChoice == 1, amount);
                isModified = true;
                isSaved = false;
                cout << "Lighten/Darken filter applied!\n";
            }
        }
        else if (choice == 4)
        {
            if (!isLoaded) cout << "Please load an image first!\n";
            else
            {
                filterEdgeDetection(image);
                isModified = true;
                isSaved = false;
                cout << "Edge Detection filter applied!\n";
            }
        }
        else if (choice == 5)
        {
            if (!isLoaded) cout << "Please load an image first!\n";
            else
            {
                PurpleFilter(image);
                isModified = true;
                isSaved = false;
                cout << "Purple filter applied!\n";
            }
        }
        else if (choice == 6)
        {
            if (!isModified) cout << "No changes to save!\n";
            else
            {
                cout << "Enter output file name: ";
                cin >> filename;
                image.saveImage(filename);
                isSaved = true;
                cout << "Image saved successfully!\n";
            }
        }

    } while (choice != 7);

    return 0;
}
