use raytracer::color::Color;
use raytracer::vector::Vector;
use raytracer::surface::Surface;

pub struct Shiny;

impl Surface for Shiny {
	fn roughness(&self) -> uint {
		50u
	}

	fn diffuse(&self, _:Vector) -> Color {
		Color {r:1.0, g:1.0, b:1.0}
	}

	fn specular(&self, _:Vector) -> Color {
		Color {r:0.5, g:0.5, b:0.5}
	}

	fn reflect(&self, _:Vector) -> f64 {
		0.3
	}
}