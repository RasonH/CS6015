#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QDialogButtonBox>
#include <QGroupBox>
#include <QRadioButton>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QGridLayout>

class mainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit mainWidget(QWidget *parent = nullptr);

private slots:
    void reset();
    void processResult();
    void readFile();

private:

    // basic layout
    QGridLayout *base_layout_;

    //component widgets
    QLabel *expression_l_;
    QTextEdit *expression_te_;
    QGroupBox *mode_rb_gb_;
    QRadioButton *interp_rb_;
    QRadioButton *pretty_print_rb_;

    QPushButton *readfile_pb_;


    QPushButton *submit_pb_;

    QLabel *result_l_;
    QTextEdit *result_te_;

    QPushButton *reset_pb_;

};

#endif // MAINWIDGET_H
