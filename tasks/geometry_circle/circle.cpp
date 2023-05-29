#include "circle.h"

#include "point.h"
#include "segment.h"
#include "line.h"

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
    return static_cast<double>(radius_) >= Length(point - centre_);
}

bool Circle::CrossesSegment(const Segment& segment) const {
    if (ContainsPoint(segment.GetStart()) || ContainsPoint(segment.GetEnd())) {
        return true;
    }
    Line l(segment.GetStart(), segment.GetEnd());
    return static_cast<double>(radius_) >= l.Distance(centre_);
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
