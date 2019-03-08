#include <vector>
#include <algorithm>    // std::min
#include <memory>       // std::unique_ptr

class MyCircularQueue {
public:
    /** Initialize your data structure here. Set the size of the queue to be k. */
    MyCircularQueue(int k) : empty(true), start(0), end(0), container(k) {
    }

    /** Insert an element into the circular queue. Return true if the operation is successful. */
    bool enQueue(int value) {
        if (isFull())
            return false;
        container[end] = value;
        end = increment(end);
        empty = false;
        return true;
    }

    /** Delete an element from the circular queue. Return true if the operation is successful. */
    bool deQueue() {
        if (isEmpty())
            return false;
        start = increment(start);
        if (start == end)
            empty = true;
        return true;
    }

    /** Get the front item from the queue. */
    int Front() {
        if (isEmpty())
            return -1;
        return container[start];
    }

    /** Get the last item from the queue. */
    int Rear() {
        if (isEmpty())
            return -1;
        return container[decrement(end)];
    }

    /** Checks whether the circular queue is empty or not. */
    bool isEmpty() {
        return empty;
    }

    /** Checks whether the circular queue is full or not. */
    bool isFull() {
        return !empty && (start == end);
    }
private:
    bool empty;
    int start, end;
    std::vector<int> container;

    inline int increment(int p)
    {
        return (p + 1) % container.size();
    }

    inline int decrement(int p)
    {
        return (p + container.size() - 1) % container.size();
    }
};


int main()
{

    std::unique_ptr<MyCircularQueue> obj(new MyCircularQueue(6));
    bool success = obj->enQueue(6);
    int result = obj->Rear();
    result = obj->Rear();
    int result = obj->deQueue();
    success = obj->enQueue(5);
    result = obj->Rear();
    success = obj->deQueue();
    result = obj->Front();
    success = obj->deQueue();
    success = obj->deQueue();
    success = obj->deQueue();

    return 0;
}
