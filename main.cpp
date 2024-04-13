#include "Image_Class.h"
#include <vector>
using namespace std;


Image copy(const Image &image){
    Image result(image.width,image.height);
    for(int i = 0; i < image.width; i++){
        for(int j = 0; j < image.height; j++){
            for (int k = 0; k < image.channels; k++){
                result(i,j,k) = image(i,j,k);
            }
        }
    }
    return result;
}

void Flip(Image &image )   {

    string choice;
    cin >> choice;

    //Declaring the image dimensions
    Image flipped_img(image.width,image.height);

    if(choice == "1"){
        //flip image horizontally
        for(int i = 0; i < image.width; i++){
            for(int j = 0; j < image.height; j++){
                for(int k = 0; k < 3; k++){
                    //fill the flipped_img pixels
                    flipped_img(i,j,k) = image(image.width - 1 - i,j,k);
                }
            }
        }
    }

    else if (choice == "2"){
        //flip image vertically
        for(int i = 0; i < image.width;i++){
            for(int j = 0; j < image.height; j++){
                for(int k = 0; k < 3; k++){
                    //fill the flipped_img pixels
                    flipped_img(i,j,k) = image(i,image.height - 1 - j ,k);
                }
            }
        }
    }
    else{
        cout << "Invalid choice please try again: ";
        return;
    }

    image = flipped_img;
}



void rotate(Image &image){

    cout << "Welcome to image rotation : "
         << "Choose 1 to flip image 270 degrees: "
         << "Choose 2 to flip image 90 degrees : "
         << "Choose 2 to flip image 180 degrees : ";
    string choice;
    cin >> choice;

    //rotate image by 270 degrees
    if(choice == "1"){
        //creating blank image with the new dimensions
        Image result(image.height,image.width);

        for(int i = 0; i < image.width; ++i){
            for(int j = 0; j < image.height; j++){
                for(int k = 0; k < 3; k++){
                    //Filling the blank image with pixels
                    result(j,image.width - i - 1,k) = image( i, j,k);
                }
            }
        }

    }
        //rotate image by 90 degrees
    else if(choice == "2"){
        //creating a blank image with new dimensions
        Image result(image.height,image.width);

        for(int i = 0; i < image.width; ++i){
            for(int j = 0; j < image.height; j++){
                for(int k = 0; k < 3; k++){
                    //filling the blank image with pixels
                    result(image.height - j - 1,i,k) = image( i, j,k);
                }
            }
        }
    }
        //rotate image by 180 degrees
    else if(choice == "3"){
        //creating blank image to avoid segmentation error
        Image result(image.width,image.height);

        for(int i = 0; i < image.width; ++i){
            for(int j = 0; j < image.height; j++){
                for(int k = 0; k < 3; k++){
                    //filling each pixel
                    result(i,j,k) = image(image.width - 1 - i, image.height - 1 - j,k);
                }
            }
        }
    }
    else cout << "Invalid choice Please try again :";
}

void brightness(Image &image ,int beta){
    for(int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; j++) {
            for (int k = 0; k < 3; k++) {

                int new_value = image(i,j,k) + beta;
                //Ensuring the value of doesn't get out of the range of the picture
                new_value = max(0,min(255,new_value));
                image(i,j,k) = new_value;
            }
        }
    }
}

void crop_images(Image &image, int x, int y, int width, int height){
    //Initializing the dimensions of the cropped image
    Image cropped(width , height);
    //iterating of the pixels of the copped image
    for(int i = 0; i < width; ++i){
        for(int j = 0; j < height; j++){
            for(int k = 0; k < 3; k++){
                //adding the value of x (the starting pixel to from the old photo to i)
                cropped(i,j,k) = image(x + i, y + j,k);
            }
        }
    }
    image = cropped;
}


void  frame(Image &image, string colour){
    int width =  50;
    int height =  50;
    Image image_new( image.width + 2 * width,  image.height + 2 * height);

    for(int i = 0; i < image.width; i++){
        for(int j = 0; j < image.height; j++){
            for(int k = 0; k < 3; k++){
                image_new(i + width ,j + height ,k) = image(i,j,k);
            }
        }
    }
    for (int i = 0; i < image_new.width; ++i) {
        for (int j = 0; j < height; ++j) {
            image_new(i, j, 0) = 0;
            image_new(i, j, 1) = 0;
            image_new(i, j, 2) = 0;

            image_new(i, image_new.height - 1 - j, 0) = 0;
            image_new(i, image_new.height - 1 - j, 1) = 0;
            image_new(i, image_new.height - 1 - j, 2) = 0;
        }
    }

    // Draw frame on the left and right sides
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < image_new.height; ++j) {
            image_new(i, j, 0) = 0;
            image_new(i, j, 1) = 0;
            image_new(i, j, 2) = 0;

            image_new(image_new.width - 1 - i, j, 0) = 0;
            image_new(image_new.width - 1 - i, j, 1) = 0;
            image_new(image_new.width - 1 - i, j, 2) = 0;
        }
    }

    image = image_new;
}


void blur(Image &image, int blur) {
    // Check if blur is odd
    Image result(image.width, image.height);
    if (blur % 2 == 0) {
        cout << "Blur size must be odd. Incrementing blur by 1." << endl;
        blur += 1;
    }
    // Adjust kernel size based on blur
    int kernel_size = blur;

    // Middle index of the kernel
    int middle = kernel_size / 2;

    // Loop through the image pixels
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            vector<float> acc = {0, 0, 0};
            //looping from from left of the pixel to its right
            for (int a = -middle; a <= middle; ++a) {
                for (int b = -middle; b <= middle; ++b) {
                    int in = i + a; //Index of the pixel
                    int jn = j + b; //Index of the pixel
                    //makeing sure not to exced the image bounds and leaving the edges
                    if (in >= 0 && in < image.width && jn >= 0 && jn < image.height) {
                        // Apply kernel to the image pixel
                        for (int c = 0; c < 3; ++c) {
                            acc[c] += image(in, jn, c);
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
    image = result;
}


void resize(Image &image,int width, int height){
    //Making new image with the new dimensions
    Image result(width,height);

    float r1 = (1.0 * image.width) / width; //Converting width to float the dividing to get a ratio
    float r2 = (1.0 * image.height) / height; //Converting height to float
    //Iterating over the new dimensions of the image
    for(int i = 0; i < width; ++i){
        for(int j = 0; j < height; j++){
            for(int k = 0; k < 3; k++){
                //Calculating the value of each pixel of the new image
                int new_width = round(i*r1);
                int new_height = round(j*r2);
                //equating the new image with the old image index new width and height
                result(i,j,k) = image(new_width,new_height,k);
            }
        }
    }
    image = result;
}



int main(){
    Image hello("luffy.jpg");
    //brightness(hello,-100);
    //crop_images(hello,700,700,500,500);
    //frame(hello,"red");
    blur(hello,20);
    hello.saveImage("2hello.png");

    Image hello2("luffy.jpg");
    blur(hello2,20);
    hello2.saveImage("hello.png");
}

