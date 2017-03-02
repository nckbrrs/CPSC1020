/*
	Nicholas Barrs
	CPSC 1020-001
	nbarrs
	28 March 2015
	Small Assignment 2 - convert to C++
	tplane.cpp - tiled plane functions
*/

///////////////////////////////////////////////////////////////////////////////
////										tiled plane											////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
// tplane_t constructor
//=============================================================================
tplane_t::tplane_t(FILE *in, model_t *model, int attrmax):plane_t (in, model, 2)
{
	int mask;

	strcpy (obj_type, "tiled_plane");

	// The parser is fairly generic but the address of where
	// to put the data must be updated for each new object
	tplane_parse[0].loc = &xdir;
	tplane_parse[1].loc = &dims;
	tplane_parse[2].loc = &altmat;
	mask = parser (in, tplane_parse, NUM_ATTRS, attrmax);
	assert (mask == 7);

	// Ask material_getbyname() to return a pointer to the alternate material
	altmat = material_getbyname(model, name);

	// Project xdir into the plane and make it a unit vector
	vec_project(normal, xdir, projxdir);
	vec_unit(projxdir, projxdir);

	
	// Build a rotation matrix that rotates the plane normal into the z-axis
	// and the projected xdir into the x-axis
	vec_copy (normal, rot[2]);
	vec_copy (projxdir, rot[0]);

}	
