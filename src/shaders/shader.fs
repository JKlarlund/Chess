#version 330 core
out vec4 FragColor;
in vec2 TexCoord;
uniform vec3 ourColor;
uniform sampler2D ourTexture;
uniform bool isTextureBound;

void main(){

    vec4 debugColor = vec4(1.0f, 0.0f, 0.698f, 0.89f);
    vec4 tex = texture(ourTexture, TexCoord);

    if (tex.a != 1.0f){

        //This never happens for some reason.
        discard;
        //FragColor = vec4(0.2f, 0.2f, 0.2f, 0.2f);
        return;
    }

    if (isTextureBound){
        FragColor = tex;
    }
    else{
        FragColor = vec4(ourColor, 1.0f);
    }
    
}
