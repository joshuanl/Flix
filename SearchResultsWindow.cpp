#include "lib/SearchResultsWindow.h"
#include "lib/MainMenuWindow.h"
#include "lib/NFDB.h"
#include "lib/User.h"
#include <set>
#include <queue>
#include <map>
#include <locale>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QLabel>
#include <QTextEdit>
#include <QObject>
#include <QAction>
#include <QApplication>

using namespace std;

SearchResultsWindow::~SearchResultsWindow(){}

SearchResultsWindow::SearchResultsWindow(NFDB *net_flixDB, string login_id, MainMenuWindow *MMW){
	window = new QWidget();
	this->login_id = login_id;
	netflixDB = net_flixDB;
	user = (netflixDB->getUser(login_id));
	this->MMW = MMW;
	search_counter = 0;
	input_kw = "";
	searchActorDB = false;

	nextMovieButton = new QPushButton("Next Movie");
	connect(nextMovieButton, SIGNAL(clicked()), this, SLOT(nextMovieButtonClicked()));

	QPushButton *addToQueueButton = new QPushButton("Add movie to Queue");
	connect(addToQueueButton, SIGNAL(clicked()), this, SLOT(addToQueueButtonClicked()));

	QPushButton *returnToMenuButton = new QPushButton("Back");
	connect(returnToMenuButton, SIGNAL(clicked()), this, SLOT(returnToMenuButtonClicked()));


	QLabel *winLabel = new QLabel(tr("Search Results"));
	QLabel *movieInfoLabel = new QLabel(tr("Movie Info: "));
	kw_text = new QTextEdit("");
	kw_text->setReadOnly(true);

	QVBoxLayout *vboxLayout = new QVBoxLayout;
	QHBoxLayout *hboxLayout = new QHBoxLayout;

	vboxLayout->addWidget(winLabel);
	vboxLayout->addWidget(movieInfoLabel);
	vboxLayout->addWidget(kw_text);
	hboxLayout->addWidget(nextMovieButton);
	hboxLayout->addWidget(addToQueueButton);
	hboxLayout->addWidget(returnToMenuButton);
	vboxLayout->addLayout(hboxLayout);

	window->setLayout(vboxLayout);

}//end of costructor


void SearchResultsWindow::nextMovieButtonClicked(){
	std::locale loc;
	search_counter++;
	string temp_str = "";


	if (!searchActorDB){
		set<Movie*>::iterator set_it = copy_set->begin();
		for (int i = 0; i < search_counter; i++){
			++set_it;
			if (set_it == copy_set->end()){
				nextMovieButton->setEnabled(false);
				return;
			}
		}//end of for	
		temp_str = (*set_it)->getTitle();
    	target_movie = (*set_it);
   		kw_text->append(tr(temp_str.c_str()));
	}//end of if not searching through actorDB
	else{
		string input_actor = "";
		vector<Movie*>* moviesActedIn;
		Movie *movie;

		for (string::size_type i=0; i<input_kw.length(); i++)
	    	input_actor += toupper(input_kw[i],loc);
		moviesActedIn = netflixDB->getActor(input_actor)->getMoviesActedIn();
		if ((unsigned)search_counter > moviesActedIn->size()-1){
			nextMovieButton->setEnabled(false);
			return;
		}//end of if out of bounds

		movie = netflixDB->getMovie(moviesActedIn->at(search_counter)->getTitle());
		kw_text->append(tr("\n"));
		kw_text->append(tr(moviesActedIn->at(search_counter)->getTitle().c_str()));
     	set<string> setA = movie->getAllKeywords();
     	set<string>::iterator itA = setA.begin();
     	kw_text->append(tr("TAGS"));
     	for(itA = setA.begin(); itA != setA.end(); ++itA){			//getting all keywords attached
     		temp_str = "";
     		temp_str = "   " + *itA + "";
     		kw_text->append(tr(temp_str.c_str()));
     	}//end of for	
    }//end of else
}//end of return movie

void SearchResultsWindow::addToQueueButtonClicked(){
	netflixDB->getUser(login_id)->movieQueue()->push(target_movie);
	kw_text->append("Added movie to queue!!\n");
}//end of add to queue

void SearchResultsWindow::returnToMenuButtonClicked(){
	search_counter = 0;
	nextMovieButton->setEnabled(true);
	window->close();
	MMW = new MainMenuWindow(netflixDB, login_id);
	MMW->setVisible();

}//end of search results

