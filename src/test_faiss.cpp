#include <Rcpp.h>
#include <faiss/Index.h>

// [[Rcpp::export]]
void test_faiss() {
  faiss::Index *index; // Just declare something from Faiss
  Rcpp::Rcout << "Faiss is linked!\n";
}
