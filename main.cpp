#include "routes.h"


// Проверяет, является ли vec маршрутом в графе graph
bool is_route(const vector<int> &vec, const vector<vector<int>> &graph) {
    vector<vector<int>> all_route;

    const int size = static_cast<int>(vec.size());
    vector<int> w(size, 0);
    w[0] = vec[0];

    get_all_routes(1, graph, size-1, w, all_route);

    // for (const auto &x: all_route)
    //     print_vec(x);

    for (const auto &x: all_route)
        if (vector_equal(vec, x))
            return true;

    return false;
}


// Проверяет, является ли vec цепью в графе graph
bool is_chain(const vector<int> &vec, const vector<vector<int>> &graph) {
    vector<vector<int>> all_chain;

    const int size = static_cast<int>(vec.size());
    vector<int> w(size, 0);
    w[0] = vec[0];
    vector<vector<int>> e;

    get_all_chains(1, e, graph, size-1, w, all_chain);

    for (const auto &x: all_chain)
        if (vector_equal(vec, x))
            return true;

    return false;
}


// Проверяет, является ли vec простой цепью в графе graph
bool is_simple_chain(const vector<int> &vec, const vector<vector<int>> &graph) {
    vector<vector<int>> all_simple_chain;

    const int size = static_cast<int>(vec.size());
    vector<int> w(size, 0);
    w[0] = vec[0];
    vector<int> v;
    v.push_back(vec[0]);

    get_all_simple_chains(1, v, graph, size-1, w, all_simple_chain);

    for (const auto &x: all_simple_chain)
        if (vector_equal(vec, x))
            return true;

    return false;
}


// Проверяет, является ли vec циклом в графе graph
bool is_cycle(const vector<int> &vec, const vector<vector<int>> &graph) {
    vector<vector<int>> all_cycle;

    const int size = static_cast<int>(vec.size());
    vector<int> w(size + 3, 0);
    w[0] = vec[0];

    get_all_cycle(1, graph, w, all_cycle);

    for (const auto &x: all_cycle) {
        if (vector_equal(vec, x))
            return true;
    }

    return false;
}


// Проверяет, является ли vec простым циклом в графе graph
bool is_simple_cycle(const vector<int> &vec, const vector<vector<int>> &graph) {
    vector<vector<int>> all_simple_cycle;

    const int size = static_cast<int>(vec.size());
    vector<int> w(size*size, 0);
    w[0] = vec[0];
    vector<int> v;

    get_all_simple_cycle(1, v, graph, w, all_simple_cycle);

    for (const auto &x: all_simple_cycle)
        if (vector_equal(vec, x))
            return true;

    return false;
}


// Находит все маршруты длины l в графе graph
void get_routes(const int i,
                const vector<vector<int>> &graph,
                const int l,
                vector<int> &w,
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


// Возвращает все пути длины l между всеми парами вершин в графе graph
vector<vector<int>> get_all_pairs_paths(const vector<vector<int>> &graph, const int l) {
    vector<vector<int>> R = graph;
    for (int i = 1; i < l; i++)
        R = multiplies_square_matrix(R, graph);
    return R;
}


// Возвращает пути длины l между вершинами v1 и v2 в графе graph
vector<vector<int>> find_paths_between_verticrs(const vector<vector<int>> &graph,
                                                const int v1,
                                                const int v2,
                                                const int l) {
    vector<vector<int>> paths;
    vector<int> w(l + 1, 0);
    w[0] = v1;
    get_all_routes(1, graph, l, w, paths);

    vector<vector<int>> result;
    for (const auto &x: paths)
        if (x[x.size() - 1] == v2)
            result.push_back(x);

    return result;
}


// Возвращает все простые максимальные пути, начинающиеся с вершины v1 в графе graph
vector<vector<int>> get_simple_maximal_paths(const int v1, const vector<vector<int>> &graph) {
    vector<vector<int>> all_simple_maximal_paths;

    const vector<int> w = {v1};
    vector<int> v = {v1};

    get_all_simple_maximal_paths(1, v, graph, w, all_simple_maximal_paths);

    return all_simple_maximal_paths;
}



int main() {
    const vector<vector<int> > G1 = {
        {0, 1, 0, 1, 1, 1, 1},
        {1, 0, 1, 0, 1, 1, 0},
        {0, 1, 0, 1, 0, 0, 0},
        {1, 0, 1, 0, 0, 0, 0},
        {1, 1, 0, 0, 0, 0, 0},
        {1, 1, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 1, 0},
    };

    const vector<vector<int> > G2 = {
        {0, 1, 0, 1, 0, 1, 1},
        {1, 0, 1, 1, 0, 0, 0},
        {0, 1, 0, 1, 1, 1, 0},
        {1, 1, 1, 0, 1, 0, 0},
        {0, 0, 1, 1, 0, 0, 0},
        {0, 1, 1, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 1, 0},
    };

    vector<int> vec1 = {6, 7, 1, 4, 3, 2};
    vector<int> vec2 = {2, 1, 7, 6, 1, 4};
    vector<int> vec3 = {1, 2, 3, 4, 1};
    vector<int> vec4 = {1, 2, 3, 4, 2, 1};
    vector<int> vec5 = {2, 1, 6, 7, 1, 4, 2};

    std::cout << is_cycle(vec3, G1) << endl;


    return 0;
}
