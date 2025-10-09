#include <iostream>
#include "Image_Class.h"
using namespace std;

// filter 1
Image applyGrayscale(Image image) {
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            int total_color = image(i, j, 0) + image(i, j, 1) + image(i, j, 2);
            int average_gray = total_color / 3;
            image(i, j, 0) = image(i, j, 1) = image(i, j, 2) = average_gray;
        }
    }
    return image;
}

// filter 2
Image applyBlackAndWhite(Image image) {
    int Half = 128;
    Image newImage(image.width, image.height);
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            unsigned int avg = (image(i, j, 0) + image(i, j, 1) + image(i, j, 2)) / 3;
            if (avg > Half) {
                newImage(i, j, 0) = 255;
                newImage(i, j, 1) = 255;
                newImage(i, j, 2) = 255;
            } else {
                newImage(i, j, 0) = 0;
                newImage(i, j, 1) = 0;
                newImage(i, j, 2) = 0;
            }
        }
    }
    return newImage;
}

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

// filter 4
Image applyMerge(Image image1) {
    string file2;
    cout << "Enter second image filename: ";
    cin >> file2;
    Image image2(file2);

    int method;
    cout << "Merge method (1 = resize & merge, 2 = merge common part): ";
    cin >> method;

    Image result;
    if (method == 1) {
        int biggest_w = max(image1.width, image2.width);
        int biggest_h = max(image1.height, image2.height);
        Image resized1(biggest_w, biggest_h), resized2(biggest_w, biggest_h);

        for (int i = 0; i < biggest_w; ++i) {
            for (int j = 0; j < biggest_h; ++j) {
                int old_i1 = i * (double)image1.width / biggest_w;
                int old_j1 = j * (double)image1.height / biggest_h;
                int old_i2 = i * (double)image2.width / biggest_w;
                int old_j2 = j * (double)image2.height / biggest_h;
                for (int c = 0; c < 3; ++c) {
                    resized1(i, j, c) = image1(old_i1, old_j1, c);
                    resized2(i, j, c) = image2(old_i2, old_j2, c);
                }
            }
        }
        result = Image(biggest_w, biggest_h);
        for (int i = 0; i < biggest_w; ++i)
            for (int j = 0; j < biggest_h; ++j)
                for (int c = 0; c < 3; ++c)
                    result(i, j, c) = (resized1(i, j, c) + resized2(i, j, c)) / 2;
    } else {
        int small_w = min(image1.width, image2.width);
        int small_h = min(image1.height, image2.height);
        result = Image(small_w, small_h);
        for (int i = 0; i < small_w; ++i)
            for (int j = 0; j < small_h; ++j)
                for (int c = 0; c < 3; ++c)
                    result(i, j, c) = (image1(i, j, c) + image2(i, j, c)) / 2;
    }

    cout << "Merge filter applied!\n";
    return result;
}

// filter 5
Image applyFlip(Image image) {
    Image newImage(image.width, image.height);
    for (int i = 0; i < image.height; i++) {
        for (int j = 0; j < image.width; j++) {
            for (int c = 0; c < 3; c++) {
                newImage(j, i, c) = image(image.width - 1 - j, i, c);
            }
        }
    }
    return newImage;
}

// filter 6
Image applyRotate(Image image) {
    int choice;
    cout << "Rotate image by:\n";
    cout << "1) 90 degrees (Clockwise)\n";
    cout << "2) 180 degrees\n";
    cout << "3) 270 degrees (Clockwise)\n";
    cout << "Enter your choice: ";
    cin >> choice;

    int w = image.width;
    int h = image.height;

    if (choice == 1) {
        Image newImg(h, w);
        for (int x = 0; x < w; x++) {
            for (int y = 0; y < h; y++) {
                for (int c = 0; c < 3; c++) {
                    newImg(h - 1 - y, x, c) = image(x, y, c);
                }
            }
        }
        return newImg;
    } else if (choice == 2) {
        Image newImg(w, h);
        for (int x = 0; x < w; x++) {
            for (int y = 0; y < h; y++) {
                for (int c = 0; c < 3; c++) {
                    newImg(w - 1 - x, h - 1 - y, c) = image(x, y, c);
                }
            }
        }
        return newImg;
    } else if (choice == 3) {
        Image newImg(h, w);
        for (int x = 0; x < w; x++) {
            for (int y = 0; y < h; y++) {
                for (int c = 0; c < 3; c++) {
                    newImg(y, w - 1 - x, c) = image(x, y, c);
                }
            }
        }
        return newImg;
    }
    return image;
}

