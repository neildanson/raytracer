use raytracer::vector::Vector;

pub struct Camera {
	pub position : Vector,
	pub forward : Vector,
	pub up : Vector,
	pub right : Vector
}

pub fn create_camera(position:Vector, look_at:Vector) -> Camera {
	let forward = look_at.subtract(position).normalize();
	let down = Vector{x: 0.0, y: -1.0, z: 0.0};
	let right = forward.cross(down).normalize().scale(1.5);
	let up = forward.cross(right).normalize().scale(1.5);
	Camera{position: position, forward: forward, right: right, up: up}
}