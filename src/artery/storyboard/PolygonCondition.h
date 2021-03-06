#ifndef _POLYGONCONDITION_H_
#define _POLYGONCONDITION_H_

#include "artery/storyboard/Condition.h"
#include "artery/utility/Geometry.h"
#include <vector>

class PolygonCondition : public Condition
{
public:
    /**
     * Creates a polygon area from the given Omnet++ Coordinates
     * \note The vector must not contain the first point as end point
     */
    PolygonCondition(const std::vector<Position>& vertices);

    /**
     * The function will return true if the TraCI vehicle is inside the given polygon,
     * or false if its not.
     * \param Vehicle to check if its inside
     * \return result of the performed check
     */
    bool testCondition(const Vehicle& car);

private:
    std::vector<Position> m_vertices;

    int edges() const;
};

#endif /* _POLYGONCONDITION_H_ */
