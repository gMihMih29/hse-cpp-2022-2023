#include "segment.h"

#include <algorithm>

namespace geometry {
Segment::Segment() : start_(Point()), end_(Point()) {
}

Segment::Segment(Point start, Point end) : start_(start), end_(end) {
}

Point Segment::GetStart() const {
    return start_;
}

Point Segment::GetEnd() const {
    return end_;
}

Segment& Segment::Move(const Vector& vector) {
    start_.Move(vector);
    end_.Move(vector);
    return *this;
}

bool Segment::ContainsPoint(const Point& point) const {
    return point.CrossesSegment(*this);
}

bool Segment::CrossesSegment(const Segment& segment) const {
    if (segment.ContainsPoint(GetStart()) || segment.ContainsPoint(GetEnd()) || ContainsPoint(segment.GetStart()) ||
        ContainsPoint(segment.GetEnd())) {
        return true;
    }
    Vector guiding_vector1 = GetEnd() - GetStart();
    Vector guiding_vector2 = segment.GetEnd() - segment.GetStart();
    Vector v1 = segment.GetEnd() - GetStart();
    Vector v2 = segment.GetStart() - GetStart();
    Vector v3 = segment.GetStart() - GetEnd();
    bool is_on_different_sides1 = (VectorMult(v1, guiding_vector1) > 0 && VectorMult(v2, guiding_vector1) < 0) ||
                                  (VectorMult(v1, guiding_vector1) < 0 && VectorMult(v2, guiding_vector1) > 0);
    bool is_on_different_sides2 = (VectorMult(-v2, guiding_vector2) > 0 && VectorMult(-v3, guiding_vector2) < 0) ||
                                  (VectorMult(-v2, guiding_vector2) < 0 && VectorMult(-v3, guiding_vector2) > 0);
    return is_on_different_sides1 && is_on_different_sides2;
}

double Segment::Distance(Point p) const {
    if (ContainsPoint(p)) {
        return 0;
    }
    Vector diff1 = GetStart() - p;
    Vector diff2 = GetEnd() - p;
    if (Degenerate()) {
        return Length(diff1);
    }
    Vector guiding = GetEnd() - GetStart();
    double perpend = VectorMult(diff1, guiding) / Length(guiding);
    return std::min(Length(diff1), std::min(Length(diff2), perpend));
}

bool Segment::Degenerate() const {
    return GetStart() == GetEnd();
}

Segment* Segment::Clone() const {
    return new Segment(*this);
}
}  // namespace geometry
