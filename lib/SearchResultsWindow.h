#ifndef SEARCHRESULTSWINDOW_H
#define SEARCHRESULTSWINDOW_H void setVisible();

#include "lib/User.h"
#include "lib/NFDB.h"
//#include "MainMenuWindow.h"
#include <string>
#include <set>
#include <queue>
#include <map>
#include <string>

#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QMainWindow>
#include <QWidget>

using namespace std;

class MainMenuWindow;

class SearchResultsWindow : public QMainWindow{
	Q_OBJECT

public:
	SearchResultsWindow(NFDB *net_fixDB, string login_id, MainMenuWindow *MMW);
	~SearchResultsWindow();
	void setVisible();
	void searchTitle(string input_text);
	void searchKeyword(string input_text);
	void searchActor(string input_text);

private slots:
	void nextMovieButtonClicked();
	void addToQueueButtonClicked();
	void returnToMenuButtonClicked();


private:
	int search_counter;
	bool searchActorDB;
	string input_kw;
	QWidget *window;
	QLineEdit *textfield;
	QTextEdit *kw_text;
	QPushButton *nextMovieButton;
	Movie *target_movie;
	User *user;
	NFDB *netflixDB;
	string login_id;
	set<Movie*> *copy_set;

	MainMenuWindow *MMW;
	
};
#endif
