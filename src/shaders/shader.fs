#version 330 core
out vec4 FragColor;
in vec2 TexCoord;
uniform vec3 ourColor;
uniform sampler2D ourTexture;

void main(){

    vec4 debugColor = vec4(1.0f, 0.0f, 0.698f, 0.89f);
    vec4 tex = texture(ourTexture, TexCoord);

    if (tex.x != 0 || tex.y != 0 || tex.z != 0 ){
        FragColor = texture(ourTexture, TexCoord);
        //FragColor = texture(ourTexture, TexCoord)*vec4(ourColor, 1.0f);
        return;
    }
    FragColor = vec4(ourColor, 1.0f);
    
}