/*
This software is released under the MIT License, see LICENSE.txt.
*/

#include<stdlib.h>
#include<assert.h>
#include<time.h>

#include<iostream>
#include<vector>


class Graph{
private:
  std::vector<std::vector<int> > adj;
  int n, m;

public:
  Graph(int n, int m, std::vector<std::vector<int> > adj):n(n), m(m), adj(adj) {
  }

  void print(){
    //std::cout << "Graph: (n, m) = (" << n << ", " << m << ")" << std::endl;
    std::cout << "#Vertices = " << n << "\t#Edges = " <<  m << std::endl; 
    for(int i = 0 ; i<adj.size() ; i++){
      std::cout << i+1 << ": ";
      for(std::vector<int>::iterator itr = adj[i].begin() ; itr != adj[i].end() ; ++itr){
	std::cout << *itr << " ";
      }
      std::cout << std::endl;
    }
  }
};


class Sequence {
private:
  std::vector<int> Seq;
  int numVertices;

  void construct(){
    for(int i=0 ; i < 2*numVertices-1 ; i++) Seq[i] = i;
    Seq[2*numVertices -1] = 0;
    randSeq();
    rotate();
  }

  void iterativeConstruction(){
    construct();
    while( !isCanonical() ){
      //std::cerr << "rejection" << std::endl;
      construct();
    }
  }

  void randSeq(){
    for(int i=2*numVertices-2 ; i > 0 ; i--){
      double r=1.0*(i+1)*rand()/RAND_MAX;
      int x=static_cast<int>(r); 
      int tmp=Seq[i];
      Seq[i]=Seq[x];
      Seq[x]=tmp;
    }
    for(int i=0 ; i < 2*numVertices-1 ; i++){
      if(Seq[i] <= numVertices-1) Seq[i]=1;
      else Seq[i]=0;
    }
  }

  bool isValid() const {
    int sum=0;
    for(int i=0 ; i < 2*numVertices-1 ; i++){
      if(Seq[i]==1) sum++;
      else{
	sum--;
	if(sum <= 0) return false;
      }
    }
    //printf("Sequence is valid");
    return true;
  }

  // This part is not linear time. 
  void rotate(){
    while(!isValid()){
      int tmp = Seq[0];
      for(int i=0 ; i < 2*numVertices-2 ; i++) Seq[i] = Seq[i+1];
      Seq[2*numVertices-2]=tmp;
    }
  }

  bool isHeavy(std::vector<int> S) const {
    for(int i=0 ; i<2*numVertices ; i++){
      if(S[i] != Seq[i]){
	if(Seq[i] == 0) return false; // not heavy
	else return true; // heavy
      }
    }
    return true; // equal
  }

  std::vector<int> reverseSeq() const {
    std::vector<int> Sj(2*numVertices);
    for(int i=0 ; i<2*numVertices ; i++){
      if(Seq[2*numVertices-i-1]==1) Sj[i]=0;
      else Sj[i]=1;
    }
    return Sj;
  }

  std::vector<int> seq2interval() const {
    std::vector<int> I(2*numVertices);

    int left = 0, right = 0;
    for(int i=0 ; i<2*numVertices ; i++){
      if(Seq[i] == 1){
	I[i] = left;
	left++;
      }
      else{
	I[i] = right;
	right++;
      }
    }
    return I;
  }
  
  Graph seq2graph() const {
    //std::vector<int> I = seq2interval();
    std::vector<std::vector<int> > adj_list(numVertices, std::vector<int>(0));

    int numEdges = 0;
    int min = 0, max = 0;
    assert(Seq[0] == 1);
    for(int i=1 ; i<2*numVertices ; i++){
      if(Seq[i] == 1){
	max++;
	for(int j = min ; j<max ; j++){
	  adj_list[max].push_back(j+1);
	  adj_list[j].push_back(max+1);
	  numEdges++;
	}
      }
      else{ // Seq[i] == 0
	min++;
      }
    }
    return Graph(numVertices, numEdges, adj_list);
  }
  

public:
  Sequence(int numVertices):numVertices(numVertices){
    srand ((int) time(NULL));
    Seq.resize(2*numVertices);
    
    iterativeConstruction();
  }

  void reConstruct(){
    iterativeConstruction();
  }
  
  //Check canonical and non-negative
  bool isCanonical() const {
    //non-negative?
    if(!isValid()) return false;
    
    std::vector<int> Sr = reverseSeq();

    //Canonical?
    if(!isHeavy(Sr)) return false;
    return true;
  }

  std::vector<int> makeInterval() const {
    return seq2interval();
  }

  Graph makeGraph() const {
    return seq2graph();
  }

  void printGraph() const{
    Graph G = seq2graph();
    G.print();
  }

  void printInterval() const {
    std::vector<int> I = seq2interval();
    for(int i=0 ; i<2*numVertices ; i++){
      std::cout << I[i]+1 << " ";
    }
    std::cout << std::endl;
  }

  void print() const {
    for(int i=0 ; i<2*numVertices ; i++){
      if(Seq[i]==1) std::cout << "1";
      else std::cout << "0";
    }
    std::cout << std::endl;
  }
};


int main(int argc, char **argv)
{
  int n;
  
  if(argc < 2){
    std::cerr << "Please input a positive integer: ";
    std::cin >> n;
  }
  else{
    n = atoi(argv[1]);
  }

  
  Sequence S(n);
  //S.print();

  std::cout << "Interval representation: ";
  S.printInterval();

  std::cout << "Graph: ";
  S.printGraph();
  
  return 0;
}
