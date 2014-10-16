package main

import (
	"Types"
	"fmt"
	"time"
)

func main() {

	camera := types.CreateCamera(types.Vector{X: 3.0, Y: 2.0, Z: 4.0},
		types.Vector{X: -1.0, Y: 0.5, Z: 0.0})

	objects := []types.SceneObject{
		types.Sphere{
			Position: types.Vector{X: 0.0, Y: 1.0, Z: 0.0}, Radius: 1.0, Surface: types.Shiny{}},
		types.Sphere{
			Position: types.Vector{X: -1.0, Y: 0.5, Z: 1.5}, Radius: 0.5, Surface: types.Shiny{}},
		types.Plane{
			PlaneNormal: types.Vector{X: 0.0, Y: 1.0, Z: 0.0},
			Offset:      0.0, Surface: types.Checkerboard{}}}

	lights := []types.Light{
		types.Light{
			Position: types.Vector{X: -2.0, Y: 2.5, Z: 0.0}, Color: types.Color{R: 0.49, G: 0.07, B: 0.07}},
		types.Light{
			Position: types.Vector{X: 1.5, Y: 2.5, Z: 1.5}, Color: types.Color{R: 0.07, G: 0.07, B: 0.49}},
		types.Light{
			Position: types.Vector{X: 1.5, Y: 2.5, Z: -1.5}, Color: types.Color{R: 0.07, G: 0.49, B: 0.07}},
		types.Light{
			Position: types.Vector{X: 0.0, Y: 3.5, Z: 0.0}, Color: types.Color{R: 0.21, G: 0.21, B: 0.35}},
	}
	scene := types.Scene{Camera: camera, Objects: objects, Lights: lights}

	start := time.Now()
	result := scene.Render(1920, 1080)
	end := time.Now()
	duration := end.Sub(start)
	fmt.Println(duration)
	types.Save(1920, 1080, result)
}
