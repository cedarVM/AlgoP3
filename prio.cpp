template<typename T>
class prio_queue { // max heap implementation

  public:
    prio_queue(T *sentinel, int capacity);
    T *dequeue(void);
    void enqueue(T *element);
    int size(void);

  private:
    T **arr;
    int qsize;
    int capacity;

};

template<typename T>
prio_queue<T>::prio_queue(T *sentinel, int capacity) {
  qsize = 0;
  this->capacity = capacity;
  for (int i = 0; i < capacity; i++) {
  arr[i] = sentinel;
  }
}

template<typename T>
T *prio_queue<T>::dequeue(void) {

    if (!qsize) {
    return 0;
    }

  T *ret = arr[0];

  arr[0] = arr[qsize - 1];

  int child1 = 1;
  int child2 = 2;
  int parent_index = 0;

  T *parent;
  int greater_index;

    while ( *arr[parent_index] < *arr[child1] || *arr[parent_index] < *arr[child2] ) {
    greater_index = *arr[child1] < *arr[child2] ? child2 : child1; // choose greater for max heap
    parent = arr[parent_index];
    arr[parent_index] = arr[greater_index];
    arr[greater_index] = parent;

    parent_index = greater_index;
    child1 = parent_index * 2 + 1;
    child2 = parent_index * 2 + 2;
    }

  qsize--;
  return ret;
}

template<typename T>
void prio_queue<T>::enqueue(T *item) {
  char nonunique = 0;

  for (int i = 0; i < qsize; i++) {
  nonunique |= item == arr[i];
  }

  if (nonunique || qsize == capacity ) {
  return;
  }

  arr[qsize] = item;

  int child_index = qsize;
  int parent_index = ( child_index - 1 ) / 2;

  T *parent;

  while (*arr[parent_index] < *arr[child_index] && child_index != 0) {
  parent = arr[parent_index];
  arr[parent_index] = arr[child_index];
  arr[child_index] = parent;
  child_index = parent_index;
  parent_index = (child_index - 1) / 2;
  }

  qsize++;
  return;

}

template<typename T>
int prio_queue<T>::size(void) {
  return qsize;
}
