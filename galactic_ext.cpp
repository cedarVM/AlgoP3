#include <string.h>
#include <stdio.h>
#include <vector>
#include <queue>

/*
 * Architecture Mar 24th
 *
 * Stuff we might expect from cachning:
 *
 * Tag, indexes and data oh my
 *
 * Consider:
 *  [ Tag ]  [ Validation ]  [ data ]
 *                           [cacheline 4bytes]
 *  Tag index word (2 bits)            | | | |
 *            \==================>   -[  MUX  ]
 *                      ^                 |
 *                      |                 V
 *                      |              [data]
 *  From [Tag][index][word]
 *        31   11..2  1 0
 *  Index is like column selection on cache line
 *
 */

/*
 * Algorithms Mar 25th
 *
 * Single source shortest paths and relaxing behavior
 * Topological sort greatly reduces time to find single shortest path
 * Agnostic of starting node for topological sort,
 * the list of nodes generated will allow us to perform
 * a single walk through the SSSP algorithm and guarantee
 * that we have sufficiently relaxed all nodes
 *
 * - only works for Directed Acyclic Graphs
 * - reduces our runtime to O(V + E) instead of Bellman-Forde's O(EV)
 *
 * Remember: Toplogical Sort sorts end (closing times) for a node using DFS
 *
 */

/*
 * Difference Constraints
 * Looks like Gaussian matrices
 *  Label each variable as node and each less-than inequality between variable
 *  be the weight of a directed edge (node2 -> node1 = var2 - var1)
 *  Create node var0 that points into all nodes with edges weighted 0.
 *
 * All-pairs shortest paths
 *  
 *
 */

/*
2 2 3 9
2 4 5
3 6 8 10
1 7
1 2
1 11
1 9
1 1
1 0
1 3

(or)

2 2 3 3
4 0 1 2 3
4 4 5 6 7
4 8 9 10 11
*/


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
  // distinguish adjoin as set or member
  // if set, add ranks together ; if member add 1 to rank and move on
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

priority_queue<set *>adjacencies = priority_queue<set *>();

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
        galaxy[*x][*y][*z] ? adjacencies.push((set *)galaxy[*x][*y][*z]->findRep()) : (void)0;
        }
      monarchies[i][j]->xyz[axis]+=2;
        if (monarchies[i][j]->xyz[axis] < space.xyz[axis]) {
        galaxy[*x][*y][*z] ? adjacencies.push((set *)galaxy[*x][*y][*z]->findRep()) : (void)0;
        }
      monarchies[i][j]->xyz[axis]-=1;

        if (adjacencies.size() == 0) {
        // make new set object and place into galaxy
        } else {
        // make new member object
        // run through queue and union all in order, leaving the member object for last
        // also update rank of first off queue
        }

      }
    printf("done\n");
    delete monarchies[i][j];
    }
  }

}

