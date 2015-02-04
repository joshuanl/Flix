#ifndef NEWUSERWINDOW_H
#define NEWUSERWINDOW_H 

#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include "lib/User.h"
#include "lib/NFDB.h"

//class OpenWindow;

class OpenWindow;
class NewUserWindow : public QMainWindow{
	Q_OBJECT

public:
	NewUserWindow(NFDB *net_flixDB, OpenWindow *OW);
	~NewUserWindow();
	void setVisible();
	bool makeNewUser();

private slots:
	void confirmButtonClicked();
	void cancelButtonClicked();

private:
	QWidget *window;
	QLineEdit *textField1;
	QLineEdit *textField2;
	QLabel *message;
	NFDB *netflixDB;
	OpenWindow *OW;
};

#endif