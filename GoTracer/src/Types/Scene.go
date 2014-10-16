package types

import (
	"image/color"
	"math"
)

type Scene struct {
	Objects []SceneObject
	Lights  []Light
	Camera  Camera
}

func (scene Scene) intersection(ray Ray) *Intersection {
	var intersection *Intersection = nil
	for index := range scene.Objects {
		object := scene.Objects[index]
		isect := object.Intersects(ray)
		if isect != nil {
			if intersection == nil {
				intersection = isect
			} else if isect.Distance < intersection.Distance {
				intersection = isect
			}
		}
	}
	return intersection
}

func (scene Scene) testRay(ray Ray) float64 {
	intersection := scene.intersection(ray)
	if intersection != nil {
		return intersection.Distance
	} else {
		return 0
	}
}

func (scene Scene) traceRay(ray Ray, depth int) Color {
	black := Color{R: 0.0, G: 0.0, B: 0.0}
	isect := scene.intersection(ray)
	if isect == nil {
		return black
	}
	return scene.shade(*isect, depth)
}

func (scene Scene) shade(intersection Intersection, depth int) Color {
	pos := intersection.Ray.Direction.Scale(intersection.Distance).Add(intersection.Ray.Position)
	normal := intersection.Object.Normal(pos)
	dot := normal.Dot(intersection.Ray.Direction)
	reflectDir := intersection.Ray.Direction.Subtract(normal.Scale(2 * dot))
	natural := scene.getNaturalColor(intersection.Object, pos, normal, reflectDir)
	if depth < 5 {
		reflectPos := reflectDir.Scale(0.001).Add(pos)
		reflectColor := scene.getReflectionColor(intersection.Object, reflectPos, reflectDir, depth)
		return natural.Add(reflectColor)
	}
	return Color{R: 0.5, G: 0.5, B: 0.5}.Add(natural)
}

func (scene Scene) getNaturalColor(object SceneObject, position Vector, normal Vector, rayDirection Vector) Color {
	var result Color
	black := Color{R: 0.0, G: 0.0, B: 0.0}
	for index := range scene.Lights {
		light := scene.Lights[index]
		lightDistance := light.Position.Subtract(position)
		livec := lightDistance.Normalize()
		ray := Ray{Position: position, Direction: livec}
		isect := scene.testRay(ray)
		isInShadow := (isect > lightDistance.Length() || isect == 0.0)
		if isInShadow {
			illum := livec.Dot(normal)

			lcolor := black
			if illum > 0.0 {
				lcolor = light.Color.Scale(illum)
			}
			normalizedRayDirection := rayDirection.Normalize()
			specular := livec.Dot(normalizedRayDirection)
			scolor := black
			if specular > 0.0 {
				scolor = light.Color.Scale(math.Pow(specular, object.GetSurface().Roughness()))
			}

			diffuseResult := object.GetSurface().Diffuse(position).Multiply(lcolor)
			specularResult := object.GetSurface().Specular(position).Multiply(scolor)

			result = result.Add(diffuseResult).Add(specularResult)
		}
	}
	return result
}

func (scene Scene) getReflectionColor(object SceneObject, pos Vector, rayDirection Vector, depth int) Color {
	ray := Ray{Position: pos, Direction: rayDirection}
	return scene.traceRay(ray, depth+1).Scale(object.GetSurface().Reflect(pos))
}

func recenter_x(x int, halfWidth float64, invWidth float64) float64 {
	dx := float64(x)
	return (dx - halfWidth) * invWidth
}

func recenter_y(y int, halfHeight float64, invHeight float64) float64 {
	dy := float64(y)
	return -(dy - halfHeight) * invHeight
}

func getPoint(x int, y int, halfWidth float64, halfHeight float64, invWidth float64, invHeight float64, camera Camera) Vector {
	right := camera.Right.Scale(recenter_x(x, halfWidth, invWidth))
	up := camera.Up.Scale(recenter_y(y, halfHeight, invHeight))
	return right.Add(up).Add(camera.Forward).Normalize()
}

func (scene Scene) Render(width int, height int) []color.Color {
	fWidth := float64(width)
	fHeight := float64(height)
	inverseAspectRatio := fHeight / fWidth
	scaleWidth := fWidth * inverseAspectRatio
	halfWidth := scaleWidth / 2.0
	halfHeight := fHeight / 2.0
	invWidth := 1.0 / (scaleWidth * 2.0)
	invHeight := 1.0 / (fHeight * 2.0)

	result := make([]color.Color, width*height)
	basey := 0
	for y := 0; y < height; y++ {
		basey = y * width
		for x := 0; x < width; x++ {
			rayDir := getPoint(x, y, halfWidth, halfHeight, invWidth, invHeight, scene.Camera)
			ray := Ray{Position: scene.Camera.Position, Direction: rayDir}
			result[basey+x] = scene.traceRay(ray, 0).ToColor()
		}
	}
	return result
}
