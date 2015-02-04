#include "lib/NFDB.h"
#include "lib/Actor.h"
#include <string>
#include <queue>
#include <vector>
#include <locale>
#include <iostream>
#include <fstream>
#include <exception>
#include <sstream>
#include <map>
#include <cmath>
#include <stdlib.h>    
#include <time.h>

using namespace std;


NFDB::NFDB(map<string, User*> *UDB, map<string, Movie*> *MDB, map<string, set<Movie*>* > *KDB){
	userDB = UDB;
	movieDB= MDB;
	keywordDB = KDB;
	actorDB = new vector<Actor*>();
}//end of constructor


map<string, User*>* NFDB::getUserDB(){
	return userDB;
}//end of returning userDB

vector<Actor*>* NFDB::getActorDB(){
	return actorDB;
}//end of returning actorDB


map<string, Movie*>* NFDB::getMovieDB(){
	return movieDB;
}

set<Movie*>* NFDB::getKWSet(string keyword){
	return (keywordDB->find(keyword)->second);
}//end of getting set of keywords

Movie* NFDB::getMovie(string title){
	string name_caps = "";
	locale loc;
	for (string::size_type i=0; i<title.length(); ++i)
     				name_caps += toupper(title[i],loc);
	return (movieDB->find(name_caps)->second);
}//end of get movie

void NFDB::addUser(string input_id, User *user){
	userDB->insert(make_pair(input_id, user));
}//end of adding  user

bool NFDB::KWExists(string keyword){
	if (keywordDB->find(keyword) != keywordDB->end()){
		return true;
	}
	return false;
}//end of kw exists

bool NFDB::actorExists(string keyword){
	for (unsigned int i = 0; i < actorDB->size(); i++){
		if (actorDB->at(i)->getName() == keyword){
			return true;
		}
	}//end of for
	return false;
}//end of actor exists

Actor* NFDB::getActor(string name){
	Actor *noActor = new Actor();
	for (unsigned int i = 0; i < actorDB->size(); i++){
		if (actorDB->at(i)->getName() == name){
			return (actorDB->at(i));
		}
	}//end of for
	return noActor;
}//end of getting actor from DB

bool NFDB::movieExists(string title){
	if (movieDB->find(title) != movieDB->end()){
		return true;
	}
	return false;
}//end of movie exists

bool NFDB::loginExists(string login_id){
	if (userDB->find(login_id) == userDB->end()){
		return false;
	}
	return true;

}//end of checking if login id exists

User* NFDB::getUser(string login_id){
	return ((userDB->find(login_id))->second);
}//end of returning user

