#include "MediaClientGui.cpp"
#include "../server/SeasonLibrary.hpp"

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Multiline_Input.H>
#include <FL/Fl_Check_Browser.H>
#include <stdio.h>
#include <iostream>
#include <chrono>
#include <ctime>
#include <stdlib.h>
#include <sstream>
#include <thread>
#include <json/json.h>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Exception.hpp>

using namespace std;

std::string cmd;
void run(){
   system(cmd.c_str());
}

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
* Purpose: An Media Library App that used to store TV Series data from the 
omdb database.
*
* Ser321 Principles of Distributed Software Systems
* see http://pooh.poly.asu.edu/Ser321
* @author Brent Garcia, Tim Lindquist Tim.Lindquist@asu.edu
*
Software Engineering, CIDSE, IAFSE, ASU Poly
* @version April 2020
*/

class MediaClient : public MediaClientGui {

public:

   std::string userId;
   std::string omdbkey;
   bool searched = false;
   std::thread * playThread;
   //MediaLibrary * library;
   SeasonLibrary * library;
   //SeasonLibrary * sLibrary;

/** ClickedX is one of the callbacks for GUI controls.
    * Callbacks need to be static functions. But, static functions
    * cannot directly access instance data. This program uses "userdata"
    * to get around that by passing the instance to the callback
    * function. The callback then accesses whatever GUI control object
    * that it needs for implementing its functionality.
    */
   static void ClickedX(Fl_Widget * w, void * userdata) {
      std::cout << "You clicked Exit" << std::endl;
      exit(1);
   }

   /**
    * Static search button callback method.
    */
    static void SearchCallbackS(Fl_Widget*w, void*data) {
      MediaClient *o = (MediaClient*)data;
      o->SearchCallback(); //call the instance callback method
   }


   void SearchCallback() {
      //MediaClient *o = (MediaClient*)data;
      cout << "Search Clicked. You asked for a OMDb search of Season: " <<
         this->seasonSrchInput->value() << " Series: " <<
         this->seriesSrchInput->value() << endl;
      try{
         std::string url = "https://www.omdbapi.com/?r=json&apikey=";
         url = url + this->omdbkey;

         //Spaces must be converted to %20
         string query = this->seriesSrchInput->value();
         string urlEncodedQuery = "";
         for (int i = 0; i < query.length(); i++) {
            if (query.at(i) == ' ') {
               urlEncodedQuery += "%20";
            } else {
               urlEncodedQuery += query.at(i);
            }
         }
         /*
         * Another API call would have to be made here to get
         * the rest of the required information. Same as assignment 2.
         */
	 std::string url2 = url + "&t=" + urlEncodedQuery;
         url = url + "&t=" + urlEncodedQuery + "&season=" + this->seasonSrchInput->value();
         
         cout << "sending request url2: " << url2 << endl;
         cout << "sending request url: " << url << endl;
         std::ostringstream os;
         curlpp::Easy myRequest;
         myRequest.setOpt(new curlpp::options::WriteStream(&os));
         //curlpp::options::Url myUrl(std::string(url));
         myRequest.setOpt(new curlpp::options::Url(url.c_str()));
         myRequest.perform();
         std::string aString1 = os.str();
         std::cout << aString1 << std::endl;
	 
         std::ostringstream os2;
	 
         curlpp::Easy myRequest2;
         myRequest2.setOpt(new curlpp::options::WriteStream(&os2));
         myRequest2.setOpt(new curlpp::options::Url(url2.c_str()));
         myRequest2.perform();
         
         std::string aString2 = os2.str();
         SeriesSeason* tempSS = new SeriesSeason(aString2, aString1);
	 //tempSS->print();
         //cout << aString2 << std::endl;
 	 //Store search results in library
	 if (tempSS){
            library->tempFromSearch = *tempSS;
            searched = true;
            this->buildTree();
         }
	 
         // PSEUDOCODE:
         // Create temporary library to hold new seriesSeason with the saved search added
                 // store new SS in a temporary library
                 // output results of new library
          
      }catch ( curlpp::LogicError & e ) {
         std::cout << e.what() << std::endl;
      }
      catch ( curlpp::RuntimeError & e ) {
         std::cout << e.what() << std::endl;
      }
   }

