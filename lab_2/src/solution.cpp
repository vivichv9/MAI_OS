#include "../include/solution.hpp"

void lab2::solution(std::vector<Point>& vec, uint32_t threads_count) {
  std::vector<WorkerResult> res_vec;
  res_vec.resize(vec.size());

  pthread_t* threads = static_cast<pthread_t*>(malloc(threads_count * sizeof(pthread_t)));

  MessageToThread* msgs = static_cast<MessageToThread*>(malloc(threads_count * sizeof(MessageToThread)));

  clock_t begin = clock();
  auto start = std::chrono::steady_clock::now();

  size_t left = 0;
  for (size_t i = 0; i < threads_count; ++i) {
    size_t right = left + (vec.size() + threads_count - 1) / threads_count;

    msgs[i].left = left;
    msgs[i].right = right;
    msgs[i].res_vec = &res_vec;
    msgs[i].vec = &vec;

    left = right;
    if (pthread_create(&threads[i], NULL, lab2::worker_func, (void*)&msgs[i]) != 0) {
      perror("pthread_create");
      exit(EXIT_FAILURE);
    }
  }

  for (size_t i = 0; i < threads_count; ++i) {
    int flag = pthread_join(threads[i], NULL);

    if (flag < 0) {
      throw std::runtime_error("Thread join return error code!");
    }
  }

  clock_t end = clock();
  auto chrono_end = std::chrono::steady_clock::now();

  std::vector<uint64_t> indexes = lab2::get_max_square_index(res_vec);

  std::cout << "Elapsed time in milliseconds(clock): " << static_cast<double>((end - begin) / CLOCKS_PER_SEC * 1000) << std::endl;

  std::cout << "Elapsed time in milliseconds(chrono): "
  << std::chrono::duration_cast<std::chrono::milliseconds>(chrono_end - start).count()
    << " ms" << std::endl;

  lab2::save_metrics("/home/kirill/Desktop/study/MAI_OS/lab_2/files/metrics.txt", threads_count, std::chrono::duration_cast<std::chrono::milliseconds>(chrono_end - start).count());

  std::cout << '[' << indexes[0] << ", " << indexes[1] << ", " << indexes[2] << ']' << std::endl;
}

std::vector<uint64_t> lab2::get_max_square_index(const std::vector<WorkerResult>& res_vec) {
  std::vector<uint64_t> indexes;
  double max_square = 0;

  for (auto& el : res_vec) {
    if (el.square > max_square) {
      max_square = el.square;
      indexes = el.indexes;
    }
  }

  return indexes;
}

void* lab2::worker_func(void* args) {
  fflush(stdout);
  MessageToThread* msg = static_cast<MessageToThread*>(args);
  double max_square = 0;
  double current_square = 0;
  std::vector<uint64_t> indexes;

  for (size_t i = msg->left; i < msg->right; ++i) {
    for (size_t j = i + 1; j < msg->vec->size() - 1; ++j) {
      for (size_t k = j + 1; k < msg->vec->size(); ++k) {
        current_square = calculate_triangle_square(msg->vec->at(i), msg->vec->at(j), msg->vec->at(k));

        if (max_square < current_square) {
          max_square = current_square;
          indexes = {i, j, k};
        }
      }
    }    
  }

  WorkerResult res;
  res.indexes = indexes;
  res.square = max_square;
  msg->res_vec->push_back(res);  
  fflush(stdout);
  pthread_exit(NULL);
}

lab2::vector_coords lab2::calc_vector_coords(const Point& point1, const Point& point2) {
  double x = point2.get_x() - point1.get_x();
  double y = point2.get_y() - point1.get_y();
  double z = point2.get_z() - point1.get_z();

  return {x, y, z};
}

lab2::vector_coords lab2::calc_vectors_product(const vector_coords& v1, const vector_coords& v2) {
  double x = std::get<1>(v1) * std::get<2>(v2) - std::get<2>(v1) * std::get<1>(v2);
  double y = std::get<0>(v1) * std::get<2>(v2) - std::get<2>(v1) * std::get<0>(v2);
  double z = std::get<0>(v1) * std::get<1>(v2) - std::get<1>(v1) * std::get<0>(v2);

  return {x, y, z};
}

double lab2::calc_vector_norm(const vector_coords& v) {
  return std::sqrt(std::pow(std::get<0>(v), 2) + std::pow(std::get<1>(v), 2) + std::pow(std::get<2>(v), 2));
}

double lab2::calculate_triangle_square(const Point& p1, const Point& p2, const Point& p3) {
  lab2::vector_coords ab = calc_vector_coords(p1, p2);
  lab2::vector_coords ac = calc_vector_coords(p1, p3);

  lab2::vector_coords c = calc_vectors_product(ab, ac);
  double len_c = calc_vector_norm(c);
  
  return len_c * 0.5;
}

void lab2::save_metrics(const std::string& file_name, auto& elapsed_time, uint64_t worker_count) {
  std::ofstream file(file_name, std::ios::app);
  file << worker_count << ' ' << elapsed_time << std::endl;
}
