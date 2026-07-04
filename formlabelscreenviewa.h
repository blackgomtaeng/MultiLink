#ifndef FORMLABELSCREENVIEWA_H
#define FORMLABELSCREENVIEWA_H

#include <QWidget>
#include <QList>
#include <QResizeEvent>
#include <QIcon>
#include <QInputDialog>
#include <QTabBar>

namespace Ui { class FormLabelScreenViewA; }

class FormLabelScreenViewA : public QWidget
{
    Q_OBJECT

public:
    explicit FormLabelScreenViewA(QWidget *parent = nullptr);
    ~FormLabelScreenViewA();

protected:
    void resizeEvent(QResizeEvent *event) override;  // 윈도우 크기 변경 시 비율 유지

private:
    Ui::FormLabelScreenViewA *ui;

    QList<int> *sizes;         // splitter 비율용 포인터
    QList<QWidget*> *tabList;  // 생성된 탭들을 관리하는 리스트
    QWidget *plusTab;          // + 탭
    int tabCounter;            // Tab 이름 증가용 카운터
};

#endif // FORMLABELSCREENVIEWA_H
