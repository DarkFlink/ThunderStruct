#ifndef MYQDATASTRUCTURE_H
#define MYQDATASTRUCTURE_H

#include <QString>

#include <Assets/DataStructures/MQueues/mergequeue.h>

class MyQDataStructure
{
public:
    MyQDataStructure();
    QString &UniqueName();
    QString& StructName();

    void setData(const QString&, const QString&);

protected:
    QString mUniqueName;
    QString mStructName;
};

template <class TYPE>
class MyQMergeQueue : public MyQDataStructure
{
public:
    MyQMergeQueue() { mStructName = "MergeQueue"; }
    MyQMergeQueue(QString& name) : MyQMergeQueue() { mUniqueName = name; }

    MergeQueue<TYPE> mQueue;
};

#endif // MYQDATASTRUCTURE_H
