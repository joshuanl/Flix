#ifndef USER_H
#define USER_H 

#include <string>
#include <queue>
#include "lib/Movie.h"

using namespace std;
class Movie;
class User {
  public:
    User();
    User (string ID, string name); //email, name 
    User (const User & other); // copy constructor
    ~User ();            // destructor
    string getID () const;    // returns the ID associated with this user
    string getName () const;  // returns the name associated with this user

    queue<Movie*>* movieQueue(); 
      /* returns a pointer to the user's movie queue.
         This is the easiest way to ensure that you can modify the queue.
         (If you return by reference, that's also possible, but you'd need
         to be very careful not to invoke any deep copy constructors or
         assignments. A pointer is thus safer.) */

    void rentMovie (Movie *m);
      /* sets the user's currently rented movie to m.
         If the user already has a movie checked out, then it does nothing.
         (So no overwriting the current movie.) */

    void returnMovie ();
      /* returns the movie that the user currently has checked out.
         Does nothing if the user doesn't currently have a movie. */

    Movie* currentMovie ();
      /* returns the user's current checked out movie.
         Returns NULL if the user has no movie checked out. */
    bool renting();
    void addWatchedMovie(Movie *movie);
    vector<Movie*>* getWatchedMovies();
    void updateLinks(vector<pair<User*, double> > *newLinks);
    vector<pair<User*, double> >* getLinks();
    double getRatingOfWatched(Movie *movie);
    double getSimOfUser(User *user);

  private:
    // you get to decide what goes here.
    string user_ID, user_name;
    queue<Movie*> *queue_of_movies;
    Movie *rented_movie;
    bool checked_out;
    vector<Movie*> *moviesWatched;
    vector<pair<User*, double> > *links;

};

#endif