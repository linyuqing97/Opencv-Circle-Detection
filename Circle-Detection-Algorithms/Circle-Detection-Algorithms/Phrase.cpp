//
//  Pharse.cpp
//  Circle-Detection-Algorithms
//
//  Created by Yuqing Lin on 2/15/20.
//  Copyright © 2020 Yuqing Lin. All rights reserved.
//

#include "Phrase.hpp"
using namespace std;

unsigned long Phrase::pharseAllImages(){
    cv::glob(this->path, this->fileNames,true); // fileNames stores all images directory
    for(int i = 1; i< fileNames.size();i++){
        string temp = removePrefix(fileNames[i]);
        this->images.push_back(temp);
    }
    return images.size(); //return all images name in vector
}

std::string Phrase:: removePrefix(const std::string& filename) {
    size_t lastPos=filename.find_last_of('/');
    if (lastPos == std::string::npos) return filename;
    string res = filename.substr(lastPos,filename.size());
    cout<<res<<endl;
    return res;
}

std::string Phrase::fileDirToName(std::string s){
    std::size_t lastPosOfName = s.find_first_of('[');
    std::string imageName = s.substr(0,lastPosOfName);
    return imageName;
}

void Phrase::phaseImagesToRecord(){
    for(int i = 0;i<this->images.size();i++){
        string s = this->images[i];
        unsigned long lastPosOfName = s.find_first_of('[');
        unsigned long lastPosOfP = s.find_last_of(']');
        std::string imageName = fileDirToName(s);
        std::vector<std::vector<int>>record; // 2d array to store all possible circle coor
        std::vector<int>temp;
        
        for(unsigned long j = lastPosOfName+1;j<lastPosOfP;j++){
            char c = s[j];
            if(this->isDigits(c)){
                temp.push_back(c-'0');
            }
            if(temp.size()==3){
                record.push_back(temp);
                temp.clear();
            }
        }

        imageRecord.insert({imageName,record});
        //std::cout<<"size of map:"<<imageRecord.size()<<std::endl;
    }
}
bool Phrase::isDigits(char c){
    if(c-'0'>=0 && c-'0'<=9){
        return true;
    }
    return false;
}

