#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <queue>

#define INF 0xffffff
using namespace std;

class Graph
{
  int numVert;
  list<pair<int, int> >* adj;

public:
  Graph(int numVert)
  {
    this->numVert = numVert;
    adj = new list<pair<int, int>>[numVert];
  }

  void addEdge(int a, int b, int weight)
  {
    adj[a].push_back(make_pair(b, weight));
    adj[b].push_back(make_pair(a, weight));
  }

  int shortestPath(vector<int> &sp, int src, int end)
  {
    vector<int> pathID;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>>pq;
    vector<pair<int, int>> dist(numVert, make_pair(INF, INF));

    pq.push(make_pair(0, src));
    dist[src] = make_pair(0, src);

    while (!pq.empty())
    {
      int u = pq.top().second;
      pq.pop();

      for (auto i = adj[u].begin(); i != adj[u].end(); ++i) {
        int vertexID = (*i).first;
        int weight = (*i).second;

        if (dist[vertexID].first > dist[u].first + weight) {
          dist[vertexID].first = dist[u].first + weight;
          dist[vertexID].second = u;
          pq.push(make_pair(dist[vertexID].first, vertexID));
        }
      }

    }

    printf("Shortest Path from A to B\n");
    int temp = dist[end].second;
    int distance = dist[end].first;
    sp.push_back(end);
    sp.push_back(temp);
    while(true){
      if(temp == src){break;}
      temp = dist[temp].second;
      sp.push_back(temp);
    }

    return distance;
  }
};

class loc{
public:
  string city;
  string state_id;
  string state_name;
  string county_name;
  float lat;
  float lng;
  int population;
  float density;
  int ID;

  loc(){};

  loc(string city, string state_id, string state_name, string county_name, float lat,
    float lng, int population, float density, int ID){
    this->city = city;
    this->state_id = state_id;
    this->state_name = state_name;
    this->county_name = county_name;
    this->lat = lat;
    this->lng = lng;
    this->population = population;
    this->density = density;
    this->ID = ID;
  }


};

int main()
{
  ifstream inFile;

  string city;
  string state_id;
  string state_name;
  string county_name;
  string lat;
  string lng;
  string population;
  string density;
  string ID;
  vector<loc> store;
  int count = 0;
  inFile.open("citylist.csv");
  if (inFile.is_open()) {
    cout << "File has been opened" << endl;
  }
  else {
    cout << "File has not been opened" << endl;
  }
  while (inFile.is_open()) {
    getline ( inFile, city, ',' );
    getline ( inFile, state_id, ',' );
    getline ( inFile, state_name, ',' );
    getline ( inFile, county_name, ',' );
    getline ( inFile, lat, ',' );
    getline ( inFile, lng, ',' );
    getline ( inFile, population, ',' );
    getline ( inFile, density, ',' );
    inFile >> ID;
    loc temp = loc(city, state_id, state_name, county_name, stof(lat), stof(lng),
             stoi(population), stof(density), stoi(ID));
    store.push_back(temp);
    count++;
    if(count > 10) {
      inFile.close();
    }
  }
  inFile.close();

  Graph g(9);

  // making above shown graph
  g.addEdge(store[0].ID, store[1].ID, 4);
  g.addEdge(store[0].ID, store[7].ID, 8);
  g.addEdge(store[1].ID, store[2].ID, 8);
  g.addEdge(store[1].ID, store[7].ID, 11);
  g.addEdge(store[2].ID, store[3].ID, 7);
  g.addEdge(store[2].ID, store[8].ID, 2);
  g.addEdge(store[2].ID, store[5].ID, 4);
  g.addEdge(store[3].ID, store[4].ID, 9);
  g.addEdge(store[3].ID, store[5].ID, 14);
  g.addEdge(store[4].ID, store[5].ID, 10);
  g.addEdge(store[5].ID, store[6].ID, 2);
  g.addEdge(store[6].ID, store[7].ID, 1);
  g.addEdge(store[6].ID, store[8].ID, 6);
  g.addEdge(store[7].ID, store[8].ID, 7);

  string a;
  cin >> a;
  string b;
  cin >> b;
  while(a != "n" || b!= "n") {
    vector<int> sp;
    cout << g.shortestPath(sp, stoi(a), stoi(b)) << endl;
    for (int i = sp.size() - 1; i >= 0; --i) {
      cout << store[sp[i]].city;
    }
    cout << endl;
    cin >> a;
    cin >> b;
  }

  return 0;
}
