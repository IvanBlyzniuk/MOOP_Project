#ifndef ISCREENCHANGEABLE_H
#define ISCREENCHANGEABLE_H

//#include "qtmetamacros.h"

#include <QWidget>
class IScreenChangeable
{
public:
    IScreenChangeable() {};
    virtual ~IScreenChangeable() {};
signals:
    void changePage(int page);
};

#endif // ISCREENCHANGEABLE_H
