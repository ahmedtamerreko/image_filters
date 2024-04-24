// FileName: CS112_A3_Part1_S23_20230012_20230201_20230345.cpp
//  Name : Ahmed Tamer Shawky && ID : 20230012 
//  Name : Abdelrahman Ahmed && ID : 20230201  
//  Name : Abdullah sharrawy

#include "Image_Class.h" // Assuming Image_Class.h defines the Image class
#include <iostream>
#include <cmath>
#include <math.h>
#include <string>
#include <algorithm> // for std::min
#include <vector>
using namespace std;
void televsion( string user_img_s);
void x_ray( string user_img_s);
void saturation(string user_img_s);
void main_menu();
bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}
void after_menu(Image user_img, string user_img_s)
{
    // Prompt the user to choose whether to save the image with the current name or another name
    cout << "Do you want to save new image's name as\n";
    cout << "[1] " << user_img_s;
    cout << "\n[2] Enter another name";

    string newString;
    int choice;
    cin >> choice;

    // Switch based on user choice
    switch (choice)
    {
    case 1:
        // Save the image with the current name
        user_img.saveImage(user_img_s);
        cout << "image edited successfully\n";
        // Return to the main menu
        main_menu();
        break;
    case 2:
        // If the user chooses to enter another name
        while (true)
        {
            cout << "please Enter the new name\n";
            cin.ignore();
            getline(cin, newString);
            try
            {
                // Attempt to save the image with the new name
                user_img.saveImage(newString);
                cout << "image edited successfully\n";
                // Return to the main menu
                main_menu();
            }
            catch (...)
            {
                // If there's an exception (e.g., wrong image extension), prompt the user to try again
                cout << "wrong image extension please try again\n";
                continue;
            }
        }
    default:
        // If the user enters an invalid choice
        cout << "Invalid choice. Please enter a number between 1 and 2.\n";
    }
}
void grayScale(Image user_img, string user_img_s)
{
    for (int i = 0; i < user_img.width; ++i)
    {
        for (int j = 0; j < user_img.height; ++j)
        {
            unsigned average = 0;
            for (int k = 0; k < 3; ++k)
            {
                average += user_img(i, j, k);
            }
            user_img.setPixel(i, j, 0, average / 3);
            user_img.setPixel(i, j, 1, average / 3);
            user_img.setPixel(i, j, 2, average / 3);
        }
    }
     
    after_menu(user_img  , user_img_s);
}

