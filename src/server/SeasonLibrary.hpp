#include "SeriesSeason.hpp"
#include <string>
#include <map>
#include <vector>
#include <json/json.h>

using namespace std;

/**
 * Copyright 2020 Brent Garcia,
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * 
 * Purpose: SeasonLibrary defines the interface for music library operations
 * media work -- song.
 * Ser321 Principles of Distributed Software Systems
 * see http://pooh.poly.asu.edu/Ser321
 * @author BrentGarcia Tim.Lindquist@asu.edu
 *         Software Engineering, CIDSE, IAFSE, ASU Poly
 * @version January 2020
 */
class SeasonLibrary {
protected:
   std::map<std::string, SeriesSeason> media;
public:
   SeriesSeason tempFromSearch;
   SeasonLibrary();
   ~SeasonLibrary();

   bool initLibraryFromJsonFile(string jsonFileName);
   bool toJsonFile(string jsonFileName);
   bool addSeriesSeason(SeriesSeason seriesSeasonToAdd);
   bool removeSeriesSeason(string seriesSeasonToRemove);
   string serviceInfo();
   Json::Value get(string aTitle);
   //std::vector<string> getTitles();
   Json::Value getTitles();
};
