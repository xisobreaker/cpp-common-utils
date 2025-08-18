// =====================================================================================
//  Copyright (C) 2025 by Jiaxing Shao. All rights reserved

//  文 件 名:  free_queue.h
//  作    者:  Jiaxing Shao, 980853650@qq.com
//  创建时间：  2025-08-18 13:16
//  描    述:
// =====================================================================================

#include <memory>

namespace xiso {
namespace container {

template <typename T>
class LockFreeQueue
{
private:
    struct Node {
        std::shared_ptr<T>  data;
        std::atomic<Node *> next;

        Node() : next(nullptr){};
        Node(const T &d) : data(std::make_shared<T>(d)), next(nullptr){};
    };

public:
    LockFreeQueue()
    {
        Node *init_node = new Node();
        head_.store(init_node);
        tail_.store(init_node);
    }

    ~LockFreeQueue()
    {
        while (Node *old_head = head_.load()) {
            head_.store(old_head->next.load());
            delete old_head;
        }
    }

    bool empty()
    {
        return head_ == tail_;
    }

    bool enqueue(T new_data)
    {
        Node *nil      = nullptr;
        Node *new_node = new Node(new_data);
        Node *old_tail = tail_.load();
        if (old_tail->next.compare_exchange_strong(nil, new_node)) {
            tail_.compare_exchange_strong(old_tail, new_node);
            return true;
        }

        delete new_node;
        return false;
    }

    void safe_enqueue(T new_data)
    {
        for (;;) {
            if (enqueue(new_data))
                break;
        }
    }

    std::shared_ptr<T> dequeue()
    {
        Node *old_head = head_.load();
        Node *next     = old_head->next.load();
        if (next == nullptr)
            return nullptr;

        std::shared_ptr<T> res = next->data;
        head_.compare_exchange_strong(old_head, next);
        delete old_head;
        return res;
    }

private:
    std::atomic<Node *> head_;
    std::atomic<Node *> tail_;
};

} // namespace container
} // namespace xiso