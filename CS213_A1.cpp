//====================================================================================
//======================================Part 2========================================
//Rawan Alaa Eldin Mohamed Nagib: 20250237 |||| filter: 1, 5, 9, 13, 17
//Aisha Ahmed Nibishy Farag:20250338 ||| filter: 2, 6, 10, 14, 18
//Malk Ayman Abdrab El Naby: 20250660 |||| filter: 3, 7, 11, 15
//Malak Hussein Hamed Mohamed: 20250662 |||| filter: 4, 8, 12, 16, GUI
//section: S15,16
//===================================================================================
//===================================================================================

#include <iostream>
#include "Image_Class.h"
#include <algorithm>
using namespace std;

void grayscale(Image& image){
for(int i = 0; i < image.width; i++ ){
for(int j = 0; j < image.height; j++){
int avg = (image(i, j , 0) + image(i, j , 1) + image(i, j, 2))/3;
image(i, j, 0) = avg;
image(i, j, 1) = avg;
image(i, j, 2) = avg;
}
}
}

void flip(Image& image){
string flipPosition;
cout << "Please enter the flip position (horizontal or vertical):";
cin >> flipPosition;
if(flipPosition == "horizontal"){
for(int i = 0; i < image.width/2; i++){
for(int j = 0; j < image.height; j++){
for(int k = 0; k < 3; k++){
int temp = image(i,j,k);
image(i,j,k) = image(image.width - 1 - i, j, k);
image(image.width - 1 - i, j , k) = temp;
}
}
}
}
else if(flipPosition == "vertical"){
for(int i = 0; i < image.width; i++){
for(int j = 0; j < image.height/2; j++){
for(int k = 0; k < 3; k++){
int temp = image(i,j,k);
image(i,j,k) = image(i, image.height - 1 - j, k);
image(i, image.height - 1 - j , k) = temp;
}
}
}
}
else{
cout << "Invalid flip position";
}
}


void blackandwhite(Image&image) {
for (int i = 0; i < image.width; i++) {
for (int j = 0; j < image.height; j++) {
unsigned int avr=0;
for (int k = 0; k < 3; k++) {
avr += image(i,j,k);
}
avr /=3;
if (avr<128) {
for (int k = 0; k < 3; k++) {
image(i,j,k) = 0;
}
}
else if (avr>=128) {
for (int k = 0; k < 3; k++) {
image(i,j,k) = 255;
}
}
}
}
}


void rotateimage(Image& image) {
int rotation_angle;
cout << "Please enter the rotation angle 90 , 180 , 270 : ";
cin >> rotation_angle;
int w=image.width, h=image.height;
if (rotation_angle == 90) {
Image rotated(h, w);
for (int i = 0; i < w; i++) {
for (int j = 0; j < h; j++) {
for (int k = 0; k < 3; k++) {
rotated(h-1-j, i, k) = image(i, j, k);
}
}
}
image = rotated;
}
else if (rotation_angle == 180) {
Image rotated(w, h);
for (int i = 0; i < w; i++) {
for (int j = 0; j < h; j++) {
for (int k = 0; k < 3; k++) {
rotated(w-1-i, h-1-j, k) = image(i, j, k);
}
}
}
image = rotated;
}
else if (rotation_angle == 270) {
Image rotated(h, w);
for (int i = 0; i < w; i++) {
for (int j = 0; j < h; j++) {
for (int k = 0; k < 3; k++) {
rotated(j, w-1-i, k) = image(i, j, k);
}
}
}
image=rotated;
}
else {
cout << "Invalid angle!" << endl;
}
}


void framer(Image &img){
int opt;
int t = min(img.width, img.height) / 10;
int t1 = min(img.width, img.height) / 15;
int t2 = min(img.width, img.height) / 30;

cout << R"(
1. Normal Frame
2. Fancy Frame

Choose a number: )";
cin >> opt;

    for (int x = 0; x < img.width; ++x){
        for(int y = 0; y < img.height; ++y){
            if(x < t || x >= img.width - t || y < t || y >= img.height - t){
                    img(x, y, 0) = 10;
                    img(x, y, 1) = 35;
                    img(x, y, 2) = 90;
                } 
            }
        }
    
    if (opt == 2){
            for (int x = 0; x < img.width; ++x){
                for(int y = 0; y < img.height; ++y){
                if(x < t1 || x >= img.width - t1 || y < t1 || y >= img.height - t1){
                    img(x, y, 0) = 25;
                    img(x, y, 1) = 80;
                    img(x, y, 2) = 200; 
                } 
            }
        }

            for (int x = 0; x < img.width; ++x){
                    for(int y = 0; y < img.height; ++y){
                    if( x < t2 || x >= img.width - t2 || y < t2 || y >= img.height - t2){
                        img(x, y, 0) = 50;
                        img(x, y, 1) = 50;
                        img(x, y, 2) = 50; 
                }
            }

        }

    }

    cout << "\nFrame Uploaded!\n" << endl;

}