void Black_and_white(Image user_img, string user_img_s)
{
    // Convert image to grey scale
    for (int i = 0; i < user_img.width; ++i)
    {
        for (int j = 0; j < user_img.height; j++)
        {
            unsigned int grey = 0;

            for (int k = 0; k < 3; k++)
            {

                grey += user_img(i, j, k);
            }
            grey /= 3;
            // change every pixel to gray scale
            for (int k = 0; k < 3; ++k)
            {
                user_img(i, j, k) = grey;
            }
        }
    }
    // convert image to black and white
    for (int i = 0; i < user_img.width; ++i)
    {
        for (int j = 0; j < user_img.height; j++)
        {
            unsigned int black = 0;

            for (int k = 0; k < 3; k++)
            {
                black += user_img(i, j, k);
            }
            black /= 3;
            // Threshold for pixels conversion
            black = (black >= 128) ? 255 : 0;

            for (int k = 0; k < 3; k++)
            {
                user_img(i, j, k) = black;
            }
        }
    }
    after_menu(user_img, user_img_s);
}
// Function to invert the colors of an image
void Invert_Image(Image user_img, string user_img_s)
{
    // Iterate over each pixel in the image
    for (int i = 0; i < user_img.width; ++i)
    {
        for (int j = 0; j < user_img.height; ++j)
        {
            int X = 0;
            // Iterate over each color channel of the pixel
            for (int k = 0; k < user_img.channels; ++k)
            {
                // Invert the color value by subtracting it from 255
                X = 255 - user_img(i, j, k);
                // Assign the inverted color value back to the image
                user_img(i, j, k) = X;
            }
        }
    }
    // Call a function after the image inversion is done, possibly to perform further operations
    after_menu(user_img, user_img_s);
}
void Merge_Images(Image user_img, string user_img_s)
{
    Image user_img2;
    while (true)
    {
        string user_img_s2;
        Image newimg;
        cout << "please upload the second image you want to merge with\n";
        cin.ignore();
        getline(cin, user_img_s2);
        try
        {
            user_img2.loadNewImage(user_img_s2);
            break;
        }
        catch (...)
        {
            cout << "wrong image name\n";
            continue;
        }
    }
    int choice_dimension;
    int w1 = user_img.width;
    int h1 = user_img.height;
    int w2 = user_img2.width;
    int h2 = user_img2.height;
    cout << "do you want the new merged image dimension as\n";
    cout << "[1] dimension of the first image "
         << "width = " << user_img.width << " height = " << user_img.height;
    cout << "\n[2] dimension of the second image "
         << "width = " << user_img2.width << " height = " << user_img2.height;
    cin >> choice_dimension;
    while (true)
    {
        if (choice_dimension == 1)
        {
            Image newimg(user_img.width, user_img.height);
            for (int i = 0; i < user_img.width; ++i)
            {
                for (int j = 0; j < user_img.height; ++j)
                {
                    int x = i * w1 / w2; // Map i from img2 to img1
                    int y = j * h1 / h2; // Map j from img2 to img1

                    // Average pixel values from both images
                    unsigned ave = (user_img(x, y, 0) + user_img2(i, j, 0)) / 2;
                    unsigned ave1 = (user_img(x, y, 1) + user_img2(i, j, 1)) / 2;
                    unsigned ave2 = (user_img(x, y, 2) + user_img2(i, j, 2)) / 2;

                    // Set pixel values in the new image
                    newimg.setPixel(i, j, 0, ave);
                    newimg.setPixel(i, j, 1, ave1);
                    newimg.setPixel(i, j, 2, ave2);
                }
            }
            after_menu(newimg, user_img_s);
        }
        else if (choice_dimension == 2)
        {
            Image newimg(user_img2.width, user_img2.height);
            for (int i = 0; i < user_img2.width; ++i)
            {
                for (int j = 0; j < user_img2.height; ++j)
                {
                    int x = i * w1 / w2; // Map i from img1 to img2
                    int y = j * h1 / h2; // Map j from img1 to img2

                    // Average pixel values from both images
                    unsigned ave = (user_img(x, y, 0) + user_img2(i, j, 0)) / 2;
                    unsigned ave1 = (user_img(x, y, 1) + user_img2(i, j, 1)) / 2;
                    unsigned ave2 = (user_img(x, y, 2) + user_img2(i, j, 2)) / 2;

                    // Set pixel values in the new image
                    newimg.setPixel(i, j, 0, ave);
                    newimg.setPixel(i, j, 1, ave1);
                    newimg.setPixel(i, j, 2, ave2);
                }
            }
            after_menu(newimg, user_img_s);
        }
        else
        {
            cout << "invalid choice please enter 1 or 2 only\n";
        }
    }
}
// Function to flip an image horizontally or vertically based on user input
void Flip_Image(Image user_img, string user_img_s)
{
    // Loop to continuously prompt the user for flipping options
    while (true)
    {
        // Prompt the user for flipping choice
        cout << "Do you want to flip it?\n";
        cout << "[1] Horizontally\n";
        cout << "[2] Vertically\n";

        int choice;
        cin >> choice;

        // Flip horizontally
        if (choice == 1)
        {
            // Create a new image with the same dimensions as the original image
            Image newimg(user_img.width, user_img.height);

            // Iterate over each pixel in the original image
            for (int i = user_img.width - 1; i >= 0; i--)
            {
                for (int j = 0; j < user_img.height; j++)
                {
                    // Copy pixel values from original image to the new image with horizontal flip
                    for (int k = 0; k < 3; ++k)
                    {
                        unsigned ave = user_img(i, j, 0);
                        unsigned ave1 = user_img(i, j, 1);
                        unsigned ave2 = user_img(i, j, 2);
                        newimg.setPixel(user_img.width - i, j, 0, ave);
                        newimg.setPixel(user_img.width - i, j, 1, ave1);
                        newimg.setPixel(user_img.width - i, j, 2, ave2);
                    }
                }
            }
            // Call a function after flipping the image
            after_menu(newimg, user_img_s);
        }
        // Flip vertically
        else if (choice == 2)
        {
            // Create a new image with the same dimensions as the original image
            Image newimg(user_img.width, user_img.height);

            // Iterate over each pixel in the original image
            for (int i = 0; i < user_img.width; i++)
            {
                for (int j = user_img.height - 1; j >= 0; j--)
                {
                    // Copy pixel values from original image to the new image with vertical flip
                    for (int k = 0; k < 3; ++k)
                    {
                        unsigned ave = user_img(i, j, 0);
                        unsigned ave1 = user_img(i, j, 1);
                        unsigned ave2 = user_img(i, j, 2);
                        newimg.setPixel(i, user_img.height - j, 0, ave);
                        newimg.setPixel(i, user_img.height - j, 1, ave1);
                        newimg.setPixel(i, user_img.height - j, 2, ave2);
                    }
                }
            }
            // Call a function after flipping the image
            after_menu(newimg, user_img_s);
        }
        else
        {
            // Notify the user of an invalid choice
            cout << "Invalid choice. Please enter 1 or 2 only.\n";
        }
    }
}

