#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <cctype>
using namespace std;

class Graph {
    private:
        int V;
        vector<vector<int>> adjMatrix;

        // Mengubah huruf (A-F) menjadi indeks, -1 jika tidak valid
        int keIndeks(char huruf) {
            int i = toupper(huruf) - 'A';
            if (i < 0 || i >= V) return -1;
            return i;
        }

        // Fungsi bantu rekursif DFS
        void dfsUtil(int current, vector<bool>& visited) {
            visited[current] = true;
            cout << char('A' + current) << " ";

            for (int i = 0; i < V; i++) {
                if (adjMatrix[current][i] != 0 && !visited[i]) {
                    dfsUtil(i, visited);
                }
            }
        }

        // Mencari titik belum final dengan jarak terkecil
        int minkey(vector<int>& dist, vector<bool>& selesai) {
            int min = INT_MAX;
            int minindex = -1;

            for (int v = 0; v < V; v++) {
                if (!selesai[v] && dist[v] < min) {
                    min = dist[v];
                    minindex = v;
                }
            }
            return minindex;
        }

        // Mencetak rute secara rekursif memakai array parent
        void printPath(vector<int>& parent, int tujuan) {
            if (parent[tujuan] == -1) {
                cout << char('A' + tujuan);
                return;
            }
            printPath(parent, parent[tujuan]);
            cout << " -> " << char('A' + tujuan);
        }

    public:
        Graph(int jumlahVertex) {
            V = jumlahVertex;
            adjMatrix.resize(V, vector<int>(V, 0));
        }

        // Graf tak berarah, berbobot
        void addEdge(char a, char b, int jarak) {
            int u = keIndeks(a);
            int v = keIndeks(b);
            if (u == -1 || v == -1) {
                cout << "Vertex tidak valid!" << endl;
                return;
            }
            adjMatrix[u][v] = jarak;
            adjMatrix[v][u] = jarak;
        }

        void printadjmatrix() {
            cout << "    ";
            for (int i = 0; i < V; i++) {
                cout << char('A' + i) << "   ";
            }
            cout << endl;

            for (int i = 0; i < V; i++) {
                cout << char('A' + i) << "   ";
                for (int j = 0; j < V; j++) {
                    cout << adjMatrix[i][j] << "   ";
                }
                cout << endl;
            }
        }

        void bfs(char start) {
            int s = keIndeks(start);
            if (s == -1) {
                cout << "Vertex tidak valid!" << endl;
                return;
            }

            vector<bool> visited(V, false);
            queue<int> antrian;

            visited[s] = true;
            antrian.push(s);

            while (!antrian.empty()) {
                int current = antrian.front();
                antrian.pop();
                cout << char('A' + current) << " ";

                for (int i = 0; i < V; i++) {
                    if (adjMatrix[current][i] != 0 && !visited[i]) {
                        visited[i] = true;
                        antrian.push(i);
                    }
                }
            }
            cout << endl;
        }

        void dfs(char start) {
            int s = keIndeks(start);
            if (s == -1) {
                cout << "Vertex tidak valid!" << endl;
                return;
            }

            vector<bool> visited(V, false);
            dfsUtil(s, visited);
            cout << endl;
        }

        // Dijkstra dari vertex awal ke vertex tujuan
        void dijkstra(char awal, char tujuan) {
            int s = keIndeks(awal);
            int t = keIndeks(tujuan);

            if (s == -1 || t == -1) {
                cout << "Vertex tidak valid! Gunakan huruf A-F." << endl;
                return;
            }

            vector<int> dist(V, INT_MAX);
            vector<int> parent(V, -1);
            vector<bool> selesai(V, false);

            dist[s] = 0;

            for (int count = 0; count < V; count++) {
                int u = minkey(dist, selesai);
                if (u == -1) break;

                selesai[u] = true;

                for (int v = 0; v < V; v++) {
                    if (adjMatrix[u][v] != 0 && !selesai[v] &&
                        dist[u] + adjMatrix[u][v] < dist[v]) {
                        dist[v] = dist[u] + adjMatrix[u][v];
                        parent[v] = u;
                    }
                }
            }

            if (dist[t] == INT_MAX) {
                cout << "Tidak ada rute dari " << char(toupper(awal))
                     << " ke " << char(toupper(tujuan)) << "." << endl;
                return;
            }

            cout << "Rute terpendek: ";
            printPath(parent, t);
            cout << endl;
            cout << "Total jarak   : " << dist[t] << endl;
        }
};

// Membaca satu huruf vertex dari pengguna
char bacaVertex(string pesan) {
    char c;
    cout << pesan;
    cin >> c;
    return c;
}

int main() {
    Graph kampus(6); // 6 vertex: A, B, C, D, E, F

    kampus.addEdge('A', 'B', 4);
    kampus.addEdge('A', 'C', 2);
    kampus.addEdge('B', 'C', 1);
    kampus.addEdge('B', 'D', 5);
    kampus.addEdge('B', 'E', 3);
    kampus.addEdge('C', 'D', 8);
    kampus.addEdge('C', 'E', 6);
    kampus.addEdge('D', 'E', 2);
    kampus.addEdge('D', 'F', 4);
    kampus.addEdge('E', 'F', 3);

    int pilihan;

    do {
        cout << "\n===== SISTEM PENCARIAN RUTE KAMPUS =====" << endl;
        cout << "1. Tampilkan Adjacency Matrix" << endl;
        cout << "2. Penelusuran BFS" << endl;
        cout << "3. Penelusuran DFS" << endl;
        cout << "4. Cari rute terpendek (Dijkstra)" << endl;
        cout << "0. Keluar" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;

        if (pilihan == 1) {
            kampus.printadjmatrix();

        } else if (pilihan == 2) {
            char awal = bacaVertex("Vertex awal (A-F): ");
            cout << "Urutan BFS: ";
            kampus.bfs(awal);

        } else if (pilihan == 3) {
            char awal = bacaVertex("Vertex awal (A-F): ");
            cout << "Urutan DFS: ";
            kampus.dfs(awal);

        } else if (pilihan == 4) {
            char awal = bacaVertex("Vertex awal   (A-F): ");
            char tujuan = bacaVertex("Vertex tujuan (A-F): ");
            kampus.dijkstra(awal, tujuan);

        } else if (pilihan != 0) {
            cout << "Pilihan tidak valid!" << endl;
        }

    } while (pilihan != 0);

    cout << "Program selesai." << endl;
    return 0;
}