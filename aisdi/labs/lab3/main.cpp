// ------------------------------------------------------------------------------------------------------------------
#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

class Graph {
private:
    int vertices_num, edges_num;
    std::vector<std::vector<int>> adjacecy_matrix;
    std::vector<int> vertices_indices;      //not to loose the vertices after sorting
    std::vector<int> connections_num;       //number of connections for each vertices
public:
    std::vector<std::vector<int>> createMatrix(int n){
        std::vector<std::vector<int>> m;
        m.resize(n);

        for (int i = 0; i < n; ++i){
            m[i].resize(n);
        }

        return m;
    }

    void printMatrix(vector<vector<int>> m){
        for (size_t i = 0; i < m.size(); ++i){
            for (size_t j = 0; j < m.size(); ++j){
                cout << m[vertices_indices[i]][vertices_indices[j]] << " ";
            }

            cout << endl;
        }
    }

    void read_file(char* filename) {
        int n = 0, a = 0, b = 0;
//        std::cout << "---- IN read_file FUNCTION ----" << std::endl;
        std::ifstream input(filename);
//        std::cout << "check input.good()" << std::endl;
        if(!input.good()) {
            throw "There is no file.";
        }
//        std::cout << "input num of vertices" << std::endl;
        input >> n;
        vertices_num = n;
//        std::cout << vertices_num << std::endl;
//create matrix to fill and vector of indices
        connections_num.resize(n);
//        std::cout << "create matrix to fill and vector of indices" << std::endl;
//        adjacecy_matrix = createMatrix(vertices_num);
        adjacecy_matrix.resize(vertices_num);
        for (int i = 0; i < vertices_num; ++i) {
            adjacecy_matrix[i].resize(vertices_num);
            vertices_indices.push_back(i);
        }
//        printMatrix(adjacecy_matrix);
// fill in the appropriate cells
//        std::cout << "fill in the appropriate cells" << std::endl;


//        std::cout << "a = " << a << " b = " << b << std::endl;
//        input >> a;
//        input >> b;
//        std::cout << "a = " << a << " b = " << b << std::endl;

        while(input >> a >> b) {
            adjacecy_matrix[a][b] = 1;
            adjacecy_matrix[b][a] = 1;
            ++edges_num;
        }
//        printMatrix(adjacecy_matrix);
        input.close();
//count numbers of connections for each vertice
//        std::cout << "count numbers of connections for each vertice" << std::endl;

//        cout << "connections numbers ";
        for(int i = 0; i < vertices_num; ++i) {
            connections_num[i] = 0;
            for(int j = 0; j < vertices_num; ++j) {
                connections_num[i] += adjacecy_matrix[i][j];
            }
//            cout << connections_num[i] << ", ";
        }
//sort the matrix to compare faster (descending)
//std::cout << "sort the matrix to compare faster (descending)" << std::endl;
        for(int i = 0; i < vertices_num-1; ++i) {
//    std::cout << "LOOP1 -- iteration" << std::endl;
            for(int j = 0; j < (vertices_num - i); ++j) {
//    std::cout << "LOOP2 -- iteration" << std::endl;
                if(connections_num[j] < connections_num[j+1]) {
//    std::cout << "condition TRUE -- SWAP" << std::endl;
                    int tmp = connections_num[j] ;
//    cout << "step1 " << endl;
                    connections_num[j] = connections_num[j+1];
//    cout << "step2" << endl;
                    connections_num[j+1] = tmp;
//    cout << "step3" << endl;
//    cout << "vertices SWAP" << endl;
                    int tmp_i = vertices_indices[j];
//    cout << "step" << endl;
                    vertices_indices[j] = vertices_indices[j+1];
//    cout << "step" << endl;
                    vertices_indices[j+1] = tmp_i;
//    cout << "step" << endl;
                }
            }
        }
        printMatrix(adjacecy_matrix);
    }

    bool is_isomorphic_to(Graph &other) {
        if((vertices_num != other.vertices_num )|| (edges_num != other.edges_num)) {
            std::cout << "Not isomorphic" << std::endl;
            return false;
        }
        for(int i = 0; i < vertices_num; ++i) {
            for(int j = 0; j < vertices_num; ++j) {
                if(adjacecy_matrix[vertices_indices[i]][vertices_indices[j]] !=
                                    other.adjacecy_matrix[other.vertices_indices[i]][other.vertices_indices[j]]) {
                    std::cout << "Not isomorphic" << std::endl;
                    return false;
                }
            }
            std::cout << vertices_indices[i] << "-->" << other.vertices_indices[i] << std::endl;
        }
        std::cout << "Isomorphic" << std::endl;
        return true;
    }
};

int main(int argc, char* argv[]) {
    if(argc != 3) {
        std::cout << "Wrong number of arguments passed to main()!" << std::endl;
    }
//    std::cout << "create g1, g2\n" << std::endl;
    Graph g1, g2;

//    std::cout << "read from file -- g1" << std::endl;
    g1.read_file(argv[1]);
//    std::cout << "read from file -- g2\n" << std::endl;
    g2.read_file(argv[2]);

    std::cout << "check isomorphism\n" << std::endl;
    g1.is_isomorphic_to(g2);

    return 0;
}
