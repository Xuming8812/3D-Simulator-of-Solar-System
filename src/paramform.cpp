#include "paramform.h"
#include "ui_paramform.h"

ParamForm::ParamForm(QWidget *parent, AstronmicalObject *astronmical_object) :
    QDialog(parent),
    ui(new Ui::ParamForm)
{
    this->astronmicalObject = astronmical_object;
    ui->setupUi(this);
    ui->editRadius->setText(QString::number(astronmicalObject->getRadius()));
    ui->editRotation->setText(QString::number(astronmicalObject->getSpeedRotation()));
    ui->editRevolution->setText(QString::number(astronmicalObject->getSpeedRevolution()));
}

ParamForm::~ParamForm()
{
    delete ui;
}

void ParamForm::on_buttonBox_accepted()
{
    astronmicalObject->setRadius(ui->editRadius->text().toFloat());
}
