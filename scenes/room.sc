camera {
	pos(0,0,-5)
	rotation(0,0,0)
}

object {
	type(cylinder)
	pos(-25, 0, 30)
	rotation(90, 0)
	radius(5)
	color(125, 137, 94)
}

object {
	type(cylinder)
	pos(25, 0, 30)
	rotation(90, 0)
	radius(5)
	color(125, 137, 94)
}

object {
	type(cylinder)
	pos(-25, 0, 80)
	rotation(90, 0)
	radius(5)
	color(125, 137, 94)
}

object {
	type(cylinder)
	pos(25, 0, 80)
	rotation(90, 0)
	radius(5)
	color(125, 137, 94)
}

object {
	type(sphere)
	pos(-25, 25, 30)
	radius(8)
	color(125, 137, 94)
}

object {
	type(sphere)
	pos(25, 25, 30)
	radius(8)
	color(125, 137, 94)
}

object {
	type(sphere)
	pos(-25, 25, 80)
	radius(8)
	color(125, 137, 94)
}

object {
	type(sphere)
	pos(25, 25, 80)
	radius(8)
	color(125, 137, 94)
}

object {
	type(sphere)
	pos(-25, -25, 30)
	radius(8)
	color(125, 137, 94)
}

object {
	type(sphere)
	pos(25, -25, 30)
	radius(8)
	color(125, 137, 94)
}

object {
	type(sphere)
	pos(-25, -25, 80)
	radius(8)
	color(125, 137, 94)
}

object {
	type(sphere)
	pos(25, -25, 80)
	radius(8)
	color(125, 137, 94)
}


object {
	type(sphere)
	pos(0, -18, 55)
	radius(8)
	color(125, 137, 228)
}


object {
	type(plane)
	pos(0, 25, 0)
	vector(0, 1, 0)
	color(254,195, 248)
}

object{
	type(plane)
	pos(0, -25, 0)
	vector(0, 1, 0)
	color(125, 195, 218)
	squared
}

object{
	type(plane)
	pos(0, 0, 100)
	vector(0, 0, 1)
	color(189, 215, 168)
}

object{
	type(plane)
	pos(-40, 0, 0)
	vector(1, 0, 0)
	color(189, 215, 168)
}

object{
	type(plane)
	pos(40, 0, 0)
	vector(1, 0, 0)
	color(189, 215, 168)
}

light{
	pos(-10,15,55)
}

light{
	pos(10,15,55)
}