void NFDB::readUserFile(string u_filename){
	stringstream ss;
	data_file = u_filename;
	ifstream file(u_filename.c_str());
	User *temp_user = new User();
	Movie *movie;
	string input, input2, id, name, name_caps;
	locale loc;
	while(file >> input){
		if (input.compare("BEGIN") == 0){
			file >> input2;
			if(input2 == "QUEUE"){
				getline(file, input);
				getline(file, input);
				while(input != "END QUEUE"){
					name_caps = "";
					for (string::size_type i=0; i<input.length(); ++i)
     					name_caps += toupper(input[i],loc);
     				//========================finding user
     				for (map<string, User*>::iterator userDB_it = userDB->begin(); userDB_it != userDB->end(); ++userDB_it){
     					if (userDB_it->first == id){
     						temp_user = userDB_it->second;
     					}
     				}//end of it for
     				//========================finding movie
     				for (map<string, Movie*>::iterator movieDB_it = movieDB->begin(); movieDB_it != movieDB->end(); ++movieDB_it){
     					if (movieDB_it->first == name_caps){
     						movie = movieDB_it->second;
     					}
     				}//end of it for
					temp_user->movieQueue()->push(movie);
					getline(file, input);
				}//end of while; reading in queue
			}//end of else if queue
			else if(input2 == "RATINGS"){
			//========================finding user
     			for (map<string, User*>::iterator userDB_it = userDB->begin(); userDB_it != userDB->end(); ++userDB_it){
     				if (userDB_it->first == id){
     						temp_user = userDB_it->second;
     				}
     			}//end of it for
     			getline(file, name); //moving line cursor to rating
     			file >> name;
     			int rating = 0;
     			while(name != "END"){
     				rating = atoi(name.c_str());
     				getline(file, name);
     				name = name = name.substr(1, name.size());
     				//===============================update rating if in currently renting
     				if (temp_user->currentMovie()->getTitle().compare(name) == 0){
     					temp_user->currentMovie()->updateRating(rating);
     				}
     				movie = new Movie(rating, name);
     				temp_user->addWatchedMovie(movie);
     				//===============================find movie in DB to add user to vec in Movie
    
     				for (map<string, Movie*>::iterator MDB_it = movieDB->begin(); MDB_it != movieDB->end(); ++MDB_it){
     					if ((*MDB_it).second->getTitle() == name){
     						(*MDB_it).second->addFeedBack(make_pair(temp_user, rating));
     						break;
     					}
     				}//end of for
     				file >> name;
     			}//end of while
			}//end of else if RATINGS
			if (input2 != "QUEUE" && input2 != "QUEUE" && input2 != "RATINGS"){	
				id = input2;
				file >> input;
				getline(file, name);
				name = name.substr(1,name.size()-1);
				temp_user = new User(id, name);
				userDB->insert(make_pair(id, temp_user));
				//file >> input;
			}//end of if user
		}//end of begin
		 	if(input == "MOVIE:"){
				getline(file, name);
				if(name.size() > 0){
					name = name.substr(1, name.size());     // "removes the space between the ':' and the keyword" that getline reads
					name_caps = "";
					for (string::size_type i=0; i<name.length(); ++i)
    	 				name_caps += toupper(name[i],loc);
     				//========================finding user
     				for (map<string, User*>::iterator userDB_it = userDB->begin(); userDB_it != userDB->end(); ++userDB_it){
     						if (userDB_it->first == id){
     							temp_user = userDB_it->second;
     						}
	     				}//end of it for
    	 				//=====================finding movie
     				for (map<string, Movie*>::iterator movieDB_it = movieDB->begin(); movieDB_it != movieDB->end(); ++movieDB_it){
     					if (movieDB_it->first == name_caps){
     						movie = movieDB_it->second;
     					}
  	   				}//end of it for
					temp_user->rentMovie(movie);
				}//end of if movie is checked out	
			}//end of if MOVIE:
	}//end of while has input
	// vector<pair<User*, double> > *usersWhoRated;
	// for (map<string, Movie*>::iterator MDB_it = movieDB->begin(); MDB_it != movieDB->end(); ++MDB_it){
 //     	usersWhoRated = (*MDB_it).second->getUsersWhoRated();
 //     	cerr << "USERS WHO RATED IN MOVIE: " << (*MDB_it).second->getTitle() << endl;
 //     	for (unsigned int i = 0; i < usersWhoRated->size(); i++){
 //     		cerr << "     " << usersWhoRated->at(i).first->getID() << endl;
 //     	}
 //    }//end of for
}//end of readUserFile

