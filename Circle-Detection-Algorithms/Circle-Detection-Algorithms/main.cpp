#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include <cassert>
#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
/**
 * @brief Convert BGR color to YCrCb color space.
 * @param bgr   Color (channel order BGR, range: [0, 255])
 *
 * Details can be found in the [documentation of OpenCV][1]
 *
 * [1]: http://docs.opencv.org/trunk/de/d25/imgproc_color_conversions.html
 */
cv::Scalar bgr2ycrcb( cv::Scalar bgr )
{
    double R = bgr[ 2 ];
    double G = bgr[ 1 ];
    double B = bgr[ 0 ];
    double delta = 128; // Note: change this value if image type isn't CV_8U.
    cout<<"r: "<<R<<" xwg: "<<G<<" B: "<<B<<endl;
    double Y  = 0.299 * R + 0.587 * G + 0.114 * B;
    double Cr = 128 + 0.5*R - 0.418688*G - 0.081312*B;
    double Cb = 128 + -0.168736*R - 0.331264*G + 0.5*B;
    cout<<"Y: "<<Y <<"Cr: "<<Cr<<"Cb: "<<Cb<<endl;
    return cv::Scalar( Y, Cr, Cb, 0 /* ignored */ );
}
/**
 * @brief Separate foreground from background using simple chroma keying.
 *
 * @param imageBGR   Image with monochrome background
 * @param chromaBGR  Color of the background (using channel order BGR and range [0, 255])
 * @param tInner     Inner threshold, color distances below this value will be counted as foreground
 * @param tOuter     Outer threshold, color distances above this value will be counted as background
 *
 * @return  Mask (0 - background, 255 - foreground, [1, 255] - partially fore- and background)
 *
 * Details can be found on [Wikipedia][1].
 *
 * [1]: https://en.wikipedia.org/wiki/Chroma_key#Programming
 */
void chromaKey( const cv::Mat3b & imageBGR, cv::Scalar chromaBGR, double tInner, double tOuter){
    // Basic outline:
    //
    // 1. Convert the image to YCrCb.
    // 2. Measure Euclidean distances of color in YCrBr to chroma value.
    // 3. Categorize pixels:
    //   * color distances below inner threshold count as foreground; mask value = 0
    //   * color distances above outer threshold count as background; mask value = 255
    //   * color distances between inner and outer threshold a linearly interpolated; mask value = [0, 255]

    assert( tInner <= tOuter );
    ofstream outfile;
outfile.open("/Users/yuqinglin/Desktop/Opencv-Circle-Detection/Circle-Detection-Algorithms/TestImages/result.txt");
    // Convert to YCrCb.
    assert( ! imageBGR.empty() );
    cv::Size imageSize = imageBGR.size();
    cv::Mat3b imageYCrCb;
    cv::cvtColor( imageBGR, imageYCrCb, cv::COLOR_BGR2YCrCb );
    cv::namedWindow("ycvcr");
    cv::imshow("ycvcr",imageYCrCb);
    cv::Scalar chromaYCrCb = bgr2ycrcb( chromaBGR ); // Convert a single BGR value to YCrCb.
    
    // Build the mask.
    cv::Mat1b mask = cv::Mat1b::zeros( imageSize );
    
    const cv::Vec3d key( chromaYCrCb[ 0 ], chromaYCrCb[ 1 ], chromaYCrCb[ 2 ] );
    int countInner = 0;int countOutter = 0;
    cout<<"iamge height"<<imageSize.height<<endl;
    cout<<"image width"<<imageSize.width<<endl;
    cout<<"total pixel"<<imageSize.height*imageSize.width<<endl;
    for ( int y = 0; y < imageSize.height; ++y )
    {
        for ( int x = 0; x < imageSize.width; ++x )
        {
            const cv::Vec3d color( imageYCrCb( y, x )[ 0 ], imageYCrCb( y, x )[ 1 ], imageYCrCb( y, x )[ 2 ] );
            double distance = cv::norm( key - color );
            if(distance<=20)
                countInner++;
            else countOutter++;
            outfile<<x<<" "<<y<<" "<<distance<<" "<<endl;
        }
    }
    cout<<"less than 20"<<countInner<<endl;
    cout<<"grater than 20"<<countOutter<<endl;
    return ;
}



int main()
{
    std::string inputFilename = "/Users/yuqinglin/Desktop/Opencv-Circle-Detection/Circle-Detection-Algorithms/TestImages/xxx[1,2,3].jpg";


    // Load the input image.
    cv::Mat input = cv::imread( inputFilename, cv::IMREAD_COLOR );

    if ( input.empty() ){
        std::cerr << "Input file <" << inputFilename << "> could not be loaded ... " << std::endl;
        return 1;
    }
    // Apply the chroma keying and save the output.
    cv::Scalar chroma( 0, 100, 80, 0 ); //tennis ball for rgb
    double tInner = 100.;
    double tOuter = 170.;
    chromaKey( input, chroma, tInner, tOuter);
    cv::namedWindow( "input" );
    cv::imshow( "input", input );
    cv::waitKey( 0 );

    return 0;
}