void Darken_and_lighten_Image(Image user_img, string user_img_s)
{
    int percent;
    string choice;
    while (true)
    {
        cout << "please enter what do you want\n";
        cout << "[1] lighten image\n";
        cout << "[2] darken image\n";
        cin >> choice;
        if (choice == "1" || choice == "2")
        {
            while (true)
            {
                cout << "chooce the percentage you want from 1 to 200\n";
                cin >> percent;
                if (percent < 1 || percent > 200)
                {
                    cout << "percentage is wrong try again\n";
                }
                else
                {
                    break;
                }
            }
            break;

        }
        else
        {
            cout << "try again\n";
        }
    }
    for (int i = 0; i < user_img.width; i++)
    {
        for (int j = 0; j < user_img.height; j++)
        {
            if (choice == "2")
            {
                unsigned pix = user_img(i, j, 0) / (2 + (percent / 100));
                unsigned pix1 = user_img(i, j, 1) / (2 + (percent / 100));
                unsigned pix2 = user_img(i, j, 2) / (2 + (percent / 100));
                user_img.setPixel(i, j, 0, pix);
                user_img.setPixel(i, j, 1, pix1);
                user_img.setPixel(i, j, 2, pix2);
            }
            if (choice == "1")
            {
                unsigned pix = user_img(i, j, 0) * (2 + (percent / 100));
                unsigned pix1 = user_img(i, j, 1) * (2 + (percent / 100));
                unsigned pix2 = user_img(i, j, 2) * (2 + (percent / 100));
                if (pix > 255)
                {
                    pix = 255;
                }
                if (pix1 > 255)
                {
                    pix1 = 255;
                }
                if (pix2 > 255)
                {
                    pix2 = 255;
                }
                user_img.setPixel(i, j, 0, pix);
                user_img.setPixel(i, j, 1, pix1);
                user_img.setPixel(i, j, 2, pix2);
            }
        }
    }
    after_menu(user_img, user_img_s);
}
void televsion( string user_img_s);
void detect_edges(Image user_img,string user_img_s){
Image img2 (user_img.width,user_img.height);
    for (int i = 0; i < user_img.width - 2; i++)
    {

        for (int j = 0; j < user_img.height - 2; j++)
        {
            img2.setPixel(i,j,0,255);
            img2.setPixel(i,j,1,255);
            img2.setPixel(i,j,2,255);


        }
    }

    for (int i = 0; i < user_img.width - 2; i++)
    {

        for (int j = 0; j < user_img.height - 2; j++)
        {
            unsigned completePix = user_img(i, j+1, 0);
            unsigned completePix2 = user_img(i, j, 0);
            unsigned pix1 = user_img(i, j, 1);
            unsigned pix2 = user_img(i, j, 2);
            if (completePix < completePix2 && completePix2 > 125 && completePix < 125)
            {
                img2.setPixel(i,j+1,0,0);
                img2.setPixel(i,j+1,1,0);
                img2.setPixel(i,j+1,2,0);
            }
            else if (completePix2 < completePix && completePix > 125 && completePix2 < 125)
            {
                img2.setPixel(i,j,0,0);
                img2.setPixel(i,j,1,0);
                img2.setPixel(i,j,2,0);
            }
        }
    }
    after_menu(img2,user_img_s);

}

