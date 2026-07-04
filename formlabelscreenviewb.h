#ifndef FORMLABELSCREENVIEWB_H
#define FORMLABELSCREENVIEWB_H

#include <QWidget>

namespace Ui { class FormLabelScreenViewB; }

class FormLabelScreenViewB : public QWidget
{
    Q_OBJECT

public:
    explicit FormLabelScreenViewB(QWidget *parent = nullptr);
    ~FormLabelScreenViewB();

private:
    Ui::FormLabelScreenViewB *ui;
};

#endif // FORMLABELSCREENVIEWB_H
