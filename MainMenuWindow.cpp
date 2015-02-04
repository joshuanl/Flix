#include "lib/MainMenuWindow.h"
#include "lib/OpenWindow.h"
#include "lib/SearchResultsWindow.h"
#include "lib/RateMovieWindow.h"
#include "lib/RecommendMovieWindow.h"
#include "lib/FindBaconWindow.h"
#include "lib/NFDB.h"
#include <string>
#include <queue>
#include <sstream>

#include <QPushButton>  
#include <QHBoxLayout>
#include <QVBoxLayout>  
#include <QLineEdit>  
#include <QLabel>
#include <QTextEdit>  
#include <QObject>
#include <QAction>
#include <QApplication>
#include <QString>
#include <iostream>

using namespace std;  


MainMenuWindow::~MainMenuWindow(){}

MainMenuWindow::MainMenuWindow(NFDB *net_flixDB, string login_id){
	window = new QWidget();
	this->login_id = login_id;
	stringstream ss;
	netflixDB = net_flixDB;
	SRW = new SearchResultsWindow(netflixDB, login_id, this);
	string temp_str = "";

	cerr << "reached inside MainMenuWindow " << endl;
	returnMovieButton = new QPushButton("Return Movie");
	connect(returnMovieButton, SIGNAL(clicked()), this, SLOT(returnMovieButtonClicked()));

	rateMoviesButton = new QPushButton("Rate Movies");
	connect(rateMoviesButton, SIGNAL(clicked()), this, SLOT(rateMoviesButtonClicked())); 

	rentMovieButton = new QPushButton("Rent Movie");
	connect(rentMovieButton, SIGNAL(clicked()), this, SLOT(rentMovieButtonClicked()));
	
	deleteMovieButton = new QPushButton("Delete movie from queue");
	connect(deleteMovieButton, SIGNAL(clicked()), this, SLOT(deleteButtonClicked()));
	
	moveToBackButton = new QPushButton("Move movie to back of queue");
	connect(moveToBackButton, SIGNAL(clicked()), this, SLOT(moveToBackButtonClicked()));
	
	QPushButton *searchTitleButton = new QPushButton("Search by Title");
	connect(searchTitleButton, SIGNAL(clicked()), this, SLOT(searchTitleButtonClicked()));
	
	QPushButton *searchKeywordButton = new QPushButton("Search by Keyword");
	connect(searchKeywordButton, SIGNAL(clicked()), this, SLOT(searchKeywordButtonClicked()));
	
	QPushButton *logoutButton = new QPushButton("Log Out");
	connect(logoutButton, SIGNAL(clicked()), this, SLOT(logoutButtonClicked()));

	findBaconButton = new QPushButton("FIND THE BACON");
	connect(findBaconButton, SIGNAL(clicked()), this, SLOT(findBaconButtonClicked()));

	searchByActorButton = new QPushButton("Search by Actor");
	connect(searchByActorButton, SIGNAL(clicked()), this, SLOT(searchByActorButtonClicked()));

	message = new QLabel("");
	movieratingLabel = new QLabel("");
	//QLabel *spacer0 = new QLabel("");				//endl;
	QLabel *spacer2 = new QLabel("");
	QLabel *winLabel = new QLabel(tr("CSCI 104-Flix"));
	winLabel->setAlignment(Qt::AlignCenter);
	QLabel *menuLabel = new QLabel(tr("------------------------------------------------Main Menu------------------------------------------------"));
	menuLabel->setAlignment(Qt::AlignCenter);

	rentMovieButton->setEnabled(false);
	returnMovieButton->setEnabled(false);
	temp_str = "No Movie Currentlty Checked Out";
	if ((netflixDB->getUser(login_id))->renting()){
		temp_str = (netflixDB->getUser(login_id))->currentMovie()->getTitle();
		rentMovieButton->setEnabled(true);
		returnMovieButton->setEnabled(true);
	}
	temp_str = "Currentlty Checked Out: " + temp_str;
	currentMovieLabel = new QLabel(tr(temp_str.c_str()));
	string movierating_str = "";
	//==================rating
	if ((netflixDB->getUser(login_id))->renting()){
		ss << netflixDB->getUser(login_id)->currentMovie()->getRating();
		ss >> movierating_str;
	}
	else{
		movierating_str = "0";
	}
	movierating_str = "Movie Rating: " + movierating_str;
	QString temp_qstr = QString::fromStdString(movierating_str);
	movieratingLabel->setAlignment(Qt::AlignCenter);
	movieratingLabel->setText(temp_qstr);	

	QLabel *queueMenuLabel = new QLabel(tr("------------------------------------------Movie Queue Menu------------------------------------------"));
	queueMenuLabel->setAlignment(Qt::AlignCenter);
	temp_str = "";
	//(netflixDB->getUser(login_id))->movieQueue()->reset();
	Movie *temp;
	deleteMovieButton->setEnabled(false);
	moveToBackButton->setEnabled(false);
	if ((netflixDB->getUser(login_id))->movieQueue()->size() > 0){
		temp = (((netflixDB->getUser(login_id))->movieQueue()->front()));			
		temp_str = "First movie in Queue: " + temp->getTitle();
		deleteMovieButton->setEnabled(true);
		moveToBackButton->setEnabled(true);
		rentMovieButton->setEnabled(true);
	}
	else{
		temp_str = "First movie in Queue: EMPTY";
	}	
	currentQueueLabel = new QLabel(tr(temp_str.c_str()));
	QLabel *searchFieldLabel = new QLabel(tr("Search"));

	textfield = new QLineEdit();

	QVBoxLayout *vboxLayout1 = new QVBoxLayout;
	QHBoxLayout *hboxLayout1 = new QHBoxLayout;
	QHBoxLayout *hboxLayout2 = new QHBoxLayout;
	QHBoxLayout *hboxLayout3 = new QHBoxLayout;

	vboxLayout1->addWidget(winLabel);
	vboxLayout1->addWidget(menuLabel);
	vboxLayout1->addWidget(currentMovieLabel);
	//vboxLayout1->addWidget(spacer0);
	vboxLayout1->addWidget(movieratingLabel);	
	vboxLayout1->addWidget(message);
	vboxLayout1->addWidget(returnMovieButton);
	vboxLayout1->addWidget(rateMoviesButton);
	vboxLayout1->addWidget(queueMenuLabel);
	vboxLayout1->addWidget(currentQueueLabel);
	vboxLayout1->addWidget(spacer2);
	hboxLayout1->addWidget(rentMovieButton);
	hboxLayout1->addWidget(deleteMovieButton);
	hboxLayout1->addWidget(moveToBackButton);
	vboxLayout1->addLayout(hboxLayout1);
	hboxLayout2->addWidget(searchFieldLabel);
	hboxLayout2->addWidget(textfield);
	vboxLayout1->addLayout(hboxLayout2);
	hboxLayout3->addWidget(searchTitleButton);
	hboxLayout3->addWidget(searchKeywordButton);
	hboxLayout3->addWidget(searchByActorButton);
	vboxLayout1->addLayout(hboxLayout3);
	vboxLayout1->addWidget(findBaconButton);
	vboxLayout1->addWidget(logoutButton);

	window->setLayout(vboxLayout1);

	if ((netflixDB->getUser(login_id))->renting()){
		rentMovieButton->setEnabled(false);
	}

	cerr << "before updateBasicSim " << endl;
	netflixDB->updateBasicSim();

	vector<pair<User*, double> > *refined_sim_vec;
	cerr << "before refined_sim_vec " << endl;	
	for (map<string, User*>::iterator map_itA = netflixDB->getUserDB()->begin(); map_itA != netflixDB->getUserDB()->end(); ++map_itA){
		refined_sim_vec = netflixDB->findRS((*map_itA).second);
		(netflixDB->getUser(login_id))->updateLinks(refined_sim_vec);
		for (unsigned int i = 0; i < refined_sim_vec->size(); i++){
		}//end of for
	}//end of for	
}//end of constructor

