#include "numbersystemconverter.h"
#include "ui_numbersystemconverter.h"
#include <QMessageBox>

int count = 0;

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
    if (ui->txtDec->text() != "") {
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
}

void NumberSystemConverter::on_txtBin_returnPressed() {
    if (ui->txtBin->text() != "") {
        binDec();
    }
}

void NumberSystemConverter::on_txtOct_returnPressed() {
    if (ui->txtOct->text() != "") {
        octAll();
    }    
}

void NumberSystemConverter::on_txtHex_returnPressed() {
    if (ui->txtHex->text() != "") {
        hexAll();
    }
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
    int binary[64];
    count = 0;
    if(dec == 0 || dec == 1) {
        ui->txtBin->setText(QString::number(dec));
    } else {
        while (1) {            
            if(dec % 2 == 1) {
                binary[count] = 1;
            } else if (dec % 2 == 0) {
                binary[count] = 0;
            }
            dec = dec / 2;
            if (dec < 0.9999) {
                break;
            }            
            count += 1;
        }
        binary[count] = 1; //since % doesn't output the final dec/2 and MSB is always = 1
        ui->txtBin->clear();
        for(int j = count; j >= 0; j--) {
            ui->txtBin->insert(QString::number(binary[j]));
        }          
    }
}

//Decimal to octal conversion -->
void NumberSystemConverter::decOct(long dec) {
    int octal[21];
    count = 0;
    if (dec < 7) {
        ui->txtOct->clear();
        ui->txtOct->setText(QString::number(dec));
    } else {
        while (1) {
            octal[count] = dec % 8;
            dec = dec / 8;
            if (dec == 0) {
                break;
            }
            count += 1;
        }
        ui->txtOct->clear();
        for(int j = count; j >= 0; j--) {
            ui->txtOct->insert(QString::number(octal[j]));
        }
    }
}

//Decimal to hex
void NumberSystemConverter::decHex(long dec) {
    int hexa[16];
    count = 0;
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
            hexa[count] = dec % 16;            
            if(hexa[count] == 10) {
                hexa[count] = 'A';
            } else if(hexa[count] == 11) {
                hexa[count] = 'B';
            } else if(hexa[count] == 12) {
                hexa[count] = 'C';
            } else if(hexa[count] == 13) {
                hexa[count] = 'D';
            } else if(hexa[count] == 14) {
                hexa[count] = 'E';
            } else if(hexa[count] == 15) {
                hexa[count] = 'F';
            }
            dec = dec / 16;
            if (dec == 0) {
                break;
            }
            count += 1;
        }
        ui->txtHex->clear();
        for(int j = count; j >= 0; j--) {
            if ((int)hexa[j] >= 0 && (int)hexa[j] < 10 ) {
                ui->txtHex->insert(QString::number(hexa[j]));
            }
            else {
                d = hexa[j];
                ui->txtHex->insert(d);
            }
        }
    }
}

//Binary to decimal
void NumberSystemConverter::binDec() {
    QString binary = ui->txtBin->text();
    int binaryLength = binary.length()-1;
    int binaryArray[binary.length()];
    bool invalid = false;
    
    // Fills binaryArray and checks for invalid values
    for (int n = 0; n < binary.length(); n++) {
        binaryArray[binaryLength] = binary[n].digitValue();
        if(binaryArray[binaryLength] > 1 || binaryArray[binaryLength] < 0) {
            invalid = true;
            clear();
            QMessageBox::information(this, tr("Error!"), tr("The value you entered is not a binary number!"));
            break;
        }
        binaryLength -= 1;
    }
    long decimal = 0;
    for(int y = 0; y < (binary.length()); y++) {
        if(binaryArray[y] == 1) {
            decimal += powers(y);
        }
    }
    if (!invalid) {
        ui->txtDec->clear();
        ui->txtDec->setText(QString::number(decimal));
        decOct(decimal);
        decHex(decimal);
    }
}

//Octal to All
void NumberSystemConverter::octAll() {
    QString octal = ui->txtOct->text();
    int octalLength = octal.length()-1;
    int octalArray[octal.length()];
    bool invalid = false;
    for (int n = 0; n < octal.length(); n++) {
        octalArray[octalLength] = octal[n].digitValue();
        if(octalArray[octalLength] > 7 || octalArray[octalLength] < 0) {
            invalid = true;
            clear();
            QMessageBox::information(this, tr("Error!"), tr("The value you entered is not an octal number!"));
            break;
        }
        octalLength -= 1;
    }
    long decimal = 0;
    for (int i = 0; i < (ui->txtOct->text()).length(); i++) {
        if(i >= 2) {
            decimal += (octalArray[i] * powers2(i, 8));
        }
        else if (i == 1) {
            decimal += (octalArray[i] * 8);
        }
        else if (i == 0) {
            decimal += (octalArray[i] * 1);
        }
    }
    if (!invalid) {
        ui->txtDec->clear();
        ui->txtDec->setText(QString::number(decimal));
        decBin(decimal);
        decHex(decimal);
    }        
}

// Hexadecimal to All
void NumberSystemConverter::hexAll() {
    QString hexString = ui->txtHex->text();
    int hexLength = hexString.length() - 1; 
    long decimal = 0;
    count = 0;
    bool invalid = false;
    int hexStringNum[hexLength];
    for (int i = hexLength; i >= 0; i--) {        
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
        if(count >= 2) {
            decimal += (hexStringNum[i]*powers2(count, 16));
        }
        else if (count == 1) {
            decimal += (hexStringNum[i] * 16);
        }
        else if (count == 0) {
            decimal += (hexStringNum[i] * 1);
        }
        count += 1;
    }
    if (!invalid) {
        ui->txtDec->clear();
        ui->txtDec->setText(QString::number(decimal));
        decBin(decimal);
        decOct(decimal);
        decHex(decimal);
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
