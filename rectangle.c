#include <stdio.h>
#include <stdlib.h>
struct _rectangle_t {
    int x;
    int y;
    int width;
    int height;
};
typedef struct _rectangle_t rectangle_t;

rectangle_t canonicalize(rectangle_t r) {
    if (r.width < 0) {
        r.x += r.width;
        r.width = abs(r.width);
    }
    if (r.height < 0) {
        r.y += r.height;
        r.height = abs(r.height);
    }
    return r;
}

int relationship(int met1, int met2) {
    if (met1 < met2) {
        return 0;
    }
    else if (met1 > met2) {
        return 1;
    }
    else {
        return 2;
    }
}

struct _rec_inter {
    int coordinate;
    int metric;
};
typedef struct _rec_inter rec_inter;

rec_inter intersection_1d(int r1_coord, int r2_coord, int r1_met, int r2_met) {
    rec_inter ri;
    if (r1_coord < r2_coord && r2_coord < r1_coord + r1_met) {
        if (r1_coord < r2_coord + r2_met && r2_coord + r2_met < r1_coord + r1_met) {
            ri.metric = r2_met;
        }
        else {
            ri.metric = r1_coord + r1_met - r2_coord;
        }
        ri.coordinate = r2_coord;
    }
    else if (r1_coord < r2_coord + r2_met && r2_coord + r2_met < r1_coord + r1_met) {
        ri.metric = r2_coord + r2_met - r1_coord;
        ri.coordinate = r1_coord;
    }
    else {
        ri.metric = r1_met;
        ri.coordinate = r1_coord;
    }
    return ri;
}

rectangle_t intersection(rectangle_t r1, rectangle_t r2) {
    r1 = canonicalize(r1);
    r2 = canonicalize(r2);
    int id = 1;
    int id_;
    int eq_fl;
    int lmets[4] = {r1.x + r1.width, r2.x + r2.width, r1.y + r1.height, r2.y + r2.height};
    int rmets[4] = {r2.x, r1.x, r2.y, r1.y};
    for (int i = 0; i < 4; i++) {
        id_ = relationship(lmets[i], rmets[i]);
        id = id * id_;
        if (id_ == 2) {
            eq_fl = i;
        }
    }
    if (id == 1) {
        //area overlap
        rec_inter h_inter;
        rec_inter v_inter;
        int r1_coords[2] = {r1.x, r1.y};
        int r2_coords[2] = {r2.x, r2.y};
        int r1_mets[2] = {r1.width, r1.height};
        int r2_mets[2] = {r2.width, r2.height};
        for (int i = 0; i < 2; i++) {
            if (i == 0) {
                h_inter = intersection_1d(r1_coords[i], r2_coords[i], r1_mets[i], r2_mets[i]);
            }
            else {
                v_inter = intersection_1d(r1_coords[i], r2_coords[i], r1_mets[i], r2_mets[i]);
            }
        }
        r1.x = h_inter.coordinate;
        r1.y = v_inter.coordinate;
        r1.width = h_inter.metric;
        r1.height = v_inter.metric;
    }
    else if (id == 2) {
        rec_inter edge;
        switch(eq_fl) {
            case 0: {
                edge = intersection_1d(r1.y, r2.y, r1.height, r2.height);
                r1.x = r2.x;
                r1.y = edge.coordinate;
                r1.width = 0;
                r1.height = edge.metric;
                break;
            }
            case 1: {
                edge = intersection_1d(r2.y, r1.y, r2.height, r1.height);
                r1.x = r1.x;
                r1.y = edge.coordinate;
                r1.width = 0;
                r1.height = edge.metric;
                break;
            }
            case 2: {
                edge = intersection_1d(r1.x, r2.x, r1.width, r2.width);
                r1.x = edge.coordinate;
                r1.y = r2.y;
                r1.width = edge.metric;
                
            }
            case 3: {
                edge = intersection_1d(r2.x, r1.x, r2.width, r1.width);
                r1.x = edge.coordinate;
                r1.y = r1.y;
                r1.width = edge.metric;
                r1.height = 0;
                break;
            }
        }
    }
    else {
        r1.width = 0;
        r1.height = 0;
    }
    return r1;
}

//You should not need to modify any code below this line
void printRectangle(rectangle_t r) {
  r = canonicalize(r);
  if (r.width == 0 && r.height == 0) {
    printf("<empty>\n");
  }
  else {
    printf("(%d, %d) to (%d, %d)\n", r.x, r.y, r.x + r.width, r.y + r.height);
  }
}

int main(void) {
  rectangle_t r1;
  rectangle_t r2;
  rectangle_t r3;
  rectangle_t r4;

  r1.x = 2;
  r1.y = 3;
  r1.width = 5;
  r1.height = 6;
  printf("r1 is ");
  printRectangle(r1);

  r2.x = 4;
  r2.y = 5;
  r2.width = -5;
  r2.height = -7;
  printf("r2 is ");
  printRectangle(r2);

  r3.x = -2;
  r3.y = 7;
  r3.width = 7;
  r3.height = -10;
  printf("r3 is ");
  printRectangle(r3);

  r4.x = 0;
  r4.y = 7;
  r4.width = -4;
  r4.height = 2;
  printf("r4 is ");
  printRectangle(r4);

  //test everything with r1
  rectangle_t i = intersection(r1, r1);
  printf("intersection(r1, r1): ");
  printRectangle(i);

  i = intersection(r1, r2);
  printf("intersection(r1, r2): ");
  printRectangle(i);

  i = intersection(r1, r3);
  printf("intersection(r1, r3): ");
  printRectangle(i);

  i = intersection(r1, r4);
  printf("intersection(r1, r4): ");
  printRectangle(i);

  //test everything with r2
  i = intersection(r2, r1);
  printf("intersection(r2, r1): ");
  printRectangle(i);

  i = intersection(r2, r2);
  printf("intersection(r2, r2): ");
  printRectangle(i);

  i = intersection(r2, r3);
  printf("intersection(r2, r3): ");
  printRectangle(i);

  i = intersection(r2, r4);
  printf("intersection(r2, r4): ");
  printRectangle(i);

  //test everything with r3
  i = intersection(r3, r1);
  printf("intersection(r3, r1): ");
  printRectangle(i);

  i = intersection(r3, r2);
  printf("intersection(r3, r2): ");
  printRectangle(i);

  i = intersection(r3, r3);
  printf("intersection(r3, r3): ");
  printRectangle(i);

  i = intersection(r3, r4);
  printf("intersection(r3, r4): ");
  printRectangle(i);

  //test everything with r4
  i = intersection(r4, r1);
  printf("intersection(r4, r1): ");
  printRectangle(i);

  i = intersection(r4, r2);
  printf("intersection(r4, r2): ");
  printRectangle(i);

  i = intersection(r4, r3);
  printf("intersection(r4, r3): ");
  printRectangle(i);

  i = intersection(r4, r4);
  printf("intersection(r4, r4): ");
  printRectangle(i);

  return EXIT_SUCCESS
