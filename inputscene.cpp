#include "inputscene.h"

#define ONE_SECOND 1000
InputScene::InputScene(QObject *parent, QList<QString> *chars, bool iterable) :
    QGraphicsScene(parent)
{
    //TODO: make iterable
	this->chars = chars;
	if (chars->isEmpty())
	{
		qDebug() << "empty chars at start";
		((QDialog*)parent)->close();
	}
    this->setSceneRect(1, 1, 600, 600);
    this->setBackgroundBrush( QBrush(Qt::black));
	this->parent = parent;
	this->circle = new QGraphicsEllipseItem((qreal)100, (qreal)100, (qreal)50, (qreal)50, 0, this);
	this->circle->setBrush(QBrush(QColor(Qt::red)));
	this->circle->setPos(0, 0);
    this->xText = new QGraphicsSimpleTextItem("x", 0, this);
    this->xText->setBrush(QBrush(QColor(Qt::green)));
    this->xText->setPos(100 + 22, 100 + 17);
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
    this->commandText = new QGraphicsSimpleTextItem("", 0, this);
    this->commandText->setBrush(QBrush(QColor(Qt::green)));
    this->commandText->setPos(200, 0);
    this->responseText = new QGraphicsSimpleTextItem("", 0, this);
    this->responseText->setBrush(QBrush(QColor(Qt::green)));
    this->responseText->setPos(200, 580);
    this->iterable = iterable;
    if (iterable)
        this->charsCopy = new QList<QString>(*chars);
    this->wrong = 0;
    this->clickCount = 0;
    this->distanceSum = 0;
	this->firstAction = true;
	this->actionCount = 0;
    this->initialize();
}

void InputScene::initialize()
{
	QString word;
	QString token = chars->takeFirst();
	this->withShift = false;
	this->withControl = false;
	this->click = false;
	this->actual = token[0];
	this->count = this->actual.digitValue() - 1;
	token = token.remove(0, 1);
	this->actual = token[0];
	if (this->actual == '^')
	{
		token = token.remove(0, 1);
		this->actual = token[0];
		this->withControl = true;
	}
	if (this->actual == 's' && token.length() > 1)
	{
		token = token.remove(0, 1);
		this->withShift = true;
		this->actual = token[0];
	}
	if (this->actual == 'p' && token.length() > 1)
	{
        this->click = true;
		this->xMouse = qrand() % 348 + 125;
		this->yMouse = qrand() % 348 + 125;
		this->circle->setPos(this->xMouse - 125, this->yMouse - 125);
		this->xText->setPos(this->xMouse - 3, this->yMouse - 11);
	}
    QString commandString;
    if (withShift)
    {
        commandString.append("shift ");
    }
    if (withControl)
    {
        commandString.append("control ");
    }
    if (click)
    {
        commandString.append("click");
    }
    else
    {
        commandString.append(this->actual);
    }
    this->commandText->setText(commandString);
	this->controlPressed = false;
	this->shiftPressed = false;
}

InputScene::~InputScene () { }

void InputScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	if (click)
	{
		QTime curTime = QTime::currentTime();
        int distance = (event->scenePos() - QPointF(xMouse, yMouse)).manhattanLength();
        if (distance < 50)
        {
            QString responseString = QString::number(100.0 - (distance / 50.0) * 100.0);
            responseString.append(" accuracy click");
            if (!firstAction)
            {
                responseString.append(" in ");
                responseString.append(QString::number(lastTime.msecsTo(curTime)));
                responseString.append(" millisecond");
            }
            responseText->setText(responseString);
            distanceSum += distance;
        } else
        {
            QString responseString = QString::number(0);
            responseString.append(" accuracy click");
            if (!firstAction)
            {
                responseString.append(" in ");
                responseString.append(QString::number(lastTime.msecsTo(curTime)));
                responseString.append(" millisecond");
            }
            responseText->setText(responseString);
            wrong++;
            distanceSum += 50;
        }
        if (firstAction)
        {
            firstActionTime = curTime;
        }
        firstAction = false;
		lastTime = curTime;
        clickCount++;
        actionCount++;
        if (chars->isEmpty() && count == 0)
        {
            if (iterable)
            {
                chars = new QList<QString>(*charsCopy);
                initialize();
            }
            else
            {
                if (actionCount > 1)
                    qDebug() << "apm" << (60000.0 / (float)firstActionTime.msecsTo(curTime)) * actionCount;
                if (clickCount > 0)
                    qDebug() << "accuracy" << 100 - (distanceSum * 100 / (50 * clickCount));
                qDebug() << wrong << " missed";
                ((QDialog*)parent)->close();
            }
        }
        else 
        {
            if (count == 0)
            {
                click = false;
                withShift = false;
                withControl = false;
                QString token = chars->takeFirst();
                actual = token[0];
                count = actual.digitValue() - 1;
                token = token.remove(0, 1);
                actual = token[0];
                if (actual == '^')
                {
                    token = token.remove(0, 1);
                    actual = token[0];
                    withControl = true;
                }
                if (actual == 's' && token.length() > 1)
                {
                    token = token.remove(0, 1);
                    withShift = true;
                    actual = token[0];
                }
                if (actual == 'p' && token.length() > 1)
                {
                    click = true;
                    xMouse = qrand() % 348 + 125;
                    yMouse = qrand() % 348 + 125;
                    circle->setPos(xMouse - 125, yMouse - 125);
                    xText->setPos(xMouse - 3, yMouse - 11);
                }
                QString commandString;
                if (withShift)
                {
                    commandString.append("shift ");
                }
                if (withControl)
                {
                    commandString.append("control ");
                }
                if (click)
                {
                    commandString.append("click");
                }
                else
                {
                    commandString.append(actual);
                }
                commandText->setText(commandString);
            } else
            {
                count--;
                xMouse = qrand() % 348 + 125;
                yMouse = qrand() % 348 + 125;
                circle->setPos(xMouse - 125, yMouse - 125);
                xText->setPos(xMouse - 3, yMouse - 11);
            }
        }
	}
}

