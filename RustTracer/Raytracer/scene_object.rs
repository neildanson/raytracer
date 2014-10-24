use raytracer::ray::Ray;
use raytracer::intersection::Intersection;
use raytracer::vector::Vector;
use raytracer::surface::Surface;

pub trait SceneObject<'a> {
	fn intersects(&'a self, ray : Ray) -> Option<(Intersection, &SceneObject<'a>)>;
	fn normal(&self, position : Vector) -> Vector;
	fn get_surface(&'a self) -> &'a Surface +'a;
}