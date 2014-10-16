package types

import (
	"image"
	"image/color"
	"image/png"
	"os"
)

func Save(width int, height int, data []color.Color) {
	m := image.NewRGBA(image.Rect(0, 0, width, height))
	for i := range data {
		x := i % width
		y := i / width
		m.Set(x, y, data[i])
	}

	toimg, _ := os.Create("Go.png")
	defer toimg.Close()
	png.Encode(toimg, m)
}
