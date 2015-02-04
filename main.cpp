#include <QApplication>
#include "Movie.cpp"
#include "User.cpp"
#include "NFDB.cpp"
#include "OpenWindow.cpp"
//#include "lib/EmptyQueueExceptionImp.h"

#include <iostream>
#include <string>
#include <fstream>
#include <locale>
#include <set>
#include <map>

using namespace std;

int main(int argc, char *argv[]){
	map<string, User*> *userDB = new map<string, User*>(); 		    		//userID, username
	map<string, Movie*> *movieDB = new map<string, Movie*>;					//movie title, movie					
	map<string, set<Movie*>* > *keywordDB = new map<string, set<Movie*>* >; 	//movie title, set of movies to that keyword

	string u_filename, m_filename, data_file;
	data_file = argv[1];
	ifstream file(argv[1]);
	file >> m_filename;
	file >> u_filename;

	NFDB *netflixDB= new NFDB(userDB, movieDB, keywordDB);
	netflixDB->readMovieFile(m_filename);
	netflixDB->readUserFile(u_filename);

	QApplication app(argc, argv); 
	OpenWindow openWin(netflixDB);				//run UI and pass data

	return app.exec();
	//return 0;
}//end of main
