camera {
	pos(-30,3,14)
	rotation(8,85,0)
}

object {
	type(sphere)
	pos(-30,-8,20)
	radius(8)
	color(250,85,64)
	shiny
}

object {
	type(sphere)
	pos(35,-8,20)
	radius(8)
	color(81,241,72)
	shiny
}

object {
	type(cylinder)
	pos(0,10,28)
	radius(6)
	rotation(90,-45, 0)
	color(239,128,183)
	shiny
}

object {
	type(cone)
	pos(5,0,30)
	angle(10)
	rotation(90,45, 0)
	color(249,224,56)
	shiny
}

object {
	type(plane)
	pos(0,0,100)
	rotation(0, 0, 0);
	color(99,102,246)
}

object {
	type(plane)
	pos(0,-15,0)
	rotation(90, 0, 0)
	color(195,195,195)
}

light {
	pos(-20,0,0)
}

light {
	pos(20,0,0)
}
