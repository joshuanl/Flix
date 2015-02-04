
#ifndef ACTOR_H
#define ACTOR_H 

#include <vector>
#include <string>

using namespace std;

class Movie;
class Actor
{
public:
	Actor();
	Actor(string name, int index);
	~Actor();
	string getName();
	int getIndex();
	vector<pair<Actor*, Movie*>* >* getRelatedActors();
	vector<Movie*>* getMoviesActedIn();
	void addRelatedActor(pair<Actor*, Movie*> *v_pair);
	void addMovieActedIn(Movie *movie);

private:
	string name;
	int index;
	vector<pair<Actor*, Movie*>* > *relatedActors;
	vector<Movie*>* moviesActedIn;
};
#endif
