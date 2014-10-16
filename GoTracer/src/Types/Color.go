package types

import "image/color"

type Color struct {
	R, G, B float64
}

func (c Color) Add(c1 Color) Color {
	return Color{R: c.R + c1.R, G: c.G + c1.G, B: c.B + c1.B}
}

func (c Color) Subtract(c1 Color) Color {
	return Color{R: c.R - c1.R, G: c.G - c1.G, B: c.B - c1.B}
}

func (c Color) Scale(s float64) Color {
	return Color{R: c.R * s, G: c.G * s, B: c.B * s}
}

func (c Color) Multiply(c1 Color) Color {
	return Color{R: c.R * c1.R, G: c.G * c1.G, B: c.B * c1.B}
}

func legalize(i float64) uint8 {
	if i > 1.0 {
		return 255
	} else {
		return uint8(i * 255.0)
	}
}

func (c Color) ToColor() color.Color {
	r, g, b := legalize(c.R), legalize(c.G), legalize(c.B)
	return color.RGBA{r, g, b, 255}
}
