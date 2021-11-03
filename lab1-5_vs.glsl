#version 400
in vec3 vp;
out vec3 zvalue;

void main () {
  gl_Position = vec4 (vec3(vp), 1.0);
  zvalue = vec3(vp);
};
  