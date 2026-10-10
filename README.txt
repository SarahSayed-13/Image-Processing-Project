Image Processing Application

Overview

The Image Processing Application is a user-friendly program that allows users to edit images using a Graphical User Interface (GUI). It provides a collection of image filters and transformation tools that can be applied easily without requiring command-line interaction.
Users can select an image, choose a filter, customize its settings when needed, preview or apply the effect, and save the resulting image.

Tools & Development Environment

Programming Language: C++ (C++17 standard)
GUI Framework: Qt Framework (Qt Widgets)
Integrated Development Environment (IDE): Qt Creator / Visual Studio Code
Compiler: MinGW (Minimalist GNU for Windows) 64-bit / GCC
Image Core Library: Custom Image_Class.h (based on stb_image and stb_image_write)
Version Control & Collaboration: Git & GitHub

How to Use the Application

1. Launch the Application: Open the program to display the main graphical interface.
2. Select an Image: Use the image selection button to browse for and open an image from your device.
3. Choose a Filter: Select the desired filter from the available filter buttons or menu.
4. Customize Settings: If the selected filter requires additional options, enter the requested values or select the desired settings through the GUI.
5. Apply the Filter: Click the Apply button or its equivalent to process the image.
6. Save the Result: Use the Save button to choose a filename and location for the edited image.
7. Continue Editing: Select another filter or load another image as supported by the application.

Note: The exact button names and interface layout may vary depending on the final GUI design.

---

Available Filters

1. Grayscale Filter

Converts a colored image into different shades of gray.

How to use it:

1. Open an image.
2. Select Grayscale.
3. Apply the filter.
4. Save the resulting image.

Result: A grayscale version of the original image.

2. Black and White Filter

Converts the image into pure black and white pixels.

How to use it:

1. Open an image.
2. Select Black and White.
3. Apply the filter.
4. Save the result.

Result: A high-contrast image containing black and white areas without intermediate gray shades.

3. Darken Filter

Reduces the brightness of the image.

How to use it:

1. Open an image.
2. Select Darken.
3. Set the darkening percentage using the available input control.
4. Apply the filter and save the image.

Settings: The percentage ranges from 0% to 100%.

Result: Higher percentages produce a darker image. At 0%, the image remains unchanged; at 100%, it becomes black.

4. Lighten Filter

Increases the brightness of the image.

How to use it:

1. Open an image.
2. Select Lighten.
3. Set the lightening percentage.
4. Apply the filter and save the result.

Settings: The percentage ranges from 0% to 100%.

Result: Higher percentages produce a brighter image. At 0%, the image remains unchanged; at 100%, it becomes white.

5. Invert Filter

Reverses the colors of the image.

How to use it:

1. Open an image.
2. Select Invert Colors.
3. Apply the filter.
4. Save the result.

Result: The image takes on a negative-like appearance, with each color replaced by its opposite.

6. Crop Filter

Removes unwanted parts of an image by selecting a rectangular region.

How to use it:

1. Open an image.
2. Select Crop.
3. Specify the starting position and the desired width and height using the GUI controls.
4. Apply the crop and save the result.

Settings:

- X: Horizontal starting position.
- Y: Vertical starting position.
- Width: Width of the selected region.
- Height: Height of the selected region.

Result: A new image containing only the selected area.

7. Purple Filter

Applies a purple color effect by increasing red and blue intensity while reducing green intensity.

How to use it:

1. Open an image.
2. Select Purple.
3. Apply the filter.
4. Save the edited image.

Result: An image with a stronger purple appearance.

8. Flip Filter

Mirrors an image horizontally or vertically.

How to use it:

1. Open an image.
2. Select Flip.
3. Choose one of the available options:
   - Horizontal Flip: Mirrors the image from left to right.
   - Vertical Flip: Mirrors the image from top to bottom.
4. Apply the transformation and save the result.

9. Merge Filter

Combines two images into a single image by blending their color values.

How to use it:
1. Select Merge.
2. Choose the first image.
3. Choose the second image.
4. If the images have different dimensions, select an available resizing or overlapping-area option.
5. Apply the merge and save the resulting image.

Result: A single image combining visual information from both selected images.

10. Sunlight Filter

Creates a warm, sunlight-like effect by adjusting the red, green, and blue color channels.

How to use it:

1. Open an image.
2. Select Sunlight.
3. Apply the filter.
4. Save the result.

Result: A warmer image with a sunlight-inspired appearance.

11. Rotate Filter

Rotates an image by a selected angle.

How to use it:

1. Open an image.
2. Select Rotate.
3. Choose the desired rotation angle:
   - 90°
   - 180°
   - 270°
4. Apply the rotation and save the result.

Result: The image is rotated according to the selected angle.

12. Detect Image Edges Filter

Highlights boundaries between different regions of an image.

How to use it:

1. Open an image.
2. Select Detect Edges.
3. Apply the filter.
4. Save the result.

Result: A simplified edge image that typically displays dark edges against a white background.

13. TV Filter

Creates a television-like effect using alternating darkened horizontal lines.

How to use it:

1. Open an image.
2. Select TV Effect.
3. Adjust the darkness factor if the interface requests it.
4. Apply the filter and save the result.

Settings: The darkness factor ranges from 0.5 to 0.7, inclusive.

Result: A striped image resembling a television screen effect.

14. Blur Filter

Softens an image by averaging the colors of neighboring pixels.

How to use it:

1. Open an image.
2. Select Blur.
3. Choose the desired blur level:
   - Light: Slight blur.
   - Medium: Moderate blur.
   - Heavy: Strong blur.
4. Apply the filter and save the result.

Result: The image becomes softer as the blur level increases.

15. Oil Painting Filter

Transforms an image into an oil-painting-like artwork by grouping nearby pixels according to their intensity.

How to use it:

1. Open an image.
2. Select Oil Painting.
3. Apply the filter.
4. Save the resulting image.

Result: A painterly effect with simplified color regions and a more artistic appearance.

16. Infrared Filter

Creates a false-color effect inspired by infrared imagery.

How to use it:

1. Open an image.
2. Select Infrared.
3. Apply the filter.
4. Save the result.

Result: A distinctive artificial color effect created by modifying the image's RGB channels.

17. Resize Filter

Changes the dimensions of an image.

How to use it:

1. Open an image.
2. Select Resize.
3. Choose a resizing method:
   - Resize by Ratio: Enter a positive scaling ratio.
   - Resize by Dimensions: Enter the desired width and height.
4. Apply the changes and save the result.

Result: An image resized according to the selected ratio or dimensions.

18. Frame Filter

Adds a decorative border around an image.

How to use it:

1. Open an image.
2. Select Frame.
3. Choose a frame style:
   - Simple Frame
   - Double Border
   - Double Border with Corner Patterns
4. Set the frame dimensions and color using the available controls.
5. Configure any additional options required by the selected style.
6. Apply the frame and save the result.

Result: An image surrounded by a customizable decorative border.

19. Skew Filter

Slants an image horizontally or vertically by a selected angle.

How to use it:

1. Open an image.
2. Select Skew.
3. Choose the desired direction:
   - Horizontal Skew: Slants the image sideways.
   - Vertical Skew: Slants the image vertically.
4. Set the skew angle between 1° and 89°.
5. Apply the transformation and save the result.

Result: The image appears slanted in the selected direction.

---

Saving and Managing Images

- Use the image selection control to load an image from your device.