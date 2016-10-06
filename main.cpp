#include "trees/interval_tree.h"
#include <vector>
#include <algorithm>

using namespace std;

struct event {
    int id, x; // Index/coordinate of rectangle
    bool type; // Type of event: 0 = Lower-left ; 1 = Upper-right
    event() {};
    event(int id, int type, int x) : id(id), type(type), x(x) {};
};

struct rect {
    int llx, lly, urx, ury;
    int index;
    rect(int x1, int y1, int x2, int y2) : llx(x1), lly(y1), urx(x2), ury(y2) {}
};

bool compare_event(const event &a, const event &b) 
{ 
    return a.x < b.x
           || (a.x==b.x && a.type < b.type); //type 0 event should be handled first
}

void rectIntersect(const vector<rect*> &rects)
{
    int i = 0, j = 0;
    int size = rects.size();

    vector<event> events;
    events.resize(size*2);

    rect *p;
    for(i=0; i<size; i++)
    {
        p = rects[i];
        p->index = i;

        events[2*i] = event(i, 0, p->llx);
        events[2*i+1] = event(i, 1, p->urx);
    }

    sort(events.begin(), events.end(), compare_event);

    Interval * interv;
    IntervalTreeNode *nodes[size];
    IntervalTree * tree = new IntervalTree();
    vector<int> result, n;
    result.reserve(100);
    for(i=0; i<size*2; i++)
    {
        if(events[i].type==0)
        {
            p = rects[events[i].id];
            
            tree->Enumerate(p->lly, p->ury, result);
            for(j=0; j<result.size(); j++)
            {
                printf("%d intersects %d\n", p->index, result[j]);
            }
            interv = new Interval(p->lly, p->ury, p->index);
            nodes[p->index] = tree->Insert(interv);
        }
        else
        {
            tree->DeleteNode(nodes[events[i].id]);
        }
    }
}

int main()
{
    //test
    vector<rect*> rects;
    srand(0);
    for(int i=0; i<10; i++)
    {
        int x = rand()%15;
        int y = rand()%15;
        rect *r = new rect(x, y, x+2, y+3);
        rects.push_back(r);
    }
    rectIntersect(rects);
    return 0;
}