   // Static menu callback method
   static void TreeCallbackS(Fl_Widget*w, void*data) {
      MediaClient *o = (MediaClient*)data;
      o->TreeCallback(); //call the instance callback method
   }


   /**
    * TreeCallback is a callback for tree selections, deselections, expand or
    * collapse.
    */
   void TreeCallback() {
      // Find item that was clicked
      Fl_Tree_Item *item = (Fl_Tree_Item*)tree->item_clicked();
      cout << "Tree callback. Item selected: ";
      if ( item ) {
         cout << item->label();
      } else {
         cout << "none";
      }
      cout << endl;
      std::string aStr("unknown");
      std::string aTitle(item->label());
      switch ( tree->callback_reason() ) {  // reason callback was invoked
      case       FL_TREE_REASON_NONE: {aStr = "none"; break;}
      case     FL_TREE_REASON_OPENED: {aStr = "opened";break;}
      case     FL_TREE_REASON_CLOSED: {aStr = "closed"; break;}
      case   FL_TREE_REASON_SELECTED: {
         aStr = "selected";
         //MediaDescription md;
	 SeriesSeason ss;
         SeriesSeason parentSS;
         if(library){
	    //Is parent
	    if (item->depth() == 1){
              if (searched == true) {
                ss = library->tempFromSearch;
              } else {
		ss = library->get(aTitle);
              }
	      //episodeInput->value(ss.title.c_str());
              seriesSeasonInput->value(ss.season.c_str());
              ratingInput->value(ss.imdbRating.c_str());
              genreInput->value(ss.genre.c_str());
	      summaryMLI->value(ss.plot.c_str());
            }//Is Child
	    else if (item->depth() == 2) {
              string episodeName = item->label();
              Fl_Tree_Item* parentNode = (Fl_Tree_Item*)item->parent();
              if (searched == true) {
                parentSS = library->tempFromSearch;
              } else {
              	parentSS = library->get(parentNode->label());
              }
              for(const auto& episode : parentSS.episodes){
                string tempEpisodeName = episode.title;
            	if (episodeName == tempEpisodeName){
                   cout << "Episode name is " << parentSS.season << "!\n";
                   episodeInput->value(episode.episode.c_str());
         	   seriesSeasonInput->value(parentSS.season.c_str());
         	   ratingInput->value(episode.imdbRating.c_str());
         	   genreInput->value(parentSS.genre.c_str());
	 	   summaryMLI->value(parentSS.plot.c_str());
                }
              }

	      cout << "Parent is " << ss.title << ".\n";
            }
            cout << "trying to get: " << item->label() << endl;
            
            //ss = library->get(aTitle);
	    //vector<string> episodeNames = ss.getAllEpisodeTitles();

         }else{
            cout << "library entry not found" << endl;
            break;
         }
         cout << "media: "<< ss.title << " " << ss.season << " "
              << ss.imdbRating << " " << ss.genre << " " << ss.poster
              << " " << ss.plot << endl;
         //episodeInput->value(ss.title.c_str());
         //seriesSeasonInput->value(ss.season.c_str());
         //ratingInput->value(ss.imdbRating.c_str());
         //genreInput->value(ss.genre.c_str());
	 //summaryMLI->value(ss.plot.c_str());
         break;
      }
      case FL_TREE_REASON_DESELECTED: {aStr = "deselected"; break;}
      default: {break;}
      }
      cout << "Callback reason: " << aStr.c_str() << endl;
   }

   // Static menu callback method
   static void Menu_ClickedS(Fl_Widget*w, void*data) {
      MediaClient *o = (MediaClient*)data;
      o->Menu_Clicked(); //call the instance callback method
   }

