//
//  ChromaKey.hpp
//  Circle-Detection-Algorithms
//
//  Created by Yuqing Lin on 2/20/20.
//  Copyright © 2020 Yuqing Lin. All rights reserved.
//

#ifndef ChromaKey_hpp
#define ChromaKey_hpp

#include <stdio.h>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include <cassert>
#include <cmath>
#include <iostream>
#include <string>
class ChromaKey{
    cv::Mat chromaKeyRange( const cv::Mat& imageBGR, cv::Scalar chromaBGR, double lower, double upper );
    cv::Scalar bgr2ycrcb( cv::Scalar bgr );
};


#endif /* ChromaKey_hpp */
