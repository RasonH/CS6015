#include <QFileDialog>

#include "mainwidget.h"

#include "expr.h"
#include "val.h"
#include "parse.h"

mainWidget::mainWidget(QWidget *parent)
    : QWidget{parent}
{
    // Create the layout
    base_layout_ = new QGridLayout();

    // Create the widget objects

    expression_l_ = new QLabel("Expression:");
    expression_te_ = new QTextEdit();

    mode_rb_gb_ = new QGroupBox();
    interp_rb_ = new QRadioButton("interp", mode_rb_gb_);
    pretty_print_rb_ = new QRadioButton("pretty print", mode_rb_gb_);
    readfile_pb_ = new QPushButton("Read from file", nullptr);

    submit_pb_ = new QPushButton("Submit", nullptr);

    result_l_ = new QLabel("Result:");
    result_te_ = new QTextEdit();

    reset_pb_ = new QPushButton("Reset", nullptr);

    // Add components to the grid layout

    base_layout_->addWidget(expression_l_,0,0);
    base_layout_->addWidget(expression_te_,0,1,1,2);

    QGridLayout* modeLayout = new QGridLayout(mode_rb_gb_);
    modeLayout->addWidget(interp_rb_, 0, 0, Qt::AlignLeft);
    modeLayout->addWidget(pretty_print_rb_, 1, 0, Qt::AlignLeft);
    mode_rb_gb_->setLayout(modeLayout);

    base_layout_->addWidget(mode_rb_gb_,1,1);
    base_layout_->addWidget(readfile_pb_,1,2);

    base_layout_->addWidget(submit_pb_,2,1);

    base_layout_->addWidget(result_l_,3,0);
    base_layout_->addWidget(result_te_,3,1,1,2);

    base_layout_->addWidget(reset_pb_,4,1);

    // Set the window layout to the created layout

    setLayout(base_layout_);

    // Connect signals and slots
    connect(reset_pb_,  &QPushButton::clicked, this, &mainWidget::reset);
    connect(submit_pb_, &QPushButton::clicked, this, &mainWidget::processResult);
    connect(readfile_pb_, &QPushButton::clicked, this, &mainWidget::readFile);
}


void mainWidget::reset(){
    expression_te_->clear();
    interp_rb_->setChecked(false);
    pretty_print_rb_->setChecked(false);
    result_te_->clear();
}

void mainWidget::processResult(){
    try{
        QString input_text = expression_te_->toPlainText();
        std::string str_to_be_parsed = input_text.toUtf8().constData();
        PTR(Expr)input = parse_str(str_to_be_parsed);
        std::string result_string = "";
        if (interp_rb_->isChecked()) { // Handle "Interp" radio button selected
            PTR(Val)value = input->interp(Env::empty);
            result_string = value->to_string();
        } else if (pretty_print_rb_->isChecked()) { // Handle "Pretty Print" radio button selected
            result_string = input->to_pretty_string();
        }
        QString result_to_display = QString::fromStdString(result_string);
        result_te_->setText(result_to_display);
    } catch (std::runtime_error &e) {
        std::string error = e.what();
        QString error_to_display = QString::fromStdString(error);
        result_te_->setText(error_to_display);
    }
}

void mainWidget::readFile(){
    try{
        QString defaultDir = QDir::currentPath();
        QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), defaultDir , tr("Text Files (*.txt)"));
        if (!fileName.isEmpty()) {
            // Do something with the selected file
            QFile file(fileName);
            if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                result_te_->setText("Failed to open " + fileName);
                return;
            }
            QTextStream in(&file);
            QString contents = in.readAll();
            file.close();
            expression_te_->setText(contents);
        }
    }catch (std::runtime_error &e) {
        std::string error = e.what();
        QString error_to_display = QString::fromStdString(error);
        result_te_->setText(error_to_display);
    }
}
