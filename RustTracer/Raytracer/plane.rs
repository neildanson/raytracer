use raytracer::vector::Vector;
use raytracer::surface::Surface;
use raytracer::scene_object::SceneObject;
use raytracer::ray::Ray;
use raytracer::intersection::Intersection;

pub struct Plane<'a> {
    pub plane_normal: Vector,
    pub offset : f64,
    pub surface : &'a Surface + 'a
}

impl<'a> SceneObject<'a> for Plane<'a> {
	fn intersects(&'a self, ray : Ray) -> Option<(Intersection, &SceneObject<'a>)> {
		let denom = self.plane_normal.dot(ray.direction);
		if denom > 0.0 { None }
 		else {
 			let intersection = Intersection { ray: ray, distance:(self.plane_normal.dot(ray.position) + self.offset) / -denom};
			Some((intersection, self as &SceneObject<'a>))
 		}
 	}

	fn normal(&self, _ : Vector) -> Vector {
		self.plane_normal
	}

	fn get_surface(&'a self) -> &'a Surface +'a  {
		self.surface
	}
}