void resize(Image &img){
    int new_w, old_w, new_h, old_h;
    old_w = img.width;
    old_h = img.height;
    cout << "Enter the new width and hight: ";
    cin >> new_w >> new_h;
    Image resized_img(new_w, new_h);
    
    for (int x = 0; x < resized_img.width; ++x){
                for(int y = 0; y < resized_img.height; ++y){
                int old_x =  x*old_w/new_w;
                int old_y =  y*old_h/new_h;  
                resized_img((x), (y), 0) = img(old_x, old_y, 0);
                resized_img((x), (y), 1) = img(old_x, old_y, 1);
                resized_img((x), (y), 2) = img(old_x, old_y, 2);
            }
        }
    
    img = resized_img;    
    cout << "\nImage Resized!\n" << endl;
}



void oldphoto(Image& image) {
        for (int i = 0; i < image.width; i++) {
            for (int j = 1; j < image.height; j+=9) {
                    unsigned int avr=0;
                    for (int k = 0; k < 3; k++) {
                        image(i,j,k)=image(0.5*i,j,k);
                        avr +=image(i, j, k);
                    }
                    avr /=3;
                    for (int k = 0; k < 3; k++) {
                        image(i, j, k)=avr;
                    }
            }
        }
    }




void darkenlighten(Image& image)
{
int choice, value;

cout << "1. Darken" << endl;
cout << "2. Lighten" << endl;
cin >> choice;

cout << "Enter value: ";
cin >> value;

for (int i = 0; i < image.width; i++)
{
for (int j = 0; j < image.height; j++)
{
for (int k = 0; k < 3; k++)
{
int newValue = image(i, j, k);

if (choice == 1)
newValue -= value;
else if (choice == 2)
newValue += value;

if (newValue > 255)
newValue = 255;

if (newValue < 0)
newValue = 0;

image(i, j, k) = newValue;

}
}
}
}

void invert(Image& image)
{
for (int y = 0; y < image.height; y++)
{
for (int x = 0; x < image.width; x++)
{
image(x, y, 0) = 255 - image(x, y, 0);
image(x, y, 1) = 255 - image(x, y, 1);
image(x, y, 2) = 255 - image(x, y, 2);
}
}
}



void crop(Image& image)
{
    int x, y, W, H;

    cout << "Enter x: ";
    cin >> x;

    cout << "Enter y: ";
    cin >> y;

    cout << "Enter width: ";
    cin >> W;

    cout << "Enter height: ";
    cin >> H;

    if (W <= 0 || H <= 0)
    {
        cout << "Invalid dimensions" << endl;
        return;
    }

    if (x < 0 || y < 0 ||
        x + W > image.width ||
        y + H > image.height)
    {
        cout << "Invalid crop area" << endl;
        return;
    }

    Image newImage(W, H);

    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                newImage(j, i, k) = image(x + j, y + i, k);
            }
        }
    }

    image = newImage;
}



void bluring(Image &img){
    int lvl, sum_R, sum_G, sum_B;
    int r;
    int count_x;
    int ave_R, ave_G, ave_B;
    Image temp_img = img;

    cout << R"(
1. Light Blur
2. Medium Blur
3. High Blur

Choose Bluring Level number: )";
cin >> lvl;
    switch (lvl)
    {
    case 1:
        r = 12;
        break;

    case 2:
        r = 14;
        break;

    case 3:
        r = 16;
        break;
        
    default:
        cout << "\nENTER A VAILD NUMBER! \n";
        return;
    }


    for (int y = 0; y < img.height; ++y){
        sum_R = 0;
        sum_G = 0;
        sum_B = 0;
        count_x = 0;
        for(int dx = 0 ; dx < r && dx < img.width ; dx++){
            sum_R += img(dx, y, 0);
            sum_G += img(dx, y, 1);
            sum_B += img(dx, y, 2);
            count_x++;

    }
                for(int x = 0; x < img.width; ++x){         
                if(x - r - 1 >= 0){
                    sum_R -= img(x - r - 1, y, 0);
                    sum_G -= img(x - r - 1, y, 1);
                    sum_B -= img(x - r - 1, y, 2);
                    count_x--;

                }

                if(temp_img.width > x + r){
                    sum_R += img(x + r, y, 0);
                    sum_G += img(x + r, y, 1);
                    sum_B += img(x + r, y, 2);
                    count_x++;
                }

                ave_R = sum_R / (count_x);
                ave_G = sum_G / (count_x);
                ave_B = sum_B / (count_x);

                temp_img((x), (y), 0) = ave_R;
                temp_img((x), (y), 1) = ave_G;
                temp_img((x), (y), 2) = ave_B;


        }
    }


    for (int x = 0; x < img.width; ++x){
            sum_R = 0;
            sum_G = 0;
            sum_B = 0;
            int count = 0;
            for(int dy = 0 ; dy < r && dy < temp_img.height ; dy++){
            sum_R += temp_img(x, dy, 0);
            sum_G += temp_img(x, dy, 1);
            sum_B += temp_img(x, dy, 2);
            count++;

            }
                for(int y = 0; y < img.height; ++y){
                    if(y - r - 1 >= 0){
                                    sum_R -= temp_img(x, y - r - 1, 0);
                                    sum_G -= temp_img(x, y - r - 1, 1);
                                    sum_B -= temp_img(x, y - r - 1, 2);
                                    count--;
                            
                }
                
                if(img.height > y + r){
                                    sum_R += temp_img(x, y + r, 0);
                                    sum_G += temp_img(x, y + r, 1);
                                    sum_B += temp_img(x, y + r, 2);
                                    count++;
                            
                }

                ave_R = sum_R / (count);
                ave_G = sum_G / (count);
                ave_B = sum_B / (count);
                img((x), (y), 0) = ave_R;
                img((x), (y), 1) = ave_G;
                img((x), (y), 2) = ave_B;
        }
    }

    cout << "\nImage Get Blured!\n" << endl;
    
}

