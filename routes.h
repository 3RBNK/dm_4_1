//
// Created by bnkr on 01.12.2024.
//

#ifndef ROUTES_H
#define ROUTES_H

#include <iostream>
#include <vector>

using namespace std;

// Печатает элементы вектора vec через пробел
void print_vec(const vector<int> &vec) {
    for (const int x: vec)
        std::cout << x << " ";
    std::cout << std::endl;
}

// Возвращает список вершин, смежных с вершиной w[i-1] в графе graph
vector<int> get_g(const vector<vector<int>> &graph, const int i, const vector<int> &w) {
    const int index = w[i - 1] - 1;
    vector<int> result;
    for (int j = 0; j < graph[index].size(); j++)
        if (graph[index][j])
            result.push_back(j + 1);
    return result;
}

// Возвращает разность двух векторов vec1 и vec2 (элементы vec1, которых нет в vec2)
vector<int> diff_vector(const vector<int>& vec1, const vector<int> &vec2) {
    vector<int> result;
    for (auto x: vec1) {
        bool push_x = true;
        for (auto y: vec2)
            if (x == y) {
                push_x = false;
                break;
            }

        if (push_x)
            result.push_back(x);
    }

    return result;
}

// Возвращает список вершин, соединенных с вершиной w_i через ребра e
vector<int> get_y_from_e(const int w_i, const vector<vector<int>> &e) {
    vector<int> y;
    for (const auto& elem: e)
        if (elem[0] == w_i)
            y.push_back(elem[1]);
    return y;
}

// Умножает две квадратные матрицы mat1 и mat2
vector<vector<int>> multiplies_square_matrix(const vector<vector<int>> &mat1,
                                             const vector<vector<int>> &mat2) {
    vector<vector<int>> res(mat1.size(), vector<int>(mat1.size(), 0));

    for (int k = 0; k < mat1.size(); k++)
        for (int i = 0; i < mat1.size(); i++)
            for (int j = 0; j < mat1.size(); j++)
                res[i][j] += mat1[i][k] * mat2[k][j];
    return res;
}

// Проверяет, включены ли все элементы vec1 в vec2 (нестрогое включение)
bool not_strikly_include(const vector<int> &vec1, const vector<int> &vec2) {
    for (const auto x: vec1) {
        bool x_not_in_vec2 = true;
        for (const auto y: vec2)
            if (x == y) {
                x_not_in_vec2 = false;
                break;
            }
        if (x_not_in_vec2)
            return false;
    }
    return true;
}

// Проверяет, равны ли два вектора v1 и v2
bool vector_equal(const vector<int> &v1, const vector<int> &v2) {
    for (int i = 0; i < v1.size(); i++)
        if (v1[i] != v2[i])
            return false;

    return true;
}

// Находит все маршруты длины l в графе graph
void get_all_routes(const int i,
                    const vector<vector<int>> &graph,
                    const int l,
                    vector<int> w,
                    vector<vector<int>> &result) {
    vector<int> g = get_g(graph, i, w);
    for (const int x: g) {
        w[i] = x;
        if (i == l)
            result.push_back(w);
        else
            get_all_routes(i + 1, graph, l, w, result);
    }
}

// Находит все цепи длины l в графе graph
void get_all_chains(const int i,
                    vector<vector<int>> e,
                    const vector<vector<int>> &graph,
                    const int l,
                    vector<int> w,
                    vector<vector<int>> &result) {
    vector<int> g = get_g(graph, i, w);
    const vector<int> y = get_y_from_e(w[i-1], e);
    g = diff_vector(g, y);

    for (const auto x: g) {
        w[i] = x;
        if (i == l) {
            result.push_back(w);
        } else {
            vector<vector<int>> sub_e = e;
            vector<int> elem = {w[i-1], x};
            sub_e.push_back(elem);
            get_all_chains(i+1, sub_e, graph, l, w, result);
        }
    }
}

// Находит все простые цепи длины l в графе graph
void get_all_simple_chains(const int i,
                           vector<int> v,
                           const vector<vector<int>> &graph,
                           const int l,
                           vector<int> w,
                           vector<vector<int>> &result) {
    vector<int> g = get_g(graph, i, w);
    g = diff_vector(g, v);

    for (const auto x: g) {
        w[i] = x;
        if (i == l) {
            result.push_back(w);
        } else {
            vector<int> sub_v = v;
            sub_v.push_back(x);
            get_all_simple_chains(i+1, sub_v, graph, l, w, result);
        }
    }
}

// Находит все циклы в графе graph
void get_all_cycle(const int i,
                   const vector<vector<int>> &graph,
                   vector<int> w,
                   vector<vector<int>> &result) {
    vector<int> g = get_g(graph, i, w);
    for (const auto &x: g) {
        w[i] = x;
        if (x == w[0] && i > 2) {
            result.push_back(w);
        } else {
            get_all_cycle(i + 1, graph, w, result);
        }
    }
}

// Находит все простые циклы в графе graph
void get_all_simple_cycle(const int i,
                          vector<int> v,
                          const vector<vector<int>> &graph,
                          vector<int> w,
                          vector<vector<int>> &result) {
    vector<int> g = get_g(graph, i, w);
    g = diff_vector(g, v);

    for (const auto &x: g) {
        w[i] = x;
        if (x == w[0] && i > 2) {
            result.push_back(w);
        } else {
            vector<int> sub_v = v;
            sub_v.push_back(x);
            get_all_simple_cycle(i+1, sub_v, graph, w, result);
        }
    }
}

// Находит все простые максимальные пути в графе graph
void get_all_simple_maximal_paths(const int i,
                                  vector<int> v,
                                  const vector<vector<int>> &graph,
                                  vector<int> w,
                                  vector<vector<int>> &result) {
    vector<int> g = get_g(graph, i, w);
    g = diff_vector(g, v);
    for (const int x: g) {
        w.push_back(x);
        if (not_strikly_include(g, v))
            result.push_back(w);
        else {
            vector<int> sub_v = v;
            sub_v.push_back(x);
            get_all_simple_maximal_paths(i+1, sub_v, graph, w, result);
        }
    }
}

#endif //ROUTES_H
