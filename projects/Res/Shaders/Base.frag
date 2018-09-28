precision mediump float;

varying vec2 v_texCoord;
//uniform sampler2D s_baseMap;
//uniform vec4 u_color;

void main(void)
{
	//vec2 texCoord = v_texCoord;
	//vec4 color = texture2D(s_baseMap, v_texCoord).bgra * u_color;
	vec4 color;
	color.r = 1.0;
	color.g = 0.0;
	color.b = 0.0;
	color.a = 1.0;
	gl_FragColor = color;
}
