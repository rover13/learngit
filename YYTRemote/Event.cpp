#include <QEvent>
#include "Event.h"
#include <QApplication>
Event::Event( E_CustomEvent eventType, int errCode, const std::string& szDesc )
	:QEvent( (Type)eventType )
{
	this->code = errCode;
	this->desc = szDesc;
}

void postCusEvent( QObject *receiver, Event* event )
{
	QApplication::postEvent( receiver, event );
}