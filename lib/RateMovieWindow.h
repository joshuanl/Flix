#ifndef RATEMOVIEWINDOW_H
#define RATEMOVIEWINDOW_H 

#include "lib/User.h"
#include "lib/NFDB.h"
#include <string>

#include <QLabel>
#include <QPushButton>
#include <QMainWindow>
#include <QWidget>
#include <QSpinBox>
#include <QComboBox>

class MainMenuWindow;

class RateMovieWindow : public QMainWindow{
	Q_OBJECT
public:
	RateMovieWindow();
	RateMovieWindow(NFDB *net_flixDB, string login_id, MainMenuWindow *MMW);
	~RateMovieWindow();
	void setVisible();

private slots:
   void rateButton1Clicked();
   void rateButton2Clicked();
   void exitWindowButtonClicked();


private:
	QWidget *window;
	NFDB *netflixDB;
	string login_id;
	User* user;
	QPushButton *rateButton1;
	QPushButton *rateButton2;
	QPushButton *exitWindowButton;
	QLabel *currentMovieLabel;
	QLabel *windowTitleLabel;
	QLabel *message1Label;
	QLabel *message2Label;
	QLabel *message3Label;
	QSpinBox *spinrating1;
	QSpinBox *spinrating2;
	QComboBox *listOfMovies;
	MainMenuWindow *MMW;

};
#endif