void MainMenuWindow::updateRecommended(Movie *movie){
	netflixDB->getUser(login_id)->movieQueue()->push(movie);
}//end of update recommended

void MainMenuWindow::openRecommend(){

	RecMW = new RecommendMovieWindow(netflixDB, login_id, this);
	RecMW->setVisible();

}

void MainMenuWindow::returnMovieButtonClicked(){

	// if they dont rate the movie then dont add to watchedMovies
	// return movie inside rateMovies instead

	vector<Movie*> *watchedMovies = (netflixDB->getUser(login_id))->getWatchedMovies();
	bool alreadyWatched = false;
	for (unsigned int i = 0; i < watchedMovies->size(); i++){
		if (watchedMovies->at(i)->getTitle() == (netflixDB->getUser(login_id))->currentMovie()->getTitle())
		{
			alreadyWatched = true;
			break;
		}
	}
	if (!alreadyWatched){
		(netflixDB->getUser(login_id))->addWatchedMovie((netflixDB->getUser(login_id))->currentMovie());
	}
	(netflixDB->getUser(login_id))->returnMovie();
	currentMovieLabel->setText("Currentlty Checked Out:   No Movie Currentlty Checked Out");
	message->setText("");
	message->setAlignment(Qt::AlignCenter);
	rentMovieButton->setEnabled(true);
	returnMovieButton->setEnabled(false);
	movieratingLabel->setText("Movie Rating: 0");	

	RMW = new RateMovieWindow(netflixDB, login_id, this);
	RMW->setVisible();
	window->close();

}//end of return button

