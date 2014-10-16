package types

type SceneObject interface {
	Intersects(Ray) *Intersection
	Normal(Vector) Vector
	GetSurface() Surface
}