void NFDB::readMovieFile(string m_filename){
	ifstream file(m_filename.c_str());
	string input, name, keyword, name_caps;
	string movie_name_caps = "";
	string temp = "";
	int actor_index = 0;
	bool stop = false;
	locale loc;
	Movie *movie;
	Actor *temp_actor;
	set<Movie*> *related_movies;
	set<Movie*> *temp_set;
	while(file >> input){
		if (input.compare("BEGIN") == 0){
			name = "";
			getline(file, name);
			name = name.substr(1, name.size());
			movie = new Movie(name);
			name_caps = "";
			for (string::size_type i=0; i<name.length(); ++i)
     				name_caps += toupper(name[i],loc);
			movieDB->insert(make_pair(name_caps, movie));
			movie_name_caps = name_caps;
			file >> input;
			stop = false;
			while(!stop){
				related_movies = new set<Movie*>();
				keyword = "";
				if(input == "KEYWORD:"){
						getline(file, keyword);
						temp = "";
						for (string::size_type i=0; i<keyword.length(); ++i)
     						temp += toupper(keyword[i],loc);
     					temp = temp.substr(1,temp.size());   // "removes the space between the ':' and the keyword" that getline reads
						
						if (keywordDB->find(temp) == keywordDB->end()){
							related_movies->insert(movie);
							keywordDB->insert(make_pair(temp, related_movies));
						}//end of if first time keyword
						else if(keywordDB->find(temp) != keywordDB->end()){
							//========================finding  movie set
     						for (map<string, set<Movie*>* >::iterator keywordDB_it = keywordDB->begin(); keywordDB_it != keywordDB->end(); ++keywordDB_it){
     							if (keywordDB_it->first == temp){
     								temp_set = keywordDB_it->second;
	     						}
    	 					}//end of it for
							temp_set->insert(movie);
						}//end of else
						temp = "";
						for (string::size_type i=0; i<keyword.length(); ++i)
	     					temp += toupper(keyword[i],loc);
    	 				//=====================finding movie
     					for (map<string, Movie*>::iterator movieDB_it = movieDB->begin(); movieDB_it != movieDB->end(); ++movieDB_it){
     						if (movieDB_it->first == name_caps){
     							movie = movieDB_it->second;
     						}
	     				}//end of it for
						movie->addKeyword(temp);
				}//end of if KEYWORD:
				else if(input == "ACTOR:"){
					name_caps = "";

					getline(file, temp);
     				temp = temp.substr(1,temp.size());   // "removes the space between the ':' and the keyword" that getline reads
					for (string::size_type i=0; i<temp.length(); ++i)
	     					name_caps += toupper(temp[i],loc);
					bool contains_actor = false;
					for (unsigned int i = 0; i < actorDB->size(); i++){
						//actor already in DB
						if (actorDB->at(i)->getName() == name_caps){
							contains_actor = true;
							//finding movie
							for (map<string, Movie*>::iterator movieDB_it = movieDB->begin(); movieDB_it != movieDB->end(); ++movieDB_it){
     							//adding actor to movie
     							if (movieDB_it->first == movie_name_caps){
     								(*movieDB_it).second->addActor(actorDB->at(i));
     							}
	     					}//end of it for
	     					break;
						}//end of if actor already added
					}//end of for
					if (!contains_actor){
						temp_actor = new Actor(name_caps, actor_index);
						actor_index++;
						actorDB->push_back(temp_actor);
						for (map<string, Movie*>::iterator movieDB_it = movieDB->begin(); movieDB_it != movieDB->end(); ++movieDB_it){
     						//adding actor to movie
     						if (movieDB_it->first == movie_name_caps){
     							movieDB_it->second->addActor(temp_actor);
     							break;
     						}
	     				}//end of it for
					}//end of if actor not added yet
				}//end of if else ACTOR:
				file >> input;
				if (input == "END"){
					stop = true;
				}
			}//end of while	
		}//end of if
	}//end of while
}//end of readUserFile

void NFDB::saveUserInfo(){
	string input, file_name;
	locale loc;
	file_name = "savefile.txt";
	ofstream myfile;
  	myfile.open (file_name.c_str());
  	map<string, User*>::iterator itA = userDB->begin();
  	User *user = new User();
  	for (unsigned int i = 0; i < userDB->size(); i++){

  		cerr << "saving user info for: " << user->getID() << endl;
  		user = (*itA).second;
  		//=========================user
 		myfile << "BEGIN ";
 		myfile << user->getID();
 		myfile << "\n";
 		myfile << "NAME: ";
 		myfile << user->getName();
 		myfile << "\n";
 		//========================if movie checked out
 		if (user->renting()){
 			myfile << "MOVIE: ";
 			myfile << user->currentMovie()->getTitle();
 			myfile << "\n";
 		}
 		else{
 			myfile << "MOVIE: ";
 			myfile << "No movie checked out\n";
 		}
 		//======================= movies in queue
 		myfile << "BEGIN QUEUE\n";
 		for(unsigned int i = 0; i < (user->movieQueue())->size(); i++){
 			myfile << user->movieQueue()->front()->getTitle();
 			myfile << "\n";
 			user->movieQueue()->pop();
 		
 		}//end of if	
 		myfile << "END QUEUE\n";
 		//====================== ratings of movies
 		myfile << "BEGIN RATINGS\n";
 		for (unsigned int i = 0; i < user->getWatchedMovies()->size(); i++){
 			myfile << user->getWatchedMovies()->at(i)->getRating();
 			myfile << " ";
 			myfile << user->getWatchedMovies()->at(i)->getTitle();
 			myfile << "\n";
 		}//end of for
 		myfile << "END RATINGS\n";
 		myfile << "END\n";
 		++itA;
 	}//end of iterator	
  	myfile.close();
}//end of saving to file

