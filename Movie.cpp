
#include "lib/Movie.h"
#include "lib/User.h"
#include <set>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

Movie::Movie(){}

Movie::Movie(string str){
	title = str;
	rating = 0;
	usersWhoRated = new vector<pair<User*, double> >();
	actors = new vector<Actor*>();
}//end of constrcutor

Movie::Movie(int n, string str){
	title = str;
	rating = n;
	usersWhoRated = new vector<pair<User*, double> >();
	actors = new vector<Actor*>();
}//end of defult constructor

Movie::Movie (const Movie & other): title(other.title), AllKeywords(other.AllKeywords){
}
//end of deep constrcutor

Movie::~Movie(){
}//end of deconstructor

string Movie::getTitle () const{
	return title;
}//end of getTitle

 void Movie::addKeyword (string keyword){
 	AllKeywords.insert(keyword);
 }//end of adding a keyword

 set<string> Movie::getAllKeywords () const{
 	set<string> allwords = AllKeywords;

 	return allwords;
 }//end of getting all keywords

 void Movie::updateRating(int n){
 	rating = n;
 }//end of updatin moving rating

int Movie::getRating(){
	return rating;
}//end of getting rating of movie

vector<pair<User*, double> >* Movie::getUsersWhoRated(){
	return usersWhoRated;
}//end of getting users who rated movie

void Movie::addFeedBack(pair<User*, double> v_pair){
	usersWhoRated->push_back(v_pair);
}

vector<Actor*>* Movie::getActors(){
	return actors;
}//end of getting all actors

void Movie::addActor(Actor *actor){
	actors->push_back(actor);
}//end of adding an actor the movie