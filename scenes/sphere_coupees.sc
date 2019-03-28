camera {
	pos(50,0,0)
	rotation(0,-45,0)
	ambient(60, 20, 20)
}

object {
	type(sphere)
	pos(0, 45,100)
	radius(35)
	color(110,180,104)
	shiny
}

object {
	type(sphere)
	pos(0,0,50)
	radius(25)
	color(110,80,164)
	plim_x(-25, 15)
	shiny
}

light {
	pos(165,5,0)
}
light {
	pos(90,0,-100)
}
