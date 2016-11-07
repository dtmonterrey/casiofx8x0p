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

#include "mainwindow.h"
#include "ui_mainwindow.h"

Q_DECLARE_METATYPE(QSerialPortInfo)
Q_DECLARE_METATYPE(BaudRate)

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // ports
    comboPorts = new QComboBox();
    QSerialPortInfo serialPortInfo;
    foreach (serialPortInfo, QSerialPortInfo::availablePorts()) {
        QVariant port;
        port.setValue<QSerialPortInfo>(serialPortInfo);
        comboPorts->addItem(serialPortInfo.portName(), port);
    }
    ui->mainToolBar->addWidget(new QLabel("Device: "));
    ui->mainToolBar->addWidget(comboPorts);

    // baud rate
    comboBaudRates = new QComboBox();
    QList<BaudRate> baudRates = QList<BaudRate>()
            << BaudRate(1, 150)
            << BaudRate(2, 300)
            << BaudRate(3, 600)
            << BaudRate(4, 1200)
            << BaudRate(5, 2400)
            << BaudRate(6, 4800);
    foreach (BaudRate baudRate, baudRates) {
        QVariant variantBaudRate;
        variantBaudRate.setValue<BaudRate>(baudRate);
        comboBaudRates->addItem(baudRate.toString().toLatin1(), variantBaudRate);
    }
    comboBaudRates->setCurrentIndex(2);
    comboBaudRates->connect(comboBaudRates, SIGNAL(currentIndexChanged(int)), this, SLOT(on_actionBaudRateChanged(int)));
    ui->mainToolBar->addWidget(new QLabel("Baud rate: "));
    ui->mainToolBar->addWidget(comboBaudRates);

    // send button
    QPushButton *btnSend = new QPushButton();
    btnSend->setText("Send");
    btnSend->connect(btnSend, SIGNAL(clicked(bool)), this, SLOT(on_actionSendButtonClicked()));
    ui->mainToolBar->addWidget(btnSend);

    // configure QScintilla2
    // lex
    QsciLexerCPP *lexer = new QsciLexerCPP();
    lexer->setDefaultFont(ui->textEdit->font());
    lexer->setFoldComments(true);
    ui->textEdit->setLexer(lexer);
    // caret
    ui->textEdit->setCaretLineVisible(true);
    ui->textEdit->setCaretLineBackgroundColor(QColor("#ffe4e4"));
    // margin
    QFontMetrics fontmetrics = QFontMetrics(ui->textEdit->font());
    ui->textEdit->setMarginsFont(ui->textEdit->font());
    ui->textEdit->setMarginWidth(0, fontmetrics.width(QString::number(ui->textEdit->lines())) + 6);
    ui->textEdit->setMarginLineNumbers(0, true);

    // default status bar message
    statusBar()->showMessage("LOAD \"COM0:3,E,8,2,N,N,N,B,N\"");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionBaudRateChanged(int index)
{
    BaudRate baudRate = comboBaudRates->itemData(index).value<BaudRate>();
    static CasioBasicHelper casioBasicHelper;
    ui->statusBar->showMessage(casioBasicHelper.getConnectionString(baudRate));
}

void MainWindow::on_actionSendButtonClicked()
{
    // get selected baud rate
    BaudRate baudRate = comboBaudRates->itemData(comboBaudRates->currentIndex()).value<BaudRate>();

    // get and configure port
    QSerialPortInfo serialPortInfo = comboPorts->itemData(comboPorts->currentIndex()).value<QSerialPortInfo>();
    QSerialPort *serialPort = new QSerialPort();
    serialPort->setPort(serialPortInfo);
    serialPort->setBaudRate(baudRate.getValue());
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setParity(QSerialPort::EvenParity);
    serialPort->setStopBits(QSerialPort::TwoStop);
    serialPort->setFlowControl(QSerialPort::SoftwareControl);

    // send data
    if (serialPort->open(QIODevice::WriteOnly)) {
        ui->statusBar->showMessage("Writting...");
        QString text = ui->textEdit->text();
        // Casio seams to only accept Windows style EOL
        text = text.replace("\r", "");      // clean all \r
        text = text.replace("\n", "\r\n");  // change remaining \n to \r\n
        QByteArray data(text.toLatin1());
        qint64 writenBytes = serialPort->write(data);
        if (writenBytes != -1) {
            ui->statusBar->showMessage(QString("%1 bytes writed with success!").arg(writenBytes));
        } else {
            ui->statusBar->showMessage(QString("Couldn't write to device!"));   // TODO should show error
        }
        serialPort->flush();
        serialPort->close();
    } else {
        ui->statusBar->showMessage(QString("Can't open %1").arg(serialPortInfo.portName()), 3000);
    }
}

void MainWindow::on_actionOpen_File_triggered()
{
    QString filename =  QFileDialog::getOpenFileName(this, tr("Open file"), QDir::currentPath(), "*.*");
    if (filename.isEmpty()) {
        return;
    }

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        return;
    }
    ui->textEdit->setText(file.readAll());

    file.close();
}





