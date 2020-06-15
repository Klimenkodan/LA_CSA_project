///------------------------------------------------------------------------------------------------------------------///
/// INCLUDES

#include <iostream>
#include "../headers/vector_operations.h"
#include <map>
#include <cmath>
#include <thread>
#include <future>
#include "../headers/matrix.h"
#include "../helper_functions/helper_functions.h"
#include "../headers/matrix_operations.h"
#include "../headers/ctpl.h"

///------------------------------------------------------------------------------------------------------------------///
///PARALLEL LIB

double dot_product_parallel(Matrix*a , Matrix* b, int threadN=2, int task_partition=1) {


    if (!is_vector(a) || !is_vector(b) || a->get_width() * a->get_height() != b->get_width() * b->get_height()) {
        std::cout << "Error: vectors sizes aren't equal" <<  std::endl;
        return -1;
    }
    if (threadN < 1 || task_partition < 1) {
        std::cout << "Error: Invalid number of threads or partitions provided. Both must be >= 1.\n";
        return -1;
    }

    double vector_mult = 0;

    ctpl::thread_pool thr_pool(threadN);
    std::vector<std::future<void>> futures(task_partition);

    std::vector<double> results(task_partition);
    for (int t = 0; t < task_partition; t++) {
        results[t] = 0;
    }

    size_t start = 0;
    size_t end;


    if (a->get_height() == 1 && b->get_height() == 1) {
        auto vector_len = a->get_width();
        auto step = vector_len/task_partition;

        if (step <= 1) {
            std::cout << "Error: task was partitioned too much.\n";
            return -1;
        }

        for (int t = 0; t < task_partition; t++) {
            end = (start+step != vector_len && t+1 == task_partition) ? vector_len : start+step;
            //threads.emplace_back(dot_product_util_m1, std::ref(a), std::ref(b), start, end, std::ref(results[t])); //dr

            auto util1 = [&a, &b, start, end, &vector_mult](int){
                for (int i = start; i < end; i++) {
                    vector_mult += a->get_element(0, i) * b->get_element(0, i);
                }
            };

            futures[t] = thr_pool.push(util1);

            start = end;
        }
    }
    else if (a->get_width() == 1 && b->get_width() == 1) {
        auto vector_len = a->get_height();
        auto step = vector_len/task_partition;

        if (step <= 1) {
            std::cout << "Error: task was partitioned too much.\n";
            return -1;
        }

        for (int t = 0; t < task_partition; t++) {
            end = (start+step != vector_len && t+1 == task_partition) ? vector_len : start+step;
            //threads.emplace_back(dot_product_util_m2, std::ref(a), std::ref(b), start, end, std::ref(results[t]));
            auto util2 = [&a, &b, start, end, &vector_mult](int){
                for (int i = start; i < end; i++) {
                    vector_mult += a->get_element(i, 0) * b->get_element(i, 0);
                }
            };

            futures[t] = thr_pool.push(util2);

            start = end;
        }
    }
    else if (a->get_height() == 1 && b->get_width() == 1) {
        auto vector_len = a->get_width();
        auto step = vector_len/task_partition;

        if (step <= 1) {
            std::cout << "Error: task was partitioned too much.\n";
            return -1;
        }

        for (int t = 0; t < task_partition; t++) {
            end = (start+step != vector_len && t+1 == task_partition) ? vector_len : start+step;
            //threads.emplace_back(dot_product_util_m3, std::ref(a), std::ref(b), start, end, std::ref(results[t]));

            auto util3 = [&a, &b, start, end, &vector_mult](int){
                for (int i = start; i < end; i++) {
                    vector_mult += a->get_element(0, i) * b->get_element(i, 0);
                }
            };

            futures[t] = thr_pool.push(util3);

            start = end;
        }
    }
    else {
        auto vector_len = a->get_height();
        auto step = vector_len/task_partition;

        if (step <= 1) {
            std::cout << "Error: task was partitioned too much.\n";
            return -1;
        }

        for (int t = 0; t < task_partition; t++) {
            end = (start+step != vector_len && t+1 == task_partition) ? vector_len : start+step;
            //threads.emplace_back(dot_product_util_m4, std::ref(a), std::ref(b), start, end, std::ref(results[t]));

            auto util4 = [&a, &b, start, end, &vector_mult](int){
                for (int i = start; i < end; i++) {
                    vector_mult += a->get_element(i, 0) * b->get_element(0, i);
                }
            };

            futures[t] = thr_pool.push(util4);

            start = end;
        }

    }

    for (auto& f: futures) {
        f.get();
    }

    for (auto& res: results) {
        //std::cout << res << std::endl;
        vector_mult += res;
    }


    return vector_mult;

}

//----------------------------------------------------------------------------------------------------------------------

bool orthogonal_parallel(Matrix*a , Matrix* b, int threadN=2, int task_partition=1) {
    return dot_product_parallel(a, b, threadN, task_partition) == 0;
}

//----------------------------------------------------------------------------------------------------------------------

