//
//  ChromaKey.cpp
//  Circle-Detection-Algorithms
//
//  Created by Yuqing Lin on 2/20/20.
//  Copyright © 2020 Yuqing Lin. All rights reserved.
//

#include "ChromaKey.hpp"
using namespace cv;
Scalar ChromaKey::bgr2ycrcb(cv::Scalar bgr){
    //converting bgr to ycrcb
  // Reference to  https://docs.opencv.org/trunk/de/d25/imgproc_color_conversions.html
    double R = bgr[ 2 ];
    double G = bgr[ 1 ];
    double B = bgr[ 0 ];
    double delta = 128; // Note: change this value if image type isn't CV_8U.

    double Y  = 0.299 * R + 0.587 * G + 0.114 * B;
    double Cr = ( R - Y ) * 0.713 + delta;
    double Cb = ( B - Y ) * 0.564 + delta;
    return cv::Scalar( Y, Cr, Cb, 0 );
}
/*
Mat ChromaKey::chromaKeyRange(const cv::Mat& imageBGR, cv::Scalar chromaBGR, double lower, double upper ){
        cv::Size imageSize = imageBGR.size();
        cv::Mat imageYCrCb;
        cv::cvtColor( imageBGR, imageYCrCb, cv::COLOR_BGR2YCrCb );
        cv::Scalar chromaYCrCb = bgr2ycrcb( chromaBGR ); // Convert a single BGR value to YCrCb.

        // Build the mask.
        cv::Mat1b mask = cv::Mat1b::zeros( imageSize );
        const cv::Vec3d key( chromaYCrCb[ 0 ], chromaYCrCb[ 1 ], chromaYCrCb[ 2 ] );

        for ( int y = 0; y < imageSize.height; ++y )
        {
            for ( int x = 0; x < imageSize.width; ++x )
            {
                const cv::Vec3d color( imageYCrCb( y, x )[ 0 ], imageYCrCb( y, x )[ 1 ], imageYCrCb( y, x )[ 2 ] );
                double distance = cv::norm( key - color );

                if ( distance < tInner )
                {
                    // Current pixel is fully part of the background.
                    mask( y, x ) = 0;
                }
                else if ( distance > tOuter )
                {
                    // Current pixel is fully part of the foreground.
                    mask( y, x ) = 255;
                }
                else
                {
                    // Current pixel is partially part both, fore- and background; interpolate linearly.
                    // Compute the interpolation factor and clip its value to the range [0, 255].
                    double d1 = distance - tInner;
                    double d2 = tOuter   - tInner;
                    uint8_t alpha = static_cast< uint8_t >( 255. * ( d1 / d2 ) );

                    mask( y, x ) = alpha;
                }
            }
        }

        return mask;
    }
}*/
