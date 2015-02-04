#include "lib/User.h"
#include <queue>
#include "lib/Movie.h"
#include <iostream>

using namespace std;

User::User(){}
User::~User(){}

User::User(string ID, string name){
	user_ID = ID;
	user_name = name;
  queue_of_movies = new queue<Movie*>();
  moviesWatched = new vector<Movie*>();
  links = new vector<pair<User*, double> >();
  checked_out = false;

}//end of default constructor

User::User(const User & other): user_ID(other.user_ID), user_name(other.user_name){

}//end of deep copy

string User::getID () const{
	return user_ID;
}//end of getID    

string User::getName () const{
  	return user_name;
}//end of getname

queue<Movie*>* User::movieQueue(){ 
      /* returns a pointer to the user's movie queue.
         This is the easiest way to ensure that you can modify the queue.
         (If you return by reference, that's also possible, but you'd need
         to be very careful not to invoke any deep copy constructors or
         assignments. A pointer is thus safer.) */
    return queue_of_movies;
}//end of movie queue         

void User::rentMovie (Movie *m){
      /* sets the user's currently rented movie to m.
         If the user already has a movie checked out, then it does nothing.
         (So no overwriting the current movie.) */
    rented_movie = m;
    checked_out = true;
}//end of rent movie


void User::returnMovie (){
      /* returns the movie that the user currently has checked out.
         Does nothing if the user doesn't currently have a movie. */
	rented_movie = NULL;
  checked_out = false;
}//end of return movie


Movie* User::currentMovie (){
      /* returns the user's current checked out movie.
         Returns NULL if the user has no movie checked out. */
	return rented_movie;
}//end of current movie

bool User::renting(){
  return checked_out;
}

void User::addWatchedMovie(Movie *movie){
  moviesWatched->push_back(movie);
}//end of adding a watched movie

vector<Movie*>* User::getWatchedMovies(){
  return moviesWatched;
}//end of returning vector of watched movies

void User::updateLinks(vector<pair<User*, double> > *newLinks){
  links = newLinks;
}//end of updateLinks

vector<pair<User*, double> >* User::getLinks(){
  return links;
}//end of get links

double User::getRatingOfWatched(Movie *movie){
  for (unsigned int i = 0; i < moviesWatched->size(); i++){
    if (moviesWatched->at(i)->getTitle() == movie->getTitle()){
      return moviesWatched->at(i)->getRating();
    }
  }//end of for
  cerr << "didnt find movie in getRatingOfWatched" << endl;
  return -1;
}//end of getting rating of a watched movie

double User::getSimOfUser(User *user){
  for (unsigned int i = 0; i < links->size(); i++){
    if (links->at(i).first->getID() == user->getID()){
      return links->at(i).second;
    }
  }//end of for
  cerr << "didnt find sim in getSimOfUser" << endl;
  return -1;
}//end of getting similarity between another user