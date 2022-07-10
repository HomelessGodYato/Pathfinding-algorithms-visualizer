#ifndef DFS_H
#define DFS_H
#include "Search.h"

class DFS_ : public Search_ {
public:

    DFS_(std::vector<Node*>* tiles_, unsigned int total_rows_, Node* start, Node* end);

    virtual ~DFS_() override;

    virtual void run(Node* start = nullptr, Node* end = nullptr) override;

    virtual void reset_attributes() override;

private:
    
    void DFS_recursion(std::unordered_map<Node*, bool>& visited, Node* current, bool& found_end);

};


#endif 