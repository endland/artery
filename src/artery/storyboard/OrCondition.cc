#include "artery/storyboard/OrCondition.h"


OrCondition::OrCondition(Condition* left, Condition* right) :
    m_left(left), m_right(right)
{
}

bool OrCondition::testCondition(const Vehicle& car)
{
    return (m_left->testCondition(car) ||  m_right->testCondition(car));
}
