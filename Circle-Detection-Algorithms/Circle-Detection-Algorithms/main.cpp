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
double bgr2y( double R,double G,double B )
{
    
    //double delta = 128; // Note: change this value if image type isn't CV_8U.
    //cout<<"r: "<<R<<" xwg: "<<G<<" B: "<<B<<endl;
    double Y  = 0.299 * R + 0.587 * G + 0.114 * B;
   // double Cr = 128 + 0.5*R - 0.418688*G - 0.081312*B;
    //double Cb = 128 + -0.168736*R - 0.331264*G + 0.5*B;
    //cout<<"Y: "<<Y <<"Cr: "<<Cr<<"Cb: "<<Cb<<endl;
    return Y;
}
double bgr2Cr(double R, double G, double B){
    double Cr = 128 + 0.5*R - 0.418688*G - 0.081312*B;
    return Cr;
}
double bgr2Cb(double R,double G,double B){
    double Cb = 128 + -0.168736*R - 0.331264*G + 0.5*B;
    return Cb;
}

void chromaKey( const cv::Mat3b & imageBGR){
    ofstream outfile;
outfile.open("/Users/yuqinglin/Desktop/Opencv-Circle-Detection/Circle-Detection-Algorithms/TestImages/result.txt");

    assert( ! imageBGR.empty() );
    cv::Size imageSize = imageBGR.size();

    
    // black color Ycbcr
    cv::Scalar blackTemp(0, 0, 0, 0);
    //cv::Scalar black = bgr2ycrcb(blackTemp);
    
    
    //const cv::Vec3d key( chromaYCrCb[ 0 ], chromaYCrCb[ 1 ], chromaYCrCb[ 2 ] );
    //int countInner = 0;int countOutter = 0;
    cout<<"iamge height"<<imageSize.height<<endl;
    cout<<"image width"<<imageSize.width<<endl;
    cout<<"total pixel"<<imageSize.height*imageSize.width<<endl;
    
    vector<int>total(3,0);
    double totalY = 0;
    double totalCr = 0;
    double totalCb= 0;
    double totalSize = 0;
      cv::Mat temp;
    // 0: blue channel 1: green channel 2: red channel
    for ( int y = 0; y < imageSize.height; ++y )
    {
        for ( int x = 0; x < imageSize.width; ++x )
        {
            cv::Vec3b intensity = imageBGR.at<cv::Vec3b>(y,x);
            if(intensity.val[0] == 0 && intensity.val[1] == 0 && intensity.val[2]==0)continue; //bgr
            double blue = intensity.val[0];double green = intensity.val[1]; double red = intensity.val[2];
            totalCr += bgr2Cr(red, green, blue);
            totalCb += bgr2Cb(red, green, blue);
            totalY += bgr2y(red, green, blue);
            totalSize++;
        }
    }
    double averageCr = totalCr/totalSize;
    double averageCb = totalCb/totalSize;
    double averageY = totalY/totalSize;
    cout<<"average Y: " << averageY << " averageCr: "<<averageCr<<" average Cb: "<<averageCb<<"total count"<<totalSize<<endl;
    cv::Mat tempImage;
    const cv::Vec3d key( averageY, averageCb, averageCr );
    
    for ( int y = 0; y < imageSize.height; ++y )
    {
        for ( int x = 0; x < imageSize.width; ++x )
        {
            cv::Vec3b intensity = imageBGR.at<cv::Vec3b>(y,x);
            if(intensity.val[0] == 0 && intensity.val[1] == 0 && intensity.val[2]==0)continue; //bgr
            double blue = intensity.val[0];double green = intensity.val[1]; double red = intensity.val[2];
            double Y = bgr2y(red, green, blue);
            double cb = bgr2Cb(red, green, blue);
            double cr = bgr2Cr(red, green, blue);
            const cv::Vec3d color( Y, cb, cr);
            double distance = cv::norm( key - color );
            outfile<<x<<","<<y<<","<<distance<<endl;
         
    }
      
}

}

int main(int argc, char*argv[])
{
    std::string inputFilename = "/Users/yuqinglin/Desktop/Opencv-Circle-Detection/Circle-Detection-Algorithms/TestImages/3.png";


    // Load the input image.
    cv::Mat input = cv::imread( inputFilename, cv::IMREAD_COLOR );

    if (input.empty() ){
        std::cerr << "Input file <" << inputFilename << "> could not be loaded ... " << std::endl;
        return 1;
    }
    // Apply the chroma keying and save the output.
   // cv::Scalar chroma( 0, 100, 80, 0 ); //tennis ball for rgb
    chromaKey( input);
    cv::namedWindow( "input" );
    cv::imshow( "input", input );
    cv::waitKey( 0 );

    return 0;
}


