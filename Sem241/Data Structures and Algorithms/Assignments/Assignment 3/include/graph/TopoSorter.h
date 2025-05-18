/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   TopoSorter.h
 * Author: ltsach
 *
 * Created on July 11, 2021, 10:21 PM
 */

#ifndef TOPOSORTER_H
#define TOPOSORTER_H
#include "graph/DGraphModel.h"
#include "hash/xMap.h"
#include "list/DLinkedList.h"
#include "sorting/DLinkedListSE.h"
#include "stacknqueue/Queue.h"
#include "stacknqueue/Stack.h"
template <class T, class V>
using XHashMap = xMap<T, V>;

template<class T>
class TopoSorter{
public:
    static int DFS;
    static int BFS; 
    
protected:
    DGraphModel<T>* graph;
    int (*hash_code)(T&, int);
    
public:
    TopoSorter(DGraphModel<T>* graph, int (*hash_code)(T&, int)=0){
        //TODO
        this->graph = graph;
        this->hash_code = hash_code;
    }   

    DLinkedList<T> sort(int mode=0, bool sorted=true){
        //TODO
        if (mode == DFS)
            return dfsSort(sorted);
        else if (mode == BFS)
            return bfsSort(sorted);
        else
            throw invalid_argument("Invalid mode for topological sort");
    }

    DLinkedList<T> bfsSort(bool sorted=true) { 
        //TODO
        DLinkedList<T> result;
        XHashMap<T, int> inDegree = vertex2inDegree(hash_code);
        Queue<T> zeroInDegreeQueue;

        for (auto vertex : graph->vertices())
            if (inDegree.get(vertex) == 0)
                zeroInDegreeQueue.push(vertex);
                
        while (!zeroInDegreeQueue.empty()) {
            T vertex = zeroInDegreeQueue.pop();
            result.add(vertex);

            for (auto neighbor : graph->getOutwardEdges(vertex)) {
                int degree = inDegree.get(neighbor) - 1;
                inDegree.put(neighbor, degree);

                if (degree == 0)
                    zeroInDegreeQueue.push(neighbor);
            }
        }

        if (result.size() != graph->vertices().size())
            throw runtime_error("Graph has at least one cycle");

        return result;
    }

    DLinkedList<T> dfsSort(bool sorted=true){
        //TODO
        DLinkedList<T> result;
        xMap<T, bool> visited(hash_code);
        Stack<T> stack;

        for (auto vertex : graph->vertices())
            if (!visited.containsKey(vertex))
                dfsVisit(vertex, visited, stack);

        while (!stack.empty())
            result.add(stack.pop());

        return result;
    }

    void dfsVisit(T &vertex, xMap<T, bool>& visited, Stack<T>& stack) {
        visited.put(vertex, true);

        for (auto neighbor : graph->getOutwardEdges(vertex))
            if (!visited.containsKey(neighbor))
                dfsVisit(neighbor, visited, stack);

        stack.push(vertex);
    }

protected:

    //Helper functions
    xMap<T, int> vertex2inDegree(int (*hash)(T&, int)) {
        xMap<T, int> inDegreeMap(hash);
    
        for (auto vertex : graph->vertices())
            inDegreeMap.put(vertex, 0);

        for (auto vertex : graph->vertices()) {
            for (auto neighbor : graph->getOutwardEdges(vertex)) {
                int currentInDegree = inDegreeMap.get(neighbor);
                inDegreeMap.put(neighbor, currentInDegree + 1);
            }
        }

        return inDegreeMap;
    };

    xMap<T, int> vertex2outDegree(int (*hash)(T&, int)) {
        xMap<T, int> outDegreeMap(hash);
    
        for (auto vertex : graph->vertices()) {
            int outDegree = graph->getOutwardEdges(vertex).size();
            outDegreeMap.put(vertex, outDegree);
        }

        return outDegreeMap;
    };

    DLinkedList<T> listOfZeroInDegrees() {
        DLinkedList<T> zeroInDegreeList;
        xMap<T, int> inDegreeMap = vertex2inDegree(hash_code);

        for (auto vertex : graph->vertices())
            if (inDegreeMap.get(vertex) == 0)
                zeroInDegreeList.add(vertex);

        return zeroInDegreeList;
    };

}; //TopoSorter
template<class T>
int TopoSorter<T>::DFS = 0;
template<class T>
int TopoSorter<T>::BFS = 1;

/////////////////////////////End of TopoSorter//////////////////////////////////

#endif /* TOPOSORTER_H */