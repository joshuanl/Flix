#include "lib/OpenWindow.h"
#include "lib/MainMenuWindow.h"
#include "lib/NewUserWindow.h"
#include "lib/User.h"
#include "lib/NFDB.h"
#include <map>

#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QLabel>
#include <QString>
#include <QObject>
#include <QAction>
#include <QApplication>
#include <iostream>
#include <string>

using namespace std;


OpenWindow::OpenWindow(NFDB *net_flixDB) : QMainWindow(){
	window = new QWidget();	
	netflixDB = net_flixDB;
	NUW = new NewUserWindow(netflixDB, this);
	
		
	QPushButton *loginButton = new QPushButton("Login");
	QPushButton *newUserButton = new QPushButton("New User");
	QPushButton *exitButton = new QPushButton("Exit");

	QLabel *loginLabel = new QLabel(tr("User ID"));
	textField1 = new QLineEdit(); 

	QVBoxLayout *vboxLayout = new QVBoxLayout;
	QHBoxLayout *hboxLayout = new QHBoxLayout;
	QHBoxLayout *loginForm = new QHBoxLayout;

	QLabel *label1 = new QLabel(tr("CSCI 104-Flix"));
	message = new QLabel(tr(""));
	label1->setAlignment(Qt::AlignCenter);
	vboxLayout->addWidget(label1);
	loginForm->addWidget(loginLabel);
	loginForm->addWidget(textField1);
	connect(textField1, SIGNAL(returnPressed()), this, SLOT(LoginButtonClicked()));
	vboxLayout->addWidget(message);
	hboxLayout->addWidget(loginButton);
	hboxLayout->addWidget(newUserButton);
	hboxLayout->addWidget(exitButton);
	vboxLayout->addLayout(loginForm);
	vboxLayout->addLayout(hboxLayout);


	connect(loginButton, SIGNAL(clicked()), this, SLOT(LoginButtonClicked()));
	connect(newUserButton, SIGNAL(clicked()), this, SLOT(NewUserButtonClicked()));
	connect(exitButton, SIGNAL(clicked()), this, SLOT(ExitButtonClicked()));

	window->setLayout(vboxLayout);
	window->show();

	// cerr << "==================printing out all movies and their actors" << endl;
	// map<string, Movie*> *MDB = netflixDB->getMovieDB();
	// Movie *temp_movie;
	// for (map<string, Movie*>::iterator MDB_it = MDB->begin(); MDB_it != MDB->end(); ++MDB_it){
	// 	cerr << (*MDB_it).second->getTitle() << endl;
	// 	temp_movie = (*MDB_it).second;
	// 	for (unsigned int i = 0; i < temp_movie->getActors()->size(); i++){
	// 		cerr << "     " << temp_movie->getActors()->at(i)->getName() << endl;
	// 	}//end of inner for
	// }//end of for


	netflixDB->buildRelatedActors();
}//end of constructor

void OpenWindow::LoginButtonClicked(){
	checkLogin();			//helper func
	
	//window->hide();
}//end of login button


void OpenWindow::NewUserButtonClicked(){	
	NUW->setWindowFlags(Qt::Window);
	NUW->setVisible();
	//cerr << "new user button clicked";
}//end of new user button


void OpenWindow::ExitButtonClicked(){
	netflixDB->saveUserInfo();
	window->hide();
	QApplication::quit();
}//end of exit button

void OpenWindow::checkLogin(){
	string login_id = textField1->text().toStdString();
	if(netflixDB->loginExists(login_id)){
		message->setText("Logged in successfully!");
		MMW = new MainMenuWindow(netflixDB, login_id);
		MMW->sendOW(this);
		MMW->setWindowFlags(Qt::Window);
		MMW->openRecommend();
		//MMW->setVisible();
		window->close();
	}
	else{
		message->setText("User not found!");
	}
}//end of check login

void OpenWindow::updateDB(NFDB *netflixDB){
	this->netflixDB = netflixDB;
}//end of updating db
