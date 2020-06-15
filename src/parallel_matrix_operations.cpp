///------------------------------------------------------------------------------------------------------------------///
///INCLUDES

#include <iostream>
#include "../headers/vector_operations.h"
#include "../headers/matrix_operations.h"
#include "../headers/parallel_matrix_operations.h"
#include <cmath>
#include "../helper_functions/helper_functions.h"
#include <cassert>
#include <future>
#include "../headers/ctpl.h"

///------------------------------------------------------------------------------------------------------------------///
///PARALLEL LIB

double determinant_parallel(Matrix* matrixx, int threadN=2, int task_partition=2) {
    if ( !check_square(matrixx) ){
        std::cout << "Error: Non-square matrices have no determinants.\n";
        return -1;
    }
    if (threadN < 1 || task_partition < 1) {
        std::cout << "Error: Invalid number of threads or partitions provided. Both must be >= 1\n";
        return -1;
    }

    auto matrix = row_echelon(matrixx);

    ctpl::thread_pool thr_pool(threadN);

    double det = 1;

    std::vector<double> results(task_partition);
    std::vector<std::future<void>> futures(task_partition);
    for (int i = 0; i < task_partition; i++){
        results[i] = 1;
    }

    auto data_len = matrix->get_width();
    size_t start = 0;
    size_t end;
    auto step = data_len/task_partition;

    if (step < 1) {
        std::cout << "Error: The task was partitioned too much\n";
        return -1;
    }

    for (int t = 0; t < task_partition; t++) {
        end = (start+step != data_len && t+1 == task_partition) ? data_len : start+step;

        //auto temp = &results[t];

        auto determinant_parallel_util = [&matrix, start, end, &results, t](int){
            for (int i = start; i < end; i++){
                results[t] *= matrix->get_element(i, i);
            }
        };

        futures[t] = thr_pool.push(determinant_parallel_util);
        start = end;
    }

    for (auto& f: futures) {
        f.get();
    }

    for (auto& x: results) {
        det *= x;
    }

    det = det * pow(10,5) / pow(10,5);
    return det;
}

//----------------------------------------------------------------------------------------------------------------------


double trace_parallel(Matrix* matrix, int threadN=2, int task_partition=2) {
    if ( !check_square(matrix) ){
        std::cout << "Error: Non-square matrices don't have a trace.\n";
        return -1;
    }

    if (threadN < 1 || task_partition < 1) {
        std::cout << "Error: Invalid number of threads or partitions provided. Both must be >= 1\n";
        return -1;
    }

    ctpl::thread_pool thr_pool(threadN);

    double trace = 0;
    std::vector<double> results;

    std::vector<std::future<void>> futures(task_partition);

    for (int i = 0; i < task_partition; i++){
        results.push_back(0);
    }

    auto data_len = matrix->get_width();
    size_t start = 0;
    size_t end;
    auto step = data_len/task_partition;

    if (step < 1) {
        std::cout << "Error: Task was partitioned too much.\n";
        return -1;
    }

    for (int t = 0; t < task_partition; t++) {
        end = (start+step != data_len && t+1 == task_partition) ? data_len : start+step;
        auto temp = &results[t];

        auto trace_parallel_util = [&matrix, start, end, temp](int){
            for (int i = start; i < end; i++){
                *temp = *temp + matrix->get_element(i, i);
            }
        };

        futures[t] = thr_pool.push(trace_parallel_util);
        start = end;
    }

    for (auto& f: futures) {
        f.get();
    }

    for (auto& x: results) {
        trace += x;
    }

    return trace;
}

//----------------------------------------------------------------------------------------------------------------------

Matrix* add_matrix_parallel(Matrix* a, Matrix* b, double a_coef, double b_coef, int threadN=2) {
    assert(sizes_equal(a, b));

    if (threadN < 1) {
        std::cout << "Error: Invalid number of threads provided.\n";
        return NULL;
    }

    ctpl::thread_pool thr_pool(threadN);
    std::vector<std::future<void>> futures(a->get_height());

    auto* c = new Matrix(a->get_height(), a->get_width());

    for (int i = 0; i < a->get_height(); i++) {
        //threads.emplace_back(add_matrix_parallel_util, std::ref(*a), std::ref(*b), std::ref(*c), a_coef, b_coef, i);

        auto add_matrix_parallel_util = [&a, &b, &c, i, a_coef, b_coef](int){
            for (int j = 0; j < a->get_width(); ++j) {
                c->set_element(i, j, (a->get_element(i, j) * a_coef) + (b->get_element(i, j) * b_coef));
            }
        };

        futures[i] = thr_pool.push(add_matrix_parallel_util);
    }

    for (auto& f: futures) {
        f.get();
    }

    return c;
}

//----------------------------------------------------------------------------------------------------------------------


Matrix* scalar_multiply_parallel(Matrix* a, double mul, int threadN) {
    auto* b = new Matrix(a->get_height(), a->get_width());

    ctpl::thread_pool thr_pool(threadN);
    std::vector<std::future<void>> futures(a->get_height() * a->get_width());

    for (int i =0; i < a->get_height(); i++) {


        for (int j =0; j < a->get_width(); j++) {
            int idx = j + a->get_width() * i;

            auto util = [&a, &b, i, j, mul](int) {
                //b->set_element(i, j, a->get_element(i, j) * mul);
                double *cell;
                cell = b->get_cell_ref(i, j);
                *cell = a->get_element(i, j) * mul;
            };

            futures[idx] = thr_pool.push(util);
        }

    }

    for (auto& f: futures) {
        f.get();
    }

    return b;
}


//----------------------------------------------------------------------------------------------------------------------


Matrix* multiply_matrix_parallel(Matrix* a , Matrix* b, int threadN=2) {
    if (a->get_width() != b->get_height()) {
        std::cout << "matrices can not be multiplied" << std::endl;
        return nullptr;
    }

    ctpl::thread_pool thr_pool(threadN);
    std::vector<std::future<void>> futures(a->get_height());

    auto* c = new Matrix(a->get_height(), b->get_width());

    for (int i = 0; i < a->get_height(); i++) {

        auto util = [&a, &b, &c, i](int){
            double vector_mult = 0;

            for (int j = 0; j < b->get_width(); j++) {

                for (int k = 0; k < a->get_width(); k++) {
                    vector_mult += a->get_element(i, k) * b->get_element(k, j);
                }

                c->set_element(i, j, vector_mult);
                vector_mult = 0;
            }
        };

        futures[i] = thr_pool.push(util);
    }

    for (auto& f: futures) {
        f.get();
    }

    return c;
}


//----------------------------------------------------------------------------------------------------------------------


bool is_non_singular(Matrix * a) {
    Matrix* ref = row_echelon(a);
    bool empty = true;
    for (int i = a->get_height() -1; i >= 0; i--) {
        for (int j = 0; j < a->get_width(); j++) {
            empty &= (ref->get_element(i, j) == 0);
        }
        if (empty) {
            return false;
        }
    }
    return true;
}



Matrix* change_of_basis_parallel(Matrix* transition_matrix, Matrix* vector, int threadN, int task_partition) {

    auto data_len = transition_matrix->get_width();
    auto step = data_len/task_partition;

    if (step < 1) {
        std::cout << "Error: The task was partitioned too much\n";
        return nullptr;
    }

    auto result_matrix = multiply_matrix_parallel(transition_matrix, vector, threadN);

    assert( check_square(transition_matrix) && is_non_singular(transition_matrix));
    assert(vector->get_height() == transition_matrix->get_height() && vector->get_width() == 1);

    return result_matrix;
}


///------------------------------------------------------------------------------------------------------------------///