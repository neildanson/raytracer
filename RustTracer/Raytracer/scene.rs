use raytracer::camera::Camera;
use raytracer::scene_object::SceneObject;
use raytracer::light::Light;
use raytracer::color::Color;
use raytracer::vector::Vector;
use raytracer::ray::Ray;
use raytracer::intersection::Intersection;
use std::num::pow;

pub struct Scene<'a> {
	pub camera : Camera,
	pub objects : Vec<&'a SceneObject<'a> +'a> ,
	pub lights : Vec<Light>
}

impl<'a> Scene<'a> {
	fn intersection(&'a self, ray : Ray) -> Option<(Intersection, &SceneObject<'a>)> {
		self.objects.iter().fold(None, |intersection: Option<(Intersection, _)>, object| {
			let isect = object.intersects(ray);
			match (isect, intersection) {
				(Some((i1,_)), Some((i2,_))) => if i1.distance < i2.distance { isect } else { intersection }, 
				(Some(_), None) => isect,
				(None, _) => intersection
			}})
	}

	fn test_ray(&'a self, ray:Ray) -> f64 {
		let intersection = self.intersection(ray);
		match intersection {
			Some((isect,_)) => isect.distance,
			None => 0.0
		}
	}

	fn trace_ray(&'a self, ray:Ray, depth:int) -> Color { 
		let black = Color{ r: 0.0, g: 0.0, b: 0.0 };
		let isect = self.intersection(ray);
		match isect {
			Some(isect) => self.shade(isect, depth),
			None => black
		}
	}

	fn shade(&'a self,intersection : (Intersection, &'a SceneObject<'a>), depth : int) -> Color { 
		let (intersection, object) = intersection;
		let pos = intersection.ray.direction.scale(intersection.distance).add(intersection.ray.position);
		let normal = object.normal(pos);
		let dot = normal.dot(intersection.ray.direction);	
		let reflect_dir = intersection.ray.direction.subtract(normal.scale(2.0 * dot));
		let natural = self.get_natural_color(object, pos, normal, reflect_dir);
		if depth < 5 { 
			let reflect_pos = reflect_dir.scale(0.001).add(pos);
			let reflect_color = self.get_reflection_color(object, reflect_pos, reflect_dir, depth);
			reflect_color.add(natural)
		} else { 
			Color { r: 0.5, g: 0.5, b: 0.5}.add(natural)
		}
	}

	fn get_natural_color(&'a self, object : &'a SceneObject<'a>, position : Vector, normal : Vector, ray_direction : Vector ) -> Color {
		let black = Color{r: 0.0, g: 0.0, b: 0.0};
		self.lights.iter().fold(black, |result, light|  {
			let light_distance = light.position.subtract(position);
			let livec = light_distance.normalize();
			let ray = Ray{position: position, direction: livec};
			let isect = self.test_ray(ray);
			let is_in_shadow = isect > light_distance.length() || isect == 0.0;
			if is_in_shadow {
				let illum = livec.dot(normal);
				let lcolor = 
					if illum > 0.0 {
						light.color.scale(illum)
					} else { black };
				let normalized_ray_direction = ray_direction.normalize();
				let specular = livec.dot(normalized_ray_direction);
				let scolor = 
					if specular > 0.0 {
						light.color.scale(pow(specular, object.get_surface().roughness()))
					} else { black };

				let diffuse_result = object.get_surface().diffuse(position).multiply(lcolor);
				let specular_result = object.get_surface().specular(position).multiply(scolor);

				result.add(diffuse_result).add(specular_result)
			} else {
				result
			}
		})
	}

	fn get_reflection_color(&'a self, object : &'a SceneObject<'a>, pos:Vector, ray_direction : Vector, depth :int ) -> Color {
		let ray = Ray { position : pos, direction : ray_direction };
		(self.trace_ray(ray, depth + 1)).scale(object.get_surface().reflect(pos))
	}

	fn recenter_x(&self, x :uint, half_width :f64, inv_width :f64) -> f64 {
		let dx = x as f64;
		(dx - half_width) * inv_width
	}

	fn recenter_y(&self, y : uint, half_height : f64, inv_height : f64) -> f64 {
		let dy = y as f64;
		(dy - half_height) * inv_height //note removed negation
	}

	fn get_point(&self, x : uint, y : uint, half_width : f64, half_height : f64, inv_width : f64, inv_height : f64, camera : Camera) -> Vector {
		let right = camera.right.scale(self.recenter_x(x, half_width, inv_width));
		let up = camera.up.scale(self.recenter_y(y, half_height, inv_height));
		right.add(up).add(camera.forward).normalize()
	}

	pub fn render(&'a self, width : uint, height : uint) -> Vec<int> {
		let f_width = width as f64;
		let f_height = height as f64;
		let inverse_aspect_ratio = f_height / f_width;
		let scale_width = f_width * inverse_aspect_ratio;
		let half_width = scale_width / 2.0;
		let half_height = f_height / 2.0;
	    let inv_width = 1.0 / (scale_width * 2.0);
		let inv_height = 1.0 / (f_height * 2.0);
		let array_size = width * height;
		let mut result : Vec<int> = Vec::with_capacity(array_size);
		for y in range(0,height) {
			for x in range(0,width) {
				let ray_dir = self.get_point(x, y, half_width, half_height, inv_width, inv_height, self.camera);
				let ray = Ray{position: self.camera.position, direction: ray_dir};
				let col = self.trace_ray(ray, 0).to_color();
				result.push(col);
			}
		}
		result
	}
}