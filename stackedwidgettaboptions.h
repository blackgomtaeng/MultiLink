#ifndef STACKEDWIDGETTABOPTIONS_H
#define STACKEDWIDGETTABOPTIONS_H

#include <QStackedWidget>

namespace Ui { class StackedWidgetTabOptions; }

class StackedWidgetTabOptions : public QStackedWidget
{
    Q_OBJECT

public:
    explicit StackedWidgetTabOptions(QWidget *parent = nullptr);
    ~StackedWidgetTabOptions();

private:
    Ui::StackedWidgetTabOptions *ui;
};

#endif // STACKEDWIDGETTABOPTIONS_H
