//
//  l0_stat.h
//  osc
//
//  Created by Futao Zhang on 12/02/2016.
//  Copyright (c) 2016 Futao Zhang. All rights reserved.
//

#ifndef __osc__l0_stat__
#define __osc__l0_stat__

#include "dcdflib.h"
#include "l0_com.h"

double t_prob(double df, double t_value, bool two_tail);
double F_prob(double df_1, double df_2, double F_value);
double pchisq(double x, double df);
double median(vector<double> vec);
double pnorm(double x);
double qnorm(double p, bool upper = true);
double dnorm(double x);
double chi_prob(double df, double chi_sqr_val);
double qchisq(double q, double df);
double gasdev(int &idum);
double pT(double T, double df);
double pchisqsum(double x, VectorXd lambda);
#endif /* defined(__osc__l0_stat__) */