void the_land_of_wano(Image user_img,string user_img_s){
    Image newimg(user_img.width, user_img.height);


    for (int i = 0; i < user_img.width; ++i) {
        for (int j = 0; j < user_img.height; ++j) {

            // Average pixel values from both images
            unsigned ave = (user_img(i, j, 0)+219)/2;
            unsigned ave1 = (user_img(i, j, 1)+219)/2;
            unsigned ave2 = (user_img(i, j, 2) +93) / 2;

            // Set pixel values in the new image
            newimg.setPixel(i, j, 0, ave);
            newimg.setPixel(i, j, 1, ave1);
            newimg.setPixel(i, j, 2, ave2);
        }
    }
    after_menu(newimg,user_img_s);
}


// Function to calculate luminosity (weighted average of RGB)
double getLuminosity(int r, int g, int b) {
  return (0.2126 * r + 0.7152 * g + 0.0722 * b);
}

void oil_painting(Image user_img,string user_img_s){
    cout << "please wait ...\n";
     // Create a new image for the adjusted result
  Image result(user_img.width, user_img.height);

  const int neighborhoodSize = 7; // Experiment with different sizes (3, 5, 7)
  int radius = (neighborhoodSize - 1) / 2;

  for (int i = radius; i < user_img.width - radius; i++) {
    for (int j = radius; j < user_img.height - radius; j++) {
      // Calculate intensity for each neighbor
      vector<double> intensities;
      for (int y = -radius; y <= radius; y++) {
        for (int x = -radius; x <= radius; x++) {
          int neighborX = i + x;
          int neighborY = j + y;
          // Check for image boundaries
          if (neighborX >= 0 && neighborX < user_img.width && neighborY >= 0 && neighborY < user_img.height) {
            int r = user_img(neighborX, neighborY, 0);
            int g = user_img(neighborX, neighborY, 1);
            int b = user_img(neighborX, neighborY, 2);
            intensities.push_back(getLuminosity(r, g, b));
          }
        }
      }

      // Find the index of the pixel with the closest intensity
      int closestIndex = std::min_element(intensities.begin(), intensities.end()) - intensities.begin();

      // Set the result pixel color to the color of the closest neighbor
      for (int k = 0; k < 3; k++) {
        int neighborX = i + radius - closestIndex % neighborhoodSize; // Adjust for indexing within neighborhood
        int neighborY = j + radius - closestIndex / neighborhoodSize;
        result(i, j, k) = user_img(neighborX, neighborY, k);
      }
    }
  }
  after_menu(result,user_img_s);
}

