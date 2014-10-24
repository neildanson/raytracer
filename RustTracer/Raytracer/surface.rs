use raytracer::vector::Vector;
use raytracer::color::Color;

pub trait Surface {
	fn roughness(&self) -> uint;
	fn diffuse(&self,Vector) -> Color;
	fn specular(&self,Vector) -> Color;
	fn reflect(&self,Vector) -> f64;
}