double NFDB::basicSimilarity(User* userA, User *userB){
	vector<Movie*> *vecA = userA->getWatchedMovies();
	vector<Movie*> *vecB = userB->getWatchedMovies();
	int ratingA = 0; int ratingB = 0;
	double sim = 0;
	double total_sim = 0;
	int matchCount = 0;
	bool found_match = false;

	for (unsigned int i = 0; i < vecA->size(); i++){
		for (unsigned int j = 0; j < vecB->size(); j++){
			if (vecA->at(i)->getTitle() == vecB->at(j)->getTitle()){
				ratingA = vecA->at(i)->getRating();
				ratingB = vecB->at(j)->getRating();
				sim = abs(ratingA-ratingB);
				sim = sim/4;
				total_sim += sim;
				matchCount++;
				found_match = true;
			}//end of if match
		}//end of inner for	
	}//end of for

	if (total_sim == 0 && found_match){
		return 0;
	}
	else if(total_sim == 0 && !found_match){
		return 1;
	}
	sim = total_sim/matchCount;
	return sim;
}//end of basic similarity 

void NFDB::updateBasicSim(){
	vector<pair<User*, double> > *temp_vec = new vector<pair<User*, double> >();
	double cost_from_start = 0;
	for (map<string, User*>::iterator map_itA = userDB->begin(); map_itA != userDB->end(); ++map_itA){
		for (map<string, User*>::iterator map_itB = userDB->begin(); map_itB != userDB->end(); ++map_itB){
			if ((*map_itA).second->getID() != (*map_itB).second->getID()){
				cost_from_start = basicSimilarity((*map_itA).second, (*map_itB).second);
				temp_vec->push_back(make_pair((*map_itB).second, cost_from_start));
			}
		}//end of inner for
		(*map_itA).second->updateLinks(temp_vec);
	}//end of outer for		
}//end of basicsim

vector<pair<User*, double> >* NFDB::findRS(User *userA){
	vector<pair<User*, double> > *refinedSim = new vector<pair<User*, double> >();
	vector<string> *visited = new vector<string>();
	queue<pair<User*, double>* > *my_queue = new queue<pair<User*, double>* >();
	
	User *temp_user = new User();
	User *start_user = new User();
	int row_size = userDB->size();
	int col_size = row_size;
	int col_index;
	int row_index;
	double temp_double = 0, cost_from_start = 0;
	double **edgeData;
	//double sim_total = 0;
	//===================== 2D double array
	edgeData = new double*[row_size];
	for (int i = 0; i < row_size; i++){
		edgeData[i] = new double[col_size];
		for (int j = 0; j < col_size; j++){
			edgeData[i][j] = 1;
		}//end of inner for
	}//end of outer for
	
	pair<User*, double> *q_pair;
	vector<pair<User*, double> >* temp_links;

	q_pair = new pair<User*, double>(userA, 0.0);
	my_queue->push(q_pair);
	start_user = temp_user = my_queue->front()->first;
	col_index = getUserIndex(start_user);
	visited->push_back(temp_user->getID());
	//=====================performing algorithm
	while(!my_queue->empty()){
		start_user = my_queue->front()->first;
		cost_from_start = my_queue->front()->second;
		my_queue->pop();
		temp_links = start_user->getLinks();
		for (unsigned int i = 0; i < temp_links->size(); i++){
			temp_user = temp_links->at(i).first;
			if (!contains(visited, temp_user)){
				row_index = getUserIndex(temp_user);
				//get cost from start to at(i)
				temp_double = (temp_links->at(i).second + cost_from_start);
				//if cost is smaller
				if (temp_double < edgeData[row_index][col_index]){
					edgeData[row_index][col_index] = temp_double;
				}//end of if cost is smaller than in graph
				q_pair = new pair<User*, double>(temp_user, temp_double);
				my_queue->push(q_pair);
				visited->push_back(temp_user->getID());
			}//end of if contains in visited	
		}//end of for
	}//end of while
	string temp_login;
	for (int i = 0; i < row_size; i++){
		temp_login = visited->at(i);
		q_pair = new pair<User*, double>(getUser(temp_login), edgeData[i][col_index]);
		refinedSim->push_back(*q_pair);
	}
	return refinedSim;
}//end of findRS

