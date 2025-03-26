template<typename T>
class prio_queue {
  public:
    prio_queue(T *, int);
    void enqueue(T *);
    T *dequeue(void);
    int size(void);
};
