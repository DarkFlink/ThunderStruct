#include "aboutdatastructure.h"
#include "ui_aboutdatastructure.h"

AboutDataStructure::AboutDataStructure(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDataStructure)
{
    ui->setupUi(this);
}

AboutDataStructure::~AboutDataStructure()
{
    delete ui;
}

void AboutDataStructure::SetMergeQueueDefinition()
{
    AboutDataStructure::setWindowTitle("MergeQueue");
    ui->LabelStructType->setText("MergeQueue");
    ui->TextBrowserStructDesc->setText("    TreapNode - class that implements node of Treap. Treap - abstract data structure, that unions attributes of"
                                    "    binary search tree, and binary heap (so, you can see that: Tree + Heap = Treap). It has splitting on storable"
                                    "    data: keys, user data and priorities (well, if you don't want to store any user information of custom type, you store only keys)"
                                    "    So, that data structure works like binary search tree and binary heap at the same time."
                                    "\n\n"
                                    "    By the way, this implementation of TreapNode hasn't explicit key, implicit index substitutes that key."
                                    "    In a nutshell that's like array element index."
                                    "    We don't store that index in nodes, but we can calculate it for each node, using sizeof subtrees of this node."
                                    "    NB: In-order detour prints out the sequence of nodes in ascenting order of indexes."
                                    "");
    ui->TextBrowserOperComplexity->setText("Merge:  lb(N)\n"
                                           "Split:  lb(N)\n"
                                           "Push:   lb(N)\n"
                                           "Pop:    lb(N)\n\n"
                                           "Important note: the complexity of these operations depends on height of treap. The height of treap"
                                           "in general case just about 4lb(N), but that constant don't have so much influence on operation complexity,"
                                           "while you don't try to create a treap of galactic measure");
}
