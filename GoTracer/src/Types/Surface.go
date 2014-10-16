package types

import "math"

type Surface interface {
	Roughness() float64
	Diffuse(Vector) Color
	Specular(Vector) Color
	Reflect(Vector) float64
}

type Shiny struct {
}

func (s Shiny) Roughness() float64 {
	return 50.0
}

func (s Shiny) Diffuse(v Vector) Color {
	return Color{R: 1.0, G: 1.0, B: 1.0}
}

func (s Shiny) Specular(v Vector) Color {
	return Color{R: 0.5, G: 0.5, B: 0.5}
}

func (s Shiny) Reflect(v Vector) float64 {
	return 0.3
}

type Checkerboard struct {
}

func (s Checkerboard) Roughness() float64 {
	return 150.0
}

func (s Checkerboard) Diffuse(v Vector) Color {
	if math.Mod(math.Floor(v.X)+math.Floor(v.Z), 2.0) != 0.0 {
		return Color{R: 1.0, G: 1.0, B: 1.0}
	} else {
		return Color{R: 0.0, G: 0.0, B: 0.0}
	}
}

func (s Checkerboard) Specular(v Vector) Color {
	return Color{R: 1.0, G: 1.0, B: 1.0}
}

func (s Checkerboard) Reflect(v Vector) float64 {
	if math.Mod(math.Floor(v.X)+math.Floor(v.Z), 2.0) != 0 {
		return 1.0
	} else {
		return 0.7
	}
}