void luffy_look_purple(Image user_img,string user_img_s){
Image newimg(user_img.width, user_img.height);


    for (int i = 0; i < user_img.width; ++i) {
        for (int j = 0; j < user_img.height; ++j) {

            // Average pixel values from both images
            unsigned ave = (user_img(i, j, 0));
            unsigned ave1 = (user_img(i, j, 1));
            unsigned ave2 = (user_img(i, j, 2) );

            // Set pixel values in the new image
            newimg.setPixel(i, j, 0, ave);
            newimg.setPixel(i, j, 1, ave1*0.45);
            newimg.setPixel(i, j, 2, ave2);
        }
    }
    after_menu(newimg,user_img_s);
}
void skew_image(Image user_img,string user_img_s){

    Image newimg(user_img.width, user_img.height);
    for (int i = 0; i < newimg.width; ++i) {
        for (int j = 0; j < newimg.height; ++j) {
            // Average pixel values from both images
            unsigned ave = 255;
            unsigned ave1 = 255;
            unsigned ave2 = 255 ;

            // Set pixel values in the new image
            newimg.setPixel(i, j, 0, ave);
            newimg.setPixel(i,j, 1, ave1);
            newimg.setPixel(i, j, 2, ave2);
        }
    }
    for (int j = 0; j < newimg.height; ++j) {
    for (int i = 0; i < newimg.width; ++i) {
        // Calculate original coordinates
        int originalX = i - -0.8 * (j - user_img.width / 2);
        int originalY = j;

        // Check if original coordinates are within bounds of img1
        if (originalX >= 0 && originalX < user_img.width && originalY >= 0 && originalY < user_img.height) {
            // Get pixel values from img1
            unsigned pix = user_img.getPixel(originalX, originalY, 0);
            unsigned pix1 = user_img.getPixel(originalX, originalY, 1);
            unsigned pix2 = user_img.getPixel(originalX, originalY, 2);

            // Set pixel values in the new image    
            newimg.setPixel(i, j, 0, pix);
            newimg.setPixel(i, j, 1, pix1);
            newimg.setPixel(i, j, 2, pix2);
        }
    }
}
after_menu(newimg,user_img_s);
}
void adding_two_picture_together(Image user_img,string user_img_s){
    Image user_img2;
    string user_img_s2;
    while (true)
    {
        cout << "please upload the second image you want to merge with\n";
        cin.ignore();
        getline(cin, user_img_s2);
        try
        {
            user_img2.loadNewImage(user_img_s2);
            break;
        }
        catch (...)
        {
            cout << "wrong image name\n";
            continue;
        }
    }
Image newimg(user_img2.width, user_img2.height);
int w1 = user_img.width;
int h1 = user_img.height;
int w2 = user_img2.width;
int h2 = user_img2.height;

for (int i = 0; i < newimg.width; ++i) {
    for (int j = 0; j < newimg.height; ++j) {
        int x = i * w1 / w2; // Map i from img1 to img2
        int y = j * h1 / h2; // Map j from img1 to img2
        newimg(i,j,0) = user_img(x,y,0);
        newimg(i,j,1) = user_img(x,y,1);
        newimg(i,j,2) = user_img(x,y,2);
    }
}

    Image newimg_herzontal(newimg.width + user_img2.width, max(newimg.height, user_img2.height));
    for (int i = 0; i < newimg_herzontal.width; ++i)
    {
        for (int j = 0; j < newimg_herzontal.height; ++j)
        {
            if (i >= newimg.width - 1)
            {
                newimg_herzontal.setPixel(i, j, 0, user_img2(i-newimg.width+1, j, 0));
                newimg_herzontal.setPixel(i, j, 1, user_img2(i-newimg.width+1, j, 1));
                newimg_herzontal.setPixel(i, j, 2, user_img2(i-newimg.width+1, j, 2));
            }
            else
            {
                newimg_herzontal.setPixel(i, j, 0, newimg(i, j, 0));
                newimg_herzontal.setPixel(i, j, 1, newimg(i, j, 1));
                newimg_herzontal.setPixel(i, j, 2, newimg(i, j, 2));
            }
        }
    }
after_menu(newimg_herzontal,user_img_s);
}

void rotate(Image user_img,string user_img_s){
    while (true)
    {
       
    
    
    cout << "Welcome to image rotation : "
         << "Choose 1 to flip image 270 degrees: "
         << "Choose 2 to flip image 90 degrees : "
         << "Choose 3 to flip image 180 degrees : ";
    string choice;
    cin >> choice;

    //rotate image by 270 degrees
    if(choice == "1"){
        //creating blank image with the new dimensions
        Image result(user_img.height,user_img.width);

        for(int i = 0; i < user_img.width; ++i){
            for(int j = 0; j < user_img.height; j++){
                for(int k = 0; k < 3; k++){
                    //Filling the blank image with pixels
                    result(j,user_img.width - i - 1,k) = user_img( i, j,k);
                }
            }
        }
        after_menu(result,user_img_s);

    }
        //rotate image by 90 degrees
    else if(choice == "2"){
        //creating a blank image with new dimensions
        Image result(user_img.height,user_img.width);

        for(int i = 0; i < user_img.width; ++i){
            for(int j = 0; j < user_img.height; j++){
                for(int k = 0; k < 3; k++){
                    //filling the blank image with pixels
                    result(user_img.height - j - 1,i,k) = user_img( i, j,k);
                }
            }
        }
        after_menu(result,user_img_s);
    }
        //rotate image by 180 degrees
    else if(choice == "3"){
        //creating blank image to avoid segmentation error
        Image result(user_img.width,user_img.height);

        for(int i = 0; i < user_img.width; ++i){
            for(int j = 0; j < user_img.height; j++){
                for(int k = 0; k < 3; k++){
                    //filling each pixel
                    result(i,j,k) = user_img(user_img.width - 1 - i, user_img.height - 1 - j,k);
                }
            }
        }
        after_menu(result,user_img_s);
    }
    else cout << "Invalid choice Please try again :";
}

}

