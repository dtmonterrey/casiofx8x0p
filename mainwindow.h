/**
    Copyright 2016 Evandro Pires Alves

    This file is part of casiofx8x0p.

    casiofx8x0p is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    casiofx8x0p is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with casiofx8x0p.  If not, see <http://www.gnu.org/licenses/>.
  */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <baudrate.h>
#include <casiobasichelper.h>
#include <QComboBox>
#include <QFileDialog>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <Qsci/qsciscintilla.h>
#include <Qsci/qscilexercpp.h>
#include <QSerialPort>
#include <QSerialPortInfo>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionBaudRateChanged(int index);
    void on_actionSendButtonClicked();

    void on_actionOpen_File_triggered();

private:
    Ui::MainWindow *ui;
    QComboBox *comboPorts;
    QComboBox *comboBaudRates;
};

#endif // MAINWINDOW_H
