#include<RcppArmadillo.h>
#include"Misc.h"
using namespace arma;

//Gradient
RcppExport SEXP grad(SEXP Ra, SEXP Rd, SEXP Rr1, SEXP RN, SEXP Rguess, 
	SEXP RTheta, SEXP Rprior) 
{ 
    BEGIN_RCPP
	//Protect and create vars
	int i, j, nfact, nquad;
    Rcpp::NumericVector Pa(Ra);
    Rcpp::NumericVector Pd(Rd);
    Rcpp::NumericVector Pr1(Rr1);
    Rcpp::NumericVector PN(RN);
    Rcpp::NumericVector guess(Rguess);
    Rcpp::NumericMatrix Theta(RTheta);
    Rcpp::NumericVector prior(Rprior);
    nfact = Pa.length();
	nquad = Theta.nrow();
	Rcpp::NumericVector ret(nfact + 1);

	double P[nquad], a[nfact], d, g;
	for(i = 0; i < nfact; i++)
	    a[i] = Pa[i];
	d = Pd[0];

	colvec N(PN.begin(), nquad, false);       // reuses memory 
    colvec r1(Pr1.begin(), nquad, false);
    colvec DIF(nquad), tempTheta(nquad), tempArray(nquad);
    
    itemtrace(P, a, &d, Theta, &g);
	for(i = 0; i < nquad; i++)      
		DIF(i) = ((r1(i) / N(i)) - P[i]) * prior(i);	  	
		
	//load gradient		  
	for(i = 0; i < nfact; i++){
		for(j = 0; j < nquad; j++)
			tempTheta(j) = Theta(j,i); 
		tempArray = N % DIF % tempTheta;
		ret(i) = sum(tempArray);
	}
	tempArray = N % DIF;
	ret(nfact) = sum(tempArray);
	for(i = 0; i <= nfact; i++)
		ret(i) = (-1) * ret(i);
    
	return(ret);
	END_RCPP
}

//Log-likelihood
/*
RcppExport SEXP loglik(SEXP Ra, SEXP Rd, SEXP Rrs, SEXP Rgues, SEXP RTheta){
{
	//Proctect and create vars
	BEGIN_RCPP
	int i, j, nitems, nquad, nfact, nzeta;
	NumericVector Pa(Ra);
	NumericVector d(Rd);
	NumericVector Pgues(Rgues);
	NumericMatrix rs(Rrs);
	NumericMatrix Theta(RTheta);
	nitems = rs.ncol();
	nquad = Theta.nrow();
	nfact = Theta.ncol();
	nzeta = d.length();

	double g = Pgues[0], l,	a[nfact], dtmp, P[nquad], 
	       itemtrace[nquad][nzeta + 1];
	for(i = 0; i < nfact; i++)
	    a[i] = Pa(i);
    for(j = 0; j < nzeta; j++){
        dtmp = d(j);
        itemtrace(P, a, &dtmp, Theta, &g);
        for(i = 0; i < nquad; i++){
            itemtrace[i][j] = P[i];



    NumericVector ret(1);    
    ret(0) = (-1.0) * l;		
	return(ret);	
	END_RCPP
}
*/