   // Menu selection instance method that has ccess to instance vars.
   void Menu_Clicked() {
      char picked[80];
      menubar->item_pathname(picked, sizeof(picked)-1);
      string selectPath(picked);
      cout << "Selected Menu Path: " << selectPath << endl;
      // Handle menu selections
      if(selectPath.compare("File/Save")==0){
         bool restSave = library->toJsonFile("series10.json");
         cout << "Save not implemented" << endl;
      }else if(selectPath.compare("File/Restore")==0){
         library = new SeasonLibrary();
         buildTree();
      }else if(selectPath.compare("File/Tree Refresh")==0){
         searched = false;
         buildTree();
      }else if(selectPath.compare("File/Exit")==0){
         if(playThread && playThread->joinable()){
            playThread->join();
         }
         exit(0);
      }else if(selectPath.compare("Series-Season/Add")==0){
         cout << "searched is  " << searched << endl;
         if (searched == true) {
            SeriesSeason tempSS = library->tempFromSearch;
            library->addSeriesSeason(tempSS);
            searched = false;
            buildTree();
         }
      }else if(selectPath.compare("Series-Season/Remove")==0){
        Fl_Tree_Item *item = (Fl_Tree_Item*)tree->item_clicked();
        if ( item && searched==false ) {
           cout << item->label() << endl;
           string seriesName;
           if (item->depth() == 1){
	      seriesName = item->label();
              library->removeSeriesSeason(seriesName);
           } else {
	      seriesName = item->parent()->label();
              library->removeSeriesSeason(seriesName);
           }
           buildTree();
      	} else {
         cout << "none" << endl;
      }
      }
   }

   /**
    * a static method to remove spaces, tabs, new lines and returns from the
    * begining or end of a string.
    */
   static std::string& trimMe (std::string& str) {
      // right trim
      while (str.length() > 0 && (str[str.length()-1] == ' '  ||
                                  str[str.length()-1] == '\t' ||
                                  str[str.length()-1] == '\n' ||
                                  str[str.length()-1] == '\r')){
         str.erase(str.length ()-1, 1);
      }
      // left trim
      while (str.length () > 0 && (str[0] == ' ' || str[0] == '\t')){
         str.erase(0, 1);
      }
      return str;
   }

   /**
    * a method to execute a command line command and to return
    * the resulting string.
    */
   std::string exec(const char* cmd) {
      FILE* pipe = popen(cmd, "r");
      if (!pipe) return "ERROR";
      char buffer[128];
      std::string result = "";
      while(!feof(pipe)) {
         if(fgets(buffer, 128, pipe) != NULL)
            result += buffer;
      }
      pclose(pipe);
      return result;
   }

   void buildTree(){
      vector<string> result = library->getTitles();
      cout << "server has titles";
      tree->clear();
      if (searched == true){
         SeriesSeason ss = library->tempFromSearch;
         cout << "SS TITLE!" << ss.title << "\n\n";
	 for(const auto& episode : ss.episodes){
            //cout << "\n another episode here\n";
	    string newDescription = ss.title + "/" + episode.title;
            tree->add(newDescription.c_str());
        }
      } else {
      	 for(int i=0; i<result.size(); i++){
            cout << " " << result[i];
            //MediaDescription md = library->get(result[i]);
            SeriesSeason ss = library->get(result[i]);
	    for(const auto& episode : ss.episodes){
               //cout << "\n another episode here\n";
	       string newDescription = ss.title + "/" + episode.title;
               tree->add(newDescription.c_str());
            }
         }
      }
	 
         //cout << ss.title << " " << ss.season << " " << ss.imdbRating
         //     << " " << ss.genre << endl;
      
      cout << endl;
      tree->redraw();
   }

   MediaClient(const char * name = "Tim", const char * key = "myKey") : MediaClientGui(name) {
      
      searchButt->callback(SearchCallbackS, (void*)this);
      menubar->callback(Menu_ClickedS, (void*)this);
      tree->callback(TreeCallbackS, (void*)this);
      callback(ClickedX);
      omdbkey = key;
      userId = "Tim.Lindquist";
      library = new SeasonLibrary();
      //library = new MediaLibrary();
      
      buildTree();
   }
};

int main(int argc, char * argv[]) {
   std::string developer = (argc>1)?argv[1]:"Tim.Lindquist";
   std::string omdbkey = (argc>2)?argv[2]:"omdbkey";
   std::string windowTitle = developer + "'s SeriesSeason Browser";
   MediaClient cm(windowTitle.c_str(),omdbkey.c_str());
   //HttpClient httpclient(host);
   //studentcollectionstub sc(httpclient);
   return (Fl::run());
}
