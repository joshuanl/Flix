#ifndef NFDB_H
#define NFDB_H

#include <set>
#include <map>
#include <string>
#include "lib/Actor.h"
#include "lib/User.h"
#include "lib/Movie.h"

class NFDB
{
public:
	NFDB(map<string, User*> *UDB, map<string, Movie*> *MDB, map<string, set<Movie*>* > *KDB);
	~NFDB();

	void readUserFile(string u_filename);
	void readMovieFile(string m_filename);
	void saveUserInfo();
	bool loginExists(string login_id);
	bool movieExists(string title);
	bool KWExists(string keyword);
	bool actorExists(string keyword);
	User* getUser(string login_id);
	Movie* getMovie(string title);
	set<Movie*>* getKWSet(string keyword);
	vector<Actor*>* getActorDB();
	Actor* getActor(string name);
	map<string, User*>* getUserDB();
	map<string, Movie*>* getMovieDB();
	int getUserIndex(User *user);
	void addUser(string input_id, User *user);
	double basicSimilarity(User* userA, User *userB);
	vector<pair<User*, double> >* findRS(User *userA);
	void updateBasicSim();
	bool contains(vector<string> *visited, User *user);
	pair<int, Movie*> recommendation(User* user);
	void buildRelatedActors();
	int findBaconLength(Actor *actorA, Actor *actorB);


private:
	map<string, User*> *userDB;
	map<string, Movie*> *movieDB;			
	map<string, set<Movie*>* > *keywordDB;
	string data_file;
	vector<Actor*> *actorDB;

};

#endif