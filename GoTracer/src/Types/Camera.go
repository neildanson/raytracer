package types

type Camera struct {
	Position Vector
	Forward  Vector
	Up       Vector
	Right    Vector
}

func CreateCamera(position Vector, lookAt Vector) Camera {
	forward := lookAt.Subtract(position).Normalize()
	down := Vector{X: 0.0, Y: -1.0, Z: 0.0}
	right := forward.Cross(down).Normalize().Scale(1.5)
	up := forward.Cross(right).Normalize().Scale(1.5)
	return Camera{Position: position, Forward: forward, Right: right, Up: up}
}
