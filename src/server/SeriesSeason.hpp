#include "Episode.hpp"
#include <string>
#include <cmath>
#include <vector>
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
class SeriesSeason {
protected:
public:

   string title;
   string season;
   string imdbRating;
   string genre;
   string poster;
   string plot;
   vector<Episode> episodes;

   SeriesSeason();
   SeriesSeason(string aTitle, string aSeason,
       string aImdbRating, string aGenre, string aPoster, 
       string aPlot, vector<Episode> aEpisodes );
   SeriesSeason(const Json::Value& jsonObj);
   SeriesSeason(const Json::Value& jsonObj1, const Json::Value& jsonObj2);
   SeriesSeason(string jsonString);
   SeriesSeason(string jsonString1, string jsonString2);
   ~SeriesSeason();
   string toJsonString();
   Json::Value toJson();
   void fromJson(Json::Value json);
   void setValues(string aTitle, string aSeason,
       string aImdbRating, string aGenre, string aPoster,
       string aPlot, vector<Episode> aEpisodes);
   void print();
};
