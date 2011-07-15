#ifndef INPUTSCENE_H
#define INPUTSCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsSimpleTextItem>
#include <QDebug>
#include <QGraphicsSceneMouseEvent> 
#include <QList> 
#include <QKeyEvent> 
#include <QDialog> 
#include <QTime> 

class InputScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit InputScene(QObject *parent = 0, QList<QString> *chars = 0, bool iterable = false);
    ~InputScene();


signals:

public slots:
private:

    QGraphicsSimpleTextItem *commandText;
	QGraphicsSimpleTextItem *xText;
	QGraphicsSimpleTextItem *responseText;
	QGraphicsEllipseItem *circle;
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
	QList<QString> *chars, *charsCopy;
	QObject *parent;
	int count;
	QChar actual;
	bool firstAction;
	QTime lastTime;
	QTime firstActionTime;
	int actionCount, wrong;
	bool withControl, withShift;
	bool controlPressed, shiftPressed;
	bool click;
	int yMouse, xMouse;
	int clickCount;
	int distanceSum;
	bool iterable;
	void initialize();
};

#endif // INPUTSCENE_H
