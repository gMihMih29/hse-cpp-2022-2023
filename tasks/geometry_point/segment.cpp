#include "segment.h"

namespace geometry
{
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
        Vector guiding_vector1 = GetEnd() - GetStart();
        Vector guiding_vector2 = segment.GetEnd() - segment.GetStart();
        if (VectorMult(guiding_vector1, guiding_vector2) == 0) {
            return false;
        }
        return true;
    }

    Segment* Segment::Clone() const {
        return new Segment(*this);
    }
} // namespace geometry
