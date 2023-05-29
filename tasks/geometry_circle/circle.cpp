#include "circle.h"

#include "point.h"
#include "segment.h"

namespace geometry {
Circle::Circle() : centre_(Point(0, 0)), radius_(0) {
}

Circle::Circle(Point p, int64_t rad) : centre_(p), radius_(rad) {
}

Circle& Circle::Move(const Vector& vector) {
    centre_.Move(vector);
    return *this;
}

bool Circle::ContainsPoint(const Point& point) const {
    return radius_ >= Length(point - centre_);
}

bool Circle::CrossesSegment(const Segment& segment) const {
    if (ContainsPoint(segment.GetStart()) || ContainsPoint(segment.GetEnd())) {
        return true;
    }
    Vector diff1 = segment.GetStart() - centre_;
    Vector diff2 = segment.GetEnd() - centre_;
    Vector v = (diff1 + diff2) / 2;
    return ContainsPoint(Point(v.GetX(), v.GetY()));
}

Circle* Circle::Clone() const {
    return new Circle(*this);
}

int64_t Circle::GetRadius() const {
    return radius_;
}

Point Circle::GetCenter() const {
    return centre_;
}
}  // namespace geometry
