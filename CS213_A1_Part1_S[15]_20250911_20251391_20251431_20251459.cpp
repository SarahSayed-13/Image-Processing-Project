
/*
================================================================================
Course: CS213 - Object-Oriented Programming (OOP)
Assignment: Assignment 1 - Part 1
Program Name: Image Processing Program

Team Members:
1. Sarah Sayed Hafez Mohamed     - ID: [20250911]   - (Filter 1: Grayscale, Filter 5: Flip)
2. Mariam Helmy Mahmoud Helmy    - ID: [20251391]   - (Filter 2: Black & White, Filter 6: Rotate)
3. Menna Tamer Hassan Said       - ID: [20251431]   - (Filter 3: Invert, Filter 7: Darken/Lighten)
4. Nour Osama Ali Ibrahim Rakha  - ID: [20251459]   - (Filter 4: Frame, Filter 8: Resize)

Section: S[ 15 || 16 ]
================================================================================
*/

#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
#include <vector>
#define _CRT_SECURE_NO_WARNINGS
#include "Image_Class.h"
using namespace std;
enum class EnFilterOptions {
    GrayScale = 1,
    BlackAndWhite=2,
    Exit = 17
};
// Function for loading Images
void LoadImage(Image& img, string prompt = "Enter image filename: ") {
    string filename;
    cout << prompt;
    cin >> filename;
    img.loadNewImage(filename);
}
// Function for saving Images //
void SaveImage(Image& img, string prompt = "Enter image filename to save: ") {
    string filename;
    cout << prompt;
    cin >> filename;
    img.saveImage(filename);
    cout << "Image saved successfully as " << filename << ".\n\n";
}
// Filter 1: Grayscale // 
void GrayScale(Image& image) {
    for (int y = 0; y < image.height; ++y) {
        for (int x = 0; x < image.width; ++x) {
            int red   = image(x, y, 0);
            int green = image(x, y, 1);
            int blue  = image(x, y, 2);
            int gray  = (red + green + blue) / 3;

            image(x, y, 0) = gray;
            image(x, y, 1) = gray;
            image(x, y, 2) = gray;
        }
    }
}
// Flow GrayScale //
void GrayScaleFlow() {
    Image userImage;
    LoadImage(userImage, "Enter image filename for GrayScale: ");
    GrayScale(userImage);
    SaveImage(userImage, "Enter image filename to save: ");
}
// Filter 2 :Black and White Filter
void BlackAndWhiteImageFilter(Image &UserImage)
{
    for (int i=0;i<UserImage.width;i++) {
        for (int j=0;j<UserImage.height;j++) {
            double Brightness=0;
            for (int k=0;k<3;k++) {
                Brightness+=UserImage(  i,j,k);
            }
            Brightness=Brightness/3;
            if (Brightness<127.5) { // 127.5 --> MidPoint between 0 and 255
                UserImage(i,j,0)=UserImage(i,j,1)=UserImage(i,j,2)=0;
            }
            else {
                UserImage(i,j,0)=UserImage(i,j,1)=UserImage(i,j,2)=255;
            }
        }
    }
}
// Flow BlackAndWhite //
void BlackAndWhiteFlow() {
    Image UserImage;
    LoadImage(UserImage, "Enter image filename for Black and White : ");
    BlackAndWhiteImageFilter(UserImage);
    SaveImage(UserImage, "Enter image filename to save: ");
}
void ExitProgram() {
    cout << "=====================\n";
    cout << "    Program Ended    \n";
    cout << "=====================\n";
}
EnFilterOptions GetChoice() {
    int choice;
    cout << "Choose a Choice : ";
    cin >> choice;
    return (EnFilterOptions)choice;
}
void FiltersMenu();
void Start(EnFilterOptions choice) {
    switch (choice) {
        case EnFilterOptions::GrayScale:
        {
            GrayScaleFlow();
            FiltersMenu();
            break;
        }
        case EnFilterOptions::BlackAndWhite:
        {
            BlackAndWhiteFlow();
            FiltersMenu();
            break;
        }
        case EnFilterOptions::Exit:
        {
            ExitProgram();
            return;
        }
        default:
            cout << "\nInvalid Choice! Try again.\n\n";
            FiltersMenu();
            break;
    }
}
void FiltersMenu() {
    cout << "=================================\n";
    cout << "\t [1]  GrayScale Filter\n";
    cout<<  "\t [2]  Black and White Filter\n";
    cout << "\t [17] Exit\n";
    cout << "=================================\n";
    Start(GetChoice());
}
int main() {
    FiltersMenu();
    return 0;
}