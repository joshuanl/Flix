#ifndef MOVIE_
#define MOVIE_ 

#include "lib/User.h"
#include "lib/Actor.h"
#include <set>
#include <vector>
#include <string>

using namespace std;

class User;
class Actor;
class Movie {
  public: 
    Movie (string title);       // constructor for a movie with the given title
    Movie(int n, string title);
    Movie (const Movie & other);  // copy constructor
    Movie();

    ~Movie ();                  // destructor

    string getTitle () const;   // returns the title of the movie

    void addKeyword (string keyword); 
      /* Adds the (free-form) keyword to this movie.
         If the exact same keyword (up to capitalization) was already
         associated with the movie, then the keyword is not added again. */

    set<string> getAllKeywords () const;
      /* Returns a set of all keywords associated with the movie. */
    void updateRating(int n);
    int getRating();
    vector<pair<User*, double> >* getUsersWhoRated();
    void addFeedBack(pair<User*, double> v_pair);    
    vector<Actor*>* getActors();
    void addActor(Actor *actor);

  private:
    // you get to decide what goes here
    string title;
    set<string> AllKeywords;
    int rating;
    vector<pair<User*, double> > *usersWhoRated;
    vector<Actor*> *actors;
};
#endif