void irPhoto(Image &img){
    for (int x = 0; x < img.width; ++x){
        for(int y = 0; y < img.height; ++y){
            int old_G = img(x, y, 1);
            int old_B = img(x, y, 2);
                img(x, y, 0) = 255;
                img(x, y, 1) = 255 - old_G;
                img(x, y, 2) = 255 - old_B;


            }
        }


    cout << "\nImage Get Updated!\n" << endl;
}


    void DetectImageEdges(Image& image) {
            Image final(image.width,image.height);
            for (int i = 0; i < image.width-1; i++) {
                for (int j = 0; j < image.height-1; j++) {
                    for (int k = 0; k < 3; k++) {
                        final(i,j,k)=255;
                    }
                }
            }
            int x=25;
            for (int i = 0; i < image.width-1; i++) {
                for (int j = 0; j < image.height-1; j++) {
                    int right=abs(image(i,j,0)-image(i+1,j,0));
                    int down=abs(image(i,j,1)-image(i,j+1,1));
                    int result;
                    if (right>x||down>x) {
                        result=0;
                    }
                    else {
                        result=255;
                    }
                    for (int k = 0; k < 3; k++) {
                        final(i,j,k)=result;
                    }

                }
            }

            image = final;
        }




void purple(Image& image)
{
for (int i = 0; i < image.width; i++)
{
for (int j = 0; j < image.height; j++)
{
int red = image(i, j, 0) + 50;
int green = image(i, j, 1) / 2;
int blue = image(i, j, 2) + 50;

if (red > 255)
red = 255;

if (blue > 255)
blue = 255;

image(i, j, 0) = red;
image(i, j, 1) = green;
image(i, j, 2) = blue;
}
}
}

void merge(Image& image1, Image& image2, Image& new_img){
string mergeType;
cout << "Please enter merge type (resize or common):";
cin >> mergeType;
int newWidth, newHeight;
if(mergeType == "resize"){
newWidth = max(image1.width,image2.width);
newHeight = max(image1.height,image2.height);
}
else if(mergeType == "common"){
newWidth = min(image1.width,image2.width);
newHeight = min(image1.height,image2.height);
}
else{
cout << "Invalid merge type\n";
return;
}
Image result(newWidth, newHeight);
for(int x = 0; x < newWidth; x++){
for(int y = 0; y < newHeight; y++){
int x1, x2, y1, y2;
if(mergeType == "resize"){
x1 = x * image1.width / newWidth;
y1 = y * image1.height / newHeight;

x2 = x * image2.width / newWidth;
y2 = y * image2.height / newHeight;
}
else{
x1 = x;
y1 = y;
x2 = x;
y2 = y;
}
for(int k = 0; k < 3; k++){
result(x , y , k) = (image1(x1, y1, k) + image2(x2, y2, k))/2;
}
}
} 
new_img = result;
cout << "\nImages merged successfully\n";
}


void brighten(Image& image){
for(int i = 0; i < image.width; i++){
for(int j = 0; j < image.height; j++){
int red = min(255,image(i, j, 0) + 35);
int green = min(255,image(i, j, 1) + 25);
int blue = min(255,image(i, j, 2) + 15);
image(i, j, 0) = red;
image(i, j, 1) = green;
image(i, j, 2) = blue;
}
}
cout << "\nImage brightened successfully\n";
}


