use raytracer::vector::Vector;
use raytracer::color::Color;
use raytracer::surface::Surface;

use std::num::Float;

pub struct Checkerboard;

impl Surface for Checkerboard {
	fn roughness(&self) -> uint {
		150u
	}

	fn diffuse(&self, v:Vector) -> Color {
		if (v.x.floor() + v.z.floor()) % 2.0 != 0.0 {
			Color {r:1.0, g:1.0, b:1.0}
		} else {
			Color {r:0.0, g:0.0, b:0.0}
		}
	}

	fn specular(&self, _:Vector) -> Color {
		Color {r:1.0, g:1.0, b:1.0}
	}

	fn reflect(&self, v:Vector) -> f64 {
		if (v.x.floor() + v.z.floor()) % 2.0 != 0.0 {
			1.0
		} else {
			0.7
		}
	}
}