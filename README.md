# Random generation of proper interval graphs

This is a software to generate a proper interval graph uniformly at random. The program is written in C++ and you can complile the source code `genPIG.cpp`. You run the program with the number of vertices in the graph. The program outputs an interval representation of the proper interval graph and its adjacency list. The implementation is based on the algorithm written in [1].

## Example how to compile and execute the program

We compile and execute the program as follows. 

```
$ g++ genPIG.cpp
$ ./a.out 6
```

The program outputs an interval representation of a proper interval graph and its adjacency list of the graph. 

```
Interval representation: 1 2 3 1 4 5 2 3 4 6 5 6
Graph: (n, m) = (6, 9)
1: 2 3 
2: 1 3 4 5 
3: 1 2 4 5 
4: 2 3 5 
5: 2 3 4 6 
6: 5 
```

The output of the interval representation is the sequence of endpoints of an interval representation. On the above example, the sequence means that the left endpoint of vertex 1, the left endpoint of vertex 2, the left endpoints of vertex 3, the right endpoint of vertex 1, ..., from left to right in the sequence.


## References
[1] [Toshiki Saitoh, Katsuhisa Yamanaka, Masashi Kiyomi, and Ryuhei Uehara: “Random Generation and Enumeration of Proper Interval Graphs,” IEICE Transactions on Information and Systems, vol. E93-D, No. 7, pp. 1816-1823, 2010.](https://www.jstage.jst.go.jp/article/transinf/E93.D/7/E93.D_7_1816/_article)

