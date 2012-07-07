uniform sampler2D diffuse;
uniform sampler2D heightmap;
uniform sampler2D heightmap_screen;
uniform vec2 screen_ratio;
uniform float height_factor;
uniform float z_pos;

void main()
{			
	gl_FragColor =  gl_Color * texture2D(heightmap, gl_TexCoord[0].xy);
	gl_FragColor[3] = 1.0;
	
	if( texture2D(heightmap, gl_TexCoord[0].xy)[3] > 0.2)
		gl_FragColor[2] /= texture2D(heightmap, gl_TexCoord[0].xy)[3];
	
	gl_FragColor[2] *=  height_factor/500.0;
	
	gl_FragColor[2] += z_pos/500.0;
	
	gl_FragColor[0] = texture2D(diffuse, gl_TexCoord[0].xy)[3];
	
	vec4 screen_color = texture2D(heightmap_screen, gl_FragCoord.xy*screen_ratio);
	
	if(gl_FragColor[2] <= screen_color[2])
	{
		gl_FragColor[2] = screen_color[2];
		
		gl_FragColor[0] = screen_color[0]/* + gl_FragColor[0] * (1.0 - screen_color[0])*/;
	}
	else
	{
		gl_FragColor[0] = gl_FragColor[0]/* + screen_color[0] * (1.0 - gl_FragColor[0])*/;
	}
}
