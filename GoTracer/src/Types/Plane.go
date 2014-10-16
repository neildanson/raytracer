package types

type Plane struct {
	PlaneNormal Vector
	Offset      float64
	Surface     Surface
}

func (p Plane) Intersects(ray Ray) *Intersection {
	denom := p.PlaneNormal.Dot(ray.Direction)
	if denom > 0.0 {
		return nil
	}

	intersection := Intersection{Ray: ray, Distance: (p.PlaneNormal.Dot(ray.Position) + p.Offset) / -denom, Object: p}
	return &intersection
}

func (p Plane) Normal(pos Vector) Vector {
	return p.PlaneNormal
}

func (p Plane) GetSurface() Surface {
	return p.Surface
}
