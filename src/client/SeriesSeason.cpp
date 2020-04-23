#include "SeriesSeason.hpp"
#include <iostream>
#include <stdlib.h>
#include <json/json.h>

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
* Purpose: An SeriesSeason class for serializing between client and server.
*
* Ser321 Principles of Distributed Software Systems
* see http://pooh.poly.asu.edu/Ser321
* @author Brent Garcia, Tim Lindquist Tim.Lindquist@asu.edu
*
Software Engineering, CIDSE, IAFSE, ASU Poly
* @version April 2020
*/
SeriesSeason::SeriesSeason(){
   title = "";
   season = "";
   imdbRating = "";
   genre = "";
   poster = "";
   plot = "";
   
}

SeriesSeason::SeriesSeason(string aTitle, string aSeason,
    string aImdbRating, string aGenre, string aPoster, string aPlot,
    vector<Episode> aEpisodes) {
   title = aTitle;
   season = aSeason;
   imdbRating = aImdbRating;
   genre = aGenre;
   poster = aPoster;
   plot = aPlot;
   episodes = aEpisodes;
}

SeriesSeason::SeriesSeason(const Json::Value& jsonObj){
   Json::Value::Members mbr = jsonObj.getMemberNames();
   for(vector<string>::const_iterator i = mbr.begin(); i!= mbr.end(); i++){
      //cout << *i << " " << endl;
      Json::Value jsonM = jsonObj[*i];
      if(*i=="Title"){
         title = jsonM.asString();
      }else if(*i=="Season"){
         season = jsonM.asString();
      }else if(*i=="imdbRating"){
         imdbRating = jsonM.asString();
      }else if(*i=="Genre"){
         genre = jsonM.asString();
      }else if(*i=="Poster"){
         poster = jsonM.asString();
      }else if(*i=="Plot"){
         plot = jsonM.asString();
      }
      else if(*i=="Episodes"){
         //episodes = jsonM.asString();
	 for (int j = 0; j< jsonM.size(); j++){
            Episode * newEpisode = new Episode(jsonM[j]);
            string episodeTitle = newEpisode->title;
            episodes.push_back(*newEpisode);
         }
         cout << "\nreached Episodes logic within SeriesSeason\n";
      }
   }
}

SeriesSeason::SeriesSeason(string jsonString){
   //cout << "in single string parser" << endl;
   Json::Reader reader;
   Json::Value root;
   bool parseSuccess = reader.parse(jsonString, root);
   cout << "\n\nparseSuccess = " << parseSuccess << "\n\n";
   if(parseSuccess){
      cout << "successful parse" << endl;
      Json::Value::Members mbr = root.getMemberNames();
      for(vector<string>::const_iterator i = mbr.begin(); i!= mbr.end(); i++){
         //cout << *i << " " << endl;
         Json::Value jsonM = root[*i];
         if(*i=="Title"){
            title = jsonM.asString();
         }else if(*i=="Season"){
            season = jsonM.asString();
         }else if(*i=="imdbRating"){
            imdbRating = jsonM.asString();
         }else if(*i=="Genre"){
            genre = jsonM.asString();
         }else if(*i=="Poster"){
            poster = jsonM.asString();
         }else if(*i=="Plot"){
            plot = jsonM.asString();
      	}else if(*i=="Episodes"){
         //episodes = jsonM.asString();
         //for (int j = 0; j< jsonM.size(); j++){
            //Episode * newEpisode = new Episode(jsonM[j]);
            //string seriesTitle = aDesc->title;
            //media[seriesTitle] = *aDesc;
            //cout << "Episode name: " << newEpisode->title << "\n";
            //vector<Episode> newEpisode = aDesc->episodes;
            //media[seriesTitle].print();
         //}
	 //int episodeSize = jsonM.size();
	cout << "Episodes Size  is \n";
         cout << "Episodes Size  is " << jsonM.size() << ".\n";
         cout << "\nreached Episodes logic within SeriesSeason\n";
      }
      }
   }else{
      cout << "SeriesSeason constructor parse error with input: " << jsonString
           << endl;
   }
}

