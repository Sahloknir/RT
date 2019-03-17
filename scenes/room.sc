camera {
	pos(0,0,-5)
	rotation(0,0,0)
}

object {
	type(cylinder)
	pos(-25, 0, 30)
	rotation(90, 0, 0)
	radius(5)
	color(125, 137, 94)
	sinus
}

object {
	type(cylinder)
	pos(25, 0, 30)
	rotation(90, 0, 0)
	radius(5)
	color(125, 137, 94)
	sinus
}

object {
	type(cylinder)
	pos(-25, 0, 80)
	rotation(90, 0, 0)
	radius(5)
	color(125, 137, 94)
	sinus
}

object {
	type(cylinder)
	pos(25, 0, 80)
	rotation(90, 0, 0)
	radius(5)
	color(125, 137, 94)
	sinus
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
	pos(0, -15, 55)
	radius(8)
	color(125, 137, 228)
	mirror(80)
}

object {
	type(plane)
	pos(0, 25, 0)
	rotation(90, 0, 0)
	color(254,195, 248)
	mirror(100)
}

object{
	type(plane)
	pos(0, -25, 0)
	rotation(90, 0, 0)
	color(125, 195, 218)
	checkered
	mirror(100)
}

object{
	type(plane)
	pos(0, 0, 100)
	rotation(0, 0, 0)
	color(189, 215, 168)
	mirror(100)
}

object{
	type(plane)
	pos(-40, 0, 0)
	rotation(0, 90, 0)
	color(189, 215, 168)
	mirror(100)
}

object{
	type(plane)
	pos(40, 0, 0)
	rotation(0, 90, 0)
	color(189, 215, 168)
	mirror(100)
}

object{
	type(plane)
	pos(0, 0, -20)
	rotation(0, 0, 0)
	color(189, 215, 168)
	mirror(100)
}

light{
	pos(-10,15,55)
}

light{
	pos(10,15,55)
}
