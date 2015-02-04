#include "FindBaconWindow.h"
#include "lib/MainMenuWindow.h"
#include "lib/NFDB.h"
#include <string>
#include <iostream>
#include <sstream>

#include <QLabel>
#include <QMainWindow>
#include <QWidget>
#include <QWidget>
#include <QSpinBox>
#include <QPushButton>
#include <QComboBox>
#include <QHBoxLayout>
#include <QVBoxLayout>

using namespace std;


FindBaconWindow::~FindBaconWindow(){}

FindBaconWindow::FindBaconWindow(NFDB *netflixDB, string login_ID){
	
	window = new QWidget();
	this->netflixDB = netflixDB;
	this->login_ID = login_ID;
	windowTitleLabel = new QLabel("MMMMMMMMM, BACON \n\nFind the Bacon Between Two Actors");
	actorList1Label = new QLabel("Actors");
	actorList2Label = new QLabel("Actors");
	QLabel *spacer1 = new QLabel("");
	QLabel *spacer2 = new QLabel("");
	QLabel *resultLabel = new QLabel("");
	actorComboBox1 = new QComboBox();
	actorComboBox2 = new QComboBox();
	vboxLayout1 = new QVBoxLayout();
	hboxLayout1 = new QHBoxLayout();
	hboxLayout2 = new QHBoxLayout();
	hboxLayout3 = new QHBoxLayout();

	findBaconButton = new QPushButton("GIVE ME THAT BACON");
	connect(findBaconButton, SIGNAL(clicked()), this, SLOT(findBaconButtonClicked()));
	cancelButton = new QPushButton("Cancel");
	connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancelButtonClicked()));

	vector<Actor*>* actorDB = netflixDB->getActorDB();

	for (unsigned int i = 0; i < actorDB->size(); i++){
		actorComboBox1->addItem(actorDB->at(i)->getName().c_str());
		actorComboBox2->addItem(actorDB->at(i)->getName().c_str());
	}//end of for filling up qcombo boxes

	windowTitleLabel->setAlignment(Qt::AlignCenter);
	actorList1Label->setAlignment(Qt::AlignCenter);
	actorList2Label->setAlignment(Qt::AlignCenter);
	vboxLayout1->addWidget(windowTitleLabel);
	vboxLayout1->addWidget(spacer2);
	hboxLayout1->addWidget(actorList1Label);
	hboxLayout1->addWidget(actorList2Label);
	vboxLayout1->addLayout(hboxLayout1);
	hboxLayout2->addWidget(actorComboBox1);
	hboxLayout2->addWidget(spacer1);
	hboxLayout2->addWidget(actorComboBox2);
	vboxLayout1->addLayout(hboxLayout2);
	vboxLayout1->addWidget(resultLabel);
	hboxLayout3->addWidget(findBaconButton);
	hboxLayout3->addWidget(cancelButton);
	vboxLayout1->addLayout(hboxLayout3);
	window->setLayout(vboxLayout1);


}//end of constructor

void FindBaconWindow::findBaconButtonClicked(){	
	string actorA = actorComboBox1->currentText().toStdString();
	string actorB = actorComboBox2->currentText().toStdString();
	Actor *temp_actorA;
	Actor *temp_actorB;
	temp_actorA = netflixDB->getActor(actorA);
	temp_actorB = netflixDB->getActor(actorB);

	int n;
	string str_temp;
	n = netflixDB->findBaconLength(temp_actorA, temp_actorB);
	stringstream ss;
	ss << n;
	ss >> str_temp;
	str_temp = "I got " + str_temp + "bacon for you";
	QMessageBox messageBox;
  	messageBox.setText(str_temp.c_str());
  	messageBox.exec();
}//end of find bacon button

void FindBaconWindow::cancelButtonClicked(){
	window->close();
}//end of cancel button

void FindBaconWindow::setVisible(){
	window->show();
}//end of setVisible