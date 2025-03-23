#include <Rcpp.h>
#include <faiss/IndexFlat.h>
#include <memory>
using namespace Rcpp;

// [[Rcpp::export]]
List faiss_flat_search(NumericMatrix data, int k) {
  int n = data.nrow();
  int d = data.ncol();
  std::vector<float> vec(n * d);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < d; j++) {
      vec[i * d + j] = data(i, j);
    }
  }
  std::unique_ptr<faiss::IndexFlatL2> index(new faiss::IndexFlatL2(d));
  index->add(n, vec.data());
  std::vector<float> distances(n * k);
  std::vector<faiss::idx_t> indices(n * k);
  index->search(n, vec.data(), k, distances.data(), indices.data());
  NumericMatrix dist_mat(n, k);
  IntegerMatrix idx_mat(n, k);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < k; j++) {
      dist_mat(i, j) = distances[i * k + j];
      idx_mat(i, j) = indices[i * k + j] + 1; // R uses 1-based indexing
    }
  }
  return List::create(Named("distances") = dist_mat, Named("indices") = idx_mat);
}
