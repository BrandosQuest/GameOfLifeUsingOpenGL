#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec3 ourCoords;

uniform float timeFormInit;
uniform float width;
uniform float hight;

float noiseBrando(){
    int time=int (timeFormInit*1000);
    return float((time%200))/200.0;
}
float sdSegment( in vec2 p, in vec2 a, in vec2 b )
{
    vec2 pa = p-a, ba = b-a;
    float h = clamp( dot(pa,ba)/dot(ba,ba), 0.0, 1.0 );
    return length( pa - ba*h );
}

void main()
{
    vec2 pos= vec2(ourCoords.x, ourCoords.y);//coord system with 2 axis 
    pos.x = pos.x * width/hight;// normalising x coord indiendently of the screen ratio
    float time=timeFormInit*1;

    //float posY=sin(time);
    float posY=0;

    float glow=10;
    
    FragColor= vec4(0,0,0,1);

    float sdf=sdSegment(pos, vec2(-0.5, posY),vec2(+0.5, posY));
    if(sdf<0.1){
        FragColor= vec4(1*glow*sdf,0,0,1);
    }else if(sdf<0.2){
        FragColor= vec4(0,-(1*glow*sdf)+2,0,1);
    }else if(sdf<0.3){
        FragColor= vec4(0,0,(1*glow*sdf)-2,1);
    }else if(sdf<0.4){
        FragColor= vec4(0,(1*glow*sdf)+4,1,1);
    }
    
}

/*
FragColor= vec4(0,0,0,1);
    if(sdSegment(pos, vec2(-0.5, sin(time)),vec2(+0.5, sin(time)))<0.1){
        FragColor= vec4(1,0,0,1);
    }


x^2 + y^2 = r^2

y=sqrt(x^2-r^2);


if(pos.y==sqrt((pos.x*pos.x)-(0.5*0.5))){
        FragColor = vec4(1.0, 1.0, 1.0 , 1.0f);
    }
    
    if((0.5-lenght(pos))<0.1 && (0.5-lenght(pos))>0.0){
        FragColor = vec4(1.0, 1.0, 1.0 , 1.0f);
    }
*/
/*
#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec3 ourCoords;

uniform float timeFormInit;
uniform float width;
uniform float hight;

float lenght(vec2 pos){
    return sqrt((pos.x*pos.x)+(pos.y*pos.y));
}

void main()
{
    vec2 pos= vec2(ourCoords.x, ourCoords.y);//coord system with 2 axis 
    pos.x = pos.x * width/hight;// normalising x coord indiendently of the screen ratio

    float l = lenght(pos);//for every pixel I calculate the distance from the center
    //float greyValue= ((sin(timeFormInit)*l)+1)/2;
    float greyValue= (sin(timeFormInit)+1)/2;
    FragColor = vec4(greyValue, greyValue, greyValue , 1.0f);
    //FragColor = vec4(1.0f, 1.0f, 1.0f , 1.0f){;
    //float distanceFromCircleNormalized=abs(lenght(pos)-0.5)*(1/sqrt(2));
    float acceleratedTime=timeFormInit*1;
    //float acceleratedTime=10*sin(timeFormInit);
    float numOfCircles=4;
    float distanceFromCircleNormalized=sin(lenght(pos)*numOfCircles*2+acceleratedTime)/8;
    //distanceFromCircleNormalized= smoothstep(0.0, 0.1, distanceFromCircleNormalized);
    distanceFromCircleNormalized= abs(distanceFromCircleNormalized);
    float glow=0.02;
    distanceFromCircleNormalized= glow/distanceFromCircleNormalized;
    FragColor = vec4(distanceFromCircleNormalized, distanceFromCircleNormalized, distanceFromCircleNormalized , 1.0f);
    


}
*/