SeriesSeason::SeriesSeason(string jsonString1, string jsonString2){
   Json::Reader reader1;
   Json::Value root1;
   bool parseSuccess1 = reader1.parse(jsonString1,root1,false);
   if(parseSuccess1){
      //cout << "successful parse1" << endl;
      Json::Value::Members mbr1 = root1.getMemberNames();
      for(vector<string>::const_iterator i = mbr1.begin(); i!= mbr1.end(); i++){
         //cout << *i << " " << endl; 
         Json::Value jsonM1 = root1[*i];
         if(*i=="Title"){
            title = jsonM1.asString();
         }else if(*i=="imdbRating"){
            imdbRating = jsonM1.asString();
         }else if(*i=="Genre"){
            genre = jsonM1.asString();
         }else if(*i=="Poster"){
            poster = jsonM1.asString();
         }else if(*i=="Plot"){
            plot = jsonM1.asString();
            cout << "plot = " << plot;
      	 }
      }
   }else{
      cout << "SeriesSeason constructor parse error with input: " << jsonString1
           << endl;
   }
   Json::Reader reader2;
   Json::Value root2;
   bool parseSuccess2 = reader2.parse(jsonString2,root2,false);
   if(parseSuccess2){
      Json::Value::Members mbr2 = root2.getMemberNames();
      for(vector<string>::const_iterator i = mbr2.begin(); i!= mbr2.end(); i++){
         //cout << *i << " " << endl;
         Json::Value jsonM2 = root2[*i];
         if(*i=="Season"){
            season = jsonM2.asString();
      	 } else if(*i=="Episodes"){
            //episodes = jsonM.asString();
	    for (int j = 0; j< jsonM2.size(); j++){
            Episode * newEpisode = new Episode(jsonM2[j]);
            string episodeTitle = newEpisode->title;
            episodes.push_back(*newEpisode);
            }
      	 }
      }
   } else{
      cout << "SeriesSeason constructor parse error with input: " << jsonString2
           << endl;
   }
}

//New constructor for 2 api calls
SeriesSeason::SeriesSeason(const Json::Value& jsonObj, const Json::Value& jsonObj2){
   cout << "\n\nI'm in double jsonObj constructor\n\n";
   //process first api call
   Json::Value::Members mbr = jsonObj.getMemberNames();
   for(vector<string>::const_iterator i = mbr.begin(); i!= mbr.end(); i++){
      //cout << *i << " " << endl;
      Json::Value jsonM = jsonObj[*i];
      if(*i=="Title"){
         title = jsonM.asString();
      }else if(*i=="imdbRating"){
         imdbRating = jsonM.asString();
      }else if(*i=="Genre"){
         genre = jsonM.asString();
      }else if(*i=="Poster"){
         poster = jsonM.asString();
      }else if(*i=="Plot"){
         plot = jsonM.asString();
      }
   }
   //process second api call
   Json::Value::Members mbr2 = jsonObj2.getMemberNames();
   for(vector<string>::const_iterator i = mbr.begin(); i!= mbr.end(); i++){
      //cout << *i << " " << endl;
      Json::Value jsonM2 = jsonObj2[*i];
      if(*i=="Season"){
         season = jsonM2.asString();
      } else if(*i=="Episodes"){
         //episodes = jsonM.asString();
	 for (int j = 0; j< jsonM2.size(); j++){
            Episode * newEpisode = new Episode(jsonM2[j]);
            string episodeTitle = newEpisode->title;
            episodes.push_back(*newEpisode);
      	 }
         cout << "\nreached Episodes logic within SeriesSeason\n";
      }
   }
}

SeriesSeason::~SeriesSeason() {
   title = "";
   season = "";
   imdbRating = "";
   genre = "";
   poster = "";
   plot = "";
}

string SeriesSeason::toJsonString(){
   string ret = "{}";
   Json::Value jsonLib;
   jsonLib["Title"] = title;
   jsonLib["Season"] = season;
   jsonLib["imdbRating"] = imdbRating;
   jsonLib["Genre"] = genre;
   jsonLib["Poster"] = poster;
   jsonLib["Plot"] = plot;
   //jsonLib["Episodes"] = episodes;
   ret = jsonLib.toStyledString();
   return ret;
}

Json::Value SeriesSeason::toJson(){
   //string ret = "{}";
   
   
   Json::Value jsonLib;
   jsonLib["Title"] = title;
   jsonLib["Season"] = season;
   jsonLib["imdbRating"] = imdbRating;
   jsonLib["Genre"] = genre;
   jsonLib["Poster"] = poster;
   jsonLib["Plot"] = plot;
   //jsonLib["Episodes"] = episodesArray;
   return jsonLib;
}

void SeriesSeason::setValues(string aTitle, string aSeason,
    string aImdbRating, string aGenre, string aPoster, string aPlot,
    vector<Episode> aEpisodes) {
   title = aTitle;
   season = aSeason;
   imdbRating = aImdbRating;
   genre = aGenre;
   poster = aPoster;
   plot = aPlot;
   episodes = aEpisodes;
}


void SeriesSeason::print(){
   cout << "title " << title << " season " << season << " imdbRating " << imdbRating
        << " genre " << genre << " poster " << poster <<  " plot " << plot << "episodes.size(): " 
	<< episodes.size() << endl;
}
