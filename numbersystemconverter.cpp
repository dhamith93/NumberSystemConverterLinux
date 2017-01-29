#include "numbersystemconverter.h"
#include "ui_numbersystemconverter.h"
#include <QMessageBox>

NumberSystemConverter::NumberSystemConverter(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NumberSystemConverter) {
	setWindowTitle( QCoreApplication::applicationName() );
    ui->setupUi(this);
    
}

NumberSystemConverter::~NumberSystemConverter() {
    delete ui;
}

void NumberSystemConverter::on_txtDec_returnPressed() {

    QRegExp chk("\\d*");
    if (chk.exactMatch(ui->txtDec->text())) {
        decBin(ui->txtDec->text().toLong());
        decOct(ui->txtDec->text().toLong());
        decHex(ui->txtDec->text().toLong());
    } else {
        clear();
        QMessageBox::information(this, tr("Error!"), tr("The value you entered contains numbers and/or symbols!"));
    }
}

void NumberSystemConverter::on_txtBin_returnPressed() {
    
    binDec();
}

void NumberSystemConverter::on_txtOct_returnPressed() {
    octAll();
}

void NumberSystemConverter::on_txtHex_returnPressed() {
    hexAll();
}

void NumberSystemConverter::on_clearAll_clicked() {
    clear();
}

void NumberSystemConverter::on_copyDec_clicked() {
    ui->txtDec->selectAll();
    ui->txtDec->copy();
}

void NumberSystemConverter::on_copyBin_clicked() {
    ui->txtBin->selectAll();
    ui->txtBin->copy();
}

void NumberSystemConverter::on_copyOct_clicked() {
    ui->txtOct->selectAll();
    ui->txtOct->copy();
}

void NumberSystemConverter::on_copyHex_clicked() {
    ui->txtHex->selectAll();
    ui->txtHex->copy();
}

void NumberSystemConverter::on_actionHelp_triggered() {
    QMessageBox::about(this,"Help","This is a number system converter.\n\nEnter the number you want to convert in to the appropriate text box and hit 'Enter' on your keyboard. It will be converted in to all available number systems. Click on copy to copy the converted number. Click 'Clear' if you want to clear all text boxes.\n\n\t\t\t\t--dhamith93");

}

void NumberSystemConverter::clear() {
    ui->txtDec->clear();
    ui->txtBin->clear();
    ui->txtOct->clear();
    ui->txtHex->clear();
}

//Decimal to binary conversion -->
void NumberSystemConverter::decBin(long dec) {
    long b[64];
    int f = 0, count = 0;
    if(dec == 0 || dec == 1) {
        ui->txtBin->setText(QString::number(dec));
    } else {
        while (1) {
            if(dec % 2 == 1) {
                count = 1;
            } else if (dec % 2 == 0) {
                count = 0;
            }
            dec = dec / 2;
            if (dec < 0.9999) {
                break;
            }
            b[f] = count;
            f++;
        }
        b[f] = 1; //since % doesn't output the final dec/2 and MSB is always = 1
        ui->txtBin->clear();
        for(int j = f; j >= 0; j--) {
            ui->txtBin->insert(QString::number(b[j]));
        }          
    }
}

//Decimal to octal conversion -->
void NumberSystemConverter::decOct(long dec) {
    long c[64];
    int f = 0;
    if (dec < 7) {
        ui->txtOct->clear();
        ui->txtOct->setText(QString::number(dec));
    } else {
        while (1) {
            c[f] = dec % 8;
            dec = dec / 8;
            if (dec == 0) {
                break;
            }
            f++;
        }
        ui->txtOct->clear();
        for(int j = f; j >= 0; j--) {
            ui->txtOct->insert(QString::number(c[j]));
        }
    }
}

//Decimal to hex
void NumberSystemConverter::decHex(long dec) {
    long c[16];
    int f = 0;
    QString d;
    if (dec >= 0 && dec < 10) {
        ui->txtHex->clear();
        ui->txtHex->setText(QString::number(dec));
    } else if(dec > 9 && dec < 16) {
        if(dec == 10) {
                d = 'A';
        } else if(dec == 11) {
            d = 'B';
        } else if(dec == 12) {
            d = 'C';
        } else if(dec == 13) {
            d = 'D';
        } else if(dec == 14) {
            d = 'E';
        } else if(dec == 15) {
            d = 'F';
        }
        ui->txtHex->clear();
        ui->txtHex->setText(d);
    } else {
        while (1) {
            c[f] = dec % 16;            
            if(c[f] == 10) {
                c[f] = 'A';
            } else if(c[f] == 11) {
                c[f] = 'B';
            } else if(c[f] == 12) {
                c[f] = 'C';
            } else if(c[f] == 13) {
                c[f] = 'D';
            } else if(c[f] == 14) {
                c[f] = 'E';
            } else if(c[f] == 15) {
                c[f] = 'F';
            }
            dec = dec / 16;
            if (dec == 0) {
                break;
            }
            f++;
        }
        ui->txtHex->clear();
        for(int j = f; j >= 0; j--) {
            if ((int)c[j] >= 0 && (int)c[j] < 10 ) {
                ui->txtHex->insert(QString::number(c[j]));
            }
            else {
                d = c[j];
                ui->txtHex->insert(d);
            }
        }
    }
}

