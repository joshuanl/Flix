#ifndef RECOMMENDMOVIEWINDOW_H
#define RECOMMENDMOVIEWINDOW_H 

#include "lib/User.h"
#include "lib/NFDB.h"
#include "lib/Movie.h"
#include <string>

#include <QLabel>
#include <QPushButton>
#include <QMainWindow>
#include <QWidget>
#include <QSpinBox>
#include <QComboBox>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QVBoxLayout> 


class MainMenuWindow;
class RecommendMovieWindow : public QMainWindow{
	Q_OBJECT
public:
	RecommendMovieWindow(NFDB *netflixDB, string login_id, MainMenuWindow *MMW);
	~RecommendMovieWindow();
    void setVisible();

private slots:	
    void addToQueueButtonClicked();
    void declineButtonClicked();


private:
	MainMenuWindow *MMW;
	string login_id;
	QWidget *window;
	User* user;
	Movie *recommended;
	NFDB *netflixDB;
	QPushButton *addToQueueButton;
	QPushButton *declineButton;
	QLabel *windowTitleLabel;
	QLabel *movieTitleLabel;
	QLabel *keywordsLabel;
	QLabel *actorsLabel;
	QVBoxLayout *vboxLayout;
	QHBoxLayout *hboxLayout;

};


#endif