//
//  TestBed.hpp
//  Circle-Detection-Algorithms
//
//  Created by Yuqing Lin on 2/15/20.
//  Copyright © 2020 Yuqing Lin. All rights reserved.
//

#ifndef TestBed_hpp
#define TestBed_hpp

#include <stdio.h>
#include "Phrase.hpp"
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <time.h> //timing algorithems
class TestBed{
private:
    unsigned long totalImages;
    unsigned long counter;
    std::unordered_map<std::string,std::vector< std::vector <int> > >imageRecord;
    std::vector<std::string> imagesDir;
public:
    TestBed();
    bool preRun();  //open all images, pass in one by one
    void runAlgorithms(cv::Mat& image,std::vector<std::vector<int>>);
    void printRunTime(float,std::string);
};

#endif /* TestBed_hpp */