// filter 7
Image applyLightDark(Image image) {
    int subChoice, amount;
    cout << "1. Lighten\n2. Darken\nEnter your choice: ";
    cin >> subChoice;
    cout << "Enter amount (50, 100): ";
    cin >> amount;

    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                int newValue = (subChoice == 1) ? image(i, j, k) + amount : image(i, j, k) - amount;
                if (newValue > 255) newValue = 255;
                if (newValue < 0) newValue = 0;
                image(i, j, k) = newValue;
            }
        }
    }
    return image;
}

// filter 8
Image applyCrop(Image image) {
    int x, y, w, h;
    cout << "Enter crop details (X Y Width Height): ";
    cin >> x >> y >> w >> h;

    if (x < 0 || y < 0 || w <= 0 || h <= 0 ||
        (x + w) > image.width || (y + h) > image.height) {
        cout << "Invalid crop dimensions.\n";
        return image;
    }

    Image newImage(w, h);
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            for (int c = 0; c < 3; c++) {
                newImage(i, j, c) = image(x + i, y + j, c);
            }
        }
    }
    return newImage;
}

// filter 9
Image applyFrame(Image image) {
    int choice;
    cout << "Choose frame type:\n";
    cout << "1) Blue Frame\n";
    cout << "2) Gold Frame\n";
    cout << "3) Fancy Gold Frame with White Lines\n";
    cin >> choice;

    int th = 20;
    int r = 0, g = 70, b = 200;

    if (choice == 2) {
        r = 212; g = 175; b = 55;
    } else if (choice == 3) {
        r = 212; g = 175; b = 55;
    }

    int newW = image.width + 2 * th;
    int newH = image.height + 2 * th;
    Image newImage(newW, newH);

    for (int x = 0; x < newW; x++) {
        for (int y = 0; y < newH; y++) {
            newImage(x, y, 0) = r;
            newImage(x, y, 1) = g;
            newImage(x, y, 2) = b;
        }
    }

    for (int x = 0; x < image.width; x++) {
        for (int y = 0; y < image.height; y++) {
            for (int c = 0; c < 3; c++) {
                newImage(x + th, y + th, c) = image(x, y, c);
            }
        }
    }

    if (choice == 3) {
        for (int x = 0; x < newW; x++) {
            for (int y = 0; y < newH; y++) {
                if ((y < th && y % 10 < 5) || (y > newH - th && y % 10 < 5) ||
                    (x < th && x % 10 < 5) || (x > newW - th && x % 10 < 5)) {
                    newImage(x, y, 0) = 255;
                    newImage(x, y, 1) = 255;
                    newImage(x, y, 2) = 255;
                }
            }
        }
    }

    cout << "Frame applied successfully!\n";
    return newImage;
}

// filter 10
Image applyEdgeDetection(Image image) {
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            unsigned int avg = (image(i, j, 0) + image(i, j, 1) + image(i, j, 2)) / 3;
            image(i, j, 0) = image(i, j, 1) = image(i, j, 2) = avg;
        }
    }

    Image temp = image;
    for (int i = 0; i < image.width - 1; ++i) {
        for (int j = 0; j < image.height - 1; ++j) {
            int diffX = abs(temp(i, j, 0) - temp(i + 1, j, 0));
            int diffY = abs(temp(i, j, 0) - temp(i, j + 1, 0));
            int diff = diffX + diffY;
            if (diff > 30)
                image(i, j, 0) = image(i, j, 1) = image(i, j, 2) = 0;
            else
                image(i, j, 0) = image(i, j, 1) = image(i, j, 2) = 255;
        }
    }
    return image;
}

