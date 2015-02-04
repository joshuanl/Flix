#include "Actor.h"
#include "lib/Movie.h"
#include <vector>
#include <string>

using namespace std;


Actor::Actor(){
	name = "";
	index = -1;
}

Actor::Actor(string name, int index){
	this->name = name;
	this->index = index;
	relatedActors = new vector<pair<Actor*, Movie*>* >();
	moviesActedIn = new vector<Movie*>();
}//end of constructor

Actor::~Actor(){}

string Actor::getName(){
	return name;
}//end of getname

int Actor::getIndex(){
	return index;
}//end of returning index of actor

vector<pair<Actor*, Movie*>* >* Actor::getRelatedActors(){
	return relatedActors;
}//end of returning actors related

vector<Movie*>* Actor::getMoviesActedIn(){
	return moviesActedIn;
}//end of returning movies actor acted in

void Actor::addRelatedActor(pair<Actor*, Movie*> *v_pair){
	relatedActors->push_back(v_pair);
}//end of adding a co-actor

void Actor::addMovieActedIn(Movie *movie){
	moviesActedIn->push_back(movie);
}