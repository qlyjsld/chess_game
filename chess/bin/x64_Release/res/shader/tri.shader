#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texcroods;

out VS_OUT{
	vec2 texcrood;
} vs_out;

uniform vec2 offset;

void main()
{
	gl_Position = vec4(position.x + offset.x, position.y + offset.y, position.z, 1.0);
	vs_out.texcrood = texcroods;
};

#shader geometry
#version 330 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in VS_OUT{
	vec2 texcrood;
} gs_in[];

out vec2 texcrood;

void main()
{
	gl_Position = gl_in[0].gl_Position;
	texcrood = gs_in[0].texcrood;
	EmitVertex();
	gl_Position = gl_in[1].gl_Position;
	texcrood = gs_in[1].texcrood;
	EmitVertex();
	gl_Position = gl_in[2].gl_Position;
	texcrood = gs_in[2].texcrood;
	EmitVertex();
	EndPrimitive();
};

#shader fragment
#version 330 core

out vec4 fragcolor;
in vec2 texcrood;

uniform sampler2D texture1;

void main()
{
	vec4 texColor = texture(texture1, texcrood);
	if (texColor.a < 0.1)
		discard;
	fragcolor = texColor;
};
