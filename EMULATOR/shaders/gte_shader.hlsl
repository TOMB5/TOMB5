struct VS_INPUT {
    float2 a_position : POSITION;
    float2 a_texcoord : TEXCOORD0;
    float4 a_color    : COLOR0;
};

struct VS_OUTPUT {
    float4 v_position : POSITION;
    float2 v_texcoord : TEXCOORD0;
    float4 v_color    : TEXCOORD1;
};

#ifdef VERTEX
    float4x4 Projection : register(c0);
    
    VS_OUTPUT main(VS_INPUT In) {
        VS_OUTPUT Out;
        Out.v_texcoord = In.a_texcoord;
        Out.v_color    = In.a_color;
        Out.v_position = mul(Projection, float4(In.a_position, 0.0, 1.0));
        return Out;
    }
#else
    sampler2D s_texture : register(s0);
    float4    PageClut  : register(c4);

    float4 main(VS_OUTPUT In) : COLOR0 {
        float2 uv = (In.v_texcoord * float2(0.25, 1.0) + PageClut.xy) * float2(1.0 / 1024.0, 1.0 / 512.0);
        float2 comp = tex2D(s_texture, uv).ra;
        int index = int(frac(In.v_texcoord.x / 4.0 + (0.5 / 255.0)) * 4.0);

        float v = comp[index / 2] * (255.0 / 16.0);
        float f = floor(v);

        float2 c = float2( (v - f) * 16.0, f );

        float2 clut_pos = PageClut.zw;
        clut_pos.x += lerp(c[0], c[1], frac(float(index) / 2.0) * 2.0) / 1024.0;
        float2 clut_color = tex2D(s_texture, clut_pos).ra * 255.0;

        float color_16 = clut_color.y * 256.0 + clut_color.x;
        float4 color = frac(floor(color_16 / float4(1.0, 32.0, 1024.0, 32768.0)) / 32.0);

        color = color * In.v_color;
        color.xyz *= 2.0;

        clip(color.a - 0.001);
        
        return color;
    }
#endif
