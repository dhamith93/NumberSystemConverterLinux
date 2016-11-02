#ifndef NUMBERSYSTEMCONVERTER_H
#define NUMBERSYSTEMCONVERTER_H

#include <QMainWindow>

namespace Ui {
class NumberSystemConverter;
}

class NumberSystemConverter : public QMainWindow
{
    Q_OBJECT

public:
    explicit NumberSystemConverter(QWidget *parent = 0);
    ~NumberSystemConverter();
    void decBin(long dec);
    void decOct(long dec);
    void decHex(long dec);
    void binDec();
    void octAll();
    void hexAll(QString x);
    long powers(long x);
    long powers_2(int x, int y);
    void clear();

private slots:
    void on_txtDec_returnPressed();

    void on_clearAll_clicked();

    void on_txtBin_returnPressed();

    void on_txtOct_returnPressed();

    void on_txtHex_returnPressed();

    void on_copyDec_clicked();

    void on_copyBin_clicked();

    void on_copyOct_clicked();

    void on_copyHex_clicked();


    void on_actionHelp_triggered();

private:
    Ui::NumberSystemConverter *ui;
};

#endif // NUMBERSYSTEMCONVERTER_H