void crop_images(Image user_img,string user_img_s, int x, int y, int width, int height){
    //Initializing the dimensions of the cropped image
    Image cropped(width , height);
    //iterating of the pixels of the copped image
    for(int i = 0; i < width; ++i){
        for(int j = 0; j < height; j++){
            for(int k = 0; k < 3; k++){
                //adding the value of x (the starting pixel to from the old photo to i)
                cropped(i,j,k) = user_img(x + i, y + j,k);
            }
        }
    }
    after_menu(cropped,user_img_s);
}

void frame(Image user_img, string user_img_s) {
    int width = 50;
    int height = 50;

    // Initialize color values based on the input string
    int frame_r = 0, frame_g = 0, frame_b = 0;

    // Set frame color based on user input
    if (user_img_s == "red") {
        frame_r = 255;
        frame_g = 0;
        frame_b = 0;
    } else if (user_img_s == "blue") {
        frame_r = 0;
        frame_g = 0;
        frame_b = 255;
    } else if (user_img_s == "green") {
        frame_r = 0;
        frame_g = 255;
        frame_b = 0;
    } else if (user_img_s == "cyan") {
        frame_r = 0;
        frame_g = 255;
        frame_b = 255;
    } else if (user_img_s == "magenta") {
        frame_r = 255;
        frame_g = 0;
        frame_b = 255;
    } else if (user_img_s == "yellow") {
        frame_r = 255;
        frame_g = 255;
        frame_b = 0;
    } else if (user_img_s == "light blue") {
        frame_r = 173;
        frame_g = 216;
        frame_b = 230;
    } else if (user_img_s == "orange") {
        frame_r = 255;
        frame_g = 165;
        frame_b = 0;
    } else {
        // Default to black frame if color is not recognized
        frame_r = 0;
        frame_g = 0;
        frame_b = 0;
    }

    // Create a new image with a frame around the user image
    Image image_new(user_img.width + 2 * width, user_img.height + 2 * height);

    // Copy the user image into the new image with an offset
    for (int i = 0; i < user_img.width; i++) {
        for (int j = 0; j < user_img.height; j++) {
            for (int k = 0; k < 3; k++) {
                image_new(i + width, j + height, k) = user_img(i, j, k);
            }
        }
    }

    // Fill top and bottom parts of the frame with the specified color
    for (int i = 0; i < image_new.width; ++i) {
        for (int j = 0; j < height; ++j) {
            image_new(i, j, 0) = frame_r;
            image_new(i, j, 1) = frame_g;
            image_new(i, j, 2) = frame_b;

            image_new(i, image_new.height - 1 - j, 0) = frame_r;
            image_new(i, image_new.height - 1 - j, 1) = frame_g;
            image_new(i, image_new.height - 1 - j, 2) = frame_b;
        }
    }

    // Fill left and right parts of the frame with the specified color
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < image_new.height; ++j) {
            image_new(i, j, 0) = frame_r;
            image_new(i, j, 1) = frame_g;
            image_new(i, j, 2) = frame_b;

            image_new(image_new.width - 1 - i, j, 0) = frame_r;
            image_new(image_new.width - 1 - i, j, 1) = frame_g;
            image_new(image_new.width - 1 - i, j, 2) = frame_b;
        }
    }

    // Pass the new image to the next function
    after_menu(image_new, user_img_s);
}

