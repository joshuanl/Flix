#ifndef MAINMENUWINDOW_H
#define MAINMENUWINDOW_H 

#include "lib/SearchResultsWindow.h"
#include "lib/RateMovieWindow.h"
#include "lib/RecommendMovieWindow.h"
#include "lib/FindBaconWindow.h"
#include "lib/User.h"
#include "lib/NFDB.h"
#include <string>


#include <QTextEdit>
#include <QLabel>
#include <QMainWindow>
#include <QWidget>

class RecommendedMovieWindow;
class OpenWindow;
class SearchResultsWindow;
class RateMovieWindow;
class FindBaconWindow;

class MainMenuWindow : public QMainWindow{
	Q_OBJECT
public:
	MainMenuWindow(NFDB *net_flixDB, string login_id);
	void sendOW(OpenWindow *OW);
	~MainMenuWindow();
	void setVisible();
	void openRecommend();
	void updateRecommended(Movie *movie);
	//void setUser(User *userInfo);

private slots:
	void returnMovieButtonClicked();
	void rentMovieButtonClicked();
	void deleteButtonClicked();
	void moveToBackButtonClicked();
	void searchTitleButtonClicked();
	void searchKeywordButtonClicked();
	void logoutButtonClicked();
	void rateMoviesButtonClicked();
	void findBaconButtonClicked();
	void searchByActorButtonClicked();

private:
	QWidget *window;
	QTextEdit *movie_kw;
	QLabel *message;
	QLabel *movieratingLabel;
	QLabel *currentMovieLabel;
	QLabel *currentQueueLabel;
	QLineEdit *textfield;
	QPushButton *deleteMovieButton;
	QPushButton *rentMovieButton;
	QPushButton *returnMovieButton;
	QPushButton *moveToBackButton;
	QPushButton *rateMoviesButton;
	QPushButton *findBaconButton;
	QPushButton *searchByActorButton;
	SearchResultsWindow *SRW;
	RateMovieWindow *RMW;
	OpenWindow *OW;
	RecommendMovieWindow *RecMW;
	FindBaconWindow *FBW;
	User *user;
	NFDB *netflixDB;
	string login_id;

};

#endif