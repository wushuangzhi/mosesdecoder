#ifndef NODE_H_
#define NODE_H_

#include <vector>
using namespace std;

template<class KeyClass, class ValueClass> 
class Node
{
    public:
        Node(const KeyClass& key) : key(key), prob(0.f), backoff(0.f) { }
        Node() { prob = 0.0, backoff = 0.0; }
        Node(const ValueClass& cProb, const ValueClass& cBackOff) : prob(cProb), backoff(cBackOff) {}
        ~Node();
        void setKey(const KeyClass& key);
        void setProb(const ValueClass& value);
        void setBackOff(const ValueClass& value);
        Node* findSub(const KeyClass& key);
        void addSubnode(Node* subnode);

        vector<Node*> getSubnodes();

    private:
        vector<Node*> subnodes;
        KeyClass key;
        ValueClass prob;
        ValueClass backoff;

};

template<class KeyClass, class ValueClass>
Node<KeyClass, ValueClass>::~Node() {}

template<class KeyClass, class ValueClass>
void Node<KeyClass, ValueClass>::setProb(const ValueClass& value)
{
    prob = value;
}

template<class KeyClass, class ValueClass>
void Node<KeyClass, ValueClass>::setBackOff(const ValueClass& value)
{
    backoff = value;
}

template<class KeyClass, class ValueClass>
void Node<KeyClass, ValueClass>::addSubnode(Node<KeyClass, ValueClass>* subnode)
{
    subnodes.push_back(subnode);
}

template<class KeyClass, class ValueClass>
vector< Node<KeyClass, ValueClass>* > Node<KeyClass, ValueClass>::getSubnodes()
{
    return subnodes;
}

template<class KeyClass, class ValueClass>
Node<KeyClass, ValueClass>* Node<KeyClass, ValueClass>::findSub(const KeyClass& cKey)
{
    for(auto subnode: subnodes)
    {
        if (subnode->key == cKey)
        {
            return subnode;
        }
    }
    return NULL;
}

#endif /* end of include guard: NODE_H_ */