void InputScene::keyPressEvent(QKeyEvent *event)
{
	switch (event->key())
	{
	case Qt::Key_Escape:
        if (actionCount > 1)
            qDebug() << "apm" << (60000.0 / (float)firstActionTime.msecsTo(QTime::currentTime())) * actionCount;
        if (clickCount > 0)
            qDebug() << "accuracy" << 100 - (distanceSum * 100 / (50 * clickCount));
        qDebug() << wrong << " missed";
		((QDialog*)parent)->close();
		break;
	case Qt::Key_Control:
		controlPressed = true;
		break;
	case Qt::Key_Shift:
		shiftPressed = true;
		break;
	default:
		if (!click)
		{
            QString text = event->text();
            QTime curTime = QTime::currentTime();
            QChar pressedKey = (QChar)QKeySequence(event->key()).toString().toLower()[0];
            if (actual == pressedKey && !((!withControl && controlPressed) || (withControl && !controlPressed)) && !((withShift && !shiftPressed) || (!withShift && shiftPressed)))
            {
                QString responseString("Good key");
                if (!firstAction)
                {
                    responseString.append(" in ");
                    responseString.append(QString::number(lastTime.msecsTo(curTime)));
                    responseString.append(" millisecond");
                }
                responseText->setText(responseString);
            } else
            {
                QString responseString("Bad key");
                if (!firstAction)
                {
                    responseString.append(" in ");
                    responseString.append(QString::number(lastTime.msecsTo(curTime)));
                    responseString.append(" millisecond");
                }
                responseText->setText(responseString);
                wrong++;
                if (!chars->isEmpty())
                {
                    QString token = chars->first();
                    QChar next = (QChar)token[0];
                    int nextCount = next.digitValue() - 1;
                    bool nextWithControl = false;
                    bool nextWithShift = false;
                    token = token.remove(0, 1);
                    next = token[0];
                    if (next == '^')
                    {
                        token = token.remove(0, 1);
                        nextWithControl = true;
                        next = token[0];
                    }
                    if (actual == 's' && token.length() > 1)
                    {
                        token = token.remove(0, 1);
                        nextWithShift = true;
                        next = token[0];
                    }
                    if (next == pressedKey)
                    {
                        actual = next;
                        withControl = nextWithControl;
                        withShift = nextWithShift;
                        count = nextCount;
                        chars->removeFirst();
                        QString commandString;
                        if (withShift)
                        {
                            commandString.append("shift ");
                        }
                        if (withControl)
                        {
                            commandString.append("control ");
                        }
                        commandString.append(actual);
                        commandText->setText(commandString);
                    }
                }
            }
            actionCount++;
            if (firstAction)
            {
                firstActionTime = curTime;
            }
            lastTime = curTime;
            firstAction = false;
            if (chars->isEmpty() && count == 0)
            {
                if (iterable)
                {
                    chars = new QList<QString>(*charsCopy);
                    initialize();
                }
                else
                {
                    if (actionCount > 1)
                        qDebug() << "apm" << (60000.0 / (float)firstActionTime.msecsTo(curTime)) * actionCount;
                    if (clickCount > 0)
                        qDebug() << "accuracy" << 100 - (distanceSum * 100 / (50 * clickCount));
                    qDebug() << wrong << " missed";
                    ((QDialog*)parent)->close();
                }
            }
            else
            {
                if (count == 0)
                {
                    withShift = false;
                    withControl = false;
                    QString token = chars->takeFirst();
                    actual = token[0];
                    count = actual.digitValue() - 1;
                    token = token.remove(0, 1);
                    actual = token[0];
                    if (actual == '^')
                    {
                        token = token.remove(0, 1);
                        actual = token[0];
                        withControl = true;
                    }
                    if (actual == 's' && token.length() > 1)
                    {
                        token = token.remove(0, 1);
                        withShift = true;
                        actual = token[0];
                    }
                    if (actual == 'p' && token.length() > 1)
                    {
                        click = true;
                        xMouse = qrand() % 348 + 125;
                        yMouse = qrand() % 348 + 125;
                        circle->setPos(xMouse - 125, yMouse - 125);
                        xText->setPos(xMouse - 3, yMouse - 11);
                    }
                    QString commandString;
                    if (withShift)
                    {
                        commandString.append("shift ");
                    }
                    if (withControl)
                    {
                        commandString.append("control ");
                    }
                    if (click)
                    {
                        commandString.append("click");
                    }
                    else
                    {
                        commandString.append(actual);
                    }
                    commandText->setText(commandString);
                }
                else
                {
                    count--;
                }
            }
		}
	}
}

void InputScene::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Control:
        controlPressed = false;
        break;
    case Qt::Key_Shift:
        shiftPressed = false;
        break;
    }
}
