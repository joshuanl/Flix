#ifndef FINDBACONWINDOW_H
#define FINDBACONWINDOW_H 

#include "lib/NFDB.h"
#include <string>

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

class MainMenuWindow;
class FindBaconWindow : public QMainWindow{
	Q_OBJECT
public:
	FindBaconWindow(NFDB *netflixDB, string login_ID);
	~FindBaconWindow();
	void setVisible();

private slots:
	void findBaconButtonClicked();
	void cancelButtonClicked();

private:
	QWidget *window;
	NFDB *netflixDB;
	string login_ID;
	QLabel *windowTitleLabel;
	QLabel *actorList1Label;
	QLabel *actorList2Label;
	QComboBox *actorComboBox1;
	QComboBox *actorComboBox2;
	QVBoxLayout *vboxLayout1;
	QHBoxLayout *hboxLayout1;
	QHBoxLayout *hboxLayout2;
	QHBoxLayout *hboxLayout3;
	QPushButton *findBaconButton;
	QPushButton *cancelButton;

};
#endif