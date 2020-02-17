//
//  Pharse.hpp
//  Circle-Detection-Algorithms
//
//  Created by Yuqing Lin on 2/15/20.
//  Copyright © 2020 Yuqing Lin. All rights reserved.
//

#ifndef Pharse_hpp
#define Pharse_hpp

#include <stdio.h>

#include <opencv2/opencv.hpp>


class Phrase{
private:
    std::vector<std::string>fileNames; //Store files that glob by opencv with directory
    std::vector<std::string>images; //Store images' name after seprate file directory
    std::string path ="/Users/yuqinglin/Desktop/Opencv-Circle-Detection/Circle-Detection-Algorithms/TestImages/*";
    std::unordered_map<std::string,std::vector< std::vector <int> > >imageRecord;
public:
    unsigned long pharseAllImages();
    void phaseImagesToRecord();
    std::vector<std::string>getFileDir(){return fileNames;};
    std::vector<std::string>getFileNames(){return images;};
    bool isDigits(char c);
    std::string fileDirToName(std::string);//return file name from file dir
    std:: string removeExtension(const std::string&);
    std:: string removePrefix(const std::string&);
    
    std::unordered_map<std::string,std::vector< std::vector <int> > >getImageRecord(){
        return imageRecord;
    };
};




#endif /* Pharse_hpp */
