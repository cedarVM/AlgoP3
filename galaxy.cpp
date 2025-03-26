#include <stdio.h>
#include <vector>

/*
 * Author: Matthew Louden
 *
 * Description: 
 *
 * Notes:
 *  Questions of implementation
 *    Should findRep() return a dominion or a set
 *    - a dominion
 *    disjoint
 *      should handle setting up pointers
 *      call setRep
 *      no findRep?
 *
 *   Now how did Gallagher go about this?
 *   dominion
 *    setRep
 *    findRep
 *    findSet
 *
 *   disjoint
 *    union (+)
 *    adjoinMember(dominion)
 *
 *  Extension implementation
 *    dominion
 *    disjoint extends dominion
 *      +rank
 *
 */

using namespace std;

class disjoint;
class dominion;

class disjoint {
  public:
    disjoint(dominion *represent) : representative(represent), rank(1) {};
    disjoint getRep(void);
    disjoint operator+(disjoint &set1);
  private:
    dominion *representative;
    int rank;
};

class dominion {
  public:
    disjoint findSet(void);
    void setRep(dominion *rep);
  private:
    void compressChain(void);
    dominion *representativeChain;
};

disjoint disjoint::operator+(disjoint &adjunct) {
return adjunct;
};

int main (int argc, char **argv) {
  // three dimensional matrix of dominions
dominion a = dominion();
(*(new disjoint(&a))) + (*(new disjoint(&a)));
}
