#ifndef MERGEQUEUE_H
#define MERGEQUEUE_H

#include "implicit_treap_node.h"

template <class TYPE>
class MergeQueue
{
public:
    MergeQueue();
    ~MergeQueue();

    void Push(TYPE* data);
    void Pop();
    void Merge(MergeQueue& queue);
    void Split(MergeQueue& q1, MergeQueue& q2, size_t index);

    TYPE& Top();
    void DisplayTreap(std::string&);
    void PrintData(std::string&);

    bool Empty();
    size_t Size();
private:
    ImplicitTreapNode<TYPE>* mRoot;
};

#endif // MERGEQUEUE_H

template<class TYPE>
MergeQueue<TYPE>::MergeQueue() {    mRoot = nullptr;    }

template<class TYPE>
MergeQueue<TYPE>::~MergeQueue() {    ImplicitTreapNode<TYPE>::Clear(mRoot);    }

template<class TYPE>
void MergeQueue<TYPE>::Push(TYPE* data)
{
    if(Empty())
    {
        mRoot = new ImplicitTreapNode<TYPE>(data);
        return;
    }
    mRoot = mRoot->Insert(data, 0);
}

template<class TYPE>
void MergeQueue<TYPE>::Pop()
{
    if(Empty())
        throw std::out_of_range("Call POP operation in empty queue");
    mRoot = mRoot->Remove(ImplicitTreapNode<TYPE>::SizeOf(mRoot)-1);
}

template<class TYPE>
void MergeQueue<TYPE>::Split(MergeQueue &q1, MergeQueue &q2, size_t index)
{
    if(index >= Size())
        throw std::out_of_range("Invalid implicit index");
    ImplicitTreapNode<TYPE>::Split(mRoot, index, q1.mRoot, q2.mRoot);
    mRoot = nullptr;
}

template<class TYPE>
TYPE &MergeQueue<TYPE>::Top()
{
    if(Empty())
        throw std::out_of_range("Call TOP operation in empty queue");
    return mRoot->GetData(ImplicitTreapNode<TYPE>::SizeOf(mRoot)-1);
}

template<class TYPE>
void MergeQueue<TYPE>::DisplayTreap(std::string& out)
{
    ImplicitTreapNode<TYPE>::Display(mRoot, out);
}

template<class TYPE>
void MergeQueue<TYPE>::PrintData(std::string &out)
{
    ImplicitTreapNode<TYPE>::PrintData(mRoot, out);
}

template<class TYPE>
void MergeQueue<TYPE>::Merge(MergeQueue<TYPE>& queue)
{
    mRoot = ImplicitTreapNode<TYPE>::Merge(queue.mRoot, mRoot);
    queue.mRoot = nullptr;
}

template<class TYPE>
bool MergeQueue<TYPE>::Empty() {    return !mRoot ? true : false;    }

template<class TYPE>
size_t MergeQueue<TYPE>::Size() {    return ImplicitTreapNode<TYPE>::SizeOf(mRoot);    }