// filter 11
Image applyResize(Image image) {
    int w, h;
    cout << "Enter new dimensions (Width Height): ";
    cin >> w >> h;
    if (w <= 0 || h <= 0) {
        cout << "Invalid dimensions.\n";
        return image;
    }
    Image newImage(w, h);
    float x_ratio = static_cast<float>(image.width) / w;
    float y_ratio = static_cast<float>(image.height) / h;
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            int srcX = static_cast<int>(x * x_ratio);
            int srcY = static_cast<int>(y * y_ratio);
            for (int c = 0; c < 3; c++) {
                newImage(x, y, c) = image(srcX, srcY, c);
            }
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
            int sumR = 0, sumG = 0, sumB = 0, count = 0;
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
    return tempImage;
}

// filter 15
Image applyOldTV(Image image) {
    Image newImage(image.width, image.height);
    for (int y = 0; y < image.height; y++) {
        for (int x = 0; x < image.width; x++) {
            for (int c = 0; c < 3; c++) {
                if (y % 2 == 0)
                    newImage(x, y, c) = image(x, y, c);
                else
                    newImage(x, y, c) = image(x, y, c) * 0.5;
            }
        }
    }
    return newImage;
}

// filter 16
Image applyPurple(Image image) {
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
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
    return image;
}

// filter 17
Image applyInfrared(Image image) {
    Image newImage(image.width, image.height);
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            unsigned char r = image(i, j, 0);
            unsigned char g = image(i, j, 1);
            unsigned char b = image(i, j, 2);
            unsigned int avg = (r + g + b) / 3;
            newImage(i, j, 0) = 255;
            newImage(i, j, 1) = 255 - avg;
            newImage(i, j, 2) = 255 - avg;
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
        cout << "2. Grayscale (Filter 1)\n";
        cout << "3. Black & White (Filter 2)\n";
        cout << "4. Invert (Filter 3)\n";
        cout << "5. Merge Images (Filter 4)\n";
        cout << "6. Flip Image (Filter 5)\n";
        cout << "7. Rotate Image (Filter 6)\n";
        cout << "8. Lighten/Darken (Filter 7)\n";
        cout << "9. Crop Image (Filter 8)\n";
        cout << "10. Frame (Filter 9)\n";
        cout << "11. Edge Detection (Filter 10)\n";
        cout << "12. Resize (Filter 11)\n";
        cout << "13. Blur (Filter 12)\n";
        cout << "14. Old TV (Filter 15)\n";
        cout << "15. Purple (Filter 16)\n";
        cout << "16. Infrared (Filter 17)\n";
        cout << "17. Save Image\n";
        cout << "18. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        string filename;

        switch (choice) {
            case 1: {
                cout << "Enter image filename: ";
                cin >> filename;
                image = Image(filename);
                isLoaded = true;
                isModified = false;
                isSaved = false;
                cout << "Image loaded successfully!\n";
                break;
            }

            case 2: {
                if (!isLoaded) { cout << "Please load an image first (Option 1)!\n"; break; }
                image = applyGrayscale(image);
                isModified = true;
                isSaved = false;
                cout << "Grayscale filter applied!\n";
                break;
            }

            case 3: {
                if (!isLoaded) { cout << "Please load an image first (Option 1)!\n"; break; }
                image = applyBlackAndWhite(image);
                isModified = true;
                isSaved = false;
                cout << "Black & White filter applied!\n";
                break;
            }

            case 4: {
                if (!isLoaded) {
                    cout << "Please load an image first (Option 1)!\n";
                    break;
                }
                image = applyInvert(image);
                isModified = true;
                isSaved = false;
                cout << "Invert filter applied!\n";
                break;
            }

            case 5: {
                if (!isLoaded) {
                    cout << "Please load an image first (Option 1)!\n";
                    break;
                }
                image = applyMerge(image);
                isModified = true;
                isSaved = false;
                cout << "Merge filter applied!\n";
                break;
            }

            case 6: {
                if (!isLoaded) {
                    cout << "Please load an image first (Option 1)!\n";
                    break;
                }
                image = applyFlip(image);
                isModified = true;
                isSaved = false;
                cout << "Flip filter applied!\n";
                break;
            }

            case 7: {
                if (!isLoaded) {
                    cout << "Please load an image first (Option 1)!\n";
                    break;
                }
                image = applyRotate(image);
                isModified = true;
                isSaved = false;
                cout << "Rotate filter applied!\n";
                break;
            }

            case 8: {
                if (!isLoaded) {
                    cout << "Please load an image first (Option 1)!\n";
                    break;
                }
                image = applyLightDark(image);
                isModified = true;
                isSaved = false;
                cout << "Lighten/Darken filter applied!\n";
                break;
            }

            case 9: {
                if (!isLoaded) {
                    cout << "Please load an image first (Option 1)!\n";
                    break;
                }
                image = applyCrop(image);
                isModified = true;
                isSaved = false;
                cout << "Crop filter applied!\n";
                break;
            }

            case 10: {
                if (!isLoaded) {
                    cout << "Please load an image first (Option 1)!\n";
                    break;
                }
                image = applyFrame(image);
                isModified = true;
                isSaved = false;
                cout << "Frame filter applied!\n";
                break;
            }

            case 11: {
                if (!isLoaded) {
                    cout << "Please load an image first (Option 1)!\n";
                    break;
                }
                image = applyEdgeDetection(image);
                isModified = true;
                isSaved = false;
                cout << "Edge Detection filter applied!\n";
                break;
            }

            case 12: {
                if (!isLoaded) {
                    cout << "Please load an image first (Option 1)!\n";
                    break;
                }
                image = applyResize(image);
                isModified = true;
                isSaved = false;
                cout << "Resize filter applied!\n";
                break;
            }

            case 13: {
                if (!isLoaded) {
                    cout << "Please load an image first (Option 1)!\n";
                    break;
                }
                image = applyBlur(image);
                isModified = true;
                isSaved = false;
                cout << "Blur filter applied!\n";
                break;
            }

            case 14: {
                if (!isLoaded) {
                    cout << "Please load an image first (Option 1)!\n";
                    break;
                }
                image = applyOldTV(image);
                isModified = true;
                isSaved = false;
                cout << "Old TV Effect applied!\n";
                break;
            }

            case 15: {
                if (!isLoaded) {
                    cout << "Please load an image first (Option 1)!\n";
                    break;
                }
                image = applyPurple(image);
                isModified = true;
                isSaved = false;
                cout << "Purple filter applied!\n";
                break;
            }

            case 16: {
                if (!isLoaded) {
                    cout << "Please load an image first (Option 1)!\n";
                    break;
                }
                image = applyInfrared(image);
                isModified = true;
                isSaved = false;
                cout << "Infrared filter applied!\n";
                break;
            }

            case 17: {
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
            }

            case 18: {
                if (isModified && !isSaved) {
                    int exitChoice;
                    cout << "You have unsaved changes! Choose an option:\n";
                    cout << "1. Save now\n2. Exit without saving\nAny other number: Cancel\n";
                    cout << "Enter your choice: ";
                    cin >> exitChoice;
                    if (exitChoice == 1) {
                        cout << "Pls enter image name to store new image\n";
                        cout << "and specify extension .jpg, .bmp, .png, .tga: ";
                        cin >> filename;
                        image.saveImage(filename);
                        cout << "Image saved!\n";
                        system(filename.c_str());
                        choice = 18;
                    } else if (exitChoice == 2) {
                        cout << "Exiting without saving...\n";
                        choice = 18;
                    } else {
                        choice = 0;
                    }
                } else {
                    cout << "Exiting...\n";
                }
                break;
            }

            default: {
                cout << "Invalid choice! Try again.\n";
                break;
            }
        }

    } while (choice != 18);

    return 0;
}
