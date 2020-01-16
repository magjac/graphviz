#include "sgd.h"
#include "neatoprocs.h"
#include <math.h>
#include <stdlib.h>

typedef struct term {
    node_t *i, *j;
    float d, w;
} term;

float calculate_stress(term *terms, int n_terms) {
    float stress = 0;
    int ij;
    for (ij=0; ij<n_terms; ij++) {
        float dx = ND_pos(terms[ij].i)[0] - ND_pos(terms[ij].j)[0];
        float dy = ND_pos(terms[ij].i)[1] - ND_pos(terms[ij].j)[1];
        float r = sqrt(dx*dx + dy*dy) - terms[ij].d;
        stress += terms[ij].w * (r * r);
    }
    return stress;
}
void fisheryates_shuffle(term *terms, int n_terms) {
    int i;
    for (i=n_terms-1; i>=1; i--) {
        // srand48() is called in neatoinit.c, so no need to seed here
        int j = (int)(drand48() * (i+1));

        term temp = terms[i];
        terms[i] = terms[j];
        terms[j] = temp;
    }
}
// single source shortest paths that also builds terms as it goes
// mostly copied from from stuff.c
// returns the number of terms built
int dijkstra_single_source(graph_t *G, node_t *source, term *terms) {
    int t;
    node_t *v, *u;
    for (t = 0; (v = GD_neato_nlist(G)[t]); t++) {
        ND_dist(v) = Initial_dist;
        ND_heapindex(v) = -1;
    }

    ND_dist(source) = 0;
    neato_enqueue(G, source);

    edge_t *e;
    int offset = 0;
    while ((v = neato_dequeue(G))) {
        // if the target is fixed then always create a term as shortest paths are not calculated from there
        // if not fixed then only create a term if the target index is lower
        if (isFixed(v) || ND_id(v)<ND_id(source)) {
            terms[offset].i = source;
            terms[offset].j = v;
            terms[offset].d = ND_dist(v);
            terms[offset].w = 1 / (terms[offset].d*terms[offset].d);
            offset++;
        }
        for (e = agfstedge(G, v); e; e = agnxtedge(G, e, v)) {
            if ((u = agtail(e)) == v)
                u = aghead(e);

            double f = ND_dist(v) + ED_dist(e);
            if (ND_dist(u) > f) {
                ND_dist(u) = f;
                if (ND_heapindex(u) >= 0) {
                    heapup(G, u);
                } else {
                    neato_enqueue(G, u);
                }
            }
        }
    }
    return offset;
}

void sgd(graph_t *G, /* input graph */
        int n, /* number of nodes */
        int model /* distance model */)
{
    if (model == MODEL_SHORTPATH) {
        agerr(AGWARN, "shortest path model not yet supported in Gmode=sgd, reverting to MDS model\n");
    } else if (model == MODEL_SUBSET) {
        agerr(AGWARN, "subset model not yet supported in Gmode=sgd, reverting to MDS model\n");
    } else if (model == MODEL_CIRCUIT) {
        agerr(AGWARN, "circuit model not yet supported in Gmode=sgd, reverting to MDS model\n");
    }

    // calculate how many terms will be needed as fixed nodes can be ignored
    int i, n_fixed = 0, n_terms = 0;
    for (i=0; i<n; i++) {
        if (!isFixed(GD_neato_nlist(G)[i])) {
            n_fixed++;
            n_terms += n-n_fixed;
        }
    }
    term *terms = N_NEW(n_terms, term);

    // calculate term values through shortest paths
    int offset = 0;
    GD_heap(G) = N_NEW(n, node_t *);
    GD_heapsize(G) = 0;
    if (Verbose) {
        fprintf(stderr, "calculating shortest paths:");
        start_timer();
    }
    for (i=0; i<n; i++) {
        node_t *source = GD_neato_nlist(G)[i];
        if (!isFixed(source)) {
            offset += dijkstra_single_source(G, source, terms+offset);
        }
    }
    free(GD_heap(G));
    assert(offset == n_terms);
    if (Verbose) {
        fprintf(stderr, " %.2f\n", elapsed_sec());
    }

    // initialise annealing schedule
    float w_min = terms[0].w, w_max = terms[0].w;
    int ij;
    for (ij=1; ij<n_terms; ij++) {
        if (terms[ij].w < w_min)
            w_min = terms[ij].w;
        if (terms[ij].w > w_max)
            w_max = terms[ij].w;
    }
    // note: Epsilon is different from MODE_KK and MODE_MAJOR as it is a minimum step size rather than energy threshold
    //       MaxIter is also different as it is a fixed number of iterations rather than a maximum
    float eta_max = 1 / w_min;
    float eta_min = Epsilon / w_max;
    float lambda = log(eta_max/eta_min) / (MaxIter-1);

    // initialise starting positions (from neatoprocs)
    initial_positions(G, n);

    // perform optimisation
    if (Verbose) {
        fprintf(stderr, "solving model:");
        start_timer();
    }
    int t;
    for (t=0; t<MaxIter; t++) {
        fisheryates_shuffle(terms, n_terms);
        float eta = eta_max * exp(-lambda * t);
        for (ij=0; ij<n_terms; ij++) {
            // cap step size
            float mu = eta * terms[ij].w;
            if (mu > 1)
                mu = 1;

            float dx = ND_pos(terms[ij].i)[0] - ND_pos(terms[ij].j)[0];
            float dy = ND_pos(terms[ij].i)[1] - ND_pos(terms[ij].j)[1];
            float mag = sqrt(dx*dx + dy*dy);

            float r = (mu * (mag-terms[ij].d)) / (2*mag);
            float r_x = r * dx;
            float r_y = r * dy;

            if (!isFixed(terms[ij].i)) {
                ND_pos(terms[ij].i)[0] -= r_x;
                ND_pos(terms[ij].i)[1] -= r_y;
            }
            if (!isFixed(terms[ij].j)) {
                ND_pos(terms[ij].j)[0] += r_x;
                ND_pos(terms[ij].j)[1] += r_y;
            }
        }
        if (Verbose) {
            fprintf(stderr, " %.3f", calculate_stress(terms, n_terms));
        }
    }
    if (Verbose) {
        fprintf(stderr, "\nfinished in %.2f sec\n", elapsed_sec());
    }
    free(terms);
}
