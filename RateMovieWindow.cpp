#include "lib/RateMovieWindow.h"
#include "lib/MainMenuWindow.h"
#include "lib/NFDB.h"
#include "lib/Movie.h"
#include "lib/User.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include <QPushButton>  
#include <QHBoxLayout>
#include <QMessageBox>
#include <QVBoxLayout>  
#include <QLineEdit>  
#include <QLabel>
#include <QTextEdit>  
#include <QObject>
#include <QAction>
#include <QApplication>
#include <QString>
#include <QSpinBox>
#include <QComboBox>

using namespace std;

RateMovieWindow::RateMovieWindow(){}
RateMovieWindow::~RateMovieWindow(){}

RateMovieWindow::RateMovieWindow(NFDB *net_flixDB, string login_id, MainMenuWindow *MMW){
	window = new QWidget();
	this->MMW = MMW;
	netflixDB = net_flixDB;
	this->login_id = login_id;
	user = netflixDB->getUser(login_id);
	vector<Movie*> *watchedMovies = user->getWatchedMovies();
	string temp_str, movie_title;
	stringstream ss;
	int rating = 0;

	rateButton1 = new QPushButton("RATE IT!");
	connect(rateButton1, SIGNAL(clicked()), this, SLOT(rateButton1Clicked()));
	rateButton2 = new QPushButton("RATE IT!");
	connect(rateButton2, SIGNAL(clicked()), this, SLOT(rateButton2Clicked()));
	exitWindowButton = new QPushButton("Close Window");
	connect(exitWindowButton, SIGNAL(clicked()), this, SLOT(exitWindowButtonClicked()));

	windowTitleLabel = new QLabel("Ratings Window");
	windowTitleLabel->setAlignment(Qt::AlignCenter);
	message1Label = new QLabel("Rate Current Movie");
	if (user->renting()){		
		movie_title = user->currentMovie()->getTitle();	
		message2Label = new QLabel(movie_title.c_str());
		rating = user->currentMovie()->getRating();
		ss << rating;
		ss >> temp_str;
		temp_str = "Current Rating: " + temp_str;
	}//end of if renting
	else{
		message2Label = new QLabel("Not currently renting a movie!");
		temp_str = "";
		rateButton1->setEnabled(false);
	}
	message3Label = new QLabel(temp_str.c_str());

	
	spinrating1 = new QSpinBox();
	spinrating1->setMaximum(5);
	spinrating2 = new QSpinBox();
	spinrating2->setMaximum(5);
	listOfMovies = new QComboBox();
	QVBoxLayout *vboxlayout = new QVBoxLayout;
	QHBoxLayout *hboxlayout1 = new QHBoxLayout;
	QHBoxLayout *hboxlayout2 = new QHBoxLayout;
	
	for (unsigned int i = 0; i < watchedMovies->size(); i++){
		listOfMovies->addItem(watchedMovies->at(i)->getTitle().c_str());
	}//end of for adding to qcombobox

	vboxlayout->addWidget(windowTitleLabel);
	vboxlayout->addWidget(message1Label);
	vboxlayout->addWidget(message2Label);
	vboxlayout->addWidget(message3Label);
	hboxlayout1->addWidget(rateButton1);
	hboxlayout1->addWidget(spinrating1);
	vboxlayout->addLayout(hboxlayout1);
	hboxlayout2->addWidget(listOfMovies);
	hboxlayout2->addWidget(rateButton2);
	hboxlayout2->addWidget(spinrating2);
	vboxlayout->addLayout(hboxlayout2);
	vboxlayout->addWidget(exitWindowButton);
	window->setLayout(vboxlayout);

	
}//
void RateMovieWindow::rateButton1Clicked(){
	string rating_str;
	stringstream ss;
	string temp_str;
	int temp_n;

	netflixDB->getUser(login_id)->currentMovie()->updateRating(spinrating1->value());
	temp_n = spinrating1->value();
	ss << temp_n;
	ss >> rating_str;
	temp_str = "Current Rating: " + rating_str;
	message3Label->setText(temp_str.c_str());

	QMessageBox messageBox;
	messageBox.setText("Movie Rated!");
	messageBox.exec();

}//end of ratebutton1clicked

void RateMovieWindow::rateButton2Clicked(){
	string movie_title;
	movie_title = listOfMovies->currentText().toStdString();
	vector<Movie*> *temp_vec;
	temp_vec = netflixDB->getUser(login_id)->getWatchedMovies();
	for (unsigned int i = 0; i < temp_vec->size(); i++){
		if (netflixDB->getUser(login_id)->getWatchedMovies()->at(i)->getTitle() == movie_title){
			netflixDB->getUser(login_id)->getWatchedMovies()->at(i)->updateRating(spinrating2->value());
		}
	}//end of for
	QMessageBox messageBox;
	messageBox.setText("Movie Rated!");
	messageBox.exec();
}//end of rateButton2Clicked

void RateMovieWindow::exitWindowButtonClicked(){
	window->close();
	MMW = new MainMenuWindow(netflixDB, login_id);
	MMW->setVisible();
}

void RateMovieWindow::setVisible(){
	window->show();
}