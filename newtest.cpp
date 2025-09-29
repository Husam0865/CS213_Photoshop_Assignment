#include <iostream>
#include "Image_Class.h"

using namespace std;

int main() {
   
    string file1, file2, outFile;
    int user_choice;

   
    cout << "Enter the first image name: ";
    cin >> file1;
    cout << "Enter the second image name: ";
    cin >> file2;

    Image image1(file1);
    Image image2(file2);

    
    cout << "\nHow to merge?\n";
    cout << "1. Make both images the same big size and merge.\n";
    cout << "2. Merge the small common part only.\n";
    cout << "Enter choice (1 or 2): ";
    cin >> user_choice;

    
    if (user_choice == 1) {
        
        int biggest_w;
        if (image1.width > image2.width) {
            biggest_w = image1.width;
        } else {
            biggest_w = image2.width;
        }

       
        int biggest_h;
        if (image1.height > image2.height) {
            biggest_h = image1.height;
        } else {
            biggest_h = image2.height;
        }
        
       
        Image new_image1(biggest_w, biggest_h);
        Image new_image2(biggest_w, biggest_h);

        
        for (int i = 0; i < biggest_w; ++i) {
            for (int j = 0; j < biggest_h; ++j) {
                int old_i = i * (double)image1.width / biggest_w;
                int old_j = j * (double)image1.height / biggest_h;
                for (int c = 0; c < 3; ++c) {
                    new_image1(i, j, c) = image1(old_i, old_j, c);
                }
            }
        }
        
        
        for (int i = 0; i < biggest_w; ++i) {
            for (int j = 0; j < biggest_h; ++j) {
                int old_i = i * (double)image2.width / biggest_w;
                int old_j = j * (double)image2.height / biggest_h;
                for (int c = 0; c < 3; ++c) {
                    new_image2(i, j, c) = image2(old_i, old_j, c);
                }
            }
        }

        
        Image result_image(biggest_w, biggest_h);

        
        for (int i = 0; i < biggest_w; ++i) {
            for (int j = 0; j < biggest_h; ++j) {
                for (int c = 0; c < 3; ++c) {
                    int color1 = new_image1(i, j, c);
                    int color2 = new_image2(i, j, c);
                    result_image(i, j, c) = (color1 + color2) / 2;
                }
            }
        }

        cout << "\nEnter the output file name: ";
        cin >> outFile;
        result_image.saveImage(outFile);

    
    } else if (user_choice == 2) {
        
        int smallest_w;
        if (image1.width < image2.width) {
            smallest_w = image1.width;
        } else {
            smallest_w = image2.width;
        }

        
        int smallest_h;
        if (image1.height < image2.height) {
            smallest_h = image1.height;
        } else {
            smallest_h = image2.height;
        }
        
        
        Image result_image(smallest_w, smallest_h);

        
        for (int i = 0; i < smallest_w; ++i) {
            for (int j = 0; j < smallest_h; ++j) {
                for (int c = 0; c < 3; ++c) {
                    int color1 = image1(i, j, c);
                    int color2 = image2(i, j, c);
                    result_image(i, j, c) = (color1 + color2) / 2;
                }
            }
        }
        
        cout << "\nEnter the output file name: ";
        cin >> outFile;
        result_image.saveImage(outFile);

    } else {
        cout << "Wrong choice!" << endl;
    }

    cout << "Done!" << endl;
    return 0;
}