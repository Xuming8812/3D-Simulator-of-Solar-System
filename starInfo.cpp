//
//  starInfo.cpp
//  starInfo
//
//  Created by Xingchen Ming on 10/30/18.
//  Copyright © 2018 Xingchen Ming. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <vector>
#include <GLUT/GLUT.h>
#include "tinyxml2.h"
#include "starInfo.hpp"

using namespace tinyxml2;
using namespace std;


/**
 * parse xlm file and save all star parameters to struct
 */
void getinfo(){
    XMLDocument doc;
    doc.LoadFile("Mydata.xml");
    stringstream ss;
    
    XMLElement* root=doc.RootElement();
//        const char * rootName = root->Value();
//        cout  << rootName << endl;
    XMLElement* info=root->FirstChildElement();
    while(info){
        XMLElement* infoChild=info->FirstChildElement();
        while(infoChild){
            const char* content = infoChild->GetText();
           // const char * contentName = infoChild->Value();
            int i=0;
//            while (*(contentName+i) != '\0') {
//                ss <<  *(contentName+i);
//                i++;
//            cout << ": ";
                while (*(content+i) != '\0') {
                    ss <<  *(content+i);
                    
                    i++;                }
            infoChild=infoChild->NextSiblingElement();
            ss << " ";
        }
        ss << '\n';
        info=info->NextSiblingElement();
    }
        
        
//
    struct objectInfo{
        std::string name;
        string type;
        GLfloat speedRevolution;
        GLfloat speedRotation;
        GLfloat radius;
        GLfloat distance;
        std::string parentName;
        GLfloat color[4];
    };
        objectInfo current;
        vector<objectInfo> parameters;
        cout << ss.str() << endl;

//        for (int a=0; a<10; a++) {
    while (ss) {
        if (ss.eof()) {
            break;
        }
        ss  >>current.name >> current.type >> current.speedRevolution >> current.speedRotation >> current.radius >> current.distance >> current.parentName;

        for (int i=0; i<4; i++)
            ss >> current.color[i];
        
        parameters.push_back(current);
    }
}





