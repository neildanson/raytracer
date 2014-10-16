package types

import "math"

type Sphere struct {
	Position Vector
	Radius   float64
	Surface  Surface
}

func (s Sphere) Intersects(ray Ray) *Intersection {
	eo := s.Position.Subtract(ray.Position)
	v := eo.Dot(ray.Direction)
	if v < 0.0 {
		return nil
	}
	dist := math.Pow(s.Radius, 2.0) - (eo.Dot(eo) - math.Pow(v, 2.0))
	if dist < 0.0 {
		return nil
	}
	dist = v - math.Sqrt(dist)
	intersection := Intersection{Ray: ray, Distance: dist, Object: s}
	return &intersection
}

func (s Sphere) Normal(position Vector) Vector {
	return position.Subtract(s.Position).Normalize()
}

func (s Sphere) GetSurface() Surface {
	return s.Surface
}
