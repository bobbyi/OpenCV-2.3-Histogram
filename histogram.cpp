#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

const char *IMAGE_PATH = "./image.bmp";


Mat histogram(Mat image)
{
    long total = 0;
    for(int row = 0; row < image.rows; row++)
        for(int col = 0; col < image.cols; col++) 
        {
            unsigned char pixel = image.at<unsigned char>(row, col);
            total += pixel;
        }
    cout << total / (double)(image.rows * image.cols) <<endl;
    return image;
}

int main() 
{
    Mat image = imread(IMAGE_PATH, 0);
    Mat hist = histogram(image);
    return 0;
}
