#include <string>
#include <cmath>
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
* Purpose: An Episodes class for serializing between client and server.
*
* Ser321 Principles of Distributed Software Systems
* see http://pooh.poly.asu.edu/Ser321
* @author Brent Garcia, Tim Lindquist Tim.Lindquist@asu.edu
*
Software Engineering, CIDSE, IAFSE, ASU Poly
* @version April 2020
*/
class Episode {
protected:
public:

   string title;
   string imdbRating;
   string episode;

   Episode();
   Episode(string aTitle, string aImdbRating,
       string aEpisode);
   Episode(const Json::Value& jsonObj);
   Episode(string jsonString);
   ~Episode();
   string toJsonString();
   Json::Value toJson();
   void fromJson(Json::Value json);
   void setValues(string aTitle, string aImdbRating,
       string episode);
   void print();
};
