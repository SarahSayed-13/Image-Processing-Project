
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
     BlackAndWhite = 2,
     Invert=3,
	 FrameImage=4,
	 FlipImage=5,
	 Rotate = 6,
     Darken=7,
     Lighten=8,
     Exit = 10
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
void GrayScale(Image& image)
{
    for (int y = 0; y < image.height; ++y) 
	{
        for (int x = 0; x < image.width; ++x) 
		{
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
void GrayScaleFlow()
{
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
void BlackAndWhiteFlow()
{
    Image UserImage;
    LoadImage(UserImage, "Enter image filename for Black and White : ");
    BlackAndWhiteImageFilter(UserImage);
    SaveImage(UserImage, "Enter image filename to save: ");
}

//Filter 3: Invert //
void Invert(Image& image)
{
    for (int i=0;i<image.width;++i) {  //width-->columns
        for (int j=0;j<image.height;++j) { //height-->rows
            for (int k=0;k<3;++k) { //3-->channels
                image(i,j,k)= 255 - image(i, j, k);
            } } }}

// Invert Flow  //
void InvertFlow() {
    Image UserImage;
    LoadImage(UserImage, "Enter image filename for Invert : ");
   Invert(UserImage);
    SaveImage(UserImage, "Enter image filename to save: ");
}
 
struct FrameData
{
	int FrameWidth;
	int FrameHeight;
	int Red;
	int Green;
	int Blue;
};
FrameData ReadData()
{
	FrameData DataOfFrame;
	do
	{
		cout << "Please, Enter the Width of Frame\n";
		cin >> DataOfFrame.FrameWidth;
		cout << "Please, Enter The Height of Frame\n";
		cin >> DataOfFrame.FrameHeight;
	} while (DataOfFrame.FrameWidth <= 0 || DataOfFrame.FrameHeight <= 0);

	do
	{
		cout << "PLease,Choose The color of the Frame from '0' to '255'\n";
		cout << "Enter the value of Red\n";
		cin >> DataOfFrame.Red;
		cout << "Enter the value of Green\n";
		cin >> DataOfFrame.Green;
		cout << "Enter the value of Blue\n";
		cin >> DataOfFrame.Blue;
	} while ((DataOfFrame.Red < 0 || DataOfFrame.Red>255) || (DataOfFrame.Green < 0 || DataOfFrame.Green>255) || (DataOfFrame.Blue < 0 || DataOfFrame.Blue>255));

	return DataOfFrame;
}
enum StyleOfFrame { SimpleFrameChoice = 1, DoubleBorderChoice = 2, DoubleBorderWithCornerPatternsChoice = 3 };
enum DoubleFrame { Inside = 1, Outside = 2 };
void SimpleFrame(Image& image, FrameData DataOfFrame)
{
	int NewWidth = image.width + 2 * DataOfFrame.FrameWidth;
	int NewHeight = image.height + 2 * DataOfFrame.FrameHeight;
	Image NewImage(NewWidth, NewHeight);
	for (int i = 0; i < NewImage.width; i++)
	{
		for (int j = 0; j < NewImage.height; j++)
		{
			if (i < DataOfFrame.FrameWidth || i >= NewWidth - DataOfFrame.FrameWidth || j < DataOfFrame.FrameHeight || j >= NewHeight - DataOfFrame.FrameHeight)
			{
				NewImage.setPixel(i, j, 0, DataOfFrame.Red);
				NewImage.setPixel(i, j, 1, DataOfFrame.Green);
				NewImage.setPixel(i, j, 2, DataOfFrame.Blue);
			}
			else
			{
				for (int c = 0;c < 3;c++)
				{
					NewImage.setPixel(i, j, c, image.getPixel(i - DataOfFrame.FrameWidth, j - DataOfFrame.FrameHeight, c));
				}
			}
		}
	}
	image = NewImage;
}
FrameData HelperFunGetSecondFrame()
{
	FrameData SecondFrame;
	int Red, Green, Blue;
	do
	{
		cout << "Enter The Color of inner frame from '0' to '255'\n";
		cout << "For Red: \n";
		cin >> SecondFrame.Red;
		cout << "For Green: \n";
		cin >> SecondFrame.Green;
		cout << "For Blue: \n";
		cin >> SecondFrame.Blue;

	} while ((SecondFrame.Red < 0 || SecondFrame.Red>255) || (SecondFrame.Green < 0 || SecondFrame.Green>255) || (SecondFrame.Blue < 0 || SecondFrame.Blue>255));
	return SecondFrame;
}
void InnerFrame(Image& image, FrameData DataOfFrame, FrameData SecondFrame, int Gap, int Thickness = 3)
{

	int StartX = DataOfFrame.FrameWidth + Gap;
	int EndX = image.width - DataOfFrame.FrameWidth - Gap;
	int StartY = DataOfFrame.FrameHeight + Gap;
	int EndY = image.height - DataOfFrame.FrameHeight - Gap;
	for (int i = StartX; i <= EndX; i++)
	{
		for (int t = 0; t < Thickness; t++)
		{
			image.setPixel(i, StartY + t, 0, SecondFrame.Red);
			image.setPixel(i, StartY + t, 1, SecondFrame.Green);
			image.setPixel(i, StartY + t, 2, SecondFrame.Blue);

			image.setPixel(i, EndY - t, 0, SecondFrame.Red);
			image.setPixel(i, EndY - t, 1, SecondFrame.Green);
			image.setPixel(i, EndY - t, 2, SecondFrame.Blue);


		}
	}
	for (int j = StartY; j <= EndY; j++)
	{
		for (int t = 0; t < Thickness; t++)
		{
			image.setPixel(t + StartX, j, 0, SecondFrame.Red);
			image.setPixel(t + StartX, j, 1, SecondFrame.Green);
			image.setPixel(t + StartX, j, 2, SecondFrame.Blue);

			image.setPixel(EndX - t, j, 0, SecondFrame.Red);
			image.setPixel(EndX - t, j, 1, SecondFrame.Green);
			image.setPixel(EndX - t, j, 2, SecondFrame.Blue);

		}
	}

}


void DoubleBorder(Image& image)
{
	FrameData DataOfFrame = ReadData();
	SimpleFrame(image, DataOfFrame);
	int Position;
	do
	{
		cout << "Please, Where do you want the frame to be ? Inside[1] , Outsid[2]\n";
		cin >> Position;
	} while (Position != 1 && Position != 2);
	DoubleFrame position = DoubleFrame(Position);
	if (position == Outside)
	{
		DataOfFrame = ReadData();
		SimpleFrame(image, DataOfFrame);
	}
	else if (position == Inside)
	{
		int Gap = 5;

		FrameData SecondFrame = HelperFunGetSecondFrame();
		InnerFrame(image, DataOfFrame, SecondFrame, Gap);


	}
}
void DoubleBorderWithCornerPatterns(Image& image)
{
	FrameData DataOfFrame = ReadData();
	SimpleFrame(image, DataOfFrame);
	FrameData SecondFrame = HelperFunGetSecondFrame();
	int Gap = 0;
	int Thickness = 3;
	InnerFrame(image, DataOfFrame, SecondFrame, Gap, Thickness);
	int CornerSize = 15;
	for (int i = 0; i < CornerSize; i++)
	{
		for (int j = 0; j < CornerSize; j++)
		{
			for (int c = 0; c < 3; c++)
			{
				image.setPixel(i + DataOfFrame.FrameWidth + Thickness, j + DataOfFrame.FrameHeight + Thickness, c, 255);
				image.setPixel(image.width - DataOfFrame.FrameWidth - Thickness - CornerSize + i, j + DataOfFrame.FrameHeight + Thickness, c, 255);
				image.setPixel(image.width - DataOfFrame.FrameWidth - Thickness - CornerSize + i, image.height - DataOfFrame.FrameHeight - Thickness - CornerSize + j, c, 255);
				image.setPixel(i + DataOfFrame.FrameWidth + Thickness, image.height - DataOfFrame.FrameHeight - Thickness - CornerSize + j, c, 255);

			}
		}
	}

}


void FrameImage(Image& image)
{
	int TypeOfStyle;
	do
	{
		cout << "What Style do You want in this Frame? SimpleFrame[1] , DoubleBorder[2] , DoubleBorderWithCornerPatterns[3]\n";
		cin >> TypeOfStyle;
	} while (TypeOfStyle <= 0 || TypeOfStyle > 3);

	StyleOfFrame StyleFrame = StyleOfFrame(TypeOfStyle);

	switch (StyleFrame)
	{
	case SimpleFrameChoice:
	{
		FrameData DataOfFrame = ReadData();
		SimpleFrame(image, DataOfFrame);
		break;
	}
	case DoubleBorderChoice:
		DoubleBorder(image);
		break;
	case DoubleBorderWithCornerPatternsChoice:
		DoubleBorderWithCornerPatterns(image);
		break;
	}
}
void FrameImageFlow()
{
	Image UserImage;
	LoadImage(UserImage, "Enter Image Filename For FrameImage : ");
	FrameImage(UserImage);
	SaveImage(UserImage, "Enter Image Filename To Save: ");
}
// Filter 5: Flip (Horizontal / Vertical) //
void FlipHorizontal(Image& image) {
    for (int y = 0; y < image.height; ++y) {
        for (int x = 0; x < image.width / 2; ++x) {
            int oppositeX = image.width - 1 - x;
            for (int c = 0; c < image.channels; ++c) {
                swap(image(x, y, c), image(oppositeX, y, c));
            }
        }
    }
}
void FlipVertical(Image& image) {
    for (int y = 0; y < image.height / 2; ++y) {
        int oppositeY = image.height - 1 - y;
        for (int x = 0; x < image.width; ++x) {
            for (int c = 0; c < image.channels; ++c) {
                swap(image(x, y, c), image(x, oppositeY, c));
            }
        }
    }
}
void ApplyFlipFilter(Image& image) {
    int choice = 0;
    cout << "\nChoose a flip option:\n";
    cout << "1. Flip Horizontally\n";
    cout << "2. Flip Vertically\n";
    cout << "Enter your choice (1 or 2): ";
    cin >> choice;
    while (choice != 1 && choice != 2) {
        cout << "Invalid choice. Please enter 1 or 2: ";
        cin >> choice;
    }
    if (choice == 1) {
        FlipHorizontal(image);
    } else {
        FlipVertical(image);
    }
}
// Flow Flip Image //
void FlipImageFlow() {
    Image userImage;
    LoadImage(userImage, "Enter image filename to Flip: ");
    ApplyFlipFilter(userImage);
    SaveImage(userImage, "Enter image filename to save: ");
}
// Rotate Filter
void RotateImageFilter(Image &UserImage) {
    int RotationDegree=0;
    while (true) {
        cout<<"Choose Rotation Degree (90,180,270) :  "<<endl;
        cin>>RotationDegree;
        if (RotationDegree==90 || RotationDegree==180 || RotationDegree==270) {
            break;
        }
        else {
            cout<<"Invalid Input, try again."<<endl;
        }
    }
    if (RotationDegree==90) {
        Image RotateImage90(UserImage.height,UserImage.width);
        for (int i=0;i<UserImage.width;i++) {
            for (int j=0;j<UserImage.height;j++) {
                RotateImage90(RotateImage90.width-j-1,i,0)=UserImage(i,j,0);
                RotateImage90(RotateImage90.width-j-1,i,1)=UserImage(i,j,1);
                RotateImage90(RotateImage90.width-j-1,i,2)=UserImage(i,j,2);
            }
        }
        UserImage=RotateImage90;
    }
    else if (RotationDegree==180) {
        Image RotateImage180(UserImage.width,UserImage.height);
        for (int i=0;i<UserImage.width;i++) {
            for (int j=0;j<UserImage.height;j++) {
                RotateImage180(RotateImage180.width-i-1,RotateImage180.height-j-1,0)=UserImage(i,j,0);
                RotateImage180(RotateImage180.width-i-1,RotateImage180.height-j-1,1)=UserImage(i,j,1);
                RotateImage180(RotateImage180.width-i-1,RotateImage180.height-j-1,2)=UserImage(i,j,2);
            }
        }
        UserImage=RotateImage180;
    }
    else if (RotationDegree==270) {
        Image RotateImage270(UserImage.height,UserImage.width);
        for (int i=0;i<UserImage.width;i++) {
            for (int j=0;j<UserImage.height;j++) {
                RotateImage270(j,RotateImage270.height-i-1,0)=UserImage(i,j,0);
                RotateImage270(j,RotateImage270.height-i-1,1)=UserImage(i,j,1);
                RotateImage270(j,RotateImage270.height-i-1,2)=UserImage(i,j,2);
            }
        }
        UserImage=RotateImage270;
    }
}
// Flow Rotate Filter //
void RotateFlow() {
    Image UserImage;
    LoadImage(UserImage, "Enter image filename for Rotating : ");
    RotateImageFilter(UserImage);
    SaveImage(UserImage, "Enter image filename to save: ");
}

//filter 7 consist of two filters(darken,lighten)
// allow the user to choose the level of darkening or lighting from 0 to 100%  (Done)
int GetPercentage()
{
	int percentage;
	cout << "Enter the percentage (0 - 100): ";
	cin >> percentage;
	while (percentage < 0 || percentage > 100)
	{
		cout << "Invalid percentage. Enter a value between 0 and 100: ";
		cin >> percentage;
	}
	return percentage;
}

void Darken(Image &image, int percentage) {
	for (int i=0;i<image.width;++i) {
		for (int j=0;j<image.height;++j) {
			for (int k=0;k<3;++k) {
				image(i,j,k) = image(i,j,k) - (image(i,j,k) * percentage / 100);   }
		}
	}

}


void Lighten(Image &image, int percentage) {
	for (int i=0;i<image.width;++i) {
		for (int j=0;j<image.height;++j) {
			for (int k=0;k<3;++k) {
				image(i,j,k) = image(i,j,k) +((255-image(i,j,k)) * percentage / 100);
			}
		}
	}

}
void DarkenImageFlow() {
	Image userImage;
	LoadImage(userImage, "Enter image filename to Darken: ");
	int percentage = GetPercentage();
	Darken(userImage, percentage);
	SaveImage(userImage, "Enter image filename to save: ");
}
void LightenImageFlow() {
	Image userImage;
	LoadImage(userImage, "Enter image filename to Lighten: ");
	int percentage = GetPercentage();
	Lighten(userImage, percentage);
	SaveImage(userImage, "Enter image filename to save: ");
}
//-------------------------------------------------------------------




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
        case EnFilterOptions::Invert:
        {
         InvertFlow();
         FiltersMenu();
         break;
        }
		case EnFilterOptions::FrameImage:
		{
			FrameImageFlow();
			FiltersMenu();
			break;
		}
		case EnFilterOptions::FlipImage:
		{
			FlipImageFlow();
			FiltersMenu();
			break;
		}
       case EnFilterOptions::Darken:{
          DarkenImageFlow();
          FiltersMenu();
          break;
              }
       case EnFilterOptions::Lighten:{
        	LightenImageFlow();
            FiltersMenu();
            break;
             }
        case EnFilterOptions::Exit:
        {
            ExitProgram();
            return;
        }
		case EnFilterOptions::Rotate:
        {
            RotateFlow();
            FiltersMenu();
            break;
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
    cout<<  "\t [3]  Invert Filter\n";
	cout << "\t [4]  Frame Image Filter\n";
	cout << "\t [5]  Flip Image Filter\n";
	cout<<  "\t [6]  Rotate Filter\n";
    cout<<  "\t [7]  Darken Image Filter\n";
    cout<<  "\t [8]  Lighten Image Filter\n";
    cout << "\t [10]  Exit\n";
    cout << "=================================\n";
    Start(GetChoice());
}
int main() {
    FiltersMenu();
    return 0;
}