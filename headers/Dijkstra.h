#ifndef DIJKSTRA_H
#define DIJKSTRA_H
#include "Search.h"



class Dijkstra_ : public Search_ {
public:

    Dijkstra_(std::vector<Node*>* tiles_, unsigned int total_rows_, Node* start, Node* end);

    virtual ~Dijkstra_() override;

    virtual void run(Node* start = nullptr, Node* end = nullptr) override;

    virtual void reset_attributes() override;

private:
    
    std::set<std::pair<unsigned int, Node*>> priority_queue;
    std::unordered_map<Node*, unsigned int>  g_score;

};

#endif 