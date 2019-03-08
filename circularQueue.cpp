#include <vector>
#include <algorithm>    // std::min
#include <memory>       // std::unique_ptr
#include <stdexcept>    // std::out_of_range exception
#include <iostream>     // std::cout, std::endl

template<typename T>
class MyCircularQueue {
public:
    /** Initialize your data structure here. Set the size of the queue to be k. */
    MyCircularQueue(int k) : empty(true), start(0), end(0), container(k) {
    }

    /** Insert an element into the circular queue. Return true if the operation is successful. */
    bool enQueue(T value) {
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
    T Front() {
        if (isEmpty())
            throw std::out_of_range("Front(): Circular queue is empty");
        return container[start];
    }

    /** Get the last item from the queue. */
    T Rear() {
        if (isEmpty())
            throw std::out_of_range("Rear(): Circular queue is empty");
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
    std::vector<T> container;

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
    try 
    {
        std::unique_ptr<MyCircularQueue<int>> obj(new MyCircularQueue<int>(6));
        bool success = obj->enQueue(6);
        int result = obj->Rear();
        result = obj->Rear();
        success = obj->deQueue();
        success = obj->enQueue(5);
        result = obj->Rear();
        success = obj->deQueue();
        result = obj->Front();
        success = obj->deQueue();
        success = obj->deQueue();
        success = obj->deQueue();
    }
    catch (std::exception e)
    {
        std::cout << e.what() << std::endl;
    }
    
    return 0;
}