void MainMenuWindow::rentMovieButtonClicked(){
		stringstream ss;
		Movie *temp = (((netflixDB->getUser(login_id))->movieQueue()->front()));
		string rating_str;
		string temp_str = "Currentlty Checked Out: " + temp->getTitle();
		message->setText("");
		message->setAlignment(Qt::AlignCenter);
		currentMovieLabel->setText(temp_str.c_str());
		(netflixDB->getUser(login_id))->rentMovie(temp);
		(netflixDB->getUser(login_id))->movieQueue()->pop();
		if ((netflixDB->getUser(login_id))->movieQueue()->size() > 0){
			temp = (((netflixDB->getUser(login_id))->movieQueue()->front()));			
			temp_str = "First movie in Queue: " + temp->getTitle();
		}
		else{
			temp_str = "First movie in Queue: EMPTY";
			deleteMovieButton->setEnabled(false);
		}	
		ss << (netflixDB->getUser(login_id))->currentMovie()->getRating();
		ss >> rating_str;
		rating_str = "Movie Rating: " + rating_str;
		movieratingLabel->setText(rating_str.c_str());
		currentQueueLabel->setText(temp_str.c_str());
		rentMovieButton->setEnabled(false);
		returnMovieButton->setEnabled(true);
}//end of rent button

void MainMenuWindow::deleteButtonClicked(){
	if ((netflixDB->getUser(login_id))->movieQueue()->size() == 1){
		(netflixDB->getUser(login_id))->movieQueue()->pop();
		currentQueueLabel->setText("First movie in Queue: (EMPTY QUEUE)");
		deleteMovieButton->setEnabled(false);
		moveToBackButton->setEnabled(false);
		return;
	}
	string temp_str;
	(netflixDB->getUser(login_id))->movieQueue()->pop();
	Movie *temp = (((netflixDB->getUser(login_id))->movieQueue()->front()));
	temp_str = "First movie in Queue: " + temp->getTitle();
	currentQueueLabel->setText(temp_str.c_str());
	

}//end of delete button

void MainMenuWindow::moveToBackButtonClicked(){
	string temp_str;
	Movie *temp = (((netflixDB->getUser(login_id))->movieQueue()->front()));
	(netflixDB->getUser(login_id))->movieQueue()->push(temp);
	(netflixDB->getUser(login_id))->movieQueue()->pop();
	temp = (((netflixDB->getUser(login_id))->movieQueue()->front()));
	temp_str = "First movie in Queue: " + temp->getTitle();
	currentQueueLabel->setText(temp_str.c_str());

}//end of move to back button

void MainMenuWindow::searchTitleButtonClicked(){
	SRW->setWindowFlags(Qt::Window);
	SRW->searchTitle(textfield->text().toStdString());
	SRW->setVisible();
}//end of search title button

void MainMenuWindow::searchKeywordButtonClicked(){
	SRW->setWindowFlags(Qt::Window);
	SRW->searchKeyword(textfield->text().toStdString());
	SRW->setVisible();
	window->close();

	//window->hide();
}//end of search keyword button

void MainMenuWindow::searchByActorButtonClicked(){
	SRW->setWindowFlags(Qt::Window);
	SRW->searchActor(textfield->text().toStdString());
	SRW->setVisible();
	window->close();	
}//end of search by actor button

void MainMenuWindow::findBaconButtonClicked(){
	FBW = new FindBaconWindow(netflixDB, login_id);
	FBW->setVisible();
}//end of find the bacon button

void MainMenuWindow::setVisible(){
	window->show();
}//end of set visible


void MainMenuWindow::logoutButtonClicked(){
	netflixDB->saveUserInfo();
	window->close();
	OW = new OpenWindow(netflixDB);
}//end of logout

void MainMenuWindow::rateMoviesButtonClicked(){
	RMW = new RateMovieWindow(netflixDB, login_id, this);
	RMW->setVisible();
	window->close();
}//end of ratemovies button

void MainMenuWindow::sendOW(OpenWindow *OW){
	this->OW = OW;
}//end of sendOW

