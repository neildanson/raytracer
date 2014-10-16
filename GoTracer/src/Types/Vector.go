package types

import "math"

type Vector struct {
	X, Y, Z float64
}

func (v Vector) Dot(v1 Vector) float64 {
	return (v.X * v1.X) + (v.Y * v1.Y) + (v.Z * v1.Z)
}

func (v Vector) Length() float64 {
	return math.Sqrt(v.Dot(v))
}

func (v Vector) Cross(v1 Vector) Vector {
	return Vector{X: v.Y*v1.Z - v.Z*v1.Y,
		Y: v.Z*v1.X - v.X*v1.Z,
		Z: v.X*v1.Y - v.Y*v1.X}
}

func (v Vector) Add(v1 Vector) Vector {
	return Vector{X: v.X + v1.X, Y: v.Y + v1.Y, Z: v.Z + v1.Z}
}

func (v Vector) Subtract(v1 Vector) Vector {
	return Vector{X: v.X - v1.X, Y: v.Y - v1.Y, Z: v.Z - v1.Z}
}

func (v Vector) Scale(s float64) Vector {
	return Vector{X: v.X * s, Y: v.Y * s, Z: v.Z * s}
}

func (v Vector) Normalize() Vector {
	mag := v.Length()
	if mag == 0.0 {
		return v.Scale(math.Inf(1))
	} else {
		return v.Scale(1.0 / mag)
	}
}
