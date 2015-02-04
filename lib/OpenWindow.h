#ifndef OPENWINDOW_H
#define OPENWINDOW_H 


#include <QMainWindow>
#include "lib/NewUserWindow.h"
#include "lib/MainMenuWindow.h"
#include "lib/User.h"
#include "lib/NFDB.h"
#include <QWidget>
#include <QLineEdit>
#include <QLabel>


class NewUserWindow;
class MainMenuWindow;

class OpenWindow : public QMainWindow{

Q_OBJECT

public:
	OpenWindow(NFDB *net_flixDB);
	void checkLogin();
	void updateDB(NFDB *netflixDB);

private slots:
	void LoginButtonClicked();
	void NewUserButtonClicked();
	void ExitButtonClicked();
private:
	QWidget *window;
	NewUserWindow *NUW;
	MainMenuWindow *MMW;
	
	QLineEdit *textField1;
	QLabel *message;
	NFDB *netflixDB;
};

#endif