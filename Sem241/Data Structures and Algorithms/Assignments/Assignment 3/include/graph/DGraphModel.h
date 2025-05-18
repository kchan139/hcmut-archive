/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DGraphModel.h
 * Author: LTSACH
 *
 * Created on 23 August 2020, 19:36
 */

#ifndef DGRAPHMODEL_H
#define DGRAPHMODEL_H
#include "graph/AbstractGraph.h"

//////////////////////////////////////////////////////////////////////
///////////// GraphModel: Directed Graph Model    ////////////////////
//////////////////////////////////////////////////////////////////////


template<class T>
class DGraphModel: public AbstractGraph<T>{
private:
    using VertexNode = typename AbstractGraph<T>::VertexNode;
    // using Edge = typename AbstractGraph<T>::Edge;

public:
    DGraphModel(
            bool (*vertexEQ)(T&, T&), 
            string (*vertex2str)(T&) ): 
        AbstractGraph<T>(vertexEQ, vertex2str){
    }
    
    void connect(T from, T to, float weight=0){
        //TODO
        VertexNode *fromNode = this->getVertexNode(from);
        VertexNode *toNode   = this->getVertexNode(to);

        if (!fromNode) throw VertexNotFoundException(this->vertex2str(from));
        if (!toNode)   throw VertexNotFoundException(this->vertex2str(to));

        fromNode->connect(toNode, weight);
    }
    void disconnect(T from, T to){
        //TODO
        VertexNode *fromNode = this->getVertexNode(from);
        VertexNode *toNode   = this->getVertexNode(to);

        if (!fromNode) throw VertexNotFoundException(this->vertex2str(from));
        if (!toNode)   throw VertexNotFoundException(this->vertex2str(to));

        typename AbstractGraph<T>::Edge *disconnectEdge = fromNode->getEdge(toNode);
        if (!disconnectEdge) {
            typename AbstractGraph<T>::Edge edgeThrown(fromNode, toNode);
            throw EdgeNotFoundException(AbstractGraph<T>::edge2Str(edgeThrown));
        }

        fromNode->removeTo(toNode);
    }
    void remove(T vertex){
        //TODO
        VertexNode *removeNode = this->getVertexNode(vertex);
        if (!removeNode)
            throw VertexNotFoundException(this->vertex2str(vertex));

        DLinkedList<T> outEdges = this->getOutwardEdges(vertex);
        DLinkedList<T> inEdges  = this->getInwardEdges(vertex);

        for (auto adjnode : outEdges) {
            VertexNode *adjNode = this->getVertexNode(adjnode);
            removeNode->removeTo(adjNode);
        }

        for (auto adjnode : inEdges) {
            VertexNode *adjNode = this->getVertexNode(adjnode);
            adjNode->removeTo(removeNode);
        }

        AbstractGraph<T>::nodeList.removeItem(
            removeNode, 
            [](VertexNode * rmVertex) { 
                delete rmVertex; 
            }
        );
    }
    
    static DGraphModel<T>* create(
            T* vertices, 
            int nvertices, 
            Edge<T>* edges, 
            int nedges,
            bool (*vertexEQ)(T&, T&),
            string (*vertex2str)(T&)) {
        //TODO
        DGraphModel<T> *model = new DGraphModel<T>(vertexEQ, vertex2str);

        for (int i = 0; i < nvertices; i++)
            model->add(vertices[i]);

        for (int i = 0; i < nedges; i++)
            model->connect(edges[i].from, edges[i].to, edges[i].weight);

        return model;
    }
};

#endif /* DGRAPHMODEL_H */