//Binary to decimal
void NumberSystemConverter::binDec() {
    QString x = ui->txtBin->text();
    int k = x.length()-1;
    int b[x.length()];
    bool invalid = false;
    for (int n = 0; n < x.length(); n++) {
        b[k] = x[n].digitValue();
        if(b[k] > 1 || b[k] < 0) {
            invalid = true;
            clear();
            QMessageBox::information(this, tr("Error!"), tr("The value you entered is not a binary number!"));
            break;
        }
        k--;
    }
    long sum = 0;
    for(int y = 0; y < (ui->txtBin->text()).length(); y++) {
        if(b[y] == 1) {
            sum = sum + powers(y);
        }
    }
    if (!invalid) {
        ui->txtDec->clear();
        ui->txtDec->setText(QString::number(sum));
        decOct(sum);
        decHex(sum);
    }
}

//Octal to All
void NumberSystemConverter::octAll() {
    QString x = ui->txtOct->text();
    int k = x.length()-1;
    int b[x.length()];
    bool invalid = false;
    for (int n = 0; n < x.length(); n++) {
        b[k] = x[n].digitValue();
        if(b[k] > 7 || b[k] < 0) {
            invalid = true;
            clear();
            QMessageBox::information(this, tr("Error!"), tr("The value you entered is not an octal number!"));
            break;
        }
        k--;
    }
    long sum = 0;
    for (int i = 0; i < (ui->txtOct->text()).length(); i++) {
        if(i >= 2) {
            sum = sum + (b[i] * powers2(i, 8));
        }
        else if (i == 1) {
            sum = sum + (b[i] * 8);
        }
        else if (i == 0) {
            sum = sum + (b[i] * 1);
        }
    }
    if (!invalid) {
        ui->txtDec->clear();
        ui->txtDec->setText(QString::number(sum));
        decBin(sum);
        decHex(sum);
    }        
}

// Hexadecimal to All
void NumberSystemConverter::hexAll() {
    QString hexString = ui->txtHex->text();
    int b = -1; // count goes like 0 > 1 > etc.
    long sum = 0;
    int c = 0;
    bool invalid = false;
    for (int a = 0; hexString[a] != 0; a++) {
        b++; // count goes like 0 > 1 > etc. first run of the loop = 0
    }
    int hexStringNum[b];
    for (int i = b; i >= 0; i--) {        
        if(hexString[i] == 'A' || hexString[i] == 'a') {
            hexStringNum[i] = 10;
        } else if(hexString[i] == 'B' || hexString[i] == 'b') {
            hexStringNum[i] = 11;
        } else if(hexString[i] == 'C' || hexString[i] == 'c') {
            hexStringNum[i] = 12;
        } else if(hexString[i] == 'D' || hexString[i] == 'd') {
            hexStringNum[i] = 13;
        } else if(hexString[i] == 'E' || hexString[i] == 'e') {
            hexStringNum[i] = 14;
        } else if(hexString[i] == 'F' || hexString[i] == 'f') {
            hexStringNum[i] = 15;
        } else if(hexString[i] == '0') {
            hexStringNum[i] = 0;
        } else if(hexString[i] == '1') {
            hexStringNum[i] = 1;
        } else if(hexString[i] == '2') {
            hexStringNum[i] = 2;
        } else if(hexString[i] == '3') {
            hexStringNum[i] = 3;
        } else if(hexString[i] == '4') {
            hexStringNum[i] = 4;
        } else if(hexString[i] == '5') {
            hexStringNum[i] = 5;
        } else if(hexString[i] == '6') {
            hexStringNum[i] = 6;
        } else if(hexString[i] == '7') {
            hexStringNum[i] = 7;
        } else if(hexString[i] == '8') {
            hexStringNum[i] = 8;
        } else if(hexString[i] == '9') {
            hexStringNum[i] = 9;
        } else {
            invalid = true;
            clear();
            QMessageBox::information(this, tr("Error!"), tr("The value you entered is not an hexadecimal number!"));
            break;
        }       
        if(c >= 2) {
            sum = sum + (hexStringNum[i]*powers2(c, 16));
        }
        else if (c == 1) {
            sum = sum + (hexStringNum[i] * 16);
        }
        else if (c == 0) {
            sum = sum + (hexStringNum[i] * 1);
        }
        c++;
    }
    if (!invalid) {
        ui->txtDec->clear();
        ui->txtDec->setText(QString::number(sum));
        decBin(sum);
        decOct(sum);
        decHex(sum);
    }
}

// powers of 2
long NumberSystemConverter::powers(long x) {
    int i = 1;
    long sum = 1;
    while (i <= x) {
        sum = 2 * sum;
        i++;
    }
    return sum;
}

// powers of 8 and 16
long NumberSystemConverter::powers2(int x, int y) {
    int l = 16;
    long sum = 16;
    if (y == 8) {
        sum = 8;
        l = 8;
    }
    for (int i = 2; i <= x; i++) {
        sum = sum * l;
    }
    return sum;
}
