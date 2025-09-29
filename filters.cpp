#include <iostream>
#include "Image_Class.h"
using namespace std;

// filter 1
void applyGrayscaleFilter(Image &image)
{
    for (int i = 0; i < image.width; ++i)
    {
        for (int j = 0; j < image.height; ++j)
        {
            unsigned int total_color = 0;
            total_color += image(i, j, 0);
            total_color += image(i, j, 1);
            total_color += image(i, j, 2);

            unsigned char average_gray = total_color / 3;

            image(i, j, 0) = average_gray;
            image(i, j, 1) = average_gray;
            image(i, j, 2) = average_gray;
        }
    }
}

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

// filter 3
Image applyInvert(Image image)
{
    Image newImage(image.width, image.height);

    for (int i = 0; i < image.width; i++)
    {
        for (int j = 0; j < image.height; j++)
        {
            newImage(i, j, 0) = 255 - image(i, j, 0);
            newImage(i, j, 1) = 255 - image(i, j, 1);
            newImage(i, j, 2) = 255 - image(i, j, 2);
        }
    }

    return newImage;
}

// filter 4
void mergeImages(Image &image1)
{
    string file2;
    int user_choice;

    cout << "Enter the second image name: ";
    cin >> file2;

    Image image2(file2);

    cout << "\nHow to merge?\n";
    cout << "1. Make both images the same big size and merge.\n";
    cout << "2. Merge the small common part only.\n";
    cout << "Enter choice (1 or 2): ";
    cin >> user_choice;

    if (user_choice == 1)
    {
        int biggest_w;
        if (image1.width > image2.width)
        {
            biggest_w = image1.width;
        }
        else
        {
            biggest_w = image2.width;
        }

        int biggest_h;
        if (image1.height > image2.height)
        {
            biggest_h = image1.height;
        }
        else
        {
            biggest_h = image2.height;
        }

        Image new_image1(biggest_w, biggest_h);
        Image new_image2(biggest_w, biggest_h);

        for (int i = 0; i < biggest_w; ++i)
        {
            for (int j = 0; j < biggest_h; ++j)
            {
                int old_i = i * (double)image1.width / biggest_w;
                int old_j = j * (double)image1.height / biggest_h;
                for (int c = 0; c < 3; ++c)
                {
                    new_image1(i, j, c) = image1(old_i, old_j, c);
                }
            }
        }

        for (int i = 0; i < biggest_w; ++i)
        {
            for (int j = 0; j < biggest_h; ++j)
            {
                int old_i = i * (double)image2.width / biggest_w;
                int old_j = j * (double)image2.height / biggest_h;
                for (int c = 0; c < 3; ++c)
                {
                    new_image2(i, j, c) = image2(old_i, old_j, c);
                }
            }
        }

        Image result_image(biggest_w, biggest_h);

        for (int i = 0; i < biggest_w; ++i)
        {
            for (int j = 0; j < biggest_h; ++j)
            {
                for (int c = 0; c < 3; ++c)
                {
                    int color1 = new_image1(i, j, c);
                    int color2 = new_image2(i, j, c);
                    result_image(i, j, c) = (color1 + color2) / 2;
                }
            }
        }

        image1 = result_image;
    }
    else if (user_choice == 2)
    {
        int smallest_w;
        if (image1.width < image2.width)
        {
            smallest_w = image1.width;
        }
        else
        {
            smallest_w = image2.width;
        }

        int smallest_h;
        if (image1.height < image2.height)
        {
            smallest_h = image1.height;
        }
        else
        {
            smallest_h = image2.height;
        }

        Image result_image(smallest_w, smallest_h);

        for (int i = 0; i < smallest_w; ++i)
        {
            for (int j = 0; j < smallest_h; ++j)
            {
                for (int c = 0; c < 3; ++c)
                {
                    int color1 = image1(i, j, c);
                    int color2 = image2(i, j, c);
                    result_image(i, j, c) = (color1 + color2) / 2;
                }
            }
        }

        image1 = result_image;
    }
    else
    {
        cout << "Wrong choice!" << endl;
    }

    cout << "Done!" << endl;
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

// filter 12
Image applyBlur(Image image)
{
    int BLUR = 20;
    Image tempImage(image.width, image.height);
    Image newImage(image.width, image.height);

    for (int i = 0; i < image.width; i++)
    {
        for (int j = 0; j < image.height; j++)
        {
            int sumR = 0, sumG = 0, sumB = 0;
            int count = 0;

            for (int i2 = -BLUR; i2 <= BLUR; i2++)
            {
                int x = i + i2;
                if (x >= 0 && x < image.width)
                {
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

    for (int i = 0; i < image.width; i++)
    {
        for (int j = 0; j < image.height; j++)
        {
            int sumR = 0, sumG = 0, sumB = 0;
            int count = 0;

            for (int j2 = -BLUR; j2 <= BLUR; j2++)
            {
                int y = j + j2;
                if (y >= 0 && y < image.height)
                {
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
        cout << "2. Apply Invert Image (Filter 3)\n";
        cout << "3. Apply Grayscale Image (Filter 1)\n";
        cout << "4. Apply merge Image (Filter 4)\n";
        cout << "5. Apply Blur Image (Filter 12)\n";
        cout << "6. Apply Black & White Image (Filter 2)\n";
        cout << "7. Apply Flip Image (Filter 5)\n";
        cout << "8. Save Image\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        string filename;

        switch (choice)
        {
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
            if (!isLoaded)
            {
                cout << "Please load an image first (Option 1)!\n";
                break;
            }
            image = applyInvert(image);
            isModified = true;
            isSaved = false;
            cout << "Invert filter applied!\n";

            break;

        case 3:
            if (!isLoaded)
            {
                cout << "Please load an image first (Option 1)!\n";
                break;
            }
            applyGrayscaleFilter(image);
            isModified = true;
            isSaved = false;
            cout << "Grayscale filter applied!\n";
            break;

        case 4:
            if (!isLoaded)
            {
                cout << "Please load an image first (Option 1)!\n";
                break;
            }
            mergeImages(image);
            isModified = true;
            isSaved = false;
            cout << "[Filter merge images applied!\n";
            break;

        case 5:
            if (!isLoaded)
            {
                cout << "Please load an image first (Option 1)!\n";
                break;
            }
            image = applyBlur(image);
            isModified = true;
            isSaved = false;
            cout << "Blur filter applied!\n";
            break;

        case 6:
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

        case 7:
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

        case 8:
            if (!isLoaded)
            {
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
            if (isModified && !isSaved)
            {
                int exit;
                cout << "You have unsaved changes! Choose an option:\n";
                cout << "1. Save now\n2. Exit without saving\nAny other number: Cancel\n";
                cout << "Enter your choice: ";
                cin >> exit;

                if (exit == 1)
                {
                    cout << "Pls enter image name to store new image\n";
                    cout << "and specify extension .jpg, .bmp, .png, .tga: ";
                    cin >> filename;
                    image.saveImage(filename);
                    cout << "Image saved!\n";
                    system(filename.c_str());
                    choice = 9;
                }
                else if (exit == 2)
                {
                    cout << "Exiting without saving...\n";
                    choice = 9;
                }
                else
                {
                    choice = 0;
                }
            }
            else
            {
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
