#ifndef CONSTRAINTGRAPH_H
#define CONSTRAINTGRAPH_H

#include <vector>
#include <Dense>
#include <unordered_set>

class NodeVisitor;
class MassSpringSystem;

class Node{
protected:
    MassSpringSystem *system;
    Eigen::VectorXf vbuff;

public:
    Node(MassSpringSystem *system, Eigen::VectorXf vbuff);

    virtual void satisfy() = 0; //satisfy constraint;
    virtual bool accept(NodeVisitor &visitor) = 0;
};

class PointNode : public Node{
public:
    PointNode(MassSpringSystem *system, Eigen::VectorXf vbuff);

    virtual bool isConstrained(unsigned int i) const = 0 ;


    // Node interface
public:
    bool accept(NodeVisitor &visitor);
};

class SpringNode : public Node
{
public:
    SpringNode(MassSpringSystem *system, Eigen::VectorXf vbuff);
    void addChild(Node * node);
    void removeChild(Node *node);

protected:
    typedef std::vector<Node*> Nodes;
    Nodes children;

    // Node interface
public:
    virtual bool accept(NodeVisitor &visitor);
};

class RootNode : public SpringNode
{
public:
    RootNode(MassSpringSystem *system, Eigen::VectorXf vbuff);
    virtual void satisfy();
    virtual bool accept(NodeVisitor &visitor);
};

class FixedPointNode : public PointNode
{
public:
    FixedPointNode(MassSpringSystem *system, Eigen::VectorXf vbuff);
    virtual void fixPoint(unsigned int i);
    virtual void releasePoint(unsigned int i);
protected:
    typedef Eigen::Vector3f Vector3f;
    std::unordered_map<unsigned int, Vector3f> fixed;


    // Node interface
public:
    virtual void satisfy();

    // PointNode interface
public:
    virtual bool isConstrained(unsigned int i) const;
};

class SpringDeformationNode : public SpringNode
{
private:
    typedef std::pair<unsigned int, unsigned int> Edge;
    typedef Eigen::Vector3f Vector3f;
    std::unordered_set<unsigned int> items;
    float crit_def;
    unsigned int nbIter;
    // Node interface
public:
    SpringDeformationNode(float crit_def, unsigned int nbIter, MassSpringSystem *system, Eigen::VectorXf vbuff);

    virtual void satisfy();

    void addSprings(std::vector<unsigned int> springs);

};

class SphereCollisionNode : public PointNode
{
private :
    typedef Eigen::Vector3f Vector3f;

    float radius;
    Vector3f center;


    // Node interface
public:
    SphereCollisionNode(MassSpringSystem *system, Eigen::VectorXf vbuff);
    virtual void satisfy();

    // PointNode interface
public:
    virtual bool isConstrained(unsigned int i) const;
};

class NodeVisitor
{
public:
    virtual bool visit(PointNode &node);
    virtual bool visit(SpringNode &node);
};

class FixedPointVisitor : public NodeVisitor
{
private:
    unsigned int i;
    bool result;

    // NodeVisitor interface
public:
    virtual bool visit(PointNode &node);
    bool query(Node &root, unsigned int i);
};


class SatisfyVisitor : public NodeVisitor{
public:
    void satisfy(Node &root);



    // NodeVisitor interface
public:
    virtual bool visit(PointNode &node);
    virtual bool visit(SpringNode &node);
};

#endif // CONSTRAINTGRAPH_H
