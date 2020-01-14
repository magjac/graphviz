#include "sgd.h"
#include "neatoprocs.h"
#include <math.h>

typedef struct term {
    node_t *i, *j;
    float d, w;
} term;

void fisheryates_shuffle(term *terms, int nC2) {
    int i;
    for (i=nC2-1; i>=1; i--) {
        // unsigned j = rk_interval(i, &rstate);
        int j = (int)(drand48() * (i+1)); // TODO: better rng

        term temp = terms[i];
        terms[i] = terms[j];
        terms[j] = temp;
    }
}
float calculate_stress(term *terms, int nC2) {
    float stress = 0;
    int ij;
    for (ij=0; ij<nC2; ij++) {
        float dx = ND_pos(terms[ij].i)[0] - ND_pos(terms[ij].j)[0];
        float dy = ND_pos(terms[ij].i)[1] - ND_pos(terms[ij].j)[1];
        float r = sqrt(dx*dx + dy*dy) - terms[ij].d;
        stress += terms[ij].w * (r * r);
    }
    return stress;
}

void sgd(graph_t *G, /* input graph */
         int n, /* number of nodes */
         int model /* distance model */)
{
    // calculate shortest paths (from neatoprocs)
    shortest_path(G, n);

    // initialise array of terms
    int nC2 = (n*(n-1))/2;
    term *terms = N_NEW(nC2, term);
    int i, j;
    int ij = 0;
    for (i=0; i<n; i++) {
        for (j=0; j<i; j++) {
            terms[ij].i = GD_neato_nlist(G)[i];
            terms[ij].j = GD_neato_nlist(G)[j];
            terms[ij].d = GD_dist(G)[ND_id(terms[ij].i)][ND_id(terms[ij].j)];
            terms[ij].w = 1 / (terms[ij].d*terms[ij].d);
            ij++;
        }
    }

    // initialise annealing schedule
    float w_min = terms[0].w, w_max = terms[0].w;
    for (ij=1; ij<nC2; ij++) {
        if (terms[ij].w < w_min)
            w_min = terms[ij].w;
        if (terms[ij].w > w_max)
            w_max = terms[ij].w;
    }
    float eta_max = 1 / w_min;
    float eta_min = .01 / w_max; // TODO: read in epsilon
    float lambda = log(eta_max/eta_min) / (30-1); // TODO: read in t_max

    // initialise starting positions (from neatoprocs)
    initial_positions(G, n);

    // perform optimisation
    int t;
    if (Verbose) {
        fprintf(stderr, "Solving model:");
        start_timer();
    }
    for (t=0; t<30; t++) {
        fisheryates_shuffle(terms, nC2);
        float eta = eta_max * exp(-lambda * t);
        for (ij=0; ij<nC2; ij++) {
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

            if (!ND_pinned(terms[ij].i)) {
                ND_pos(terms[ij].i)[0] -= r_x;
                ND_pos(terms[ij].i)[1] -= r_y;
            }
            if (!ND_pinned(terms[ij].j)) {
                ND_pos(terms[ij].j)[0] += r_x;
                ND_pos(terms[ij].j)[1] += r_y;
            }
        }
        if (Verbose) {
            fprintf(stderr, " %.3f", calculate_stress(terms, nC2));
        }
    }
    if (Verbose) {
        fprintf(stderr, "\n %.2f sec\n", elapsed_sec());
    }
    free(terms);
}
