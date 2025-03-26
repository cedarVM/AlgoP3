#include <string.h>
#include <stdio.h>
#include "prio.cpp"
#include <vector>
#include <queue>

using namespace std;

union coord {
  struct {
  int xyz[3];
  };
  struct {
  int x; // n
  int y; // m
  int z; // k
  };
};

union coord *convert(int singleton, int boundX, int boundY) {
return new union coord (
        {
        .xyz = {
                singleton % boundX,
                (singleton / boundX) % boundY,
                singleton  / (boundX * boundY)
                }
       });
}

class setUnit { // base class for set functionality

  public:
    setUnit(setUnit *arg) { rep = arg; };
    setUnit() {};
    setUnit *findRep();
    void setRep(setUnit *in) { rep = in; };
  protected:
    setUnit *rep;

};

class set : public setUnit { // actual set (is really just a representative)

  public:
    // makeset and union+
    set() : rank(1) { setUnit(this); };
    setUnit *operator+(setUnit *a);
    void makeset();

    // the following allows us to create priority queue
    bool operator<(set &a) { return this->rank < a.rank; };
  protected:
    int rank; // heuristic

};

class member : public setUnit { // set members
  public:
    member(setUnit *repr) { rep = repr; };
};

setUnit *setUnit::findRep() { // recursively call until we get rep
  return
    this == rep ?            // are we representing ourselves?
      this      :            // return us
      rep = rep->findRep();  // return them (and then compress)
}

void set::makeset() { // is necessary on new'ing
rep = this;
}

setUnit *set::operator+(setUnit *adjoin) {
  set    *head =    (set *)adjoin; // can we use set members?
  member *body = (member *)adjoin;

  if (!adjoin) {
  return this;
  }

  if (adjoin == adjoin->findRep()) {
  rank += head->rank; // I don't think this is possible
  }

  adjoin->setRep(this);
  return this;
}

int main () {
int n, m, k;
int monarch_count;
int dominion_count;
union coord space;
int *x, *y, *z;
int galaxy_size = 1;
int set_number = 0;
int broken = 0;

set *handle;

prio_queue<set>adjacencies = prio_queue<set>(new set(), 16);

scanf("%d %d %d %d\n", &space.x, &space.y, &space.z, &monarch_count);
vector<union coord *>monarchies[monarch_count];
setUnit *galaxy[space.x][space.y][space.z];

  for (int i = 0; i < 3; i++) {
    galaxy_size *= space.xyz[i];
  }

memset((void *)galaxy, 0, galaxy_size * sizeof(void *));

  for (int i = 0; i < monarch_count; i++) {
  scanf("%d", &dominion_count);
    for (int j = 0; j < dominion_count; j++) {
    scanf("%d", &n);
    monarchies[i].push_back( convert(n, space.x, space.y) );
    }
  }

// run through monarchies in reverse and for each monarchy add dominions to galaxy

  for (int i = monarch_count - 1; i >= 0; i--) {
    for (int j = 0; j < monarchies[i].size(); j++) {
    x = &monarchies[i][j]->x;
    y = &monarchies[i][j]->y;
    z = &monarchies[i][j]->z;
      for (int axis = 0; axis < 3; axis++) {
      monarchies[i][j]->xyz[axis]-=1;
        if (monarchies[i][j]->xyz[axis] != -1) {
        galaxy[*x][*y][*z] ? adjacencies.enqueue((set *)galaxy[*x][*y][*z]->findRep()) : (void)0;
        }
      monarchies[i][j]->xyz[axis]+=2;
        if (monarchies[i][j]->xyz[axis] < space.xyz[axis]) {
        galaxy[*x][*y][*z] ? adjacencies.enqueue((set *)galaxy[*x][*y][*z]->findRep()) : (void)0;
        }
      monarchies[i][j]->xyz[axis]-=1;
      }

      if (adjacencies.size() == 0) {
      set_number++;
      handle = new set();
      handle->makeset();
      galaxy[*x][*y][*z] = (setUnit *)handle;
      } else {
      set_number -= adjacencies.size() - 1;
      handle = adjacencies.dequeue();
        while (adjacencies.size()) {
        handle = (set *)( *handle + (setUnit *)adjacencies.dequeue() );
        }
        handle = (set *)( *handle + galaxy[*x][*y][*z] );
      }
    delete monarchies[i][j];
    }
  printf("sets: %d\n", set_number);
  broken += set_number > 1;
  }
  printf("%d\n", broken);

}

