//FileName: CS112_A3_Part1_S23_20230012_20230201_20230345.cpp
// Name : Ahmed Tamer Shawky && ID : 20230012 && filters: grayScale and Merge_Images and Flip_Image
// Name : Abdelrahman Ahmed && ID : 20230201 && filters: Black_white
// Name : Mohammed Essam Mahmoud && ID : 20230345 && filters: Invert_Image


#include "Image_Class.h"
#include <string>
using namespace std;
void main_menu();
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
    after_menu(user_img, user_img_s);
}

void Black_and_white(Image user_img, string user_img_s)
{
    //Convert image to grey scale
    for(int i = 0; i < user_img.width; ++i){
        for(int j = 0; j < user_img.height; j++){
            unsigned int grey = 0;

            for(int k = 0; k < 3; k++){

                grey += user_img(i,j,k) ;
            }
            grey /= 3;
            //change every pixel to gray scale
            for(int k = 0; k < 3; ++k){
                user_img(i,j,k) = grey;
            }
        }
    }
    //convert image to black and white
        for(int i = 0; i < user_img.width; ++i){
            for(int j = 0; j < user_img.height; j++){
                unsigned int black = 0;

                for(int k = 0; k < 3; k++){
                    black += user_img(i,j,k);
                }
                black /= 3;
                 //Threshold for pixels conversion
                 black = (black >= 128) ? 255 : 0;

                for(int k = 0; k < 3; k++){
                    user_img(i,j,k) = black;
                }
            }
        }
after_menu(user_img,user_img_s);

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
            case 3:
                Invert_Image(user_img, user_img_s);
            case 4:
                Merge_Images(user_img, user_img_s);
            case 5:
                Flip_Image(user_img,user_img_s);

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
int main()
{
    main_menu();
    return 0;
}
