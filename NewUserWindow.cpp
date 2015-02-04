#include "lib/NewUserWindow.h"
#include "lib/User.h"

#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QLabel>
#include <QObject>
#include <QAction>
#include <QApplication>

#include <iostream>
#include <string>
#include "lib/NFDB.h"
#include "lib/OpenWindow.h"

using namespace std;

NewUserWindow::~NewUserWindow(){}

NewUserWindow::NewUserWindow(NFDB *netflixDB, OpenWindow *OW){
	window = new QWidget();
	this->netflixDB = netflixDB;
	this->OW = OW;
	
	QLabel *loginLabel = new QLabel(tr("User ID"));
	textField1 = new QLineEdit(); 

	QLabel *nameLabel = new QLabel(tr("Name"));
	textField2 = new QLineEdit();

	QLabel *winLabel = new QLabel(tr("CSCI 104-Flix"));
	winLabel->setAlignment(Qt::AlignCenter);	
	message = new QLabel(tr(""));

	QPushButton *confirmButton = new QPushButton("Confirm");
	connect(confirmButton, SIGNAL(clicked()), this, SLOT(confirmButtonClicked()));
	connect(textField2, SIGNAL(returnPressed()), this, SLOT(confirmButtonClicked()));

	QPushButton *cancelButton = new QPushButton("Cancel");
	connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancelButtonClicked()));
	
	QVBoxLayout *vboxLayout = new QVBoxLayout;
	QHBoxLayout *hboxLayout1 = new QHBoxLayout;
	QHBoxLayout *hboxLayout2 = new QHBoxLayout;
	QHBoxLayout *hboxLayout3 = new QHBoxLayout;

	vboxLayout->addWidget(winLabel);
	vboxLayout->addWidget(message);
	hboxLayout1->addWidget(loginLabel);
	hboxLayout1->addWidget(textField1);
	hboxLayout2->addWidget(nameLabel);
	hboxLayout2->addWidget(textField2);
	hboxLayout3->addWidget(confirmButton);
	hboxLayout3->addWidget(cancelButton);

	vboxLayout->addLayout(hboxLayout1);
	vboxLayout->addLayout(hboxLayout2);
	vboxLayout->addLayout(hboxLayout3);

	window->setLayout(vboxLayout);
	//window->show();


}//end of constructor

void NewUserWindow::confirmButtonClicked(){
	if(makeNewUser()){
		OW->updateDB(netflixDB);
		cerr << "number of users: " << netflixDB->getUserDB()->size() << endl;
		window->close();
	}
}//end of confirmButton clicked

void NewUserWindow::cancelButtonClicked(){
	cout << "cancel " << endl;
	window->close();

}//end of cancelButtonClicked

void NewUserWindow::setVisible(){
	window->show();
}

bool NewUserWindow::makeNewUser(){
	User *user;
	string input_id = textField1->text().toStdString();
	string input_name = textField2->text().toStdString();
	cerr << "sending id: " << input_id << endl;
	if(netflixDB->loginExists(input_id)){
		message->setText("User already Exists!!");
		return false;
	}
	if (!netflixDB->loginExists(input_id)){
		message->setText("User Created!!");
		user = new User(input_id, input_name);
		netflixDB->addUser(input_id, user);
		return true;
	}//end of else
	return false;
}//end of makeNewUser