void resize(Image user_img,string user_img_s,int width, int height){
    //Making new image with the new dimensions
    Image result(width,height);

    float r1 = (1.0 * user_img.width) / width; //Converting width to float the dividing to get a ratio
    float r2 = (1.0 * user_img.height) / height; //Converting height to float
    //Iterating over the new dimensions of the image
    for(int i = 0; i < width; ++i){
        for(int j = 0; j < height; j++){
            for(int k = 0; k < 3; k++){
                //Calculating the value of each pixel of the new image
                int new_width = round(i*r1);
                int new_height = round(j*r2);
                //equating the new image with the old image index new width and height
                result(i,j,k) = user_img(new_width,new_height,k);
            }
        }
    }
   after_menu(result,user_img_s);
}

void blur(Image user_img,string user_img_s, int blur) {
    // Check if blur is odd
    Image result(user_img.width, user_img.height);
    cout << "this filter take a time so please wait\n";
    if (blur % 2 == 0) {
        cout << "Blur size must be odd. Incrementing blur by 1." << endl;
        blur += 1;
    }
    // Adjust kernel size based on blur
    int kernel_size = blur;

    // Middle index of the kernel
    int middle = kernel_size / 2;

    // Loop through the image pixels
    for (int i = 0; i < user_img.width; ++i) {
        for (int j = 0; j < user_img.height; ++j) {
            vector<float> acc = {0, 0, 0};
            //looping from from left of the pixel to its right
            for (int a = -middle; a <= middle; ++a) {
                for (int b = -middle; b <= middle; ++b) {
                    int in = i + a; //Index of the pixel
                    int jn = j + b; //Index of the pixel
                    //makeing sure not to exced the image bounds and leaving the edges
                    if (in >= 0 && in < user_img.width && jn >= 0 && jn < user_img.height) {
                        // Apply kernel to the image pixel
                        for (int c = 0; c < 3; ++c) {
                            acc[c] += user_img(in, jn, c);
                        }
                    }
                }
            }
            // Update the result image
            for (int c = 0; c < 3; ++c) {
                result(i, j, c) = acc[c] / (kernel_size * kernel_size);
            }
        }
    }
    after_menu(result,user_img_s);
}

