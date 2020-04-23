#include "Episode.hpp"
#include <iostream>
#include <stdlib.h>

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
* Purpose: An Episodes class for serializing between client and server.
*
* Ser321 Principles of Distributed Software Systems
* see http://pooh.poly.asu.edu/Ser321
* @author Brent Garcia, Tim Lindquist Tim.Lindquist@asu.edu
*
Software Engineering, CIDSE, IAFSE, ASU Poly
* @version April 2020
*/
Episode::Episode(){
   title = "";
   imdbRating = "";
   episode = "";
}

Episode::Episode(string aTitle, string aImdbRating,
       string aEpisode) {
   title = aTitle;
   imdbRating = aImdbRating;
   episode = aEpisode;
}

Episode::Episode(const Json::Value& jsonObj){
   Json::Value::Members mbr = jsonObj.getMemberNames();
   for(vector<string>::const_iterator i = mbr.begin(); i!= mbr.end(); i++){
      //cout << *i << " " << endl;
      Json::Value jsonM = jsonObj[*i];
      if(*i=="Title"){
         title = jsonM.asString();
      }else if(*i=="imdbRating"){
         imdbRating = jsonM.asString();
      }else if(*i=="Episode"){
         episode = jsonM.asString();
         cout << "The Episode is: " << episode << "\n";
      }
   }
}

Episode::Episode(string jsonString){
   Json::Reader reader;
   Json::Value root;
   bool parseSuccess = reader.parse(jsonString,root,false);
   if(parseSuccess){
      //cout << "successful parse" << endl;
      Json::Value::Members mbr = root.getMemberNames();
      for(vector<string>::const_iterator i = mbr.begin(); i!= mbr.end(); i++){
         //cout << *i << " " << endl;
         Json::Value jsonM = root[*i];
         if(*i=="Title"){
            title = jsonM.asString();
         }else if(*i=="imdbRating"){
            imdbRating = jsonM.asString();
         }else if(*i=="Episode"){
            episode = jsonM.asString();
	    cout << "The Episode is: " << episode << "\n";
         }
      }
   }else{
      cout << "SeriesSeason constructor parse error with input: " << jsonString
           << endl;
   }
}

Episode::~Episode() {
   title = "";
   imdbRating = "";
   episode = "";
}

string Episode::toJsonString(){
   string ret = "{}";
   Json::Value jsonLib;
   jsonLib["Title"] = title;
   jsonLib["imdbRating"] = imdbRating;
   jsonLib["Episode"] = episode;
   ret = jsonLib.toStyledString();
   return ret;
}

Json::Value Episode::toJson(){
   //string ret = "{}";
   Json::Value jsonLib;
   jsonLib["Title"] = title;
   jsonLib["imdbRating"] = imdbRating;
   jsonLib["Episode"] = episode;
   return jsonLib;
}

void Episode::setValues(string aTitle, string aImdbRating,
       string aEpisode) {
   title = aTitle;
   imdbRating = aImdbRating;
   episode = aEpisode;
}

void Episode::print(){
   cout << "title " << title << " imdbRating " << imdbRating 
	<< " episode " << episode <<"\n";
}