int NFDB::getUserIndex(User *user){
	int n = 0;
	for (map<string, User*>::iterator map_itA = userDB->begin(); map_itA != userDB->end(); ++map_itA){
		if ((*map_itA).second->getID() == user->getID()){
			return n;
		}
		n++;
	}//end of for
	return -1;	
}//end of getIndex

bool NFDB::contains(vector<string> *visited, User *user){
	for (unsigned int i = 0; i < visited->size(); i++){
		if (user->getID() == visited->at(i)){
			return true;
		}
	}//end of for
	return false;
}//end of contains

pair<int, Movie*> NFDB::recommendation(User* user){
	vector<Movie*>* watchedMovies = user->getWatchedMovies();
	vector<Movie*> *moviesNotWatched = new vector<Movie*>();
	vector<pair<User*, double> > *usersWhoRated;
	Movie *temp_movie = new Movie();
	vector<Movie*> *recommend_pool = new vector<Movie*>();
	srand (time(NULL));
	double interestingness = 0.0;
	double temp_interestingness = 0.0;
	double temp_rating = 0.0;
	double temp_sim = 0.0;
	double R_of_M = 0.0;
	double W = 0.0;
	bool watched = false;
	//=====================building vector of movies not watched by user
	for (map<string, Movie*>::iterator MDB_it = movieDB->begin(); MDB_it != movieDB->end(); ++MDB_it){
     	for (unsigned int i = 0; i < watchedMovies->size(); i++){
     		if (watchedMovies->at(i)->getTitle() == (*MDB_it).second->getTitle()){
     			watched = true;
     		}	
     	}//end of inner for through watched movies
     	if (!watched){
     		moviesNotWatched->push_back((*MDB_it).second);
     	}//end of if not watched
     	watched = false;
	}//end of for
	//===================== finding interestingness for all movies
	for (unsigned int i = 0; i < moviesNotWatched->size(); i++){
		temp_movie = moviesNotWatched->at(i);
		usersWhoRated = temp_movie->getUsersWhoRated();
		for (unsigned int i = 0; i < usersWhoRated->size(); i++){
			temp_rating = usersWhoRated->at(i).first->getRatingOfWatched(temp_movie);
			temp_sim = user->getSimOfUser(usersWhoRated->at(i).first);
			R_of_M += (1-temp_sim)*(temp_rating);
			W += 1-temp_sim;
		}//end of movies who have rated movie M
		temp_interestingness = R_of_M/W;
		if (R_of_M == 0 || W == 0){
			temp_interestingness = 0;
		}
		if(interestingness < temp_interestingness){
			interestingness = temp_interestingness;
			recommend_pool->push_back(temp_movie);
		}//end of if	
	}//end of for all movies not watched
	int n;
	pair<int, Movie*> r_pair;
	temp_movie = new Movie();
	if (recommend_pool->size() == 0){	
		r_pair = make_pair(0, temp_movie);
		return r_pair;	
	}
	n = rand()%(recommend_pool->size());
	temp_movie = recommend_pool->at(n);
	r_pair = make_pair(1, temp_movie);
	return (r_pair);
}//end of recommendation

void NFDB::buildRelatedActors(){
	vector<Actor*>* ActorsInMovie;
	vector<pair<Actor*, Movie*>* > *relatedActor;
	pair<Actor*, Movie*> *temp_pair;
	//Movie *movie;
	bool contains = false;
	//===================grabs movie
	for (map<string, Movie*>::iterator MDB_it = movieDB->begin(); MDB_it != movieDB->end(); ++MDB_it){
     	ActorsInMovie = (*MDB_it).second->getActors();
     	//=========================grabs all the Actor in the movie
     	for (unsigned i = 0; i < ActorsInMovie->size(); i++){
     		ActorsInMovie->at(i)->addMovieActedIn((*MDB_it).second);
     		relatedActor = ActorsInMovie->at(i)->getRelatedActors();
     		//======================grabs all the related Actor in Actor class
     		contains = false;
     		for (unsigned int j = 0; j < relatedActor->size(); j++){
     			//=================check if already in related actor vecvtor
     			if (relatedActor->at(j)->first->getName() == ActorsInMovie->at(i)->getName()){
     				contains = true;
     			}
     		}//end of 3rd for
     		if (!contains){
     			for (unsigned int h = 0; h < ActorsInMovie->size(); h++){
     				if (ActorsInMovie->at(i)->getName() != ActorsInMovie->at(h)->getName()){
     					temp_pair = new pair<Actor*, Movie*>(make_pair(ActorsInMovie->at(h), (*MDB_it).second));
     					ActorsInMovie->at(i)->addRelatedActor(temp_pair);
     				}	
     			}//end of for
     		}//end of if actor not in related Actor
     	}//end of 2nd for
     	
    }//end of outer for

}//end of buil related Actor 

