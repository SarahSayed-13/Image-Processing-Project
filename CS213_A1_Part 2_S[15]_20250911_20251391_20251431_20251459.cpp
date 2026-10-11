/*
================================================================================
Course: CS213 - Object-Oriented Programming (OOP)
Assignment: Assignment 1 - Part 2 
Program Name: Image Processing Program
Team Members:
1. Sarah Sayed Hafez Mohamed     - ID: [20250911]   - (Filter 1: Grayscale, Filter 5: Flip, Filter 9: Merge, Filter 13: Sunlight)
2. Mariam Helmy Mahmoud Helmy    - ID: [20251391]   - (Filter 2: Black & White, Filter 6: Rotate, Filter 10: Detect Edges, Filter 14: TV Noise)
3. Menna Tamer Hassen Said       - ID: [20251431]   - (Filter 3: Invert, Filter 7: Darken/Lighten, Filter 11: Crop, Filter 15: Purple)
4. Nour Osama Ali Ibrahim Rakha  - ID: [20251459]   - (Filter 4: Frame, Filter 8: Resize, Filter 12: Blur, Filter 16: Infrared Radiation)

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
	Invert = 3,
	FrameImage = 4,
	FlipImage = 5,
	Rotate = 6,
	Darken = 7,
	Lighten = 8,
	Resize = 9,
	Merge = 10,
	DetectEdges = 11,
	CropImage = 12,
	SunLight = 13,
	Blur=14,
	TV=15,
    Purple=16,
	Infrared=17,
	SkewImage = 18,
	OilPainting=19,
	Exit = 20
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
		cout << "Please, Where do you want the frame to be ? Inside[1] , Outside[2]\n";
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
 
void WhiteSquaresinCorner(Image& image, FrameData DataOfFrame, int Thickness)
{
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
void DiamondInCorners(Image& image, FrameData DataOfFrame, int Thickness)
{
	int CornerSize = 30;
	int Center = CornerSize / 2;
	int Radius = CornerSize / 2;
	for (int i = 0; i < CornerSize; i++)
	{
		for (int j = 0; j < CornerSize; j++)
		{
			if (abs(i - Center) + abs(j - Center) <= Radius)
			{
				for (int c = 0; c < 3; c++)
				{
					image.setPixel(i + DataOfFrame.FrameWidth + Thickness, j + DataOfFrame.FrameHeight + Thickness, c, 255);
					image.setPixel(image.width - DataOfFrame.FrameWidth - Thickness - CornerSize + i, j + DataOfFrame.FrameHeight + Thickness, c, 255);
					image.setPixel(i + DataOfFrame.FrameWidth + Thickness, image.height - DataOfFrame.FrameHeight - Thickness - CornerSize + j, c, 255);
					image.setPixel(image.width - DataOfFrame.FrameWidth - Thickness - CornerSize + i, image.height - DataOfFrame.FrameHeight - Thickness - CornerSize + j, c, 255);
				}
			}
		}
	}
}

void FullDiamondInImage(Image& image, FrameData DataOfFrame)
{
	int CornerSize = min(DataOfFrame.FrameWidth, DataOfFrame.FrameHeight);
	int Radius = CornerSize / 2;
	int Center = CornerSize / 2;
	for (int i = 0; i < CornerSize; i++)
	{
		for (int j = 0; j < CornerSize; j++)
		{
			if (abs(i - Center) + (abs(j - Center)) <= Radius)
			{

				for (int x = 0; x < image.width; x += CornerSize)
				{
					if ((x + i) < image.width && (image.height - CornerSize + j) < image.height)
					{
						image.setPixel(x + i, j, 0, 255);
						image.setPixel(x + i, j, 1, 215);
						image.setPixel(x + i, j, 2, 0);

						image.setPixel(i + x, image.height - CornerSize + j, 0, 255);
						image.setPixel(i + x, image.height - CornerSize + j, 1, 215);
						image.setPixel(i + x, image.height - CornerSize + j, 2, 0);
					}

				}
				for (int y = 0; y < image.height; y += CornerSize)
				{
					if ((j + y) < image.height && (image.width - CornerSize + i) < image.width)
					{
						image.setPixel(i, j + y, 0, 255);
						image.setPixel(i, j + y, 1, 215);
						image.setPixel(i, j + y, 2, 0);

						image.setPixel(image.width - CornerSize + i, j + y, 0, 255);
						image.setPixel(image.width - CornerSize + i, j + y, 1, 215);
						image.setPixel(image.width - CornerSize + i, j + y, 2, 0);
					}
				}

			}
		}
	}
}
void DiagonalStripesInImage(Image& image, FrameData DataOfFrame)
{
	int CornerSize = min(DataOfFrame.FrameHeight, DataOfFrame.FrameWidth);
	for (int i = 0; i < CornerSize; i++)
	{
		for (int j = 0; j < CornerSize; j++)
		{
			if ((i + j) % 4 == 0)
			{
				for (int x = 0; x < image.width; x += CornerSize)
				{
					if ((x + i) < image.width && j < image.height)
					{
						image.setPixel(x + i, j, 0, 255);
						image.setPixel(x + i, j, 1, 215);
						image.setPixel(x + i, j, 2, 0);
					}

					if ((x + i) < image.width && ((image.height - CornerSize + j) < image.height))
					{
						image.setPixel(i + x, image.height - CornerSize + j, 0, 255);
						image.setPixel(i + x, image.height - CornerSize + j, 1, 215);
						image.setPixel(i + x, image.height - CornerSize + j, 2, 0);
					}
				}
				for (int y = 0; y < image.height; y += CornerSize)

				{
					if ((j + y) < image.height && i < image.width)
					{
						image.setPixel(i, j + y, 0, 255);
						image.setPixel(i, j + y, 1, 215);
						image.setPixel(i, j + y, 2, 0);
					}
					if ((j + y) < image.height && (image.width - CornerSize + i) < image.width)
					{
						image.setPixel(image.width - CornerSize + i, j + y, 0, 255);
						image.setPixel(image.width - CornerSize + i, j + y, 1, 215);
						image.setPixel(image.width - CornerSize + i, j + y, 2, 0);
					}
				}
			}
		}
	}
}
enum StyleOfDoubleBorderWithCornerPatterns { CornerWhiteSquares = 1, CorenerDiamond = 2, FullDiamond = 3, DiagonalStripes = 4 };
void DoubleBorderWithCornerPatterns(Image& image)
{
	int StyleNum;
	do
	{
		cout << "Please,Enter What Style Of Double Border With Corner Patterns do You Want? CornerWhiteSquares[1] ,CornerDiamond[2] ,FullDiamond[3],DiagonalStripes[4]\n";
		cin >> StyleNum;
	} while (StyleNum != 1 && StyleNum != 2 && StyleNum != 3 && StyleNum != 4);
	StyleOfDoubleBorderWithCornerPatterns Styles = StyleOfDoubleBorderWithCornerPatterns(StyleNum);
	FrameData DataOfFrame = ReadData();
	SimpleFrame(image, DataOfFrame);
	FrameData SecondFrame = HelperFunGetSecondFrame();
	int Gap = 0;
	int Thickness = 3;
	InnerFrame(image, DataOfFrame, SecondFrame, Gap, Thickness);
	if (Styles == CornerWhiteSquares)
	{
		WhiteSquaresinCorner(image, DataOfFrame, Thickness);

	}
	else if (Styles == CorenerDiamond)
	{
		DiamondInCorners(image, DataOfFrame, Thickness);
	}
	else if (Styles == FullDiamond)
	{
		FullDiamondInImage(image, DataOfFrame);
	}
	else
	{
		DiagonalStripesInImage(image, DataOfFrame);
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
	default:
		cout << "Wrong Choice,Please Try Again\n";
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


enum TypeOfResize { Ratio = 1, Dimensions = 2 };
void ResizeImage(Image& image)
{
	int ChooseResize;
	do
	{
		cout << "Would you like to resize the image by Ratio or Dimensions? Ratio[1] , Dimensions[2]\n";
		cin >> ChooseResize;
	} while (ChooseResize != 1 && ChooseResize != 2);

	int NewWidth, NewHeight;
	TypeOfResize Resize = TypeOfResize(ChooseResize);

	if (Resize == Ratio)
	{
		double ratio;
		do
		{
			cout << "PLease,Enter the Ratio Number to  resize the image\n";
			cin >> ratio;
		} while (ratio <= 0);
		NewWidth = max(1, (int)(image.width * ratio));
		NewHeight = max(1, (int)(image.height * ratio));
	}
	else if (Resize == Dimensions)
	{
		int WidthNumber, HeightNumber;
		do
		{
			cout << "Please,Enter the New Width to resize the image\n";
			cin >> WidthNumber;
		} while (WidthNumber <= 0);
		do
		{
			cout << "Please,Enter the New Height to  resize the image\n";
			cin >> HeightNumber;
		} while (HeightNumber <= 0);
		NewWidth = WidthNumber;
		NewHeight = HeightNumber;
	}
	Image NewImage(NewWidth, NewHeight);
	double ScaleWidth = (double)image.width / NewImage.width;
	double ScaleHeight = (double)image.height / NewImage.height;
	for (int i = 0; i < NewImage.width; i++)
	{
		for (int j = 0; j < NewImage.height; j++)
		{
			int OldWidth = i * ScaleWidth;
			int OldHeight = j * ScaleHeight;
			for (int c = 0; c < 3; c++)
			{
				NewImage.setPixel(i, j, c, image.getPixel(OldWidth, OldHeight, c));
			}
		}
	}
	image = NewImage;
}
void ResizeFlow() {
	Image UserImage;
	LoadImage(UserImage, "Enter Image FileName to Resize Image : ");
	ResizeImage(UserImage);
	SaveImage(UserImage, "Enter Image FileName To Save: ");
}
// Filter 9: Merge // 
void ResizeImageInternal(const Image& src, int targetW, int targetH, Image& resized) {
    resized = Image(targetW, targetH);
    for (int y = 0; y < targetH; ++y) {
        for (int x = 0; x < targetW; ++x) {
            int srcX = (x * src.width) / targetW;
            int srcY = (y * src.height) / targetH;
            for (int c = 0; c < src.channels; ++c) {
                resized(x, y, c) = src(srcX, srcY, c);
            }
        }
    }
}
void MergeImages(const Image& img1, const Image& img2, int targetW, int targetH, Image& output) {
    output = Image(targetW, targetH);
    for (int y = 0; y < targetH; ++y) {
        for (int x = 0; x < targetW; ++x) {
            for (int c = 0; c < img1.channels; ++c) {
                output(x, y, c) = (img1(x, y, c) + img2(x, y, c)) / 2;
            }
        }
    }
}
void MergeFlow() {
    Image img1, img2;
    LoadImage(img1, "Enter first image filename to Merge: ");
    LoadImage(img2, "Enter second image filename to Merge: ");

    int targetW = max(img1.width, img2.width);
    int targetH = max(img1.height, img2.height);

    Image resized1, resized2, result;
    ResizeImageInternal(img1, targetW, targetH, resized1);
    ResizeImageInternal(img2, targetW, targetH, resized2);

    MergeImages(resized1, resized2, targetW, targetH, result);
    SaveImage(result, "Enter image filename to save merged image: ");
}
// Filter 10 Detect Edges
void DetectImageEdgesFilter( Image &UserImage) {
    GrayScale(UserImage);
    Image EdgedImage(UserImage.width,UserImage.height);
    for (int i=0;i<EdgedImage.width;i++) {
        for (int j=0;j<EdgedImage.height;j++) {
            for (int k=0;k<3;k++) {
                EdgedImage(i,j,k)=255;
            }
        }
    }
    for (int i=1;i<EdgedImage.width-1;i++) {
        for (int j=1;j<EdgedImage.height-1;j++) {
            int Gradient_X=UserImage(i,j+1,0)-UserImage(i,j-1,0);
            int Gradient_Y=UserImage(i+1,j,0)-UserImage(i-1,j,0);
            int Threshold=128;
            if (abs(Gradient_X)+abs(Gradient_Y)>Threshold) {
                EdgedImage(i,j,0)=0;
                EdgedImage(i,j,1)=0;
                EdgedImage(i,j,2)=0;
            }
            else {
                EdgedImage(i,j,0)=255;
                EdgedImage(i,j,1)=255;
                EdgedImage(i,j,2)=255;
            }
        }
    }
    UserImage=EdgedImage;
}
// Flow Detect Edges //
void DetectFlow() {
    Image UserImage;
    LoadImage(UserImage, "Enter image filename for Detecting Edges : ");
    DetectImageEdgesFilter(UserImage);
    SaveImage(UserImage, "Enter image filename to save: ");
}

//Filter 11: Crop
void CropImage(Image &image) {
	int x, y, width, height;

	cout << "Enter x, y, width, and height: ";
	cin >> x >> y >> width >> height;
	while (x < 0  || y < 0||
		  width <= 0 ||   height <= 0 ||
		  x + width > image.width// out of width of photo
		  ||
		  y + height > image.height)//out of height of photo
	{
		cout << "Invalid crop dimensions. Please enter valid values.\n";
		cout << "Enter x, y, width, and height: ";
		cin >> x >> y >> width >> height;
	}
	Image cropped(width,height);
	for (int i=0;i<width;++i) {
		for (int j=0;j<height;j++) {
			for (int k=0;k<3;++k) {
				cropped(i,j,k)=image(x+i,y+j,k);
			}
		}
	}


	image = cropped;
}


void CropImageFlow() {
	Image UserImage;
	LoadImage(UserImage, "Enter image filename for CropImage : ");
	CropImage(UserImage);
	SaveImage(UserImage, "Enter image filename to save: ");
}


// Filter 13: Sunlight //
void SunLightFilter(Image& image) {
    for (int y = 0; y < image.height; ++y) {
        for (int x = 0; x < image.width; ++x) {
            int r = image(x, y, 0) + 40;
            image(x, y, 0) = min(255, r);
            int g = image(x, y, 1) + 25;
            image(x, y, 1) = min(255, g);
            int b = image(x, y, 2) - 20;
            image(x, y, 2) = max(0, b);
        }
    }
}

// Flow Sunlight //
void SunLightFlow() {
    Image userImage;
    LoadImage(userImage, "Enter image filename for Sunlight filter: ");
    SunLightFilter(userImage);
    SaveImage(userImage, "Enter image filename to save: ");
}
enum LevelOfBlur { Light = 1, Medium = 2, Heavy = 3 };
void BlurImage(Image& image)
{
	Image NewBlurImage(image.width, image.height);
	int Num;
	do
	{
		cout << "What Level Of Blur You Want In This Image?Light [1] , Medium[2] , Heavy [3]? Please,Enter The Level\n";
		cin >> Num;
	} while (Num < 1 || Num>3);
	LevelOfBlur Level = LevelOfBlur(Num);
	int Rad = Level;
	for (int i = 0; i < image.width; i++)
	{
		for (int j = 0; j < image.height; j++)
		{
			int RedSum = 0;
			int GreenSum = 0;
			int BlueSum = 0;
			int Count = 0;
			for (int x = i - Rad; x <= i + Rad; x++)
			{
				for (int y = j - Rad; y <= j + Rad; y++)
				{
					if (x >= 0 && x < image.width && y >= 0 && y < image.height)
					{
						RedSum += image.getPixel(x, y, 0);
						GreenSum += image.getPixel(x, y, 1);
						BlueSum += image.getPixel(x, y, 2);
						Count++;
					}
				}
			}
			NewBlurImage.setPixel(i, j, 0, RedSum / Count);
			NewBlurImage.setPixel(i, j, 1, GreenSum / Count);
			NewBlurImage.setPixel(i, j, 2, BlueSum / Count);

		}
	}
	image = NewBlurImage;
}

void BlurFlow() {
	Image userImage;
	LoadImage(userImage, "Enter Image Filename for Blur filter: ");
	BlurImage(userImage);
	SaveImage(userImage, "Enter image filename to save: ");
}
// Filter TV
double GetDarkFactor() {
    double DarkFactor=0;
    while (true) {
        cout<<"Enter The Darkness Factor (0.5 to 0.7,inclusive) "<<endl;
        cin>>DarkFactor;
        if (DarkFactor>=0.5 && DarkFactor<=0.7) {
            break;
        }
        else {
            cout<<"Invalid Input, try again."<<endl;
        }
    }
    return DarkFactor;
}
void TVImageFilter(Image &UserImage) {
    double DarkFactor=GetDarkFactor();
    for (int i=0;i<UserImage.height;i+=2) {
        for (int j=0;j<UserImage.width;j++) {
            for (int k=0;k<3;k++) {
                UserImage(j,i,k)*=DarkFactor;
            }
        }
    }
}
void TVFlow() {
	Image userImage;
	LoadImage(userImage, "Enter Image Filename for Blur filter: ");
	TVImageFilter(userImage);
	SaveImage(userImage, "Enter image filename to save: ");
}
// Filter 15  look purple
void Purple(Image &image) {
	for (int i=0;i<image.width;++i) {
		for (int j=0;j<image.height;++j) {
			// Red --> k = 0
			int red = image(i, j, 0);
			red = red + (red * 20 / 100);

			if (red > 255)
				red = 255;

			image(i, j, 0) = red;//update the old value of red with the new value


			// Green --> k = 1
			int green = image(i, j, 1);
			green = green - (green * 20 / 100);

			if (green < 0)
				green = 0;

			image(i, j, 1) = green;//update value


			// Blue --> k = 2
			int blue = image(i, j, 2);
			blue = blue + (blue * 20 / 100);

			if (blue > 255)
				blue = 255;

			image(i, j, 2) = blue;
		}


	}}

	void PurpleFlow() {
		Image UserImage;
		LoadImage(UserImage, "Enter image filename for Purple Filter: : ");
		Purple(UserImage);
		SaveImage(UserImage, "Enter image filename to save: ");
	}

	void InfraredRadiation(Image& image)
	{
		for (int i = 0; i < image.width; i++)
		{
			for (int j = 0; j < image.height; j++)
			{
				image.setPixel(i, j, 0, 255);
				int Green = 255 - image.getPixel(i, j, 1);
				int Blue = 255 - image.getPixel(i, j, 2);
				image.setPixel(i, j, 1, Green);
				image.setPixel(i, j, 2, Blue);
			}
		}
	}

	void InfraredFlow() {
		Image UserImage;
		LoadImage(UserImage, "Enter image filename for Infrared Radiation Filter: : ");
		InfraredRadiation(UserImage);
		SaveImage(UserImage, "Enter image filename to save: ");
	}

void OilPainting(Image &image)
{
    Image result = image;

    int radius = 4;
    int levels = 10;

    for (int i = 0; i < image.width; i++)
    {
        for (int j = 0; j < image.height; j++)
        {
            int intensityCount[256] = {0};
            int redSum[256] = {0};
            int greenSum[256] = {0};
            int blueSum[256] = {0};

            for (int x = max(0, i - radius); x <= min(image.width - 1, i + radius); x++)
            {
                for (int y = max(0, j - radius); y <= min(image.height - 1, j + radius); y++)
                {
                    int r = image(x, y, 0);

                    int g = image(x, y, 1);

                    int b = image(x, y, 2);

                    int curIntensity = ((r + g + b) / 3) * levels / 256;

                    if (curIntensity >= levels) curIntensity = levels - 1;

                    intensityCount[curIntensity]++;
                    redSum[curIntensity] += r;
                    greenSum[curIntensity] += g;
                    blueSum[curIntensity] += b;
                }
            }


            int maxLevel = 0;
            for (int k = 1; k < levels; k++)
            {
                if (intensityCount[k] > intensityCount[maxLevel])
                {
                    maxLevel = k;
                }
            }


            if (intensityCount[maxLevel] > 0)
            {
                result(i, j, 0) = redSum[maxLevel] / intensityCount[maxLevel];
                result(i, j, 1) = greenSum[maxLevel] / intensityCount[maxLevel];
                result(i, j, 2) = blueSum[maxLevel] / intensityCount[maxLevel];
            }
        }
    }

    image = result;


}

void OilPaintingFlow() {
	Image UserImage;
	LoadImage(UserImage, "Enter image filename for OilPainting Filter: : ");
	OilPainting(UserImage);
	SaveImage(UserImage, "Enter image filename to save: ");
}

// 1.Horizontal Skew
void SkewHorizontal(Image& image, double angleDegree) {
    const double PI = 3.14159265358979323846;
    double rad = (angleDegree * PI) / 180.0;
    int shift = abs((int)(image.height * tan(rad)));
    Image skewed(image.width + shift, image.height);
    for (int y = 0; y < skewed.height; ++y)
        for (int x = 0; x < skewed.width; ++x)
            for (int c = 0; c < skewed.channels; ++c)
                skewed(x, y, c) = 255;
    for (int y = 0; y < image.height; ++y) {
        int currentShift = (int)((image.height - 1 - y) * tan(rad));
        for (int x = 0; x < image.width; ++x) {
            for (int c = 0; c < image.channels; ++c) {
                skewed(x + currentShift, y, c) = image(x, y, c);
            }
        }
    }
    image = skewed;
}

// 2. Vertical Skew
void SkewVertical(Image& image, double angleDegree) {
    const double PI = 3.14159265358979323846;
    double rad = (angleDegree * PI) / 180.0;
    int shift = abs((int)(image.width * tan(rad)));
    Image skewed(image.width, image.height + shift);
    for (int y = 0; y < skewed.height; ++y)
        for (int x = 0; x < skewed.width; ++x)
            for (int c = 0; c < skewed.channels; ++c)
                skewed(x, y, c) = 255;
    for (int x = 0; x < image.width; ++x) {
        int currentShift = (int)(x * tan(rad));
        for (int y = 0; y < image.height; ++y) {
            for (int c = 0; c < image.channels; ++c) {
                skewed(x, y + currentShift, c) = image(x, y, c);
            }
        }
    }
    image = skewed;
}
void SkewImageFlow() {
    Image userImage;
    LoadImage(userImage, "Enter image filename for Skewing: ");
    int dirChoice;
    cout << "\nChoose Skew Direction:\n";
    cout << "1. Skew Horizontally\n";
    cout << "2. Skew Vertically\n";
    cout << "Enter your choice (1 or 2): ";
    cin >> dirChoice;
    while (dirChoice != 1 && dirChoice != 2) {
        cout << "Invalid choice! Enter 1 or 2: ";
        cin >> dirChoice;
    }
    double angle;
    cout << "Enter skew angle in degrees: ";
    cin >> angle;
    if (dirChoice == 1) {
        SkewHorizontal(userImage, angle);
    } else {
        SkewVertical(userImage, angle);
    }
    SaveImage(userImage, "Enter image filename to save: ");
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
        case EnFilterOptions::Darken:
        {
            DarkenImageFlow();
            FiltersMenu();
            break;
        }
        case EnFilterOptions::Lighten:
        {
            LightenImageFlow();
            FiltersMenu();
            break;
        }
        case EnFilterOptions::Rotate:
        {
            RotateFlow();
            FiltersMenu();
            break;
        }
        case EnFilterOptions::Resize:
        {
            ResizeFlow();
            FiltersMenu();
            break;
        }
        case EnFilterOptions::Merge:
        {
            MergeFlow();
            FiltersMenu();
            break;
        }
        case EnFilterOptions::DetectEdges:
        {
            DetectFlow();
            FiltersMenu();
            break;
        }
        case EnFilterOptions::CropImage:
        {
            CropImageFlow();
            FiltersMenu();
            break;
        }
        case EnFilterOptions::SunLight:
        {
            SunLightFlow();
            FiltersMenu();
            break;
        }
		case EnFilterOptions::Blur:
		{
			BlurFlow();
			FiltersMenu();
			break;
		}
		case EnFilterOptions::TV:
		{
			TVFlow();
			FiltersMenu();
			break;
		}
        case EnFilterOptions::Purple:
		{
            PurpleFlow();
            FiltersMenu();
            break;
         }
	     
		case  EnFilterOptions::Infrared:
		{
			InfraredFlow();
			FiltersMenu();
			break;
		}

        case EnFilterOptions::OilPainting:{
        OilPaintingFlow();
        FiltersMenu();
        break;
          }

		case EnFilterOptions::SkewImage:
        {
            SkewImageFlow();
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
    cout<< "=================================\n";
    cout<< "\t [1]   GrayScale Filter\n";
    cout<< "\t [2]   Black and White Filter\n";
    cout<< "\t [3]   Invert Filter\n";
	cout<< "\t [4]   Frame Image Filter\n";
	cout<< "\t [5]   Flip Image Filter\n";
	cout<< "\t [6]   Rotate Filter\n";
    cout<< "\t [7]   Darken Image Filter\n";
    cout<< "\t [8]   Lighten Image Filter\n";
	cout<< "\t [9]   Resize Image Filter\n";
	cout<< "\t [10]  Merge Images Filter\n";
	cout<< "\t [11]  Detect Image Edges\n";
    cout<< "\t [12]  Crop Image Filter\n";
    cout<< "\t [13]  Sunlight Filter\n";
	cout <<"\t [14]  Blur Image Filter\n";
	cout <<"\t [15]  TV Noise Image Filter\n";
    cout<< "\t [16]  Purple Image Filter\n";
	cout<< "\t [17]  Infrared Radiation Filter\n";
    cout<< "\t [18]  Skew Image Filter\n";
    cout<< "\t [19]  Oil Painting Filter\n";
    cout<< "\t [20]  Exit\n";
    cout<< "=================================\n";
    Start(GetChoice());
}
int main() {
    FiltersMenu();
    return 0;
}