bool collinear_parallel(Matrix*a , Matrix* b, int threadN=2, int task_partition=1) {

    ctpl::thread_pool thr_pool(threadN);
    std::vector<std::future<void>> futures(task_partition);

    std::vector<int> res(task_partition);

    for (int t = 0; t < task_partition; t++) {
        res[t] = 1;
    }

    if (!is_vector(a) || !is_vector(b)) {
        std::cout << "Error: Provided matrices are not vectors." << std::endl;
        return false;
    }

    bool cond1 = (a->get_width() == 1 && b->get_width() == 1 && a->get_height() == b->get_height());
    bool cond2 = (a->get_height() == 1 && b->get_height() == 1 && a->get_width() == b->get_width());
    bool cond3 = (a->get_width() == 1 && b->get_height() == 1 && a->get_height() == b->get_width());
    bool cond4 = (a->get_height() == 1 && b->get_width() == 1 && a->get_width() == b->get_height());

    if (!(cond1 || cond2 || cond3 || cond4)) {
        std::cout << "Error: Vectors' sizes aren't equal." << std::endl;
        return false;
    }

    if (threadN < 1 || task_partition < 1) {
        std::cout << "Error: Invalid number of threads or partitions provided. Both should be >= 1.\n";
        return false;
    }

    if (threadN == 1 || task_partition == 1) {
        return collinear_m(a, b);
    }

    double coeff = a->get_element(0, 0) / b->get_element(0, 0);

    // row - row
    if (a->get_height() == 1 && b->get_height() == 1) {
        auto vector_len = a->get_width();
        size_t start = 0;
        size_t end;
        auto step = vector_len/task_partition;

        if (step <= 1) {
            std::cout << "Too many threads for the vectors of this size.\n";
            return false;
        }

        for (int t = 0; t < task_partition; t++) {
            end = (start+step != vector_len && t+1 == task_partition) ? vector_len : start+step;
            auto util1 = [&a, &b, start, end, coeff, &res, t](int){
                for (int i = start; i < end; i++) {

                    if (a->get_element(0, i) == 0 && b->get_element(0, i) == 0) {
                        continue;
                    }

                    else if (coeff != a->get_element(0, i) / b->get_element(0, i)) {
                        res[t] = 0;
                    }
                }
            };

            futures[t] = thr_pool.push(util1);

            start = end;
        }
    }
    else if (a->get_width() == 1 && b->get_width() == 1) {
        //cout << "if 2\n";
        auto vector_len = a->get_height();
        size_t start = 0;
        size_t end;
        auto step = vector_len/task_partition;

        if (step <= 1) {
            std::cout << "Too many threads for the vectors of this size.\n";
            return false;
        }

        for (int t = 0; t < task_partition; t++) {
            end = (start+step != vector_len && t+1 == task_partition) ? vector_len : start+step;
            //threads.emplace_back(collinear_util_m1, std::ref(a), std::ref(b), start, end, coeff, std::ref(res[t]));
            //auto temp = &res[t];
            auto util1 = [&a, &b, start, end, coeff, &res, t](int){
                for (int i = start; i < end; i++) {

                    if (a->get_element(i, 0) == 0 && b->get_element(i, 0) == 0) {
                        continue;
                    }

                    else if (coeff != a->get_element(i, 0) / b->get_element(i, 0)) {
                        res[t] =  0;
                    }
                }
            };

            futures[t] = thr_pool.push(util1);

            start = end;
        }
    }
    else if (a->get_width() == 1 && b->get_height() == 1) {
        //cout << "if 3\n";
        auto vector_len = a->get_height();
        size_t start = 0;
        size_t end;
        auto step = vector_len/task_partition;

        if (step <= 1) {
            std::cout << "Too many threads for the vectors of this size.\n";
            return false;
        }

        for (int t = 0; t < task_partition; t++) {
            end = (start+step != vector_len && t+1 == task_partition) ? vector_len : start+step;
            //threads.emplace_back(collinear_util_m1, std::ref(a), std::ref(b), start, end, coeff, std::ref(res[t]));
            //auto temp = &res[t];
            auto util1 = [&a, &b, start, end, coeff, &res, t](int){
                for (int i = start; i < end; i++) {

                    if (a->get_element(i, 0) == 0 && b->get_element(0, i) == 0) {
                        continue;
                    }

                    else if (coeff != a->get_element(i, 0) / b->get_element(0, i)) {
                        res[t] =  0;
                    }
                }
            };

            futures[t] = thr_pool.push(util1);

            start = end;
        }

    }
    else {
        //cout << "if 4\n";
        auto vector_len = a->get_width();
        size_t start = 0;
        size_t end;
        auto step = vector_len/task_partition;

        if (step <= 1) {
            std::cout << "Too many threads for the vectors of this size.\n";
            return false;
        }

        for (int t = 0; t < task_partition; t++) {
            end = (start+step != vector_len && t+1 == task_partition) ? vector_len : start+step;
            //threads.emplace_back(collinear_util_m1, std::ref(a), std::ref(b), start, end, coeff, std::ref(res[t]));
            auto temp = &res[t];
            auto util1 = [&a, &b, start, end, coeff, &res, t](int){
                for (int i = start; i < end; i++) {

                    if (a->get_element(0, i) == 0 && b->get_element(i, 0) == 0) {
                        continue;
                    }

                    else if (coeff != a->get_element(0, i) / b->get_element(i, 0)) {
                        res[t] =  0;
                    }
                }
            };

            futures[t] = thr_pool.push(util1);

            start = end;
        }

    }

    for (auto& f: futures) {
        f.get();
    }

    bool total = true;

    for (auto oneres: res) {
        total = total && oneres;
    }

    return total;
}





//----------------------------------------------------------------------------------------------------------------------

double norm_prl (Matrix* matrix, int threadN=2, int task_partition=1) {
    return sqrt(dot_product_parallel(matrix, matrix, threadN, task_partition));
}

///------------------------------------------------------------------------------------------------------------------///