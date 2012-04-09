#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

const char *IMAGE_PATH = "./image.bmp";
const int NUM_BUCKETS = 10;
const int BUCKET_SIZE = 26; 


Mat histogram(const Mat& image)
{
    // Output histogram, initially empty
    Mat hist = Mat::zeros(NUM_BUCKETS, 1, CV_64F);

    // For each pixel in the input image, determine the bucket
    // that it falls into and increment that bucket in the histogram.
    for(int row = 0; row < image.rows; row++)
    {
        for(int col = 0; col < image.cols; col++) 
        {
            const unsigned char pixel = image.at<unsigned char>(row, col);
            const int bucket = pixel / BUCKET_SIZE;
            hist.at<double>(bucket) += 1;
        }
    }

    // Normalize the histogram so that it sums to one.
    // (Divide all elements by the total number of pixels).
    hist /= (image.rows * image.cols);
    return hist;
}


void test_histogram()
{
    // Verify the histogram() function works by loading in a test image,
    // calculating its histogram, and checking that the histogram value
    // for each bucket is approximately equal to our expected result.
    Mat image = imread(IMAGE_PATH, CV_LOAD_IMAGE_GRAYSCALE);
    Mat hist = histogram(image);
    Mat expected = (Mat_<double>(10,1) << 
        0.256, 0.229, 0.171, 0.103, 0.144, 0.019, 0.023, 0.021, 0.022, 0.011);
    for(int bucket = 0; bucket < NUM_BUCKETS; bucket++)
    {
        const double actual_value = hist.at<double>(bucket);
        const double expected_value = expected.at<double>(bucket);
        const double diff = abs(actual_value - expected_value);
        if (diff > .001)
        {
            cerr << "Value for bucket " << (bucket + 1) << " did not match" << endl;
            cerr << "\tExpected: " << expected_value << endl;
            cerr << "\tGot: " << actual_value << endl;
            exit(1);
        }
    }
}


int main() 
{
    test_histogram();
    cout << "All tests passed" << endl;
    return 0;
}