void skewFilter(Image& image){
    double angle;
    cout << "Please enter the angle of skewness:";
    cin >> angle;
    double radians = angle * 3.14 / 180.0;
    double skew = tan(radians);

    int newHeight = image.height;
    double totalShift = (newHeight - 1) * skew;

    int extraWidth = (int)ceil(abs(totalShift));
    int newWidth = extraWidth + image.width;

    int offset = (int)ceil(max(0.0,-totalShift));

    Image output(newWidth, newHeight);

    for(int y = 0; y < newHeight; y++){
        for(int x = 0; x < newWidth; x++){
            for(int c = 0; c < 3; c++){
                output.getPixel(x, y, c) = 255;
            }
        }
    }
    for(int y = 0; y < image.height; y++){
        for(int x = 0; x < image.width; x++){
            int shift = (int)round((image.height - 1 - y) * skew);
            int newX = x + shift + offset;
            if(newX >= 0 && newX < newWidth){
                for(int c = 0; c < 3; c++){
                    output.getPixel(newX, y, c) = image.getPixel(x, y, c);
                }
            }
        }
    }
    image = output;
    cout<<"\nImage skewed successfully\n";
}




void oilimage(Image&image){
        Image final= image;
        int levels = 20;
        int radius =3;
        for (int i=0;i<image.width;i++) {
            for (int j=0;j<image.height;j++) {
                int freq[20]={0};
                int redsum[20]={0};
                int greensum[20]={0};
                int bluesum[20]={0};
                for (int x=i-radius;x<=i+radius;x++) {
                    for (int y=j-radius;y<=j+radius;y++) {
                        if (x>=0 && x<image.width && y>=0 && y<image.height) {
                           int red =final(x,y,0) ;
                            int green =final(x,y,1) ;
                            int blue =final(x,y,2) ;
                            int intensity =( red+green+blue)/3;
                            int level =(intensity*levels)/256;
                            if (level>=levels) {
                                level =levels-1;
                            }
                            freq[level]++;
                            redsum[level] +=red;
                            greensum[level] +=green;
                            bluesum[level] +=blue;
                        }
                    }
                }
                int bestlevel=0;
                for (int k=1 ; k<levels ; k++) {
                    if (freq[k]>freq[bestlevel]) {
                        bestlevel = k;
                    }
                }
                if (freq[bestlevel]>0) {
                    image(i,j,0)=redsum[bestlevel]/freq[bestlevel];
                    image(i,j,1)=greensum[bestlevel]/freq[bestlevel];
                    image(i,j,2)=bluesum[bestlevel]/freq[bestlevel];
                }
            }

        }

    }




int main() {

string image1;
int filter_num;

cout << "Enter file's name: ";
cin >> image1;

Image image(image1);

while (true) {

cout << R"(
Filters:
1. Grayscale
2. Black And White
3. Invert Image
4. Adding A Frame
5. Flip Image
6. Rotate Image
7. Darken And Lighten Image
8. Resize Image
9. Merge Images
10. Detect Image Edges
11. Crop Image
12. Blur Image
13. Brighten Image
14. TV image
15. Purple Look
16. Infrared Photography
17. Image Skewing
18. Oil Paint Image
19. Save Image
20. Quit

Enter filter's number: )";

cin >> filter_num;

if (filter_num == 1) {
    grayscale(image);
}
else if (filter_num == 2) {
    blackandwhite(image);
}
else if (filter_num == 3) {
    invert(image);
}
else if (filter_num == 4) {
    framer(image);
}
else if (filter_num == 5) {
    flip(image);
}
else if (filter_num == 6) {
    rotateimage(image);
}
else if (filter_num == 7) {
    darkenlighten(image);
}
else if (filter_num == 8) {
resize(image);
}
else if (filter_num == 9) {
    string image2;
    cout << "Enter the second file name: " << endl;
    cin >> image2;
    Image image2nd(image2);
    Image new_img;
    merge(image, image2nd, new_img);
    image = new_img;
}
else if (filter_num == 10) {
    DetectImageEdges(image);
}
else if (filter_num == 11) {
    crop(image);
}
else if (filter_num == 12) {
    bluring(image);
}
else if (filter_num == 13) {
    brighten(image);
}
else if (filter_num == 14) {
    oldphoto(image);
}
else if (filter_num == 15) {
    purple(image);
}
else if (filter_num == 16) {
    irPhoto(image);
}
else if (filter_num == 17) {
    skewFilter(image);
}
else if (filter_num == 18) {
    oilimage(image);
}
else if (filter_num == 19) {

int ans;

cout << R"(
Do you want to rename file?
1. Yes
2. No
Choose a num: )";

cin >> ans;

if (ans == 1) {
string save_img;

cout << "Enter file name: ";
cin >> save_img;

image.saveImage(save_img);
}
else {
image.saveImage("output.jpg");
}

}
else if (filter_num == 20) {
break;
}
else {
cout << "ENTER A VALID NUM!" << endl;
}
}

return 0;
}