void main_menu()
{
    while (true)
    {
        cout << "\n\nWelcome to PhotoShop Editor\n";
        Image user_img;
        string user_img_s;
        cout << "Please enter the name of the image you want to apply edits on:\n";
        cout << "Please make sure that the image exists in this folder.\n";
        getline(cin, user_img_s);
        try
        {
            user_img.loadNewImage(user_img_s); // Added semicolon
            cout << "Please choose which filter you want to apply:\n";
            cout << "[1] Gray scale\n";
            cout << "[2] Black and white\n";
            cout << "[3] Invert Image\n";
            cout << "[4] Merge Images\n";
            cout << "[5] Flip Image\n";
            cout << "[6] rotate Image\n";
            cout << "[7] Darken and lighten Image\n";
            cout << "[8] crop image\n";
            cout << "[9] frame image\n";
            cout << "[10] Detect edges\n";
            cout << "[11] resizing image\n";
            cout << "[12] bluring image\n";
            cout << "[13] the land of wano\n";
            cout << "[14] oil painting\n";
            cout << "[15] televsion screen\n";
            cout << "[16] luffy look purple\n";
            cout << "[17] x-ray\n";
            cout << "[18] skew image\n";
            cout << "[19] saturation change \n";
            cout << "[20] adding two images together\n";
            // Add code here for applying selected filter
            int choice;
            cin >> choice;
            switch (choice)
            {
            case 1:
                grayScale(user_img, user_img_s);
                break;
            case 2:
                Black_and_white(user_img, user_img_s);
                break;
            case 3:
                Invert_Image(user_img, user_img_s);
                break;
            case 4:
                Merge_Images(user_img, user_img_s);
                break;
            case 5:
                Flip_Image(user_img, user_img_s);
                break;
            case 6:
                rotate(user_img,user_img_s);
                break;
            case 7:
                Darken_and_lighten_Image(user_img, user_img_s);
                break;
            case 8:
                while (true)
                {
                    string x,y,width,height;
                    cout << "please enter x (x-axis starting point)\n";
                    cin >> x;
                    cout << "please enter y (y-axis starting point)\n";
                    cin >> y;
                    cout << "please enter the width you want\n";
                    cin >> width;
                    cout << "please enter the height you want\n";
                    cin >> height;
                    if (is_number(x) && is_number(y) && is_number(width) && is_number(height)){
                    crop_images(user_img,user_img_s,stoi(x),stoi(y),stoi(width),stoi(height));
                    }
                    else{
                        cout << "wrong data you must enter integer numbers\n";
                        continue;
                    }
                }
                break;
            case 9:
                frame(user_img,user_img_s);
                break;
            case 10:
                detect_edges(user_img,user_img_s);
                break;
            case 11:
                int width,height;
                while(true){
                cout << "please enter the width you want\n";
                cin >> width;
                cout << "please enter the height you want\n";
                cin >> height;
                try{
                resize(user_img,user_img_s,width,height);
                }
                catch(...){
                    throw(width);
                    throw(height);
                    continue;
                }
                }
            case 12:
                int bluring;
                while(true){
                cout << "please enter the bluring degree you want\n";
                cin >> bluring;
                try{
                    blur(user_img,user_img_s,bluring);
                }
                catch(...){
                    throw(bluring);
                    continue;
                }
                }


            case 13:
                the_land_of_wano(user_img,user_img_s);
                break;
            case 14:
                oil_painting(user_img,user_img_s);
                break;
             case 15:
                 televsion(  user_img_s);
                break;
            case 16:
                luffy_look_purple(user_img,user_img_s);
                break;
            case 17:
                x_ray(user_img_s);
                break;
            case 18:
                skew_image(user_img,user_img_s);
                break;
            case 19:
               saturation( user_img_s);
            break;
            case 20:
                adding_two_picture_together(user_img,user_img_s);
                break;


            default:
                cout << "Invalid choice. Please enter a number between 1 and 5.\n";
            }
        }
        catch (...)
        {
            continue;
        }
    }
}
void televsion( string user_img_s);
void x_ray( string user_img_s);
void saturation(string user_img_s);
int main()
{
    main_menu();
    return 0;
}
void televsion( string user_img_s)
{
    int counter=2;
     // Open the image
  Image image(user_img_s);
  // Create a new image for the adjusted result
  Image new_image(image.width, image.height);

  
  // Iterate through each pixel and adjust brightness
  for (int i = 0; i < image.width; i++) {
    for (int j = 0; j < image.height; j++) {
        if(j%counter!=0 ){
      for (int channel = 0; channel < 3; channel++) {
        if(channel==0)
        new_image(i,j,channel)=image(i,j,channel)/2;
        else if(channel==1)
        new_image(i,j,channel)=image(i,j,channel)/2;
        else if(channel==2)
        new_image(i,j,channel)=image(i,j,channel)/2;
      }
      
        }
        else{
        for (int channel = 0; channel < 3; channel++) {
new_image(i,j,channel)=image(i,j,channel);
        }
        }
        
      }
      
    }
  after_menu(new_image,user_img_s);

};
void x_ray( string user_img_s)
{
    // Open the image
  Image image(user_img_s);
  // Create a new image for the adjusted result
  Image new_image(image.width, image.height);

  
  // Iterate through each pixel and adjust brightness
  for (int i = 0; i < image.width; i++) {
    for (int j = 0; j < image.height; j++) {
      for (int channel = 0; channel < 3; channel++) {
        if(channel==0)
        new_image(i,j,channel)=255;
        if(channel==1)
        new_image(i,j,channel)=-image(i,j,channel)+255;
        if(channel==2)
        new_image(i,j,channel)=-image(i,j,channel)+255;
      }
    }
  }

  after_menu(new_image,user_img_s);

};
void saturation(string user_img_s)
{
      // Open the image
  Image image(user_img_s);
  // Create a new image for the adjusted result
  Image new_image(image.width, image.height);

  
  // Iterate through each pixel and adjust brightness
  for (int i = 0; i < image.width; i++) {
    for (int j = 0; j < image.height; j++) {
      for (int channel = 0; channel < 3; channel++) {
        if(image(i,j,channel)>=128)
        new_image(i,j,channel)=255;
        else 
        new_image(i,j,channel)=0;
      }
      
        }
        }
 after_menu(new_image,user_img_s);
}
