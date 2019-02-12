camera {
	pos(0,0,0)
	rotation(0,0,0)
}

object {
	type(sphere)
	pos(-5,-5,30)
	radius(10)
	color(255,0,0)
	shiny
}

object {
	type(cylinder)
	pos(0,10,32)
	radius(6)
	rotation(90,-45)
	color(0,255,0)
	shiny
}

object {
	type(cone)
	pos(5,0,30)
	angle(20)
	rotation(90,45)
	color(255,255,0)
	shiny
}

object {
	type(plane)
	pos(0,0,80)
	vector(-1,0,4)
	color(0,0,255)
}

object {
	type(plane)
	pos(0,-15,0)
	vector(0,1,0)
	color(195,195,195)
}

light {
	pos(90,0,-50)
}
