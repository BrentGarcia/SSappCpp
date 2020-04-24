#include "SeasonLibrary.hpp"
#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
/*
* Copyright 2020 Brent Garcia,
*
* This software is the intellectual property of the author, and can not be
distributed, used, copied, or
* reproduced, in whole or in part, for any purpose, commercial or otherwise.
The author grants the ASU
* Software Engineering program the right to copy, execute, and evaluate this
work for the purpose of
* determining performance of the author in coursework, and for Software
Engineering program evaluation,
* so long as this copyright and right-to-use statement is kept in-tact in such
use.
* All other uses are prohibited and reserved to the author.
*
* Purpose: An SeasonLibrary class for serializing between client and server.
*
* Ser321 Principles of Distributed Software Systems
* see http://pooh.poly.asu.edu/Ser321
* @author Brent Garcia, Tim Lindquist Tim.Lindquist@asu.edu
*
Software Engineering, CIDSE, IAFSE, ASU Poly
* @version April 2020
*/

SeasonLibrary::SeasonLibrary(){
   initLibraryFromJsonFile("series.json");
}

SeasonLibrary::~SeasonLibrary() {
   media.clear();
}

bool SeasonLibrary::initLibraryFromJsonFile(string jsonFileName){
   bool ret = false;
   Json::Reader reader;
   Json::Value root;
   std::ifstream json(jsonFileName.c_str(), std::ifstream::binary);
   bool parseSuccess = reader.parse(json,root,false);
   if(parseSuccess){
      Json::Value::Members mbr = root.getMemberNames();


      for(vector<string>::const_iterator i = mbr.begin(); i!= mbr.end(); i++){
         Json::Value jsonMedia = root[*i];
        
	 //for (int j = 0; j< jsonMedia.size(); j++){
            //SeriesSeason * aDesc = new SeriesSeason(jsonMedia[j]);
            //string seriesTitle = aDesc->title;
            //media[seriesTitle] = *aDesc;
            //cout << "adding ";
            //cout << "Episodes Size  is " << episodeName << ".\n";
            //media[seriesTitle].print();
         //}
         
	 //series 4 style with series title as parent objects
	 SeriesSeason * aSeries = new SeriesSeason(jsonMedia);
         media[*i] = *aSeries;
         cout << "adding " << "media.size =  " << media.size();
         aSeries->print();
      }
      ret = true;
   }
   return ret;
}

bool SeasonLibrary::toJsonFile(string jsonFileName){
   bool ret = false;
   Json::Value jsonLib;
   for(std::map<string,SeriesSeason>::iterator i = media.begin();
                                                         i!= media.end(); i++){
      string key = i->first;
      cout << key << " " << endl;
      SeriesSeason aMedia = media[key];
      Json::Value jsonMedia = aMedia.toJson();
      jsonLib[key] = jsonMedia;
   }
   Json::StyledStreamWriter ssw("  ");
   std::ofstream jsonOutFile(jsonFileName.c_str(), std::ofstream::binary);
   ssw.write(jsonOutFile, jsonLib);
   return true;
}

//Adds a season series to library
bool SeasonLibrary::addSeriesSeason(SeriesSeason seriesSeasonToAdd){
   bool result = false;
   string seriesTitle = seriesSeasonToAdd.title;
   media[seriesTitle] = seriesSeasonToAdd;
   return true;
}

bool SeasonLibrary::removeSeriesSeason(string seriesSeasonToRemove){
   bool result = false;
   media.erase (seriesSeasonToRemove.c_str());
   return true;
}

Json::Value SeasonLibrary::get(string aTitle){
   SeriesSeason aMedia = media[aTitle];
   Json::Value newMedia = aMedia.toJson();
   return newMedia;
}

Json::Value SeasonLibrary::getTitles(){
   Json::Value ret(Json::arrayValue);
   vector<string> myVec;
   for(map<string,SeriesSeason>::iterator it = media.begin();
                                              it != media.end();++it){
      myVec.push_back(it->first);
   }
   for(std::vector<string>::iterator it = myVec.begin(); it!=myVec.end();++it) {
      ret.append(Json::Value(*it));
   }
   return ret;
}

//Example


//vector<string> SeasonLibrary::getTitles(){
//   vector<string> myVec;
//   for(map<string,SeriesSeason>::iterator it = media.begin();
//                                              it != media.end();++it){
//     myVec.push_back(it->first);
//   }
//   return myVec;
//}
