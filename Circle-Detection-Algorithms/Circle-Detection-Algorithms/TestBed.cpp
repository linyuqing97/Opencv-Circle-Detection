//
//  TestBed.cpp
//  Circle-Detection-Algorithms
//
//  Created by Yuqing Lin on 2/15/20.
//  Copyright © 2020 Yuqing Lin. All rights reserved.
//

#include "TestBed.hpp"
using namespace std;
using namespace cv;

TestBed::TestBed(){
    counter = 1;
    totalImages = 0;
}

bool TestBed::preRun(){
    Phase p;
    totalImages = p.pharseAllImages();
    p.phaseImagesToRecord();
    this->imagesDir=p.getFileDir();
    this->imageRecord= p.getImageRecord();
    
    while(counter<=totalImages){
        //get image from diractory
        cv::Mat image = cv::imread(imagesDir[counter]);
        
        //convert image diractory to image name
        string imageName = p.fileDirToName(imagesDir[counter]);
        imageName = p.removePrefix(imageName);
        
        //read correct circle coordinate from imageRecord(Hash map)
        vector<vector<int>>coor = imageRecord[imageName];
        
        //run to every algorithms
        this->runAlgorithms(image,coor);
        
        counter++;
    }
    return true;
}

void TestBed::runAlgorithms(cv::Mat& image,vector<vector<int>>coor){
    clock_t start,end;
    start = clock();
    namedWindow( "Display window", WINDOW_AUTOSIZE );
    imshow("img", image);
    end = clock();
    printRunTime((float)(end-start)*1000/CLOCKS_PER_SEC, "show");
  
}

void TestBed::printRunTime(float time ,string name){
    cout << "Time taken by function "<<name<<":"
    << time<< " microseconds" << endl;
}
