camera {
	pos(0,0,0)
	rotation(0,0,0)
	ambient(100, 100, 100)
}

object {
	shiny
	type(cylinder)
	pos(0,0,80)
	radius(20)
	rotation(150,10, 0)
	color(23,110,16)
	rlim_z(-20,20);
}

light {
	pos(0,-90,-10)
}
