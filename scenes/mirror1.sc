camera {
	pos(0,0,-5)
	rotation(0,0,0)
}

object {
	type(sphere)
	pos(0, 15, 55)
	radius(8)
	color(125, 137, 228)
}

object {
	type(sphere)
	pos(15, 0, 55)
	radius(8)
	color(125, 228, 137)
}

object {
	type(sphere)
	pos(-15, 0, 55)
	radius(8)
	color(228, 137, 125)
}

object {
	type(plane)
	pos(0, 25, 0)
	rotation(90, 0, 0)
	color(255, 255, 255)
	mirror(100)
}

object{
	type(plane)
	pos(0, -25, 0)
	rotation(90, 0, 0)
	color(255, 255, 255)
	checkered
	mirror(100)
}

object{
	type(plane)
	pos(0, 0, 100)
	rotation(0, 0, 0)
	color(255, 255, 255)
	mirror(100)
}

object{
	type(plane)
	pos(-40, 0, 0)
	rotation(0, 90, 0)
	color(255, 255, 255)
	mirror(100)
}

object{
	type(plane)
	pos(40, 0, 0)
	rotation(0, 90, 0)
	color(255, 255, 255)
	mirror(100)
}

object{
	type(plane)
	pos(0, 0, -20)
	rotation(0, 0, 0)
	color(255, 255, 255)
	mirror(100)
}

light{
	pos(0,0,-5)
}
light{
	pos(0,0,90)
}
