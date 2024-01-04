#include "constraintgraph.h"
#include "massspringsystem.h"

#include <qdebug.h>


Node::Node(MassSpringSystem *system,  Eigen::VectorXf vbuff) : system(system),
    vbuff(vbuff)
{}

PointNode::PointNode(MassSpringSystem *system,  Eigen::VectorXf vbuff) : Node(system, vbuff)
{}

bool PointNode::accept(NodeVisitor &visitor)
{
    return visitor.visit(*this);
}

SpringNode::SpringNode(MassSpringSystem *system, Eigen::VectorXf vbuff) : Node(system, vbuff)
{}

void SpringNode::addChild(Node *node)
{
    children.push_back(node);
}

void SpringNode::removeChild(Node *node)
{
    children.erase(find(children.begin(), children.end(), node));
}

bool SpringNode::accept(NodeVisitor &visitor)
{
    for(Node * child : children)
    {
        if(!child->accept(visitor)) return false;
    }
    return visitor.visit(*this);
}

RootNode::RootNode(MassSpringSystem *system, Eigen::VectorXf vbuff) : SpringNode(system, vbuff)
{}

void RootNode::satisfy()
{
    // do nothing cause root;
    return;
}

bool RootNode::accept(NodeVisitor &visitor)
{
    for(Node* child : children)
    {
        if(!child->accept(visitor)) return false;
    }
    return true;
}

FixedPointNode::FixedPointNode(MassSpringSystem *system, Eigen::VectorXf vbuff) : PointNode(system, vbuff)
{}

void FixedPointNode::fixPoint(unsigned int i)
{
    assert(i<system->getNbPoints());
    fixed[3*i] = Vector3f(vbuff[3*i], vbuff[3*i+1], vbuff[3*i+2]);
}

void FixedPointNode::releasePoint(unsigned int i)
{
    assert(i<system->getNbPoints());
    fixed.erase(3*i);
}

void FixedPointNode::satisfy()
{
    for(const auto &fix : fixed)
    {
        for (int i = 0; i < 3; i++)
            vbuff[fix.first + i] = fix.second[i];
    }
}

bool FixedPointNode::isConstrained(unsigned int i) const
{
    //if(fixed.find(3*i) != fixed.end())qDebug()<<i;
    return fixed.find(3*i) != fixed.end();
}

SphereCollisionNode::SphereCollisionNode(MassSpringSystem *system, Eigen::VectorXf vbuff) : PointNode(system, vbuff)
{}

void SphereCollisionNode::satisfy()
{
//    for(unsigned int i=0; i<system->getNbPoints(); i++)
//    {
//        Vector3f p(vbuff[i] - center);
//        if(p.norm()<radius)
//        {
//            p.normalize();
//            p = radius * p;
//        }else continue;

//        vbuff[i] = p + center;
//    }
}

bool SphereCollisionNode::isConstrained(unsigned int i) const
{
    return false;
}

bool FixedPointVisitor::visit(PointNode &node)
{
    result = node.isConstrained(i);
    //qDebug()<<"here : "<<result;
    return !result;
}

bool FixedPointVisitor::query(Node &root, unsigned int i)
{
    this->i = i;
    root.accept(*this);
    return result;
}

void SatisfyVisitor::satisfy(Node &root)
{
    root.accept(*this);
}

bool SatisfyVisitor::visit(PointNode &node)
{
    node.satisfy();
    return true;
}

bool SatisfyVisitor::visit(SpringNode &node)
{
    node.satisfy();
    return true;
}

bool NodeVisitor::visit(PointNode &node)
{
    return true;
}

bool NodeVisitor::visit(SpringNode &node)
{
    return true;
}

SpringDeformationNode::SpringDeformationNode(float crit_def, unsigned int nbIter, MassSpringSystem *system, Eigen::VectorXf vbuff) : SpringNode(system, vbuff),
    crit_def(crit_def),
    nbIter(nbIter)
{}

void SpringDeformationNode::satisfy()
{
    FixedPointVisitor visitor;
    for(unsigned int k = 0; k < nbIter;k++)
    {
        for(unsigned int i : items)
        {
            Edge spring = system->getSprings()[i];
//            Vector3f p12(
//                vbuff[spring.first] - vbuff[spring.second]);
            Vector3f p12(
                vbuff[3 * spring.first + 0] - vbuff[3 * spring.second + 0],
                vbuff[3 * spring.first + 1] - vbuff[3 * spring.second + 1],
                vbuff[3 * spring.first + 2] - vbuff[3 * spring.second + 2]
                );
            //qDebug()<<p12[0]<<","<<p12[1]<<","<<p12[2];
            float len = p12.norm();
            float rlen = system->getVd_rest()[i];
            float diff = (len - (1 + crit_def) * rlen)/len;
            float rate = (len - rlen)/rlen;
            //qDebug()<<(len - rlen);
            //qDebug()<<rate<<" "<<crit_def;
            //if(spring.first == 0) qDebug()<<vbuff[spring.first][0]<<","<<vbuff[spring.first][1];
            if(rate <= crit_def) continue;

            float f1,f2;
            f1 = f2 = 0.5f;

            if(visitor.query(*this, spring.first))
            {
                f1 = 0.0f;
                f2 = 1.0f;
            }

            if(visitor.query(*this, spring.second))
            {
                f1 = (f1 != 0.0f) ? 1.0f : 0.0f;
                f2 = 0.0f;
            }
            //qDebug()<<"here";

//            vbuff[spring.first] -= p12 * f1 * diff;

//            vbuff[spring.second] += p12 * f2 * diff;
            for (int j = 0; j < 3; j++) {
                vbuff[3 * spring.first + j] -= p12[j] * f1 * diff;
                vbuff[3 * spring.second + j] += p12[j] * f2 * diff;
            }

        }
    }
}

void SpringDeformationNode::addSprings(std::vector<unsigned int> springs)
{
    items.insert(springs.begin(), springs.end());
}