void SearchResultsWindow::setVisible(){
	search_counter = 0;
	window->show();

}//end of set visibile

void SearchResultsWindow::searchTitle(string input_text){
	string input_title = "";
	string temp_str;
	for (string::size_type i=0; i<input_text.length(); ++i)		//changes all search text to uppercase
     	input_title += toupper(input_text[i]);				//able to compared search to title
     if(netflixDB->movieExists(input_title)){
     	temp_str = "  " + netflixDB->getMovie(input_title)->getTitle();
     	target_movie = netflixDB->getMovie(input_title);
     	kw_text->setText(tr("MOVIE"));
     	kw_text->append(tr(temp_str.c_str()));
     	kw_text->append("\n");
     	set<string> setA = (netflixDB->getMovie(input_title))->getAllKeywords();
     	set<string>::iterator itA = setA.begin();
     	kw_text->append(tr("TAGS"));
     	for(itA = setA.begin(); itA != setA.end(); ++itA){			//getting all keywords attached
     		temp_str = "";
     		temp_str = "   " + *itA + "";
     		kw_text->append(tr(temp_str.c_str()));
     	}//end of for	
     }//end of if movie is in movieDB 							 	
     else{ 						
     	temp_str = ">> Error:\n>> Movie: " + input_title + " not in database";								
     	kw_text->setText(tr(temp_str.c_str()));
     }
}//end of search title

void SearchResultsWindow::searchKeyword(string input_text){
	input_kw = input_text;
	string temp_str, int_str;
	string input_title = "";
	stringstream ss;
	search_counter = 0;
	for (string::size_type i=0; i<input_text.length(); ++i)			//changes to uppercase to get around case sensitivity
   	 	input_title += toupper(input_text[i]);

    if(netflixDB->KWExists(input_title)){
		copy_set = netflixDB->getKWSet(input_title);
     	set<Movie*>::iterator set_it = copy_set->begin();		

    	ss << copy_set->size();
    	ss >> int_str;
     	temp_str = "Found " + int_str + " result(s) \n";
     	kw_text->setText(tr(temp_str.c_str()));	
     	temp_str = (*set_it)->getTitle();
     	target_movie = (*set_it);
     	kw_text->append(tr(temp_str.c_str()));
	}//end if there are results
	else{
		temp_str = "Found 0 result(s) \n";
     	kw_text->setText(tr(temp_str.c_str()));
     	nextMovieButton->setEnabled(false);		
	}	     		
}//end of search by KW

void SearchResultsWindow::searchActor(string input_text){
	string input_actor = "";
	string temp_str = "";
	searchActorDB = true;
	std::locale loc;

	stringstream ss;
	vector<Movie*>* moviesActedIn;

	for (string::size_type i=0; i<input_text.length(); ++i)
	    input_actor += toupper(input_text[i],loc);
	input_kw = input_actor;

	if(netflixDB->actorExists(input_actor)){
     	temp_str = "  " + input_actor;
     	moviesActedIn = netflixDB->getActor(input_actor)->getMoviesActedIn();
     	kw_text->setText(tr("ACTOR:"));
     	kw_text->append(tr(temp_str.c_str()));
     	kw_text->append("\n");

     	ss << moviesActedIn->size();
     	ss >> temp_str;
     	temp_str = "Found " + temp_str + " result(s) \n";
     	kw_text->setText(tr(temp_str.c_str()));
     	kw_text->append(tr(moviesActedIn->at(0)->getTitle().c_str()));
     	set<string> setA = (netflixDB->getMovie(moviesActedIn->at(0)->getTitle()))->getAllKeywords();
     	set<string>::iterator itA = setA.begin();
     	kw_text->append(tr("TAGS"));
     	for(itA = setA.begin(); itA != setA.end(); ++itA){			//getting all keywords attached
     		temp_str = "";
     		temp_str = "   " + *itA + "";
     		kw_text->append(tr(temp_str.c_str()));
     	}//end of for	
     }//end of if movie is in movieDB 							 	
     else{ 						
     	temp_str = ">> Error:\n>> Actor: " + input_actor + " not in database";								
     	kw_text->setText(tr(temp_str.c_str()));
     	nextMovieButton->setEnabled(false);
     }

}
