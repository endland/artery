#include "artery/storyboard/AndCondition.h"

AndCondition::AndCondition(Condition* left, Condition* right) :
    m_left(left), m_right(right)
{
}

bool AndCondition::testCondition(const Vehicle& car)
{
    return(m_left->testCondition(car) && m_right->testCondition(car));
}
