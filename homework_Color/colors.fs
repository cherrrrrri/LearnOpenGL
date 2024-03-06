#version 330 core
out vec4 FragColor;

uniform vec3 objColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos; 

in vec3 Normal;
in vec3 FragPos;

void main()
{
    // 环境光照
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    // 漫反射光照
    vec3 norm = normalize(Normal); // 标准化
    vec3 lightDir = normalize(lightPos -  FragPos); // 光照方向的反方向：光照位置指向光源方向，此时点乘结果才会为正
    float diff = max(dot(norm,lightDir), 0.0); // 这里的diff不能为负数，要在0-1之间，要不然会影响其他光照的表现
    vec3 diffuse = diff * lightColor;

    // 镜面光照
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm); // 参数为入射方向和法向量
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64);
    vec3 specular = specularStrength * spec * lightColor;  
    
    vec3 result = (ambient + diffuse + specular) * objColor;
    FragColor = vec4(result, 1.0); 
}