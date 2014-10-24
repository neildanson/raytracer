use raytracer::scene_object::SceneObject;
use raytracer::vector::Vector;
use raytracer::ray::Ray;
use raytracer::intersection::Intersection;
use raytracer::surface::Surface;
use std::num::pow;

pub struct Sphere<'a> {
    pub position: Vector,
    pub radius : f64,
    pub surface : &'a Surface + 'a
}

impl<'a> SceneObject<'a> for Sphere<'a> {

	fn intersects(&'a self, ray : Ray) -> Option<(Intersection, &SceneObject<'a>)> {
		let eo = self.position.subtract(ray.position);
		let v = eo.dot(ray.direction);
		if v < 0.0 {
			None
		} else {
			let dist = pow(self.radius,2) - (eo.dot(eo) - pow(v, 2));
			if dist < 0.0 {
				None
			} else {
				let dist = v - dist.sqrt();
				let intersection = Intersection { ray: ray, distance:dist};
				Some((intersection, self as &SceneObject<'a>))
			}
		}
	}

	fn normal(&self, position : Vector) -> Vector {
		position.subtract(self.position).normalize()
	}

	fn get_surface(&'a self) -> &'a Surface +'a  {
		self.surface
	}
}