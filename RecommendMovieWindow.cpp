#include "lib/RecommendMovieWindow.h"
#include "lib/MainMenuWindow.h"
#include "lib/NFDB.h"
#include "lib/User.h"
#include "lib/Movie.h"
#include <vector>
#include <iostream>
#include <string>

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

using namespace std;

RecommendMovieWindow::~RecommendMovieWindow(){}

RecommendMovieWindow::RecommendMovieWindow(NFDB *netflixDB, string login_id, MainMenuWindow *MMW){
	this->netflixDB = netflixDB;
	this->MMW = MMW;
	this->login_id = login_id;
	user = netflixDB->getUser(login_id);
	pair<int, Movie*> temp_pair;
	window = new QWidget();

	addToQueueButton = new QPushButton("Add to Queue");
	connect(addToQueueButton, SIGNAL(clicked()), this, SLOT(addToQueueButtonClicked()));

	declineButton = new QPushButton("Cancel");
	connect(declineButton, SIGNAL(clicked()), this, SLOT(declineButtonClicked()));

	windowTitleLabel = new QLabel("Recommended Movie to Watch");
		
	string temp_str = "   ";

	temp_pair = netflixDB->recommendation(user);
	if (temp_pair.first == 1){
		recommended = temp_pair.second;	
		movieTitleLabel = new QLabel(recommended->getTitle().c_str());
		set<string> kw_set = recommended->getAllKeywords();
		for (set<string>::iterator set_it = kw_set.begin(); set_it != kw_set.end(); ++set_it){
			temp_str += (*set_it) + "\n   ";
		}
	keywordsLabel = new QLabel(temp_str.c_str());
	}//end of if recommendation found

	else{
		movieTitleLabel = new QLabel("You've watched all the movies!\nNothing to be recommended");
		keywordsLabel = new QLabel("");
		addToQueueButton->setEnabled(false);
	}

	vboxLayout = new QVBoxLayout();
	hboxLayout = new QHBoxLayout();

	QLabel *spacer = new QLabel("");

	vboxLayout->addWidget(windowTitleLabel);
	vboxLayout->addWidget(movieTitleLabel);
	vboxLayout->addWidget(keywordsLabel);
	vboxLayout->addWidget(spacer);
	hboxLayout->addWidget(addToQueueButton);
	hboxLayout->addWidget(declineButton);
	vboxLayout->addLayout(hboxLayout);

	window->setLayout(vboxLayout);
	//window->setLayout(vboxLayout1);

}//end of constructor

void RecommendMovieWindow::addToQueueButtonClicked(){
	MMW->updateRecommended(recommended);
	addToQueueButton->setText("Movie Added!");
	addToQueueButton->setEnabled(false);
}//end of add to queue button
    
void RecommendMovieWindow::declineButtonClicked(){
	window->close();
	MMW = new MainMenuWindow(netflixDB, login_id);
	MMW->setVisible();
}//end of declineButton

void RecommendMovieWindow::setVisible(){
	window->show();
}//end of setVisible