/*
I am sorry to the TA who has to look at this.... :c
*/


int NFDB::findBaconLength(Actor *actorA, Actor *actorB){
	//queue<pair<Actor*, int> > *my_queue = new queue<pair<Actor*, int> >();
	//=======================pairs to add to queue
	queue<pair<Actor*, int>* >* my_Xqueue = new queue<pair<Actor*, int>* >();
	queue<pair<vector<Actor*>*, vector<Movie*>* >* >* my_Yqueue = new queue<pair<vector<Actor*>*, vector<Movie*>* >* >();
	//==================next actor and total edge cost
	pair<Actor*, int> *smallPairX;
	pair<Actor*, int> *temp_smallPairX;
	//===================chain history of Actor and movies
	pair<vector<Actor*>*, vector<Movie*>* > *smallPairY;
	pair<vector<Actor*>*, vector<Movie*>* > *temp_smallPairY;
	//==================chain of Actor from A
	vector<Actor*> *actorChainHistory = new vector<Actor*>();
	vector<Actor*> *temp_actorChainHistory;
	//==================chain of movies between X-Y
	vector<Movie*> *movieChainHistory = new vector<Movie*>();
	vector<Movie*> *temp_movieChainHistory;

	vector<pair<Actor*, Movie*>* > *relatedActors = new vector<pair<Actor*, Movie*>* >();
	
	bool *visited = new bool[actorDB->size()];
	for (unsigned int i = 0; i < actorDB->size(); i++){
		visited[i] = false;
	}
	Actor *target = actorB;
	Actor *temp_actor;
	int chains_from_A = 0;

	smallPairX = new pair<Actor*, int>(make_pair(actorA, 0));
	actorChainHistory->push_back(actorA);
	smallPairY = new pair<vector<Actor*>*, vector<Movie*>* >(make_pair(actorChainHistory, movieChainHistory));

	visited[actorA->getIndex()] = true;
	my_Xqueue->push(smallPairX);
	my_Yqueue->push(smallPairY);
	while(!my_Xqueue->empty()){

		temp_smallPairX = my_Xqueue->front();
		my_Xqueue->pop();
		temp_smallPairY = my_Yqueue->front();
		my_Yqueue->pop();
		
		temp_actor = temp_smallPairX->first;
		chains_from_A = temp_smallPairX->second;
		chains_from_A++;
		relatedActors = temp_actor->getRelatedActors();

		// vector<pair<Actor*, Movie*>* >* getRelatedActors();
		for (unsigned int i = 0; i < relatedActors->size(); i++){
			temp_actorChainHistory = temp_smallPairY->first;
			temp_movieChainHistory = temp_smallPairY->second;

			if (!visited[relatedActors->at(i)->first->getIndex()]){
				visited[relatedActors->at(i)->first->getIndex()] = true;
				//=====================push back actor-movie relationship
				temp_actorChainHistory->push_back(relatedActors->at(i)->first);
				temp_movieChainHistory->push_back(relatedActors->at(i)->second);
				
				if (relatedActors->at(i)->first->getName() == target->getName()){
					break;
				}
				//======================create actor-cost
				temp_smallPairX = new pair<Actor*, int>(make_pair(relatedActors->at(i)->first, chains_from_A)); 
				temp_smallPairY = new pair<vector<Actor*>*, vector<Movie*>* >(make_pair(temp_actorChainHistory, temp_movieChainHistory));
				my_Xqueue->push(temp_smallPairX);
				my_Yqueue->push(temp_smallPairY);

				temp_actorChainHistory->pop_back();
				temp_movieChainHistory->pop_back();
			}//end of if not visited
		}//end of for
	}//end of while queue isnt empty
	temp_actorChainHistory = temp_smallPairY->first;
	temp_movieChainHistory = temp_smallPairY->second;

	return chains_from_A;
}//end of find the bacon
