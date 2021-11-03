#version 400
in vec3 vp;
out vec3 pos;
out vec3 pos2;
uniform vec2 position_offset;

void main () {
  
	// Change this so that you don't just set `gl_Position` to `vp`, but
	// also add an offset from a `uniform` variable:
	gl_Position = vec4(vp.x + position_offset.x, vp.y + position_offset.y, vp.z, 1.0);
	// pos = vec3(vp.x + position_offset.x, vp.y + position_offset.y, vp.z);
	 pos2 = vp;
};
  
