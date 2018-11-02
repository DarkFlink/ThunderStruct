#include "myqdatastructure.h"

MyQDataStructure::MyQDataStructure()
{
    mUniqueName = "None";
    mStructName = "None";
}

QString &MyQDataStructure::UniqueName()
{
    return mUniqueName;
}

QString &MyQDataStructure::StructName()
{
    return mStructName;
}

void MyQDataStructure::setData(const QString &name, const QString &type)
{
    mUniqueName = name;
    mStructName = type;
}
